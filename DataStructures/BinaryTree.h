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
    class Node{
    private:
        Node<T>* right;
        Node<T>* left;
        T data;
    public:
        Node(T d) : right(nullptr), left(nullptr), data(d) {}

        Node(T d, Node<T>* r, Node<T>* l) : right(r), left(l), data(d) {}

        Node(const Node<T> &node) {
            if(this != &node) {
                data = node.data;
                left = node.left;
                right = node.right;
            }
        }

        Node<T>& operator=(const Node<T> &rhs) {
            if(this != &rhs) {
                data = rhs.data;
                left = rhs.left;
                right = rhs.right;
            }
            return *this;
        }

        bool operator<(Node<T> other) {
            return data < other.data;
        }

        bool operator>(Node<T> other) {
            return other.data < data;
        }

        T getdata() {
            return data;
        }
    };

    template<typename T>
    class BinaryTree{
        static_assert(is_less_than_comparable<T>::value, "Type T must be comparable with the < operator");

    private:
        Node<T>* root;

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(Node<T>* r) : root(r) {}

    };
}

#endif //UTILITYCODE_BINARYTREE_H
