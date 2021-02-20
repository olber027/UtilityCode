//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/SmartPointerTestDriver.h"
#include "../TestDrivers/TestDriver.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv)
{
    auto* driver = new SmartPointerTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}