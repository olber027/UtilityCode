//
// Created by molberding on 9/12/2017.
//

#ifndef UTILITYCODE_SMARTPOINTER_H
#define UTILITYCODE_SMARTPOINTER_H

namespace smart_pointer {

    template<typename T>
    class SmartPointer {
    private:

        class ReferenceCounter {
        private:
            int numReferences;
        public:
            ReferenceCounter() : numReferences(0) {}
            ReferenceCounter(const int init) : numReferences(init) {}
            int addRef() { return ++numReferences; }
            int removeRef() { return --numReferences; }
            int getNumReferences() const { return numReferences; }
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

        SmartPointer(const SmartPointer<T>& smartPointer) : SmartPointer() {
            if(&smartPointer != this) {
                destroy();
                pointer = smartPointer.pointer;
                referenceCounter = smartPointer.referenceCounter;
                referenceCounter->addRef();
            }
        }

        SmartPointer<T>& operator=(const SmartPointer<T>& rhs) {
            if(&rhs != this) {
                destroy();
                pointer = rhs.pointer;
                referenceCounter = rhs.referenceCounter;
                referenceCounter->addRef();
            }
            return *this;
        }

        void destroy() {
            if(referenceCounter != nullptr && referenceCounter->removeRef() == 0) {
                delete referenceCounter;
                delete pointer;
            }
            pointer = nullptr;
            referenceCounter = nullptr;
        }

        ~SmartPointer() {
            destroy();
        }

        T& operator*() const { return *pointer; }
        T* operator->() const { return pointer; }
        T* getPointer() const { return pointer; }
        int numReferences() const { return referenceCounter->getNumReferences(); }

    };
}

#endif //UTILITYCODE_SMARTPOINTER_H
