#include <iostream>

#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
#include <windows.h>
#endif

#include <Core/Error.h>
#include <Core/Log.h>
#include <Util/Platform.h>


void print_error(const char* msg)
{
#if (ZV_PLATFORM_IS_WIN32 || ZV_PLATFORM_IS_WIN64)
	::OutputDebugStringA(msg);
	::OutputDebugStringA("\n");
#endif
	std::cout << msg << "\n";
}

void fatal_error(const char* msg, int line, const char* func)
{
	print_error(zv::format("Fatal Error in {}({}): {}", func, line, msg).c_str());
	print_error("Fatal Error in");
	std::exit(-1);
}

void zv::internal::abort_msg_handler(const char* message, int line_number, const char* filename, const char* func_name, int /*frame_to_skip_count*/)
{
  ZV_LOG_ERROR(message);
  ZV_LOG_ERROR("    in {}, {}:{}", func_name, filename, line_number);
}

void zv::internal::assert_msg_handler_with_args(const char* message, FormatArgs args, int line_number, const char* filename, const char* func_name, const char* condition_str, int frame_to_skip_count) {
  if (message != nullptr) {
    abort_msg_handler(zv::format("Assertion failed: {}, {}", condition_str, zv::vformat(message, args)).c_str(), line_number, filename, func_name, frame_to_skip_count + 1);
  } else {
    abort_msg_handler(zv::format("Assertion failed: {}", condition_str).c_str(), line_number, filename, func_name, frame_to_skip_count + 1);
  }
}

void zv::internal::abort_msg_handler_with_args(const char* message, FormatArgs args, int line_number, const char* filename, const char* func_name, int frame_to_skip_count) {
  abort_msg_handler(zv::vformat(message, args).c_str(), line_number, filename, func_name, frame_to_skip_count);
}
