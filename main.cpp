#include "Testing/TestDriver.h"
#include "Testing/LinkedListTestDriver.h"
#include "Testing/SortingTestDriver.h"
#include "Testing/GraphTestDriver.h"
#include "Testing/StackTestDriver.h"
#include "Testing/BinaryTreeTestDriver.h"
#include "Testing/SmartPointerTestDriver.h"
#include <iostream>


using namespace std;

int main() {

    TestDriver* driver;

    vector<TestDriver*> testDrivers = vector<TestDriver*>();
    testDrivers.push_back(new LinkedListTestDriver());
    testDrivers.push_back(new SortingTestDriver());
    testDrivers.push_back(new GraphTestDriver());
    testDrivers.push_back(new StackTestDriver());
    testDrivers.push_back(new BinaryTreeTestDriver());
    testDrivers.push_back(new SmartPointerTestDriver());

    for(int i = 0; i < testDrivers.size(); i++) {
        driver = testDrivers[i];
        driver->run();
        cout << driver->getOutput();
    }

//    for(int i = 0; i < testDrivers.size(); i++) {
//        delete testDrivers[i];
//    }

    return 0;
}