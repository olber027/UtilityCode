//
// Created by molberding on 6/27/2017.
//

#ifndef UTILITYCODE_STACK_H
#define UTILITYCODE_STACK_H

#include <stdexcept>

namespace stack {

    template<typename T>
    class Stack {
    private:

        class Item {
        public:
            Item(const T& dat, Item* n) : data(dat), next(n) {}
            T data;
            Item* next;
        };

        Item* top;
        int size;

        void destroy() {
            if(top) {
                while (top->next) {
                    Item *temp = top->next;
                    delete top;
                    top = temp;
                }
                delete top;
            }
        }

    public:
        Stack() : top(nullptr), size(0) {}
        Stack(const T& init) : top(new Item(init, nullptr)), size(1) {}
        ~Stack() {
            destroy();
        }

        void cleanup() {
            destroy();
        }

        Stack(const Stack<T>& stack) {
            if(&stack != this) {
                top = stack.top;
                size = stack.size;
            }
        }

        Stack<T>& operator=(const Stack<T>& rhs) {
            if(&rhs != this) {
                top = rhs.top;
                size = rhs.size;
            }
            return *this;
        }

        Stack<T>& push(const T& item) {
            if(top != nullptr) {
                Item* temp = new Item(item, top);
                top = temp;
            } else {
                top = new Item(item, nullptr);
            }
            size++;

            return *this;
        }

        T pop() {
            if(top != nullptr) {
                size--;
                Item* temp = top;
                top = top->next;
                return temp->data;
            }
            throw std::out_of_range("Attempted to pop an empty stack");
        }

        T peek() const {
            if(top != nullptr) {
                return top->data;
            }
            throw std::out_of_range("Attempted to peek an empty stack");
        }

        bool isEmpty() const { return size == 0; }

        int getSize() const { return size; }
    };
}

#endif //UTILITYCODE_STACK_H
