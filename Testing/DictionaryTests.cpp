//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/TestDriver.h"
#include "../TestDrivers/DictionaryTestDriver.h"

using namespace std;

int main(int argc, char** argv) {

    DictionaryTestDriver* driver = new DictionaryTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}