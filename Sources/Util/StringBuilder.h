#pragma once

#include <stdio.h>
#include <stdarg.h>
#include <array>

#include <Util/Format.h>
#include <Core/Error.h>

namespace zv
{
  //
  // StringBuilder is an helper class to build a string
  // using formatting on a fixed size buffer
  //
  template<size_t CAPACITY>
  class StringBuilder
  {
  public:
    constexpr static size_t Capacity = CAPACITY;
    StringBuilder() {
      static_assert(Capacity > 0, "StringBuild size should be strictly greater than zero.");
      m_data[Capacity] = '\0';
      m_data[0] = '\0';
    }

    constexpr size_t max_size() const {
      return Capacity;
    }
    bool is_full() const {
      return m_size == Capacity;
    }

    size_t size() const {
      return m_size;
    }

    size_t remaining_size() const {
      return Capacity - m_size;
    }

    const char* c_str() const {
      return &m_data[0];
    }

    std::string_view string_view() const {
      return std::string_view(&m_data[0], m_size);
    }

    //
    // Write one character `c`
    // If `force` == true and the list is full,
    // the last character will be overwritten by `c`.
    // (Expected to enforce \n at the end, even if the builder is full)
    //
    bool append(char c, bool force = false) {
      if (m_size < Capacity) {
        m_data[m_size] = c;
        m_size += 1;
        write_termination_zero();
        return false;
      }
      if (force) {
        m_data[Capacity - 1] = c;
      }
      return true;
    }

    template <typename ...Args>
    bool append(std::string_view fmt, Args&&... args) {
      return vappend(fmt, make_format_args(std::forward<Args>(args)...));
    }

    bool vappend(std::string_view fmt, FormatArgs args) {
      const size_t remaining = remaining_size();
      if (remaining > 0) {
        auto result = vformat_to_n(&m_data[m_size], remaining, fmt, args);
        if (result.size > remaining_size()) {
          m_size = Capacity;
          ZV_ASSERT(m_data[Capacity] == '\0');
          return true;
        }
        else {
          m_size += result.size;
          write_termination_zero();
          return false;
        }
      }
      else {
        return true;
      }
    }

  protected:
    void write_termination_zero() {
      ZV_ASSERT(m_size <= Capacity);
      m_data[m_size] = '\0';
    }

  private:
    constexpr static size_t k_buffer_size = CAPACITY + 1;

    size_t m_size = 0;
    std::array<char, k_buffer_size> m_data;
  };
}
