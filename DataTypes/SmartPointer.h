//
// Created by molberding on 9/12/2017.
//

#ifndef UTILITYCODE_SMARTPOINTER_H
#define UTILITYCODE_SMARTPOINTER_H

namespace smart_pointer {

    template<typename T>
    class SmartPointer {
    private:
        T* pointer;
        int numReferences;
    public:
        SmartPointer() : pointer(nullptr), numReferences(0) { }
        SmartPointer(T* val) : pointer(val), numReferences(1) { }
        SmartPointer(T val) : pointer(new T(val)), numReferences(1) { }

        T& operator*() {
            return *pointer;
        }

        T* operator->() {
            return pointer;
        }
    };
}

#endif //UTILITYCODE_SMARTPOINTER_H
