#include "Testing/TestDriver.h"
#include "Testing/LinkedListTestDriver.h"
#include "SortingAlgorithms/Sort.h"
#include <iostream>
#include <vector>


using namespace std;

int main() {

    TestDriver* driver;

    vector<TestDriver*> testDrivers = vector<TestDriver*>();
    testDrivers.push_back(new LinkedListTestDriver());

    for(int i = 0; i < testDrivers.size(); i++) {
        driver = testDrivers[i];
        driver->run();
        cout << driver->getOutput();
    }

    int arr[] = {3,7,8,5,2,1,9,5,4};
    int size = 9;
    cout << "[ ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
    Sort::quicksort<int>(arr, 9);
    cout << "[ ";
    for(int i = 0; i < size; i++) {
        cout << arr[i] << " ";
    }
    cout << "]" << endl;
    return 0;
}