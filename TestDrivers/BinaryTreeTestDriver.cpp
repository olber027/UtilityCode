//
// Created by olber on 2/17/2021.
//

#include "BinaryTreeTestDriver.h"
#include <cstdlib>
#include <ctime>

using namespace Utilities;

BinaryTreeTestDriver::BinaryTreeTestDriver()
    : TestDriver("Binary Tree"),
      tree(BinaryTree<double>())
{
    srand(time(nullptr));
}

void BinaryTreeTestDriver::run()
{
    /*
                5
             /     \
            4       6
          /        /  \
         2       5.5   7
          \             \
           3             9
            \
            3.5
    */
    tree.insert(5);
    assert(5.0, tree.getParent(tree.find(5))->getData());

    tree.insert(4);
    assert(5.0, tree.getParent(tree.find(4))->getData());
    tree.insert(6);
    assert(5.0, tree.getParent(tree.find(6))->getData());

    tree.insert(2);
    assert(4.0, tree.getParent(tree.find(2))->getData());
    tree.insert(7);
    assert(6.0, tree.getParent(tree.find(7))->getData());
    tree.insert(3);
    assert(2.0, tree.getParent(tree.find(3))->getData());
    tree.insert(5.5);
    assert(6.0, tree.getParent(tree.find(5.5))->getData());

    tree.insert(3.5);
    assert(3.0, tree.getParent(tree.find(3.5))->getData());
    tree.insert(9);
    assert(7.0, tree.getParent(tree.find(9))->getData());
    assert(5, tree.getDepth());
    Utilities::BinaryTreeNode<double>* node = tree.find(6);
    assert(true, node != nullptr);
    assert(3, tree.getDepth(node));
    assert(tree.find(5), tree.getParent(node));
    assert(tree.find(2), tree.getParent(tree.find(3)));
    assert(tree.find(6), tree.getParent(tree.find(5.5)));

    assert(5.0, tree.getRoot()->getData());
    tree.rightRotation();
    assert(4.0, tree.getRoot()->getData());
    tree.leftRotation();
    assert(5.0, tree.getRoot()->getData());

    assert(3, tree.getDepth(tree.getRoot()->getRight()));
    assert(4, tree.getDepth(tree.getRoot()->getLeft()));
    tree.leftRotation();
    assert(2, tree.getDepth(tree.getRoot()->getRight()));
    assert(5, tree.getDepth(tree.getRoot()->getLeft()));


    BinaryTree<double> bigTree = BinaryTree<double>();
    for(int i = 0; i < 1000; i++)
    {
        bigTree.insert(rand() % 1000);
    }
    int initialTreeDepth = bigTree.getDepth();
    bigTree.balance();
    int finalTreeDepth = bigTree.getDepth();
    assert(true, initialTreeDepth >= finalTreeDepth, "balanced depth was larger than unbalanced depth");
}