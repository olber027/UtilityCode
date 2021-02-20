//
// Created by molberding on 6/27/2017.
//

#ifndef UTILITYCODE_STACKTESTDRIVER_H
#define UTILITYCODE_STACKTESTDRIVER_H

#include "DataStructures/Stack.h"
#include "TestDriver.h"

using namespace Utilities;

class StackTestDriver : public TestDriver
{
private:
    class TestItem
    {
    public:
        explicit TestItem(int d) : data(d) {}
        int data;
    };
    Stack<TestItem> stack;

public:
    StackTestDriver();

    void run() override;
};

#endif//UTILITYCODE_STACKTESTDRIVER_H
