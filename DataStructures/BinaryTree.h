//
// Created by molberding on 7/19/2017.
//

#ifndef UTILITYCODE_BINARYTREE_H
#define UTILITYCODE_BINARYTREE_H

#include <type_traits>
#include <iostream>

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

        T getData() {
            return data;
        }

        Node<T>* getLeft() {
            return left;
        }

        Node<T>* getRight() {
            return right;
        }

        void setData(T newData) {
            data = newData;
        }

        void setLeft(Node<T>* newLeft) {
            left = newLeft;
        }

        void setRight(Node<T>* newRight) {
            right = newRight;
        }
    };

    template<typename T>
    class BinaryTree{
        static_assert(is_less_than_comparable<T>::value, "Type T must be comparable with the < operator");

    private:
        Node<T>* root;

        int max(int a, int b) {
            if(a > b) {
                return a;
            }
            return b;
        }

        int abs(int a) {
            if(a < 0) {
                return a*-1;
            }
            return a;
        }

    public:
        BinaryTree() : root(nullptr) {}
        BinaryTree(Node<T>* r) : root(r) {}

        void insert(T item) {
            Node<T>* newNode = new Node<T>(item);
            Node<T>* currentNode = root;
            Node<T>* trailingNode = nullptr;

            while(currentNode != nullptr) {
                trailingNode = currentNode;
                if(newNode->getData() < currentNode->getData()) {
                    currentNode = currentNode->getLeft();
                } else {
                    currentNode = currentNode->getRight();
                }
            }

            if(trailingNode == nullptr) {
                root = newNode;
            } else {
                if(newNode->getData() < trailingNode->getData()) {
                    trailingNode->setLeft(newNode);
                } else {
                    trailingNode->setRight(newNode);
                }
            }
        }

        Node<T>* find(T item) {
            return find(root, item);
        }

        Node<T>* find(Node<T>* start, T item) {
            if(start == nullptr) {
                return nullptr;
            }
            Node<T>* currentNode = start;
            while(currentNode != nullptr && currentNode->getData() != item) {
                if(item < currentNode->getData()) {
                    currentNode = currentNode->getLeft();
                } else {
                    currentNode = currentNode->getRight();
                }
            }
            return currentNode;
        }

        bool contains(Node<T>* target) {
            return contains(root, target);
        }

        bool contains(Node<T>* start, Node<T>* target) {
            if(start == nullptr) {
                return false;
            }
            if(start == target) {
                return true;
            }
            return (contains(start->getLeft(), target) || contains(start->getRight(), target));
        }

        int getDepth() {
            return getDepth(root);
        }

        int getDepth(Node<T>* node) {
            if(node != nullptr) {
                return 1 + max(getDepth(node->getLeft()), getDepth(node->getRight()));
            }
            return 0;
        }

        Node<T>* getParent(Node<T>* target) {
            return getParent(root, target);
        }

        Node<T>* getParent(Node<T>* start, Node<T>* target) {
            if(start == nullptr || target == nullptr) {
                return nullptr;
            }
            if(target == start) {
                return start;
            }
            if(start->getLeft() == target || start->getRight() == target) {
                return start;
            }
            Node<T>* leftResult = getParent(start->getLeft(), target);
            Node<T>* rightResult = getParent(start->getRight(), target);
            if(leftResult != nullptr) {
                return leftResult;
            }
            if(rightResult != nullptr) {
                return rightResult;
            }
            return nullptr;
        }

        void rightRotation() {
            rightRotation(root);
        }

        void rightRotation(Node<T>* pivot) {
            if(pivot == nullptr){
                return;
            }
            Node<T>* parent = getParent(pivot);

            Node<T>* leftTree = pivot->getLeft();
            if(leftTree == nullptr) {
                return;
            }
            pivot->setLeft(leftTree->getRight());
            leftTree->setRight(pivot);

            if(root == pivot) {
                root = leftTree;
            } else {
                if(parent->getLeft() == pivot) {
                    parent->setLeft(leftTree);
                } else {
                    parent->setRight(leftTree);
                }
            }
        }

        void leftRotation() {
            leftRotation(root);
        }

        void leftRotation(Node<T>* pivot) {
            if(pivot == nullptr) {
                return;
            }
            Node<T>* parent = getParent(pivot);

            Node<T>* rightTree = pivot->getRight();
            if(rightTree == nullptr) {
                return;
            }
            pivot->setRight(rightTree->getLeft());
            rightTree->setLeft(pivot);
            if(root == pivot) {
                root = rightTree;
            } else {
                if(parent->getLeft() == pivot) {
                    parent->setLeft(rightTree);
                } else {
                    parent->setRight(rightTree);
                }
            }
        }

        void balance() {
            balance(root);
        }

        void balanceSubTrees(Node<T>* node) {
            if(node != nullptr) {
                if(node->getLeft() != nullptr) {
                    balance(node->getLeft());
                }
                if(node->getRight() != nullptr) {
                    balance(node->getRight());
                }
            }
        }

        void balance(Node<T>* start) {
            if(start == nullptr) {
                return;
            } else {
                balanceSubTrees(start);
            }
            int leftDepth = getDepth(start->getLeft());
            int rightDepth = getDepth(start->getRight());
            int difference = abs(leftDepth - rightDepth);
            int previousDifference = difference + 1; //set this to something not difference initially
            while(difference > 1 && previousDifference != difference) {
                if(leftDepth < rightDepth) {
                    Node<T>* right = start->getRight();
                    leftRotation(start);
                    start = right;
                } else {
                    Node<T>* left = start->getLeft();
                    rightRotation(start);
                    start = left;
                }
                balanceSubTrees(start);
                leftDepth = getDepth(start->getLeft());
                rightDepth = getDepth(start->getRight());
                //previousDifference is used to avoid infinite thrashing.
                previousDifference = difference;
                difference = abs(leftDepth - rightDepth);
            }
        }

        Node<T>* getRoot() {
            return root;
        }

        void print() {
            print(root, 0, 'o');
        }

        void print(Node<T>* node, int depth, char prefix) {
            if(node != nullptr) {
                for(int i = 0; i < depth; i++) {
                    std::cout << "\t";
                }
                std::cout << "(" << prefix << ")" << node->getData() << std::endl;
                print(node->getLeft(), depth + 1, 'l');
                print(node->getRight(), depth + 1, 'r');
            }
        }
    };
}

#endif //UTILITYCODE_BINARYTREE_H