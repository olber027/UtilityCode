//
// Created by molberding on 1/31/2018.
//

#include <TestDrivers/DictionaryTestDriver.h>
#include <iostream>

int main(int argc, char** argv)
{
    auto* driver = new DictionaryTestDriver();

    driver->run();
    std::cout << driver->getOutput();

    delete driver;

    return 0;
}