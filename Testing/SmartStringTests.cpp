//
// Created by molberding on 1/31/2018.
//
#include <TestDrivers/SmartStringTestDriver.h>
#include <iostream>

int main(int argc, char** argv)
{
    auto* driver = new SmartStringTestDriver();

    driver->run();
    std::cout << driver->getOutput();

    delete driver;

    return 0;
}