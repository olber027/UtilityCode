//
// Created by molberding on 5/25/2017.
//

#ifndef UTILITYCODE_LINKEDLISTTESTDRIVER_H
#define UTILITYCODE_LINKEDLISTTESTDRIVER_H

#include "../DataStructures/LinkedList.h"
#include "TestDriver.h"

using namespace linked_list;

class LinkedListTestDriver : public TestDriver {
private:
    LinkedList<int> list;
    Node<int> node;
public:
    LinkedListTestDriver() : node(Node<int>(0)) {
        passed = 0;
        failed = 0;
        total = 0;
        output = std::stringstream();
        list = LinkedList<int>();
        for(int i = 0; i < 80; i++) {
            output << "=";
        }
        output << std::endl << "Start of Linked List Testing\n";
        for(int i = 0; i < 80; i++) {
            output << "=";
        }
        output << std::endl;
    }

    void verifyContructors() {

        output << "Checking default Linked List constructor...\n";
        assert((Node<int>*) nullptr, list.getHead());
        assert((Node<int>*) nullptr, list.getTail());

        output << "Checking Node constructors...\n";
        assert(0, node.getData());
        assert((Node<int>*) nullptr, node.getNext());
        Node<int>* temp = new Node<int>(1, nullptr);
        Node<int>* secondTemp = new Node<int>(2, temp);
        assert(2, secondTemp->getData());
        assert(1, secondTemp->getNext()->getData());

        output << "Checking LinkedList constructors...\n";
        list = LinkedList<int>(secondTemp);
        assert(secondTemp->getData(), list.getHead()->getData());
        assert(temp->getData(), list.getTail()->getData());
        assert(temp->getData(), list.getHead()->getNext()->getData());
        delete temp;
        delete secondTemp;
    }

    void verifyAdd() {

        output << "Checking adding Functionality...\n";
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

        output << "Checking length() function...\n";
        assert(3, list.length());
    }

    void verifyGet() {

        output << "Checking the Get functions...\n";
        assert(1, list.getNode(1)->getData());
        assert(2, list.getNodeAtIndex(1)->getData());
        assert(3, list.getNode(Node<int>(3))->getData());
        assert((Node<int>*) nullptr, list.getNode(4));
        assert((Node<int>*) nullptr, list.getNodeAtIndex(5));
        assert((Node<int>*) nullptr, list.getNode(Node<int>(4)));
    }

    void verifyPop() {

        output << "Checking the Pop functions...\n";
        assert(3, list.pop()->getData());
        assert(1, list.pop(0)->getData());
        assert(2, list.pop()->getData());
        assert((Node<int>*) nullptr, list.pop());
        list.addNode(1);
        list.addNode(2);
        list.addNode(3);
        assert(2, list.pop(1)->getData());
    }

    void testFunction(Node<int> node) {
        node.getData();
    }

    void run() {
        verifyContructors();
        verifyAdd();
        verifyGet();
        verifyPop();

        node = Node<int>(2);
        testFunction(node);
        assert(2, node.getData());
    }
};

#endif //UTILITYCODE_LINKEDLISTTESTDRIVER_H
