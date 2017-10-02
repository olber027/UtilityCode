//
// Created by molberding on 9/18/2017.
//

#ifndef UTILITYCODE_SMARTSTRINGTESTDRIVER_H
#define UTILITYCODE_SMARTSTRINGTESTDRIVER_H

#include "../DataTypes/SmartString.h"
#include "TestDriver.h"
#include <iostream>
#include <string>

using namespace smart_string;

class SmartStringTestDriver : public TestDriver {
private:
    SmartString smartString;
    std::string standardString;
    char* charStar;
public:
    SmartStringTestDriver() {
        init("Smart String");
        smartString = "this is a {0}";
        standardString = "test";
        charStar = new char[5];
    };

    ~SmartStringTestDriver() {
        std::cout << "in the delete" << std::endl;
        if(charStar != nullptr) {
            delete [] charStar;
        }
        std::cout << "exiting the delete" << std::endl;
    }

    void run() {
        SmartString a;
        SmartString b("b");
        std::string var = "c";
        SmartString c(var);
        SmartString d(5, 'd');
        SmartString e = d;
    }
};
#endif //UTILITYCODE_SMARTSTRINGTESTDRIVER_H
