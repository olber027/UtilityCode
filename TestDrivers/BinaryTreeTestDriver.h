//
// Created by molberding on 7/20/2017.
//

#ifndef UTILITYCODE_BINARYTREETESTDRIVER_H
#define UTILITYCODE_BINARYTREETESTDRIVER_H

#include "TestDriver.h"
#include <DataStructures/BinaryTree.h>

class BinaryTreeTestDriver : public TestDriver
{
private:
    Utilities::BinaryTree<double> tree;

public:
    BinaryTreeTestDriver();

    void run() override;
};

#endif//UTILITYCODE_BINARYTREETESTDRIVER_H
