//
// Created by olber on 2/20/2021.
//
#include "SmartPointerTestDriver.h"

SmartPointerTestDriver::SmartPointerTestDriver() : TestDriver("Smart Pointer") {}

void SmartPointerTestDriver::run()
{
    int* temp                                  = new int(5);
    SmartPointer<int> intPointer               = SmartPointer<int>(temp);
    SmartPointer<TestObject> testObjectPointer = SmartPointer<TestObject>(new TestObject(7));

    assert(5, *intPointer);
    assert(7, testObjectPointer->get());
    for(int i = 0; i < 5; i++)
    {
        SmartPointer<TestObject> tempObjectPointer = testObjectPointer;
        assert(7, tempObjectPointer->get());
    }
    assert(7, testObjectPointer->get());
    SmartPointer<TestObject> newPointer = SmartPointer<TestObject>(new TestObject(11));
    assert(11, newPointer->get());
    testObjectPointer = newPointer;
    assert(11, testObjectPointer->get());
    SmartPointer<TestObject> pointer1 = testObjectPointer;
    assert(11, pointer1->get());
    SmartPointer<TestObject> pointer2 = testObjectPointer;
    assert(11, pointer2->get());
    SmartPointer<TestObject> pointer3 = testObjectPointer;
    assert(11, pointer3->get());
    SmartPointer<TestObject> pointer4 = testObjectPointer;
    assert(11, pointer4->get());
    newPointer.destroy();
    assert(11, pointer1->get());
    assert(11, pointer2->get());
    assert(11, pointer3->get());
    assert(11, pointer4->get());
    testObjectPointer.destroy();
    assert(11, pointer1->get());
    assert(11, pointer2->get());
    assert(11, pointer3->get());
    assert(11, pointer4->get());
    pointer1.destroy();
    assert(11, pointer2->get());
    assert(11, pointer3->get());
    assert(11, pointer4->get());
    pointer2.destroy();
    assert(11, pointer3->get());
    assert(11, pointer4->get());
    pointer3.destroy();
    assert(11, pointer4->get());
    TestObject* dumbPointer = pointer4.getPointer();
    assert(11, dumbPointer->get());
    assert(1, pointer4.numReferences());
    pointer4.destroy();
}
