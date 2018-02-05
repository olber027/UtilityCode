//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/TestDriver.h"
#include "../TestDrivers/LinkedListTestDriver.h"
#include <iostream>

using namespace std;

int main(int argc, char** argv) {

    LinkedListTestDriver* driver = new LinkedListTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}