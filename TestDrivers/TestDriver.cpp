//
// Created by olber on 2/17/2021.
//

#include "TestDriver.h"

TestDriver::TestDriver(const std::string& driverName)
{
    passed = 0;
    failed = 0;
    total  = 0;

    output = std::stringstream();
    for(int i = 0; i < 80; i++)
    {
        output << "=";
    }
    output << std::endl
           << "Start of " << driverName << " TestDrivers\n";
    for(int i = 0; i < 80; i++)
    {
        output << "=";
    }
    output << std::endl;
}

std::string TestDriver::getOutput()
{
    output << "Test Run Results were:";
    output << "\n\tpassed: " << passed;
    output << "\n\tfailed: " << failed;
    output << "\n\ttotal: " << total << std::endl;
    return output.str();
}

int TestDriver::getFailures()
{
    return failed;
}

int TestDriver::getPasses()
{
    return passed;
}