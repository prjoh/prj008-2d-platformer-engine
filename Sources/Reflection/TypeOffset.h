// MIT License - Copyright(c) 2023 James Edward Anhalt III - https://github.com/jeaiii
#pragma once

using size_t = decltype(sizeof(0));

#pragma pack(push, 1)
template<auto, class, size_t N> union member_at;
template<class T, class U, T U::* M, class B, size_t N> union member_at<M, B, N>
{
  char data[sizeof(B)];
  struct
  {
    char at[N];
    T member;
  };
  B parent;
  U base;
};
#pragma pack(pop)

template<auto M, class B, size_t Lo = 0, size_t Hi = sizeof(B)> constexpr size_t find_offset_of()
{   
  constexpr size_t Mid = Lo + (Hi - Lo) / 2;
  if constexpr (Lo == Mid)
  {
      return Mid;
  }
  else
  {
    constexpr member_at<M, B, Mid> test{ };

    if constexpr (&(test.parent.*M) < &test.member)
      return find_offset_of<M, B, Lo, Mid>();
    else
      return find_offset_of<M, B, Mid, Hi>();
  }
}

template<auto M, class B = decltype(member_at<M, int, 1>::base)> constexpr size_t as_offset = find_offset_of<M, B>();

#define offset_of(...) as_offset<__VA_ARGS__>
#define offset_of_base(...) as_offset<__VA_ARGS__>

/*
MIT License
Copyright(c) 2023 James Edward Anhalt III - https://github.com/jeaiii
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/