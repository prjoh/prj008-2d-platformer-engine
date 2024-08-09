#pragma once

#include <Config.h>
#include <Util/Format.h>
#include <Util/Platform.h>


#if LE_PLATFORM_IS_WIN64
extern "C" __declspec(dllimport) void __stdcall DebugBreak(void);
extern "C" __declspec(dllimport) int __stdcall IsDebuggerPresent(void);
#define ZV_BREAKPOINT() do { if(::IsDebuggerPresent()) { ::DebugBreak(); } } while(false)
#elif ZV_PLATFORM_IS_OSX
#if defined(__x86_64) || defined(__x86_64__) || defined(__amd64__) || defined(__i386)
#define BREAK_INTO_DEBUGGER() __asm__("int $3\n" : :) // NOLINT (hicpp-no-assembler)
#else
#define BREAK_INTO_DEBUGGER() __asm__("brk #0"); // NOLINT (hicpp-no-assembler)
#endif
#define ZV_BREAKPOINT() do { BREAK_INTO_DEBUGGER() } while(false)
#else
# error "The current platform is undefined"
#endif

void print_error(const char* msg);
[[ noreturn ]] void fatal_error(const char* msg, int line, const char* func);

#define ZV_ABORT_INTERNAL(message) fatal_error(message, __LINE__, __func__);

#define ZV_ASSERT_INTERNAL(condition, message)		  \
	do {											  \
		if (!(condition))							  \
		{											  \
			ZV_BREAKPOINT();						  \
			fatal_error(message, __LINE__, __func__);  \
		}											  \
	} while (false)

#define ZV_ABORT(message, ...) \
    do {                                                                                                                      \
        ZV_BREAKPOINT();                                                                                                      \
        ::zv::internal::abort_msg_handler_with_args(message, ::zv::make_format_args( __VA_ARGS__ ),  __LINE__, __FILE__, __func__); \
        std::exit(-1);                                                                                                        \
    } while (false)

#define ZV_ASSERT_UNREACHABLE() ZV_ABORT("This code should be unreachable")

#if ZV_ASSERT_ENABLED

#define ZV_ASSERT_MSG(condition, message, ...) \
	do {										\
		if (!(condition))						\
		{										\
			ZV_BREAKPOINT();					\
      ::zv::internal::assert_msg_handler_with_args(message, ::zv::make_format_args( __VA_ARGS__ ), __LINE__, __FILE__, __func__, (#condition)); \
			std::exit(-1);						\
		}										\
	} while (false)

#define ZV_ASSERT(condition) ZV_ASSERT_MSG(condition, #condition)

#else

#define ZV_ASSERT_MSG(...) (void)(0)
#define ZV_ASSERT(...) (void)(0)

#endif

namespace zv::internal
{
  void abort_msg_handler(const char* message, int line_number, const char* filename, const char* func_name, int /*frame_to_skip_count*/);
  void assert_msg_handler_with_args(const char* message, FormatArgs args, int line_number, const char* filename, const char* func_name, const char* condition_str, int frame_to_skip_count = 0);
  void abort_msg_handler_with_args(const char* message, FormatArgs args, int line_number, const char* filename, const char* func_name, int frame_to_skip_count = 0);
}
