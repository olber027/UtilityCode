//
// Created by molberding on 5/23/2017.
//

#ifndef UTILITYCODE_LINKEDLIST_H
#define UTILITYCODE_LINKEDLIST_H

template <class T> class Node {
private:
    T data;
    Node* next;

public:
    Node(T d, Node* n) {
        data = d;
        next = n;
    }

    Node(T d) {
        data = d;
        next = nullptr;
    }

    Node(const Node &node) {
        data = node.data;
        next = node.next;
    }

    Node* getNext() { return next; }
    void setNext(Node* n) { next = n; }
    T getData() { return data; }
    void setData(T d) { data = d; }
};

template <class T> class LinkedList {
private:
    Node* head;
    Node* tail;

public:
    LinkedList() {
        head = nullptr;
        tail = nullptr;
    }

    LinkedList(Node* node) {
        head = node;
        tail = node;
    }

    LinkedList(T value) {
        LinkedList(new Node<T>(value));
    }

    ~LinkedList() {
        Node* next = head->getNext();
        delete head;
        while(next) {
            Node* temp = next;
            next = next->getNext();
            delete temp;
        }
    }

    void addNode(Node* node) {
        tail->setNext(node);
        tail = tail->getNext();
    }

    void addNode(T value) {
        addNode(new Node<T>(value));
    }

    Node* pop() {
        Node* lead = head->getNext();
        Node* trail = head;
        while(lead) {
            trail = lead;
            lead = lead->getNext();
        }
        tail = trail;
        return lead;
    }

    Node* pop(int index) {
        Node* lead = head;
        Node* trail = head;
        int i = 0;
        while(i < index && lead) {
            trail = lead;
            lead = lead->getNext();
            i++;
        }

        trail->setNext(lead ? lead->getNext() : nullptr);

        return lead;
    }

    Node* getNodeAtIndex(int index) {
        Node* search = head;
        int i = 0;
        while(i < index && search) {
            search = search->getNext();
        }
        return search;
    }

    Node* getNode(T value) {
        Node* search = head;
        while(search && search->getData() != value) {
            search = search->getNext();
        }
        return search;
    }

    Node* getNode(Node node) {
        return getNode(node.getData());
    }

    Node* getHead() {
        return head;
    }

    Node* getTail() {
        return tail;
    }

    int length() {
        Node* search = head;
        int len = 0;
        while(search) {
            search = search->getNext();
            len++;
        }
        return len;
    }
};

#endif //UTILITYCODE_LINKEDLIST_H
