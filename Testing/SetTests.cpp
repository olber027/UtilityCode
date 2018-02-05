//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/TestDriver.h"
#include "../TestDrivers/SetTestDriver.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    SetTestDriver* driver = new SetTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}