#pragma once

#include <type_traits>

namespace zv
{
  template <typename EnumType>
  struct BitFlag
  {
    static_assert( std::is_enum<EnumType>::value == true, "This is supported only for enums!" );

  private:
		using this_type = BitFlag<EnumType>;
		using value_type = typename std::underlying_type<EnumType>::type;

  public:
      //Sets flag to true
      void set(EnumType flag)
      {
          m_value |= (value_type)flag;
      }

      constexpr value_type get() const
      {
        return m_value;
      }

      //Sets flag to false
      void unset(EnumType flag)
      {
          m_value &= ~(value_type)flag;
      }

      //Sets a flag value from true to false and vice versa
      void flip(EnumType flag)
      {
          m_value ^= (value_type)flag;
      }

      //Check whether a flag is set to true
      constexpr bool is_set(EnumType flag) const
      {
          return (m_value & (value_type)flag) == (value_type)flag;
      }

      value_type m_value{ 0 };
  };
}
