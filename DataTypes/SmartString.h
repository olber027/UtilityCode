//
// Created by molberding on 9/15/2017.
//

#ifndef UTILITYCODE_SMARTSTRING_H
#define UTILITYCODE_SMARTSTRING_H

#include <string>
#include <sstream>
#include <cstdarg>

namespace smart_string {

    class SmartString {
    private:
        char* backingString;
        int stringSize;

        void destroy() {
            if(backingString != nullptr) {
                delete backingString;
                stringSize = 0;
            }
        }

        void initialize(int newSize, char* newString) {
            stringSize = newSize;
            backingString = newString;
        }

        int calculateSize(const char* str) {
            int size = 0;
            while(str[size] != '\0') {
                size++;
            }
            return size;
        }

        char digitToChar(int digit) {
            switch(digit) {
                case 0:
                    return '0';
                case 1:
                    return '1';
                case 2:
                    return '2';
                case 3:
                    return '3';
                case 4:
                    return '4';
                case 5:
                    return '5';
                case 6:
                    return '6';
                case 7:
                    return '7';
                case 8:
                    return '8';
                case 9:
                    return '9';
                default:
                    return '\0';
            }
        }

        template<typename T> T abs(T val) {
            if(val < 0) {
                val *= -1;
            }
            return val;
        }

        int numDigits(int val) {
            int count = 1;
            while(val / 10 > 0) {
                count++;
                val /= 10;
            }
            return count;
        }

