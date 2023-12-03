//
// Created by molberding on 9/18/2017.
//

#ifndef UTILITYCODE_SMARTSTRINGTESTDRIVER_H
#define UTILITYCODE_SMARTSTRINGTESTDRIVER_H

#include "DataTypes/SmartString.h"
#include "TestDriver.h"
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <array>

using namespace Utilities;

class SmartStringTestDriver : public TestDriver
{
public:
    SmartStringTestDriver();

    void testConstructors();

    void testAppendPrepend();

    void testOperators();

    void testReplaceAndFormat();

    void testRemove();

    void testSubstrings();

    void testMiscFunctions();

    void testFunctionPassing();

    SmartString getBasicString();

    SmartString& getReferenceString();

    void passBasicString(SmartString test);

    void passReferenceString(SmartString& test);

    void run() override;
};
#endif//UTILITYCODE_SMARTSTRINGTESTDRIVER_H
