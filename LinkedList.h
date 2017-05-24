//
// Created by molberding on 5/23/2017.
//

#ifndef UTILITYCODE_LINKEDLIST_H
#define UTILITYCODE_LINKEDLIST_H

#include <ostream>

namespace linked_list {
    template<class T>
    class Node {
    private:
        T data;
        Node<T> *next;

    public:
        Node(T d, Node<T> *n) {
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

        Node<T> *getNext() { return next; }

        void setNext(Node<T> *n) { next = n; }

        T getData() { return data; }

        void setData(T d) { data = d; }

        friend std::ostream &operator<<(std::ostream &out, Node<T> &node) {
            out << node.getData();
            return out;
        }
    };

    template<class T>
    class LinkedList {
    private:
        Node<T> *head;
        Node<T> *tail;

    public:
        LinkedList() {
            head = nullptr;
            tail = nullptr;
        }

        LinkedList(Node<T> *node) {
            head = node;
            tail = node;
        }

        LinkedList(T value) {
            LinkedList(new Node<T>(value));
        }

        ~LinkedList() {
            if (!head)
                return;
            Node<T> *next = head->getNext();
            delete head;
            while (next) {
                Node<T> *temp = next;
                next = next->getNext();
                delete temp;
            }
        }

        void addNode(Node<T> *node) {
            if (tail) {
                tail->setNext(node);
                tail = tail->getNext();
            } else {
                head = node;
                tail = node;
            }

        }

        void addNode(T value) {
            addNode(new Node<T>(value));
        }

        Node<T> *pop() {
            if (!head)
                return nullptr;

            Node<T> *lead = head->getNext();
            Node<T> *trail = head;
            Node<T> *end = head;
            while (lead) {
                end = trail;
                trail = lead;
                lead = lead->getNext();
            }
            Node<T> *temp = trail;
            if (trail == head) {
                head = nullptr;
                tail = nullptr;
            } else {
                tail = end;
                end->setNext(nullptr);
            }
            return temp;
        }

        Node<T> *pop(int index) {
            if (!head)
                return nullptr;
            Node<T> *lead = head;
            Node<T> *trail = head;
            int i = 0;
            while (i < index && lead) {
                trail = lead;
                lead = lead->getNext();
                i++;
            }

            trail->setNext(lead ? lead->getNext() : nullptr);

            return lead;
        }

        Node<T> *getNodeAtIndex(int index) {
            Node<T> *search = head;
            int i = 0;
            while (i < index && search) {
                search = search->getNext();
            }
            return search;
        }

        Node<T> *getNode(T value) {
            Node<T> *search = head;
            while (search && search->getData() != value) {
                search = search->getNext();
            }
            return search;
        }

        Node<T> *getNode(Node<T> node) {
            return getNode(node.getData());
        }

        Node<T> *getHead() {
            return head;
        }

        Node<T> *getTail() {
            return tail;
        }

        int length() {
            Node<T> *search = head;
            int len = 0;
            while (search) {
                search = search->getNext();
                len++;
            }
            return len;
        }

        friend std::ostream &operator<<(std::ostream &out, LinkedList<T> &list) {
            Node<T> *node = list.getHead();
            while (node) {
                out << "[" << *node << "]->";
                node = node->getNext();
            }
            out << "[ ]" << std::endl;
            return out;
        }
    };
}
#endif //UTILITYCODE_LINKEDLIST_H
