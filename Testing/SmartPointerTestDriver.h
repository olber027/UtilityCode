//
// Created by molberding on 9/12/2017.
//

#ifndef UTILITYCODE_SMARTPOINTERTESTDRIVER_H
#define UTILITYCODE_SMARTPOINTERTESTDRIVER_H

#include "../DataTypes/SmartPointer.h"
#include "TestDriver.h"

using namespace smart_pointer;

class TestObject {
private:
    int val;
public:
    TestObject() : val(0) {}
    TestObject(int num) : val(num) {}
    int get() { return val; }
    int set(int num) { val = num; }
};

class SmartPointerTestDriver : public TestDriver {
private:
    SmartPointer<int> intPointer;
    SmartPointer<TestObject> testObjectPointer;
public:

    SmartPointerTestDriver() {
        init("Smart Pointer");
        int* temp = new int(5);
        intPointer = SmartPointer<int>(temp);
        testObjectPointer = SmartPointer<TestObject>(new TestObject(7));
    }

    void run() {
        assert(5, *intPointer);
        assert(7, testObjectPointer->get());
    }
};

#endif //UTILITYCODE_SMARTPOINTERTESTDRIVER_H
