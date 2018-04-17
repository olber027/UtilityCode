//
// Created by molberding on 11/30/2017.
//

#ifndef UTILITYCODE_DICTIONARYTESTDRIVER_H
#define UTILITYCODE_DICTIONARYTESTDRIVER_H

#include "../DataStructures/Dictionary.h"
#include "TestDriver.h"
#include <string>
#include <iostream>
#include <vector>

using namespace dictionary;

class DictionaryTestDriver : public TestDriver {
private:

public:
    DictionaryTestDriver() {
        init("Dictionary");
    }

    void run() {
        Dictionary<std::string, int> dict;
        dict.addEntry("one", 1);
        assert(1, dict["one"]);
        dict["one"] = 2;
        assert(2, dict["one"]);
        std::string errorMessage = "no error";
        try {
            dict["two"] = 1;
        } catch (InvalidIndexException<std::string> &e) {
            errorMessage = e.what();
        }
        assert(std::string("Invalid Index : two"), errorMessage);
        dict["one"] = 1;
        assert(true, dict.containsKey("one"));
        assert(false, dict.containsKey("two"));
        assert(true, dict.containsValue(1));
        assert(false, dict.containsValue(2));
        assert(1, dict.getValue("one"));
        assert(std::string("one"), dict.getKey(1));
        try {
            dict.getValue("two");
        } catch (InvalidIndexException<std::string> &e) {
            errorMessage = e.what();
        }
        assert(std::string("Invalid Index : two"), errorMessage);
        try {
            dict.getKey(2);
        } catch (InvalidIndexException<int> &e) {
            errorMessage = e.what();
        }
        assert(std::string("Invalid Index : 2"), errorMessage);

        assert(1, dict.length());
        dict.clear();
        assert(0, dict.length());

        std::vector<std::string> keys = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
        std::vector<int> values = {1,2,3,4,5,6,7,8,9};
        for(int i = 0; i < keys.size(); i++) {
            dict.addEntry(keys[i], values[i]);
        }
        assert(9, dict.length(), "correct number of entries were not added");
        for(int i = keys.size()-1; i >= 0; i--) {
            dict.remove(keys[i]);
            assert(values[i] - 1, dict.length());
        }

        dict.clear();
        assert(0, dict.length(), "dictionary did not clear correctly");
        dict = Dictionary<std::string, int>(keys, values);
        for(int i = 0; i < keys.size(); i++) {
            assert(dict[keys[i]], values[i]);
        }
        assert(9, dict.length(), "correct number of entries were not added");
        for(int i = 0; i < values.size(); i--) {
            dict.remove(values[i]);
            assert(9 - values[i], dict.length());
        }

    }
};

#endif //UTILITYCODE_DICTIONARYTESTDRIVER_H
