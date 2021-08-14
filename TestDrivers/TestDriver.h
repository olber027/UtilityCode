//
// Created by molberding on 5/25/2017.
//

#ifndef UTILITYCODE_TESTDRIVER_H
#define UTILITYCODE_TESTDRIVER_H

#include <sstream>
#include <string>
#include <vector>
#include <type_traits>

class TestDriver
{
protected:
    int passed;
    int failed;
    int total;
    std::stringstream output;

    explicit TestDriver(const std::string& driverName);

public:
    virtual void run() = 0;

    virtual std::string getOutput();

    virtual int getFailures();

    virtual int getPasses();

    template <typename T, typename U>
    bool assert(T expected, U actual)
    {
        static_assert(std::is_convertible<T, U>::value, "U must be convertible to T");
        bool result = expected == actual;
        if(result)
        {
            passed++;
        }
        else
        {
            output << "TestFailed\n__________\n";
            output << "\texpected: " << expected << "\n\tactual  : " << actual << std::endl;
            failed++;
        }
        total++;
        return result;
    }

    template <typename T, typename U>
    bool assert(T expected, U actual, const char* message)
    {
        static_assert(std::is_convertible<T, U>::value, "U must be convertible to T");
        bool result = expected == actual;
        if(result)
        {
            passed++;
        }
        else
        {
            output << "TestFailed\n__________\n";
            output << "\texpected: " << expected << "\n\tactual  : " << actual << std::endl;
            output << "\tmessage : " << message << std::endl;
            failed++;
        }
        total++;
        return result;
    }

    template <typename T, typename U>
    bool assert_vector(const std::vector<T>& expected, const std::vector<U>& actual, const char* message)
    {
        static_assert(std::is_convertible<T, U>::value, "U must be convertible to T");
        total++;
        if(expected.size() != actual.size())
        {
            output << "TestFailed\n__________\n";
            output << "\texpected vector of size " << actual.size() << ". got " << expected.size() << std::endl;
            output << "\tmessage : " << message << std::endl;
            failed++;
            return false;
        }
        for(int i = 0; i < expected.size(); i++)
        {
            if(expected[i] != actual[i])
            {
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

#endif//UTILITYCODE_TESTDRIVER_H
