//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/TestDriver.h"
#include "../TestDrivers/SmartStringTestDriver.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    auto* driver = new SmartStringTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}