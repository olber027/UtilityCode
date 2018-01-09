#include "Testing/TestDriver.h"
#include "Testing/LinkedListTestDriver.h"
#include "Testing/SortingTestDriver.h"
#include "Testing/GraphTestDriver.h"
#include "Testing/StackTestDriver.h"
#include "Testing/BinaryTreeTestDriver.h"
#include "Testing/SmartPointerTestDriver.h"
#include "Testing/SmartStringTestDriver.h"
#include "Testing/DictionaryTestDriver.h"

using namespace std;

int main(int argc, char** argv) {


    vector<TestDriver*> testDrivers = vector<TestDriver*>();
    testDrivers.push_back(new LinkedListTestDriver());
    testDrivers.push_back(new SortingTestDriver());
    testDrivers.push_back(new GraphTestDriver());
    testDrivers.push_back(new BinaryTreeTestDriver());
    testDrivers.push_back(new StackTestDriver());
    testDrivers.push_back(new SmartPointerTestDriver());
    testDrivers.push_back(new SmartStringTestDriver());
    testDrivers.push_back(new DictionaryTestDriver());

    int totalFailures = 0;
    int totalPasses = 0;

    for(int i = 0; i < testDrivers.size(); i++) {
        testDrivers[i]->run();
        cout << testDrivers[i]->getOutput();
        totalFailures += testDrivers[i]->getFailures();
        totalPasses += testDrivers[i]->getPasses();
    }

    for(int i = 0; i < 80; i++) {
        cout << "=";
    }
    cout << endl << "Run Summary" << endl;
    for(int i = 0; i < 80; i++) {
        cout << "=";
    }
    cout << endl << "Total Passes:   " << totalPasses << endl;
    cout <<         "Total Failures: " << totalFailures << endl;

    for(int i = 0; i < testDrivers.size(); i++) {
        delete testDrivers[i];
    }

    return 0;
}