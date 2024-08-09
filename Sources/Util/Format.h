#pragma once

#include <string>
#include <string_view>
#include <utility>

#include <fmt/color.h>
#include <fmt/core.h>

namespace zv
{
  using FormatColor = fmt::color;
  using FormatContext = fmt::format_context;
  using FormatArgs = fmt::format_args;

  template<typename Context, typename ...Args>
  using FormatArgStorage = fmt::format_arg_store<Context, fmt::remove_cvref_t<Args>...>;

  template<typename ...Args>
  FormatArgStorage<FormatContext, fmt::remove_cvref_t<Args>...> make_format_args(Args&&... args) {
    return fmt::make_format_args(args...);
  }

  template<typename OutputIt>
  using FormatToNResult = fmt::format_to_n_result<OutputIt>;

  template <typename OutputIt>
  FormatToNResult<OutputIt> vformat_to_n(OutputIt out, size_t length, std::string_view fmt, FormatArgs args) {
    return fmt::vformat_to_n(out, length, fmt, args);
  }

  template<typename ...T>
  std::string format(fmt::format_string<T...> fmt, T&&... args) {
      return fmt::format(fmt, std::forward<T>(args)...);
  }

  inline std::string vformat(std::string_view fmt, FormatArgs args) {
    return fmt::vformat(fmt, args);
  }
}
