//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/DictionaryTestDriver.h"
#include "../TestDrivers/TestDriver.h"

using namespace std;

int main(int argc, char** argv)
{
    auto* driver = new DictionaryTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}