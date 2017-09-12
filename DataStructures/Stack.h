//
// Created by molberding on 6/27/2017.
//

#ifndef UTILITYCODE_STACK_H
#define UTILITYCODE_STACK_H

namespace stack {

    template<typename T>
    class Stack {
    private:

        class Item {
        public:
            Item(T* dat, Item* n) : data(dat), next(n) {}
            ~Item() {
                if(data != nullptr) {
                    delete data;
                }
            }
            T* data;
            Item* next;
        };

        Item* top;
        int size;

    public:
        Stack() : top(nullptr), size(0) {}
        Stack(T* init) : top(new Item(init, nullptr)), size(1) {}
        ~Stack() {
            if(top) {
                while (top->next) {
                    Item *temp = top->next;
                    delete top;
                    top = temp;
                }
                delete top;
            }
        }

        void cleanup() {
            delete *this;
        }

        Stack(const Stack<T> &stack) {
            if(&stack != this) {
                top = stack.top;
                size = stack.size;
            }
        }

        Stack<T> operator=(const Stack<T> &rhs) {
            if(&rhs != this) {
                top = rhs.top;
                size = rhs.size;
            }
            return *this;
        }

        void push(T* item) {
            if(top != nullptr) {
                Item* temp = new Item(item, top);
                top = temp;
            } else {
                top = new Item(item, nullptr);
            }
            size++;
        }

        void push(T item) {
            T* tempItem = new T;
            *tempItem = item;
            push(tempItem);
        }

        T* pop() {
            if(top != nullptr) {
                size--;
                Item* temp = top;
                top = top->next;
                return temp->data;
            }
            return nullptr;
        }

        T* peek() {
            if(top != nullptr) {
                return top->data;
            }
            return nullptr;
        }

        int getSize() { return size; }
    };
}

#endif //UTILITYCODE_STACK_H
