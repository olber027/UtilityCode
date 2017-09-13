//
// Created by molberding on 9/12/2017.
//

#ifndef UTILITYCODE_SMARTPOINTER_H
#define UTILITYCODE_SMARTPOINTER_H

#include <iostream>

namespace smart_pointer {

    template<typename T>
    class SmartPointer {
    private:

        class ReferenceCounter {
        private:
            int numReferences;
        public:
            ReferenceCounter() : numReferences(0) {}
            ReferenceCounter(int init) : numReferences(init) {}
            int addRef() { return ++numReferences; }
            int removeRef() { return --numReferences; }
            int getNumReferences() { return numReferences; }
        };

        T* pointer;
        ReferenceCounter* referenceCounter;

    public:
        SmartPointer() : pointer(nullptr) {
            referenceCounter = new ReferenceCounter();
        }

        SmartPointer(T* val) : pointer(val) {
            referenceCounter = new ReferenceCounter(1);
        }

        SmartPointer(const SmartPointer<T>& smartPointer) {
            pointer = smartPointer.pointer;
            referenceCounter = smartPointer.referenceCounter;
            referenceCounter->addRef();
        }

        void destroy() {
            if(referenceCounter->removeRef() == 0) {
                delete referenceCounter;
                delete pointer;
                pointer = nullptr;
            }
        }

        ~SmartPointer() {
            destroy();
        }

        T& operator*() { return *pointer; }
        T* operator->() { return pointer; }
        T* getPointer() { return pointer; }
        int numReferences() { return referenceCounter->getNumReferences(); }

        SmartPointer<T>& operator=(const SmartPointer<T>& rhs) {
            if(&rhs != this) {
                destroy();

                pointer = rhs.pointer;
                referenceCounter = rhs.referenceCounter;
                referenceCounter->addRef();
            }
            return *this;
        }
    };
}

#endif //UTILITYCODE_SMARTPOINTER_H
