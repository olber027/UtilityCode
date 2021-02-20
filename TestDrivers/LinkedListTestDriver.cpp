//
// Created by olber on 2/17/2021.
//

#include "LinkedListTestDriver.h"

LinkedListTestDriver::LinkedListTestDriver()
    : node(LinkedListNode<int>(0)),
      list(LinkedList<int>()),
      TestDriver("Linked List") {}

void LinkedListTestDriver::verifyContructors()
{

    assert((LinkedListNode<int>*) nullptr, list.getHead());
    assert((LinkedListNode<int>*) nullptr, list.getTail());

    assert(0, node.getData());
    assert((LinkedListNode<int>*) nullptr, node.getNext());

    auto* temp       = new LinkedListNode<int>(1, nullptr);
    auto* secondTemp = new LinkedListNode<int>(2, temp);

    assert(2, secondTemp->getData());
    assert(1, secondTemp->getNext()->getData());

    list = LinkedList<int>(secondTemp);
    assert(secondTemp->getData(), list.getHead()->getData());
    assert(temp->getData(), list.getTail()->getData());
    assert(temp->getData(), list.getHead()->getNext()->getData());
    delete temp;
    delete secondTemp;
}

void LinkedListTestDriver::verifyAdd()
{
    list = LinkedList<int>();
    assert(false, list.addNodeAt(-1, 5));
    assert(true, list.addNodeAt(0, 1));
    assert(1, list.getHead()->getData());
    assert(true, list.addNodeAt(0, 2));
    assert(2, list.getHead()->getData());
    assert(true, list.addNodeAt(2, 3));
    assert(3, list.getTail()->getData());
    assert(true, list.addNodeAt(1, 4));
    assert(4, list.getHead()->getNext()->getData());
    assert(false, list.addNodeAt(500, 5));
    list = LinkedList<int>();
    list.addNode(1);
    assert(1, list.getHead()->getData());
    list.addNode(2);
    assert(2, list.getTail()->getData());
    list.addNode(3);
    assert(3, list.getTail()->getData());

    assert(3, list.length());
}

void LinkedListTestDriver::verifyGet()
{
    assert(1, list.getNode(1)->getData());
    assert(2, list.getNodeAtIndex(1)->getData());
    assert((LinkedListNode<int>*) nullptr, list.getNode(4));
    assert((LinkedListNode<int>*) nullptr, list.getNodeAtIndex(5));
}

void LinkedListTestDriver::verifyPop()
{
    assert(3, list.pop()->getData());
    assert(1, list.pop(0)->getData());
    assert(2, list.pop()->getData());
    assert((LinkedListNode<int>*) nullptr, list.pop());
    list.addNode(1);
    list.addNode(2);
    list.addNode(3);
    assert(2, list.pop(1)->getData());
}

void LinkedListTestDriver::testFunction(const LinkedListNode<int>& testNode) const
{
    node.getData();
}

void LinkedListTestDriver::run()
{
    verifyContructors();
    verifyAdd();
    verifyGet();
    verifyPop();

    list.transform([](LinkedListNode<int>* x) { x->setData(x->getData() + 1); });
    assert(2, list.getHead()->getData());
    assert(4, list.pop()->getData());
    node = LinkedListNode<int>(2);
    testFunction(node);
    assert(2, node.getData());
}