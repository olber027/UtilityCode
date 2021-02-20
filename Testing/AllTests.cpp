#include "BinaryTreeTestDriver.h"
#include "DictionaryTestDriver.h"
#include "GraphTestDriver.h"
#include "LinkedListTestDriver.h"
#include "SetTestDriver.h"
#include "SmartPointerTestDriver.h"
#include "SmartStringTestDriver.h"
#include "SortingTestDriver.h"
#include "StackTestDriver.h"
#include "TestDriver.h"

#include <memory>
#include <vector>

int main(int argc, char** argv)
{
    std::vector<std::unique_ptr<TestDriver>> testDrivers = std::vector<std::unique_ptr<TestDriver>>();
    testDrivers.push_back(std::make_unique<LinkedListTestDriver>());
    testDrivers.push_back(std::make_unique<SortingTestDriver>());
    testDrivers.push_back(std::make_unique<GraphTestDriver>());
    testDrivers.push_back(std::make_unique<BinaryTreeTestDriver>());
    testDrivers.push_back(std::make_unique<StackTestDriver>());
    testDrivers.push_back(std::make_unique<SmartPointerTestDriver>());
    testDrivers.push_back(std::make_unique<SmartStringTestDriver>());
    testDrivers.push_back(std::make_unique<DictionaryTestDriver>());
    testDrivers.push_back(std::make_unique<SetTestDriver>());

    int totalFailures = 0;
    int totalPasses   = 0;

    for(const auto& driver : testDrivers)
    {
        driver->run();
        std::cout << driver->getOutput();
        totalFailures += driver->getFailures();
        totalPasses += driver->getPasses();
    }

    for(int i = 0; i < 80; i++)
    {
        std::cout << "=";
    }
    std::cout << std::endl
              << "Run Summary" << std::endl;
    for(int i = 0; i < 80; i++)
    {
        std::cout << "=";
    }
    std::cout << std::endl
              << "Total Passes:   " << totalPasses << std::endl;
    std::cout << "Total Failures: " << totalFailures << std::endl;

    return 0;
}