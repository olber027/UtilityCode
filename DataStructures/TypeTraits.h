//
// Created by olber on 2/17/2021.
//

#ifndef UTILITYCODE_TYPETRAITS_H
#define UTILITYCODE_TYPETRAITS_H

#include <type_traits>

namespace Utilities
{
    template<typename T, typename = void>
    struct is_less_than_comparable : std::false_type { };

    template<typename T>
    struct is_less_than_comparable<T, typename std::enable_if<std::is_convertible<
            decltype(std::declval<T &>() < std::declval<T &>()), bool>{}>::type>
            : std::true_type { };

    template<typename T, typename = void>
    struct is_greater_than_comparable : std::false_type { };

    template<typename T>
    struct is_greater_than_comparable<T, typename std::enable_if<std::is_convertible<
            decltype(std::declval<T &>() > std::declval<T &>()), bool>{}>::type>
            : std::true_type { };

    template<typename T, typename = void>
    struct is_equal_comparable : std::false_type { };

    template<typename T>
    struct is_equal_comparable<T, typename std::enable_if<std::is_convertible<
            decltype(std::declval<T &>() == std::declval<T &>()), bool>{}>::type>
            : std::true_type { };
}

#endif // UTILITYCODE_TYPETRAITS_H
