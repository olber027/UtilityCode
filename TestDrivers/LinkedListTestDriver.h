//
// Created by molberding on 5/25/2017.
//

#ifndef UTILITYCODE_LINKEDLISTTESTDRIVER_H
#define UTILITYCODE_LINKEDLISTTESTDRIVER_H

#include "DataStructures/LinkedList.h"
#include "TestDriver.h"

using namespace Utilities;

class LinkedListTestDriver : public TestDriver
{
private:
    LinkedList<int> list;
    LinkedListNode<int> node;

public:
    LinkedListTestDriver();

    void verifyContructors();

    void verifyAdd();

    void verifyGet();

    void verifyPop();

    void testFunction(const LinkedListNode<int>& testNode) const;

    void run() override;
};

#endif//UTILITYCODE_LINKEDLISTTESTDRIVER_H
