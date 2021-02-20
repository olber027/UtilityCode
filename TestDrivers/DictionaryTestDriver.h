//
// Created by molberding on 11/30/2017.
//

#ifndef UTILITYCODE_DICTIONARYTESTDRIVER_H
#define UTILITYCODE_DICTIONARYTESTDRIVER_H

#include "DataStructures/Dictionary.h"
#include "TestDriver.h"
#include <iostream>
#include <string>
#include <vector>

using namespace Utilities;

class DictionaryTestDriver : public TestDriver
{
private:
public:
    DictionaryTestDriver();

    void run() override;
};

#endif//UTILITYCODE_DICTIONARYTESTDRIVER_H
