//
// Created by molberding on 6/27/2017.
//

#ifndef UTILITYCODE_STACKTESTDRIVER_H
#define UTILITYCODE_STACKTESTDRIVER_H

#include "../DataStructures/Stack.h"
#include "TestDriver.h"

using namespace stack;

class StackTestDriver : public TestDriver {
private:
    class TestItem {
    public:
        TestItem(int d) : data(d) {}
        int data;
    };
    Stack<TestItem> stack;
public:
    StackTestDriver() {
        init("Stack");
        stack = Stack<TestItem>();
    }

    void run() {
        assert(0, stack.getSize());
        stack.push(new TestItem(1));
        stack.push(new TestItem(2));
        stack.push(new TestItem(3));
        assert(3, stack.getSize());
        assert(3, stack.peek()->data);
        assert(3, stack.pop()->data);
        assert(2, stack.getSize());
        assert(2, stack.pop()->data);
        assert(1, stack.getSize());
        assert(1, stack.pop()->data);
        assert((TestItem*) nullptr, stack.pop());
        assert((TestItem*) nullptr, stack.peek());
        assert(0, stack.getSize());
        assert((TestItem*) nullptr, stack.pop());

        Stack<int> intStack = Stack<int>();
        intStack.push(5);
        assert(5, *(intStack.pop()));
    }
};

#endif //UTILITYCODE_STACKTESTDRIVER_H
