//
// Created by olber on 2/20/2021.
//
#include "StackTestDriver.h"

StackTestDriver::StackTestDriver() : TestDriver("Stack"), stack(Stack<TestItem>()) {}

void StackTestDriver::run()
{
    assert(0, stack.getSize());
    stack.push(TestItem(1));
    stack.push(TestItem(2));
    stack.push(TestItem(3));
    assert(3, stack.getSize());
    assert(3, stack.peek().data);
    assert(3, stack.pop().data);
    assert(2, stack.getSize());
    assert(2, stack.pop().data);
    assert(1, stack.getSize());
    assert(false, stack.isEmpty());
    assert(1, stack.pop().data);
    assert(true, stack.isEmpty());
    std::string errorMessage;
    try
    {
        stack.pop();
    }
    catch(std::out_of_range& e)
    {
        errorMessage = e.what();
    }
    assert(std::string("Attempted to pop an empty stack"), errorMessage);

    try
    {
        stack.peek();
    }
    catch(std::out_of_range& e)
    {
        errorMessage = e.what();
    }
    assert(std::string("Attempted to peek an empty stack"), errorMessage);

    Stack<int> intStack = Stack<int>();
    intStack.push(5).push(5).push(5).push(5).push(5).push(5);
    while(!intStack.isEmpty())
    {
        assert(5, intStack.pop());
    }

    Stack<TestItem*> pointerStack;
    for(int i = 0; i < 5; i++)
    {
        pointerStack.push(new TestItem(i));
    }
    for(int i = 4; i >= 0; i--)
    {
        assert(i, pointerStack.pop()->data);
    }

    Stack<int> stack1;
    Stack<int> stack2;
    for(int i = 0; i < 5; i++)
    {
        stack1.push(i);
        stack2.push(stack1.pop());
    }
    for(int i = 4; i >= 0; i--)
    {
        assert(i, stack2.pop());
    }
}