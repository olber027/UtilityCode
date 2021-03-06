//
// Created by molberding on 5/23/2017.
//

#ifndef UTILITYCODE_LINKEDLIST_H
#define UTILITYCODE_LINKEDLIST_H

#include "TypeTraits.h"
#include <functional>
#include <ostream>

namespace Utilities
{
    template <typename T>
    class LinkedListNode
    {
    private:
        T data;
        LinkedListNode<T>* next;

    public:
        LinkedListNode(const T& d, LinkedListNode<T>* n) : data(d), next(n) {}
        explicit LinkedListNode(const T& d) : LinkedListNode(d, nullptr) {}
        LinkedListNode(const LinkedListNode<T>& node)
        {
            if(this != &node)
            {
                data = node.data;
                next = node.next;
            }
        }

        LinkedListNode<T>* getNext() const { return next; }

        void setNext(LinkedListNode<T>* n) { next = n; }

        T getData() const { return data; }

        void setData(const T& d) { data = d; }

        bool operator==(const LinkedListNode<T>& rhs) const
        {
            return (data == rhs.data) && (next == rhs.next);
        }

        bool operator!=(const LinkedListNode<T>& rhs) const
        {
            return !(*this == rhs);
        }

        friend std::ostream& operator<<(std::ostream& out, const LinkedListNode<T>& node)
        {
            out << node.getData();
            return out;
        }
    };

    template <class T>
    class LinkedList
    {
        static_assert(is_equal_comparable<T>::value, "Type T must be comparable with the == operator");

    private:
        LinkedListNode<T>* head;
        LinkedListNode<T>* tail;

    public:
        LinkedList() : head(nullptr), tail(nullptr) {}
        explicit LinkedList(LinkedListNode<T>* node) : LinkedList()
        {
            if(!node)
            {
                return;
            }
            head                    = node;
            tail                    = head;
            LinkedListNode<T>* next = tail->getNext();
            while(next)
            {
                tail = next;
                next = next->getNext();
            }
        }
        explicit LinkedList(const T& value) : LinkedList()
        {
            head = new LinkedListNode<T>(value);
            tail = head;
        }
        LinkedList(const LinkedList<T>& list)
        {
            if(&list != this)
            {
                head = list.head;
                tail = list.tail;
            }
        }
        LinkedList(LinkedList<T>&& list) noexcept
        {
            head      = list.head;
            tail      = list.tail;
            list.head = nullptr;
            list.tail = nullptr;
        }

        LinkedList<T>& operator=(const LinkedList<T>& rhs)
        {
            if(&rhs != this)
            {
                head = rhs.head;
                tail = rhs.tail;
            }
            return *this;
        }

        LinkedList<T>& operator=(LinkedList<T>&& rhs) noexcept
        {
            if(&rhs != this)
            {
                head     = rhs.head;
                tail     = rhs.tail;
                rhs.tail = nullptr;
                rhs.head = nullptr;
            }
            return *this;
        }

        ~LinkedList()
        {
            if(!head)
            {
                return;
            }
            LinkedListNode<T>* next = head->getNext();
            delete head;
            while(next)
            {
                LinkedListNode<T>* temp = next;
                next                    = next->getNext();
                delete temp;
            }
        }

        void addNode(LinkedListNode<T>* node)
        {
            if(tail)
            {
                tail->setNext(node);
                tail = tail->getNext();
            }
            else
            {
                head = node;
                tail = node;
            }
        }

        void addNode(const T& value)
        {
            addNode(new LinkedListNode<T>(value));
        }

        bool addNodeAt(const int index, const T& value)
        {
            if(index < 0)
            {
                return false;
            }
            if(!head)
            {
                if(index > 0)
                {
                    return false;
                }
                else
                {
                    addNode(value);
                    return true;
                }
            }
            else
            {
                if(index == 0)
                {
                    head = new LinkedListNode<T>(value, head);
                    return true;
                }
            }

            int i                   = 0;
            LinkedListNode<T>* node = head;
            while(++i < index && node)
            {
                node = node->getNext();
            }

            if(node)
            {
                LinkedListNode<T>* next = node->getNext();
                node->setNext(new LinkedListNode<T>(value, next));
                if(next == nullptr)
                {
                    tail = node->getNext();
                }
                return true;
            }

            return false;
        }