    public:
        SmartString() : backingString(nullptr), stringSize(0) {}
        SmartString(SmartString init) {
            if(init.length() == 0) {
                initialize(0, nullptr);
                return;
            }
            initialize(init.length(), new char[init.length()]);
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = init[i];
            }
        }
        SmartString(std::string init) {
            if(init.length() == 0) {
                initialize(0, nullptr);
                return;
            }
            initialize(init.length(), new char[init.length()]);
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = init[i];
            }
        }
        SmartString(const char* init) {
            if(init == nullptr) {
                initialize(0, nullptr);
                return;
            }
            int size = calculateSize(init);
            initialize(size, new char[size]);
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = init[i];
            }
        }
        SmartString(int numChars, char fill) {
            initialize(numChars, new char[numChars]);
            for(int i = 0; i < numChars; i++) {
                backingString[i] = fill;
            }
        }
        SmartString(const SmartString& other) {
            if(&other != this) {
                destroy();
                initialize(other.stringSize, new char[other.stringSize]);
                for(int i = 0; i < stringSize; i++) {
                    backingString[i] = other.backingString[i];
                }
            }
        }
        ~SmartString() {
            destroy();
        }

        operator std::string() { return str(); }
        operator char*() { return c_str(); }

        SmartString operator=(const SmartString& rhs) {
            if(&rhs != this) {
                destroy();
                initialize(rhs.stringSize, new char[rhs.stringSize]);
                for(int i = 0; i < stringSize; i++) {
                    backingString[i] = rhs.backingString[i];
                }
            }
            return *this;
        }

        SmartString operator=(const std::string& rhs) {
            destroy();
            initialize(rhs.length(), new char[rhs.length()]);
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = rhs[i];
            }
            return *this;
        }

        SmartString operator=(const char* rhs) {
            destroy();
            int size = calculateSize(rhs);
            initialize(size, new char[size]);
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = rhs[i];
            }
            return *this;
        }

        SmartString append(std::string str) {
            if(str.length() == 0) {
                return *this;
            }

            int newSize = stringSize + str.length();
            char* tempPointer = new char[newSize];
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i] = backingString[i];
            }
            for(int i = stringSize; i < newSize; i++) {
                tempPointer[i] = str[i - stringSize];
            }

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString prepend(std::string str) {
            if(str.length() == 0) {
                return *this;
            }

            int newSize = stringSize + str.length();
            char* tempPointer = new char[newSize];
            for(int i = 0; i < str.length(); i++) {
                tempPointer[i] = str[i];
            }
            for(int i = str.length(); i < newSize; i++) {
                tempPointer[i] = backingString[i - str.length()];
            }

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString append(SmartString str) {
            return this->append(str.str());
        }

        SmartString prepend(SmartString str) {
            return this->prepend(str.str());
        }

        SmartString append(const char* str) {
            int size = calculateSize(str);
            if(size == 0) {
                return *this;
            }
            int newSize = stringSize + size;
            char* tempPointer = new char[newSize];
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i] = backingString[i];
            }
            for(int i = stringSize; i < newSize; i++) {
                tempPointer[i] = str[i - stringSize];
            }

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString prepend(const char* str) {
            int size = calculateSize(str);
            if(size == 0) {
                return *this;
            }
            int newSize = stringSize + size;
            char* tempPointer = new char[newSize];
            for(int i = 0; i < size; i++) {
                tempPointer[i] = str[i];
            }
            for(int i = size; i < newSize; i++) {
                tempPointer[i] = backingString[i - size];
            }

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString append(char c) {
            int newSize = stringSize + 1;
            char* tempPointer = new char[newSize];
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i] = backingString[i];
            }
            tempPointer[stringSize] = c;

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString prepend(char c) {
            int newSize = stringSize + 1;
            char* tempPointer = new char[newSize];
            tempPointer[0] = c;
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i+1] = backingString[i];
            }

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString append(int val) {

        }

        SmartString append(double val) {

        }

        SmartString append(float val) {

        }

        SmartString operator<<(std::string str) {
            append(str);
            return *this;
        }

        SmartString operator<<(const char* str) {
            append(str);
            return *this;
        }

        SmartString operator<<(int val) {
            append(val);
            return *this;
        }

        SmartString operator<<(double val) {
            append(val);
            return *this;
        }

        SmartString operator<<(float val) {
            append(val);
            return *this;
        }

        SmartString operator+(SmartString str) {
            return append(str);
        }

        SmartString operator+(std::string str) {
            return append(str);
        }

        SmartString operator+(const char* str) {
            return append(str);
        }

        SmartString operator+(char c) {
            return append(c);
        }

        SmartString operator+(int val) {
            return append(val);
        }

        SmartString operator+(double val) {
            return append(val);
        }

        SmartString operator+(float val) {
            return append(val);
        }

        char operator[](int index) {
            return backingString[index];
        }

        friend std::ostream& operator<<(std::ostream& out, SmartString string) {
            out << string.str();
            return out;
        }

        bool replace(std::string target, std::string newSubString) {
            int newSize = stringSize + newSubString.length() - target.length();
            char* tempPointer = new char[newSize];

            int location = findSubstring(target);
            if(location < 0) {
                return false;
            }

            for(int i = 0; i < location; i++) {
                tempPointer[i] = backingString[i];
            }
            for(int i = 0; i < newSubString.length(); i++) {
                tempPointer[location + i] = newSubString[i];
            }
            for(int i = 0; i < stringSize - location + target.length(); i++) {
                tempPointer[location + newSubString.length() + i] = backingString[location + target.length() + i];
            }

            destroy();
            initialize(newSize, tempPointer);

            return true;
        }

        int findSubstring(std::string target) {
            for(int i = 0; i < stringSize; i++) {
                if(target[0] == backingString[i]) {
                    bool match = true;
                    for(int j = 1; j < target.length(); j++) {
                        if(target[j] != backingString[i+j]) {
                            match = false;
                            break;
                        }
                    }
                    if(match) {
                        return i;
                    }
                }
            }
            return -1;
        }

        bool replaceAll(std::string target, std::string newSubString) {
            bool result = false;
            while(replace(target, newSubString)) {
                result = true;
            }
            return result;
        }

        SmartString format(int count, ...) {
            va_list arguments;
            va_start(arguments, count);
            for(int i = 0; i < count; i++) {
                SmartString target;
                target << "{" << i << "}";
                std::string argument = va_arg(arguments, std::string);
                replaceAll(target.str(), argument);
            }
            va_end(arguments);

            return *this;
        }

        std::string str() {
            return std::string(backingString);
        }

        char* c_str() {
            append('\0');
            return backingString;
        }

        int length() {
            return stringSize;
        }
    };

}

#endif //UTILITYCODE_SMARTSTRING_H
