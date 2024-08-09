#pragma once

#include <type_traits>

namespace zv
{
    // Since c++20
    template< class T >
    struct remove_cvref {
        typedef std::remove_cv_t<std::remove_reference_t<T>> type;
    };

    template< class T >
    using remove_cvref_t = typename remove_cvref<T>::type;
}
