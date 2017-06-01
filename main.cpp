#include "Testing/TestDriver.h"
#include "Testing/LinkedListTestDriver.h"
#include "Testing/SortingTestDriver.h"
#include "SortingAlgorithms/Sort.h"
#include <iostream>
#include <vector>


using namespace std;

int main() {

    TestDriver* driver;

    vector<TestDriver*> testDrivers = vector<TestDriver*>();
    testDrivers.push_back(new LinkedListTestDriver());
    testDrivers.push_back(new SortingTestDriver());

    for(int i = 0; i < testDrivers.size(); i++) {
        driver = testDrivers[i];
        driver->run();
        cout << driver->getOutput();
    }

    return 0;
}