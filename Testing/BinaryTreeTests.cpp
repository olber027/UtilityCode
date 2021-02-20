//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/BinaryTreeTestDriver.h"
#include "../TestDrivers/TestDriver.h"

using namespace std;

int main(int argc, char** argv)
{
    auto* driver = new BinaryTreeTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}