        LinkedListNode<T>* pop()
        {
            if(!head)
            {
                return nullptr;
            }
            LinkedListNode<T>* lead  = head->getNext();
            LinkedListNode<T>* trail = head;
            LinkedListNode<T>* last  = head;
            while(lead)
            {
                last  = trail;
                trail = lead;
                lead  = lead->getNext();
            }
            LinkedListNode<T>* temp = trail;
            if(trail == head)
            {
                head = nullptr;
                tail = nullptr;
            }
            else
            {
                tail = last;
                last->setNext(nullptr);
            }
            return temp;
        }

        LinkedListNode<T>* pop(const int index)
        {
            if(!head)
            {
                return nullptr;
            }
            if(index == 0)
            {
                LinkedListNode<T>* temp = head;
                head                    = head->getNext();
                if(tail == temp)
                {
                    tail = head;
                }
                return temp;
            }

            LinkedListNode<T>* lead  = head;
            LinkedListNode<T>* trail = head;
            int i                    = 0;
            while(i++ < index && lead)
            {
                trail = lead;
                lead  = lead->getNext();
            }

            trail->setNext(lead ? lead->getNext() : nullptr);

            return lead;
        }

        LinkedListNode<T>* operator[](const int index) const
        {
            return getNodeAtIndex(index);
        }

        bool operator==(const LinkedList<T>& rhs) const
        {
            LinkedListNode<T>* thisPtr = head;
            LinkedListNode<T>* rhsPtr  = rhs.head;

            while((thisPtr != nullptr) && (rhsPtr != nullptr))
            {
                if(*thisPtr != *rhsPtr)
                {
                    return false;
                }
                thisPtr = thisPtr->getNext();
                rhsPtr  = rhsPtr->getNext();
            }

            return thisPtr == rhsPtr;
        }

        bool operator!=(const LinkedList<T>& rhs) const
        {
            return !(*this == rhs);
        }

        void transform(LinkedListNode<T>* startNode, const LinkedListNode<T>* endNode, std::function<void(LinkedListNode<T>*)> func)
        {
            LinkedListNode<T>* ptr = startNode;
            while(ptr != endNode)
            {
                func(ptr);
                ptr = ptr->getNext();
            }
        }

        void transform(LinkedListNode<T>* startNode, std::function<void(LinkedListNode<T>*)> func)
        {
            transform(startNode, nullptr, func);
        }

        void transform(std::function<void(LinkedListNode<T>*)> func)
        {
            transform(head, nullptr, func);
        }

        LinkedListNode<T>* getNodeAtIndex(const int index) const
        {
            if(index < 0)
            {
                return nullptr;
            }
            LinkedListNode<T>* search = head;
            int i                     = 0;
            while(i++ < index && search)
            {
                search = search->getNext();
            }
            return search;
        }

        LinkedListNode<T>* getNode(const T& value) const
        {
            LinkedListNode<T>* search = head;
            while(search && !(search->getData() == value))
            {
                search = search->getNext();
            }
            return search;
        }

        LinkedListNode<T>* getHead() const
        {
            return head;
        }

        LinkedListNode<T>* getTail() const
        {
            return tail;
        }

        int length() const
        {
            LinkedListNode<T>* search = head;
            int len                   = 0;
            while(search)
            {
                search = search->getNext();
                len++;
            }
            return len;
        }

        friend std::ostream& operator<<(std::ostream& out, const LinkedList<T>& list)
        {
            LinkedListNode<T>* node = list.getHead();
            while(node)
            {
                out << "[" << *node << "]->";
                node = node->getNext();
            }
            out << "[ ]" << std::endl;
            return out;
        }
    };
}// namespace Utilities
#endif//UTILITYCODE_LINKEDLIST_H
