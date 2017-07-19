//
// Created by molberding on 7/19/2017.
//

#ifndef UTILITYCODE_BINARYTREE_H
#define UTILITYCODE_BINARYTREE_H

#include <type_traits>

namespace binary_tree {
    //used to ensure that the type given to the binary tree is comparable.
    template<typename T, typename = void>
    struct is_less_than_comparable : std::false_type { };

    template<typename T>
    struct is_less_than_comparable<T, typename std::enable_if<std::is_convertible<decltype(std::declval<T&>() < std::declval<T&>()), bool>{}>::type> : std::true_type{};

    template<typename T>
    class BinaryTree{
        static_assert(is_less_than_comparable<T>::value, "Type T must be comparable with the < operator");


    };
}

#endif //UTILITYCODE_BINARYTREE_H
