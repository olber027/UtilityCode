//
// Created by molberding on 5/23/2017.
//

#ifndef UTILITYCODE_LINKEDLIST_H
#define UTILITYCODE_LINKEDLIST_H

#include <ostream>
#include <functional>

namespace linked_list {

    template<typename T, typename = void>
    struct is_equal_comparable : std::false_type { };

    template<typename T>
    struct is_equal_comparable<T, typename std::enable_if<std::is_convertible<decltype(std::declval<T&>() == std::declval<T&>()), bool>{}>::type> : std::true_type {};

    template<typename T>
    class Node {
    private:
        T data;
        Node<T>* next;

    public:
        Node(const T& d, Node<T>* n) : data(d), next(n) { }
        explicit Node(const T& d) : Node(d, nullptr) { }
        Node(const Node<T>& node) {
            if (this != &node) {
                data = node.data;
                next = node.next;
            }
        }

        Node<T>* getNext() const { return next; }

        void setNext(Node<T>* n) { next = n; }

        T getData() const { return data; }

        void setData(const T& d) { data = d; }

        bool operator==(const Node<T>& rhs) const {
            return (data == rhs.data) && (next == rhs.next);
        }

        bool operator!=(const Node<T>& rhs) const {
            return !(*this == rhs);
        }

        friend std::ostream &operator<<(std::ostream& out, const Node<T>& node) {
            out << node.getData();
            return out;
        }
    };

    template<class T>
    class LinkedList {

        static_assert(is_equal_comparable<T>::value, "Type T must be comparable with the == operator");

    private:
        Node<T>* head;
        Node<T>* tail;

    public:
        LinkedList() : head(nullptr), tail(nullptr) {}
        explicit LinkedList(Node<T>* node) : LinkedList() {
            if(!node) {
                return;
            }
            head = node;
            tail = head;
            Node<T>* next = tail->getNext();
            while(next) {
                tail = next;
                next = next->getNext();
            }
        }
        explicit LinkedList(const T& value) : LinkedList() {
            head = new Node<T>(value);
            tail = head;
        }
        LinkedList(const LinkedList<T>& list) {
            if(&list != this) {
                head = list.head;
                tail = list.tail;
            }
        }
        LinkedList(LinkedList<T>&& list) noexcept {
            head = list.head;
            tail = list.tail;
            list.head = nullptr;
            list.tail = nullptr;
        }

        LinkedList<T>& operator=(const LinkedList<T>& rhs) {
            if(&rhs != this) {
                head = rhs.head;
                tail = rhs.tail;
            }
            return *this;
        }

        LinkedList<T>& operator=(LinkedList<T>&& rhs) noexcept {
            if(&rhs != this) {
                head = rhs.head;
                tail = rhs.tail;
                rhs.tail = nullptr;
                rhs.head = nullptr;
            }
            return *this;
        }

        ~LinkedList() {
            if (!head) {
                return;
            }
            Node<T>* next = head->getNext();
            delete head;
            while (next) {
                Node<T>* temp = next;
                next = next->getNext();
                delete temp;
            }
        }

        void addNode(Node<T>* node) {
            if (tail) {
                tail->setNext(node);
                tail = tail->getNext();
            } else {
                head = node;
                tail = node;
            }
        }

        void addNode(const T& value) {
            addNode(new Node<T>(value));
        }

        bool addNodeAt(const int index, const T& value) {
            if(index < 0) {
                return false;
            }
            if(!head) {
                if(index > 0) {
                    return false;
                } else {
                    addNode(value);
                    return true;
                }
            } else {
                if(index == 0) {
                    head = new Node<T>(value, head);
                    return true;
                }
            }

            int i = 0;
            Node<T>* node = head;
            while(++i < index && node) {
                node = node->getNext();
            }

            if(node) {
                Node<T>* next = node->getNext();
                node->setNext(new Node<T>(value, next));
                if(next == nullptr) {
                    tail = node->getNext();
                }
                return true;
            }

            return false;
        }

        Node<T>* pop() {
            if (!head) {
                return nullptr;
            }
            Node<T>* lead = head->getNext();
            Node<T>* trail = head;
            Node<T>* last = head;
            while (lead) {
                last = trail;
                trail = lead;
                lead = lead->getNext();
            }
            Node<T>* temp = trail;
            if (trail == head) {
                head = nullptr;
                tail = nullptr;
            } else {
                tail = last;
                last->setNext(nullptr);
            }
            return temp;
        }

        Node<T>* pop(const int index) {
            if (!head) {
                return nullptr;
            }
            if (index == 0) {
                Node<T>* temp = head;
                head = head->getNext();
                if (tail == temp) {
                    tail = head;
                }
                return temp;
            }

            Node<T>* lead = head;
            Node<T>* trail = head;
            int i = 0;
            while (i++ < index && lead) {
                trail = lead;
                lead = lead->getNext();
            }

            trail->setNext(lead ? lead->getNext() : nullptr);

            return lead;
        }

        Node<T>* operator[](const int index) const {
            return getNodeAtIndex(index);
        }

        bool operator==(const LinkedList<T>& rhs) const {
            Node<T>* thisPtr = head;
            Node<T>* rhsPtr = rhs.head;

            while((thisPtr != nullptr) && (rhsPtr != nullptr)) {
                if(*thisPtr != *rhsPtr) {
                    return false;
                }
                thisPtr = thisPtr->getNext();
                rhsPtr = rhsPtr->getNext();
            }

            return thisPtr == rhsPtr;
        }

        bool operator!=(const LinkedList<T>& rhs) const {
            return !(*this == rhs);
        }

        void transform(Node<T>* startNode, const Node<T>* endNode, std::function<void(Node<T>*)> func) {
            Node<T>* ptr = startNode;
            while(ptr != endNode) {
                func(ptr);
                ptr = ptr->getNext();
            }
        }

        void transform(Node<T>* startNode, std::function<void(Node<T>*)> func) {
            transform(startNode, nullptr, func);
        }

        void transform(std::function<void(Node<T>*)> func) {
            transform(head, nullptr, func);
        }

        Node<T>* getNodeAtIndex(const int index) const {
            if(index < 0) {
                return nullptr;
            }
            Node<T>* search = head;
            int i = 0;
            while (i++ < index && search) {
                search = search->getNext();
            }
            return search;
        }

        Node<T>* getNode(const T& value) const {
            Node<T>* search = head;
            while (search && !(search->getData() == value)) {
                search = search->getNext();
            }
            return search;
        }

        Node<T>* getHead() const {
            return head;
        }

        Node<T>* getTail() const {
            return tail;
        }

        int length() const {
            Node<T>* search = head;
            int len = 0;
            while (search) {
                search = search->getNext();
                len++;
            }
            return len;
        }

        friend std::ostream &operator<<(std::ostream& out, const LinkedList<T>& list) {
            Node<T>* node = list.getHead();
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
