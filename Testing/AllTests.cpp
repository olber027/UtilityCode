#include "../TestDrivers/TestDriver.h"
#include "../TestDrivers/LinkedListTestDriver.h"
#include "../TestDrivers/SortingTestDriver.h"
#include "../TestDrivers/GraphTestDriver.h"
#include "../TestDrivers/StackTestDriver.h"
#include "../TestDrivers/BinaryTreeTestDriver.h"
#include "../TestDrivers/SmartPointerTestDriver.h"
#include "../TestDrivers/SmartStringTestDriver.h"
#include "../TestDrivers/DictionaryTestDriver.h"
#include "../TestDrivers/SetTestDriver.h"

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
    testDrivers.push_back(new SetTestDriver());

    int totalFailures = 0;
    int totalPasses = 0;

    for(const auto& driver : testDrivers) {
        driver->run();
        cout << driver->getOutput();
        totalFailures += driver->getFailures();
        totalPasses += driver->getPasses();
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

    for(auto& driver : testDrivers) {
        delete driver;
    }

    return 0;
}