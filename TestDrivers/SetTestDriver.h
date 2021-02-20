//
// Created by molberding on 1/15/2018.
//

#ifndef UTILITYCODE_SETTESTDRIVER_H
#define UTILITYCODE_SETTESTDRIVER_H

#include "DataStructures/Set.h"
#include "TestDriver.h"

using namespace Utilities;

class SetTestDriver : public TestDriver
{
private:
    class TestItem
    {
    public:
        explicit TestItem(int d) : data(d) {}
        int data;
    };

public:
    SetTestDriver();

    void run() override;
};

#endif//UTILITYCODE_SETTESTDRIVER_H
