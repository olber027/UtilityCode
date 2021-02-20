//
// Created by molberding on 7/19/2017.
//

#ifndef UTILITYCODE_BINARYTREE_H
#define UTILITYCODE_BINARYTREE_H

#include "TypeTraits.h"
#include <iostream>

namespace Utilities
{
    template <typename T>
    class BinaryTreeNode
    {
    private:
        BinaryTreeNode<T>* right;
        BinaryTreeNode<T>* left;
        T data;

    public:
        explicit BinaryTreeNode(const T& d) : right(nullptr), left(nullptr), data(d) {}

        BinaryTreeNode(const T& d, BinaryTreeNode<T>* r, BinaryTreeNode<T>* l) : right(r), left(l), data(d) {}

        BinaryTreeNode(const BinaryTreeNode<T>& node)
        {
            data  = node.data;
            left  = node.left;
            right = node.right;
        }

        BinaryTreeNode(BinaryTreeNode<T>&& node) noexcept
        {
            data       = node.data;
            left       = node.left;
            right      = node.right;
            node.left  = nullptr;
            node.right = nullptr;
        }

        BinaryTreeNode<T>& operator=(const BinaryTreeNode<T>& rhs)
        {
            data  = rhs.data;
            left  = rhs.left;
            right = rhs.right;

            return *this;
        }

        BinaryTreeNode<T>& operator=(BinaryTreeNode<T>&& rhs) noexcept
        {
            data      = rhs.data;
            left      = rhs.left;
            right     = rhs.right;
            rhs.right = nullptr;
            rhs.left  = nullptr;

            return *this;
        }

        T getData() const
        {
            return data;
        }

        BinaryTreeNode<T>* getLeft() const
        {
            return left;
        }

        BinaryTreeNode<T>* getRight() const
        {
            return right;
        }

        void setData(const T& newData)
        {
            data = newData;
        }

        void setLeft(BinaryTreeNode<T>* newLeft)
        {
            left = newLeft;
        }

        void setRight(BinaryTreeNode<T>* newRight)
        {
            right = newRight;
        }
    };

    template <typename T>
    class BinaryTree
    {
        static_assert(is_less_than_comparable<T>::value, "Type T must be comparable with the < operator");

    private:
        BinaryTreeNode<T>* root;

        int max(int a, int b) const
        {
            if(a > b)
            {
                return a;
            }
            return b;
        }

        int abs(int a) const
        {
            if(a < 0)
            {
                return a * -1;
            }
            return a;
        }

    public:
        BinaryTree() : root(nullptr) {}
        explicit BinaryTree(BinaryTreeNode<T>* r) : root(r) {}

        BinaryTree(const BinaryTree<T>& other)
        {
            root = other.root;
        }

        BinaryTree(BinaryTree<T>&& other) noexcept
        {
            root       = other.root;
            other.root = nullptr;
        }

        BinaryTree<T>& operator=(const BinaryTree<T>& rhs)
        {
            root = rhs.root;
            return *this;
        }

        BinaryTree<T>& operator=(BinaryTree<T>&& rhs) noexcept
        {
            root     = rhs.root;
            rhs.root = nullptr;
            return *this;
        }

        void insert(const T& item)
        {
            auto newBinaryTreeNode                    = new BinaryTreeNode<T>(item);
            auto currentBinaryTreeNode                = root;
            BinaryTreeNode<T>* trailingBinaryTreeNode = nullptr;

            while(currentBinaryTreeNode != nullptr)
            {
                trailingBinaryTreeNode = currentBinaryTreeNode;
                if(newBinaryTreeNode->getData() < currentBinaryTreeNode->getData())
                {
                    currentBinaryTreeNode = currentBinaryTreeNode->getLeft();
                }
                else
                {
                    currentBinaryTreeNode = currentBinaryTreeNode->getRight();
                }
            }

            if(trailingBinaryTreeNode == nullptr)
            {
                root = newBinaryTreeNode;
            }
            else
            {
                if(newBinaryTreeNode->getData() < trailingBinaryTreeNode->getData())
                {
                    trailingBinaryTreeNode->setLeft(newBinaryTreeNode);
                }
                else
                {
                    trailingBinaryTreeNode->setRight(newBinaryTreeNode);
                }
            }
        }

        BinaryTreeNode<T>* find(const T& item)
        {
            return find(root, item);
        }

        BinaryTreeNode<T>* find(BinaryTreeNode<T>* start, const T& item) const
        {
            if(start == nullptr)
            {
                return nullptr;
            }
            BinaryTreeNode<T>* currentBinaryTreeNode = start;
            while(currentBinaryTreeNode != nullptr && currentBinaryTreeNode->getData() != item)
            {
                if(item < currentBinaryTreeNode->getData())
                {
                    currentBinaryTreeNode = currentBinaryTreeNode->getLeft();
                }
                else
                {
                    currentBinaryTreeNode = currentBinaryTreeNode->getRight();
                }
            }
            return currentBinaryTreeNode;
        }

