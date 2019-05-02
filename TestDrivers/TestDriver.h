//
// Created by molberding on 5/25/2017.
//

#ifndef UTILITYCODE_TESTDRIVER_H
#define UTILITYCODE_TESTDRIVER_H

#include <string>
#include <vector>
#include <sstream>

class TestDriver {
protected:
    int passed;
    int failed;
    int total;
    std::stringstream output;
public:
    virtual void run() = 0;

    virtual void init(const std::string& driverName) {
        passed = 0;
        failed = 0;
        total = 0;

        output = std::stringstream();
        for(int i = 0; i < 80; i++) {
            output << "=";
        }
        output << std::endl << "Start of " << driverName << " TestDrivers\n";
        for(int i = 0; i < 80; i++) {
            output << "=";
        }
        output << std::endl;
    }

    virtual std::string getOutput() {
        output << "Test Run Results were:";
        output << "\n\tpassed: " << passed;
        output << "\n\tfailed: " << failed;
        output << "\n\ttotal: " << total << std::endl;
        return output.str();
    }

    virtual int getFailures() {
        return failed;
    }

    virtual int getPasses() {
        return passed;
    }

    template<typename T> bool assert(T expected, T actual) {
        bool result = expected == actual;
        if(result) {
            passed++;
        } else {
            output << "TestFailed\n__________\n";
            output << "\texpected: " << expected << "\n\tactual  : " << actual << std::endl;
            failed++;
        }
        total++;
        return result;
    }

    template<typename T> bool assert(T expected, T actual, const char* message) {
        bool result = expected == actual;
        if(result) {
            passed++;
        } else {
            output << "TestFailed\n__________\n";
            output << "\texpected: " << expected << "\n\tactual  : " << actual << std::endl;
            output << "\tmessage : " << message << std::endl;
            failed++;
        }
        total++;
        return result;
    }

    template<typename T>
    bool assert_vector(const std::vector<T>& expected, const std::vector<T>& actual, const char* message) {
        total++;
        if(expected.size() != actual.size()) {
            output << "TestFailed\n__________\n";
            output << "\texpected vector of size " << actual.size() << ". got " << expected.size() << std::endl;
            output << "\tmessage : " << message << std::endl;
            failed++;
            return false;
        }
        for(int i = 0; i < expected.size(); i++) {
            if(expected[i] != actual[i]) {
                output << "TestFailed\n__________\n";
                output << "\telement " << i << " did not match." << std::endl;
                output << "\texpected: " << expected[i] << std::endl;
                output << "\tactual  : " << actual[i] << std::endl;
                output << "\tmessage : " << message << std::endl;
                failed++;
                return false;
            }
        }
        passed++;
        return true;
    }
};

#endif //UTILITYCODE_TESTDRIVER_H
