//
// Created by molberding on 9/12/2017.
//

#ifndef UTILITYCODE_SMARTPOINTERTESTDRIVER_H
#define UTILITYCODE_SMARTPOINTERTESTDRIVER_H

#include "DataTypes/SmartPointer.h"
#include "TestDriver.h"

using namespace Utilities;

class TestObject
{
private:
    int val;

public:
    TestObject() : val(0) {}
    explicit TestObject(int num) : val(num) {}
    int get() const { return val; }
    void set(int num) { val = num; }
};

class SmartPointerTestDriver : public TestDriver
{
public:
    SmartPointerTestDriver();

    void run() override;
};

#endif//UTILITYCODE_SMARTPOINTERTESTDRIVER_H
