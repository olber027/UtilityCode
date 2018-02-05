//
// Created by molberding on 1/31/2018.
//

#include "../TestDrivers/TestDriver.h"
#include "../TestDrivers/BinaryTreeTestDriver.h"

using namespace std;

int main(int argc, char** argv) {

    BinaryTreeTestDriver* driver = new BinaryTreeTestDriver();

    driver->run();
    cout << driver->getOutput();

    delete driver;

    return 0;
}