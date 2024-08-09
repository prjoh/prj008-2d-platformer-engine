#include <filesystem>
#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
#include <fileapi.h>
#endif
#include <chrono>
#include <string_view>

#include <fmt/chrono.h>

#include <Core/Error.h>
#include <Core/Log.h>
#include <Util/StringBuilder.h>


void zv::internal::log(int line, const char* file, const char* func, eLogSeverity severity, std::string_view fmt, FormatArgs args)
{
  LogManager::get().log(line, file, func, severity, fmt, args);
}

void zv::internal::log_flush()
{
  LogManager::get().flush();
}

constexpr uint32_t k_message_size = 1024;
constexpr uint32_t k_line_size = 1024; 
constexpr uint32_t k_time_size = 23;
constexpr uint32_t k_header_size = k_time_size + 16;
constexpr uint32_t k_headed_message_size = k_header_size + k_message_size;

inline zv::FormatColor severity_to_color(zv::eLogSeverity severity)
{
  switch (severity)
  {
  case zv::eLogSeverity::Error:
    return zv::FormatColor::red;
  case zv::eLogSeverity::Warning:
    return zv::FormatColor::yellow;
  case zv::eLogSeverity::Info:
    return zv::FormatColor::light_gray;
  case zv::eLogSeverity::Trace:
    return zv::FormatColor::gray;
  case zv::eLogSeverity::Debug:
    return zv::FormatColor::gray;
  default:
    ZV_ABORT_INTERNAL("Unreachable code!");
  }
}

inline std::string_view severity_to_string(zv::eLogSeverity severity)
{
  switch (severity)
  {
  case zv::eLogSeverity::Error:
    return "ERROR";
  case zv::eLogSeverity::Warning:
    return "WARN";
  case zv::eLogSeverity::Info:
    return "INFO";
  case zv::eLogSeverity::Trace:
    return "TRACE";
  case zv::eLogSeverity::Debug:
    return "DEBUG";
  default:
    ZV_ABORT_INTERNAL("Unreachable code!");
  }
}

template <typename BUILDER>
bool _formatTime(BUILDER& builder)
{
  std::chrono::time_point now = std::chrono::system_clock::now();
  auto now_in_seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
  auto msec = std::chrono::duration_cast<std::chrono::milliseconds>(now - now_in_seconds);
  return builder.append("{}.{:03}", now_in_seconds, msec.count());
}

template <typename BUILDER>
bool _formatHeader(BUILDER& builder, std::string_view time, zv::eLogSeverity severity) {
  return builder.append("{} - {}: ", time, severity_to_string(severity));
}

template <typename BUILDER>
bool _formatLine(BUILDER& builder, int line, const char* file, const char* /*func*/) {
  return builder.append("{}({}):\n", file, line);
}

zv::internal::LogManager::LogManager()
  : base_type(this)
{
  m_log_level_maximum = std::max({ m_log_level_console, m_log_level_stdout_file, m_log_level_visual_studio });

#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
  std::filesystem::path log_path = Application::s_Path + "stdout.log";
  m_file_handle = CreateFileW(log_path.wstring().c_str(), GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_NEW, FILE_ATTRIBUTE_NORMAL, NULL);
  ZV_ASSERT_INTERNAL(m_file_handle, "Failed to open the log file.");
  const unsigned int bom_size = 3;
  const char bom[bom_size] = { static_cast<char>(0xEF), static_cast<char>(0xBB), static_cast<char>(0xBF) };
  BOOL success = ::WriteFile(m_file_handle, bom, bom_size, NULL, NULL);
  ZV_ASSERT_INTERNAL(success, "Failed to write BOM to the log file.");
#endif
}

zv::internal::LogManager::~LogManager()
{
#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
  ::CloseHandle(m_file_handle);
#endif
}

