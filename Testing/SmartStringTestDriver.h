//
// Created by molberding on 9/18/2017.
//

#ifndef UTILITYCODE_SMARTSTRINGTESTDRIVER_H
#define UTILITYCODE_SMARTSTRINGTESTDRIVER_H

#include "../DataTypes/SmartString.h"
#include "TestDriver.h"

using namespace smart_string;

class SmartStringTestDriver : public TestDriver {
private:
    SmartString smartString;
    std::string standardString;
public:
    SmartStringTestDriver() {
        init("Smart String");
        smartString = SmartString("this is {0}");
        standardString = "a test";
    }

    void run() {

    }
};
#endif //UTILITYCODE_SMARTSTRINGTESTDRIVER_H
