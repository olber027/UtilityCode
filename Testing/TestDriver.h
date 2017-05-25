//
// Created by molberding on 5/25/2017.
//

#ifndef UTILITYCODE_TESTDRIVER_H
#define UTILITYCODE_TESTDRIVER_H

#include <string>
#include <sstream>

class TestDriver {
protected:
    int passed;
    int failed;
    int total;
    std::stringstream output;
public:
    virtual void run() = 0;
    virtual std::string getOutput() {
        output << "Test Run Results were: \n";
        output << "\tpassed: " << passed;
        output << "\n\tfailed: " << failed;
        output << "\n\ttotal: " << total << std::endl;
        return output.str();
    }
    template<typename T> bool assert(T expected, T actual) {
        bool result = expected == actual;
        if(result) {
            passed++;
        } else {
            output << "TestFailed\n__________\n";
            output << "\texpected: " << expected << "\n\tactual: " << actual << std::endl;
            failed++;
        }
        total++;
        return result;
    }
};

#endif //UTILITYCODE_TESTDRIVER_H