void zv::internal::LogManager::log(s32 line, const char* file, const char* func, eLogSeverity severity, std::string_view fmt, FormatArgs args)
{
  if (m_log_level_maximum < severity) {
      return;
  }

  StringBuilder<k_line_size> line_builder;
  _formatLine(line_builder, line, file, func);

  StringBuilder<k_time_size> time_builder;
  _formatTime(time_builder);

  StringBuilder<k_header_size> header_builder;
  _formatHeader(header_builder, time_builder.string_view(), severity);

  std::string message;
  try
  {
      message =  vformat(fmt, args);
  }
  catch (std::runtime_error e)
  {
      message = zv::format("Invalid Log format: {} : at {}({})", e.what(), file, line);
  }

  message += "\n";

  std::string headed_message = std::string(header_builder.string_view()) + message;

  bool print_line = severity == zv::eLogSeverity::Error || severity == zv::eLogSeverity::Warning;
  log_impl(severity, severity_to_color(severity), headed_message, print_line, line_builder.string_view());
}

void zv::internal::LogManager::flush()
{
#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
  BOOL success = ::FlushFileBuffers(m_file_handle);
  ZV_ASSERT_INTERNAL(success, "Failed to flush the log file.");
#endif
}

void zv::internal::LogManager::log_impl(eLogSeverity severity, FormatColor color, std::string_view message, bool print_line, std::string_view line)
{
  if (is_severity_enabled(severity, m_log_level_console) && m_console_enabled)
  {
    log_console(color, message, print_line, line);
  }

#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
  if (is_severity_enabled(severity, m_log_level_stdout_file))
  {
    LogStdoutFile(m_file_handle, message, print_line, line);
  }

  if (is_severity_enabled(severity, m_log_level_visual_studio) && ::IsDebuggerPresent())
  {
    LogVisualStudio(message, print_line, line);
  }
#endif
}

void zv::internal::LogManager::log_console(FormatColor color, std::string_view message, bool print_line, std::string_view line)
{
  fmt::print(fmt::fg(color), "{}", message);
  if (print_line)
  {
    fmt::print(fmt::fg(color), line);
  }
}

#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
void zv::internal::LogManager::LogStdoutFile(HANDLE file_handle, std::string_view message, bool print_line, std::string_view line)
{
  BOOL success = ::WriteFile(file_handle, message.data(), static_cast<unsigned int>(message.size()), NULL, NULL);
  ZV_ASSERT_INTERNAL(success, "Failed to write to message log file.");
  if (print_line)
  {
    BOOL success = ::WriteFile(file_handle, line.data(), static_cast<unsigned int>(line.size()), NULL, NULL);
    ZV_ASSERT_INTERNAL(success, "Failed to write line to log file.");
  }
}

void zv::internal::LogManager::LogVisualStudio(std::string_view message, bool print_line, std::string_view line)
{
  auto convert_to_utf16 = [](std::string_view& input) {
    int size = ::MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), nullptr, 0);
    if (size == 0)
      ZV_ABORT_INTERNAL("Fatal Error in LogManager: Failed finding utf16 message size.");

    std::vector<wchar_t> buffer(size + 1);
    if (buffer.size() != size + 1)
      ZV_ABORT_INTERNAL("Fatal Error in LogManager: Failed to allocate buffer.");

    int writtenSize = ::MultiByteToWideChar(CP_UTF8, 0, input.data(), static_cast<int>(input.size()), buffer.data(), static_cast<int>(buffer.size()));
    if (size != writtenSize)
      ZV_ABORT_INTERNAL("Fatal Error in LogManager: Failed encoding.");

    return buffer;
  };

  std::vector<wchar_t> utf16message = convert_to_utf16(message);
  OutputDebugStringW(utf16message.data());
  if (print_line)
  {
    OutputDebugStringA(line.data());
  }
}
#endif

bool zv::internal::LogManager::is_severity_enabled(eLogSeverity message_log_level, eLogSeverity max_log_level)
{
  return static_cast<int>(message_log_level) <= static_cast<int>(max_log_level);
}