        bool contains(const BinaryTreeNode<T>* target) const
        {
            return contains(root, target);
        }

        bool contains(const BinaryTreeNode<T>* start, const BinaryTreeNode<T>* target) const
        {
            if(start == nullptr)
            {
                return false;
            }
            if(start == target)
            {
                return true;
            }
            return (contains(start->getLeft(), target) || contains(start->getRight(), target));
        }

        int getDepth() const
        {
            return getDepth(root);
        }

        int getDepth(const BinaryTreeNode<T>* node) const
        {
            if(node != nullptr)
            {
                return 1 + max(getDepth(node->getLeft()), getDepth(node->getRight()));
            }
            return 0;
        }

        BinaryTreeNode<T>* getParent(const BinaryTreeNode<T>* target)
        {
            return getParent(root, target);
        }

        BinaryTreeNode<T>* getParent(BinaryTreeNode<T>* start, const BinaryTreeNode<T>* target) const
        {
            if(start == nullptr || target == nullptr)
            {
                return nullptr;
            }
            if(target == start)
            {
                return start;
            }
            if(start->getLeft() == target || start->getRight() == target)
            {
                return start;
            }
            BinaryTreeNode<T>* leftResult  = getParent(start->getLeft(), target);
            BinaryTreeNode<T>* rightResult = getParent(start->getRight(), target);
            if(leftResult != nullptr)
            {
                return leftResult;
            }
            if(rightResult != nullptr)
            {
                return rightResult;
            }
            return nullptr;
        }

        void rightRotation()
        {
            rightRotation(root);
        }

        void rightRotation(BinaryTreeNode<T>* pivot)
        {
            if(pivot == nullptr)
            {
                return;
            }
            BinaryTreeNode<T>* parent = getParent(pivot);

            BinaryTreeNode<T>* leftTree = pivot->getLeft();
            if(leftTree == nullptr)
            {
                return;
            }
            pivot->setLeft(leftTree->getRight());
            leftTree->setRight(pivot);

            if(root == pivot)
            {
                root = leftTree;
            }
            else
            {
                if(parent->getLeft() == pivot)
                {
                    parent->setLeft(leftTree);
                }
                else
                {
                    parent->setRight(leftTree);
                }
            }
        }

        void leftRotation()
        {
            leftRotation(root);
        }

        void leftRotation(BinaryTreeNode<T>* pivot)
        {
            if(pivot == nullptr)
            {
                return;
            }
            BinaryTreeNode<T>* parent = getParent(pivot);

            BinaryTreeNode<T>* rightTree = pivot->getRight();
            if(rightTree == nullptr)
            {
                return;
            }
            pivot->setRight(rightTree->getLeft());
            rightTree->setLeft(pivot);
            if(root == pivot)
            {
                root = rightTree;
            }
            else
            {
                if(parent->getLeft() == pivot)
                {
                    parent->setLeft(rightTree);
                }
                else
                {
                    parent->setRight(rightTree);
                }
            }
        }

        void balance()
        {
            balance(root);
        }

        void balanceSubTrees(BinaryTreeNode<T>* node)
        {
            if(node != nullptr)
            {
                if(node->getLeft() != nullptr)
                {
                    balance(node->getLeft());
                }
                if(node->getRight() != nullptr)
                {
                    balance(node->getRight());
                }
            }
        }

        void balance(BinaryTreeNode<T>* start)
        {
            if(start == nullptr)
            {
                return;
            }
            else
            {
                balanceSubTrees(start);
            }
            int leftDepth          = getDepth(start->getLeft());
            int rightDepth         = getDepth(start->getRight());
            int difference         = abs(leftDepth - rightDepth);
            int previousDifference = difference + 1;//set this to something not difference initially
            while(difference > 1 && previousDifference != difference)
            {
                if(leftDepth < rightDepth)
                {
                    BinaryTreeNode<T>* right = start->getRight();
                    leftRotation(start);
                    start = right;
                }
                else
                {
                    BinaryTreeNode<T>* left = start->getLeft();
                    rightRotation(start);
                    start = left;
                }
                balanceSubTrees(start);
                leftDepth  = getDepth(start->getLeft());
                rightDepth = getDepth(start->getRight());
                //previousDifference is used to avoid infinite thrashing.
                previousDifference = difference;
                difference         = abs(leftDepth - rightDepth);
            }
        }

        BinaryTreeNode<T>* getRoot() const
        {
            return root;
        }

        void print() const
        {
            print(root, 0, 'o');
        }

        void print(const BinaryTreeNode<T>* node, int depth, char prefix) const
        {
            if(node != nullptr)
            {
                for(int i = 0; i < depth; i++)
                {
                    std::cout << "\t";
                }
                std::cout << "(" << prefix << ")" << node->getData() << std::endl;
                print(node->getLeft(), depth + 1, 'l');
                print(node->getRight(), depth + 1, 'r');
            }
        }
    };
}// namespace Utilities

#endif//UTILITYCODE_BINARYTREE_H
