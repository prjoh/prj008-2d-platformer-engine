#pragma once

#include <string_view>

#include <Config.h>
#include <Util/Format.h>
#include <Util/Platform.h>
#include <Util/Singleton.h>

#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
#include <windows.h>
#endif

#if ZV_LOG_ENABLED

#define ZV_LOG_ERROR(format, ...)   do { ::zv::internal::log(__LINE__, __FILE__, __func__, ::zv::eLogSeverity::Error, format, ::zv::make_format_args(__VA_ARGS__)); } while(0)
#define ZV_LOG_WARNING(format, ...) do { ::zv::internal::log(__LINE__, __FILE__, __func__, ::zv::eLogSeverity::Warning, format, ::zv::make_format_args(__VA_ARGS__)); } while(0)
#define ZV_LOG_INFO(format, ...)    do { ::zv::internal::log(__LINE__, __FILE__, __func__, ::zv::eLogSeverity::Info, format, ::zv::make_format_args(__VA_ARGS__)); } while(0)
#define ZV_LOG_TRACE(format, ...)   do { ::zv::internal::log(__LINE__, __FILE__, __func__, ::zv::eLogSeverity::Trace, format, ::zv::make_format_args(__VA_ARGS__)); } while(0)
#define ZV_LOG_DEBUG(format, ...)   do { ::zv::internal::log(__LINE__, __FILE__, __func__, ::zv::eLogSeverity::Debug, format, ::zv::make_format_args(__VA_ARGS__)); } while(0)

#define ZV_LOG_FLUSH(...) do { log_flush(); } while(0)

#else

#define ZV_LOG_ERROR(...)   (void)(0)
#define ZV_LOG_WARNING(...) (void)(0)
#define ZV_LOG_INFO(...)    (void)(0)
#define ZV_LOG_TRACE(...)   (void)(0)
#define ZV_LOG_DEBUG(...)   (void)(0)

#define ZV_LOG_FLUSH(...)   (void)(0)

#endif


namespace zv
{
	enum class eLogSeverity : u8 {
		Error   = (1 << 0),
		Warning = (1 << 1),
		Info    = (1 << 2),
		Trace   = (1 << 3),
		Debug   = (1 << 4),
	};
}

namespace zv::internal
{
	void log(int line, const char* file, const char* func, zv::eLogSeverity severity, std::string_view fmt, FormatArgs args);
	void log_flush();

	class LogManager : public Singleton<LogManager>
  {
  public:
    LogManager();
		~LogManager();

	public:
		void log(s32 line, const char* file, const char* func, zv::eLogSeverity severity, std::string_view fmt, FormatArgs args);
		void flush();

	private:
		bool is_severity_enabled(zv::eLogSeverity message_log_level, zv::eLogSeverity max_log_level);

		void log_impl(zv::eLogSeverity severity, FormatColor color, std::string_view message, bool print_line, std::string_view line);
		void log_console(FormatColor color, std::string_view message, bool print_line, std::string_view line);

#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
		void log_stdout_file(HANDLE file_handle, std::string_view message, bool print_line, std::string_view line);
		void log_visual_studio(std::string_view message, bool print_line, std::string_view line);
#endif

  private:
#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
		HANDLE m_file_handle;
#endif
		bool m_console_enabled{ true };

		zv::eLogSeverity m_log_level_console{ zv::eLogSeverity::Info };
		zv::eLogSeverity m_log_level_stdout_file{ zv::eLogSeverity::Trace };
		zv::eLogSeverity m_log_level_visual_studio{ zv::eLogSeverity::Info };

    zv::eLogSeverity m_log_level_maximum;
	};
}
