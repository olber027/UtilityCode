//
// Created by molberding on 1/31/2018.
//

#include <TestDrivers/StackTestDriver.h>
#include <iostream>

int main(int argc, char** argv)
{
    auto* driver = new StackTestDriver();

    driver->run();
    std::cout << driver->getOutput();

    delete driver;

    return 0;
}