//
// Created by molberding on 9/15/2017.
//

#ifndef UTILITYCODE_SMARTSTRING_H
#define UTILITYCODE_SMARTSTRING_H

#include <string>
#include <cstdarg>

namespace smart_string {

    class SmartString {
    private:
        char* backingString;
        int stringSize;

        void destroy() {
            if(backingString != nullptr) {
                delete [] backingString;
                stringSize = 0;
                backingString = nullptr;
            }
        }

        void initialize(const int size) {
            destroy();
            stringSize = size;
            backingString = new char[stringSize+1];
            backingString[stringSize] = '\0';
        }

        void initialize(int newSize, char* newString) {
            destroy();
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

        int getNumArguments(SmartString& str) {
            int location = -1;
            int count = 0;
            do {
                SmartString arg;
                arg << "{" << count << "}";
                location = str.findSubstring(arg);
                if(location >= 0) {
                    count++;
                }
            } while(location >= 0);
            return count;
        }

    public:
        SmartString() : backingString(nullptr), stringSize(0) { }
        SmartString(const std::string init) : SmartString() {
            if(init.length() != 0) {
                initialize(init.length());
                for (int i = 0; i < stringSize; i++) {
                    backingString[i] = init[i];
                }
            }
        }
        SmartString(const char init) : SmartString() {
            initialize(1);
            stringSize = 1;
            backingString[0] = init;
        }
        SmartString(const char* init) : SmartString() {
            if(init != nullptr) {
                int size = calculateSize(init);
                initialize(size);
                for (int i = 0; i < stringSize; i++) {
                    backingString[i] = init[i];
                }
            }
        }
        SmartString(const int numChars, const char fill) : SmartString() {
            initialize(numChars);
            for(int i = 0; i < numChars; i++) {
                backingString[i] = fill;
            }
        }
        SmartString(const SmartString& other) : SmartString() {
            if(&other != this) {
                destroy();
                initialize(other.stringSize);
                for(int i = 0; i < stringSize; i++) {
                    backingString[i] = other.backingString[i];
                }
            }
        }
        ~SmartString() {
            destroy();
        }

        explicit operator std::string() { return str(); }
        explicit operator char*() { return c_str(); }

        SmartString& operator=(const SmartString& rhs) {
            if(&rhs != this) {
                destroy();
                initialize(rhs.stringSize);
                for(int i = 0; i < stringSize; i++) {
                    backingString[i] = rhs.backingString[i];
                }
            }
            return *this;
        }

        SmartString& operator=(const std::string& rhs) {
            destroy();
            initialize(rhs.length());
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = rhs[i];
            }
            return *this;
        }

        SmartString& operator=(const char* rhs) {
            destroy();
            int size = calculateSize(rhs);
            initialize(size);
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = rhs[i];
            }
            return *this;
        }

        SmartString& append(const std::string str) {
            if(str.length() == 0) {
                return *this;
            }

            int newSize = stringSize + str.length();
            char* tempPointer = new char[newSize+1];
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i] = backingString[i];
            }
            for(int i = stringSize; i < newSize; i++) {
                tempPointer[i] = str[i - stringSize];
            }
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString& prepend(const std::string str) {
            if(str.length() == 0) {
                return *this;
            }

            int newSize = stringSize + str.length();
            char* tempPointer = new char[newSize+1];
            for(int i = 0; i < str.length(); i++) {
                tempPointer[i] = str[i];
            }
            for(int i = str.length(); i < newSize; i++) {
                tempPointer[i] = backingString[i - str.length()];
            }
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString& append(SmartString str) {
            return append(str.str());
        }

        SmartString& prepend(SmartString str) {
            return prepend(str.str());
        }

        SmartString& append(const char* str) {
            int size = calculateSize(str);
            if(size == 0) {
                return *this;
            }
            int newSize = stringSize + size;
            char* tempPointer = new char[newSize+1];
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i] = backingString[i];
            }
            for(int i = stringSize; i < newSize; i++) {
                tempPointer[i] = str[i - stringSize];
            }
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString& prepend(const char* str) {
            int size = calculateSize(str);
            if(size == 0) {
                return *this;
            }
            int newSize = stringSize + size;
            char* tempPointer = new char[newSize+1];
            for(int i = 0; i < size; i++) {
                tempPointer[i] = str[i];
            }
            for(int i = size; i < newSize; i++) {
                tempPointer[i] = backingString[i - size];
            }
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString& append(const char c) {
            int newSize = stringSize + 1;
            char* tempPointer = new char[newSize+1];
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i] = backingString[i];
            }
            tempPointer[stringSize] = c;
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString& prepend(const char c) {
            int newSize = stringSize + 1;
            char* tempPointer = new char[newSize+1];
            tempPointer[0] = c;
            for(int i = 0; i < stringSize; i++) {
                tempPointer[i+1] = backingString[i];
            }
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return *this;
        }

        SmartString& append(const int val) {
            SmartString temp("");
            bool isNegative = val < 0;
            int num = abs(val);
            do {
                int digit = num % 10;
                temp.prepend(digitToChar(digit));
                num /= 10;
            } while ( num > 0 );
            if(isNegative) {
                temp.prepend("-");
            }
            return append(temp);
        }

        SmartString& prepend(const int val) {
            // TODO
        }

        SmartString& append(const double val) {
            // TODO
        }

        SmartString& prepend(const double val) {
            // TODO
        }

        SmartString& append(const float val) {
            // TODO
        }

        SmartString& prepend(const float val) {
            // TODO
        }

        SmartString& operator<<(const std::string& str) {
            append(str);
            return *this;
        }

        SmartString& operator<<(const char* str) {
            append(str);
            return *this;
        }

        SmartString& operator<<(const char c) {
            append(c);
            return *this;
        }

        SmartString& operator<<(const int val) {
            append(val);
            return *this;
        }

        SmartString& operator<<(const double val) {
            append(val);
            return *this;
        }

        SmartString& operator<<(const float val) {
            append(val);
            return *this;
        }

        SmartString& operator+=(SmartString str) {
            return append(str);
        }

        SmartString& operator+=(const std::string str) {
            return append(str);
        }

        SmartString& operator+=(const char* str) {
            return append(str);
        }

        SmartString& operator+=(const char c) {
            return append(c);
        }

        SmartString& operator+=(const int val) {
            return append(val);
        }

        SmartString& operator+=(const double val) {
            return append(val);
        }

        SmartString& operator+=(const float val) {
            return append(val);
        }

        SmartString operator+(const std::string str) {
            SmartString result(backingString);
            result.append(str);
            return result;
        }

        SmartString operator+(const char* str) {
            SmartString result(backingString);
            result.append(str);
            return result;
        }

        SmartString operator+(SmartString str) {
            SmartString result(backingString);
            result.append(str);
            return result;
        }

        SmartString operator+(const char c) {
            SmartString result(backingString);
            result.append(c);
            return result;
        }

        char& operator[](const int index) {
            return backingString[index];
        }

        friend char* operator+(const char* left, SmartString& right) {
            SmartString result(left);
            result.append(right);
            return result.c_str();
        }

        friend std::string operator+(const std::string& left, SmartString& right) {
            SmartString result(left);
            result.append(right);
            return result.str();
        }

        friend std::ostream& operator<<(std::ostream& out, SmartString& string) {
            out << string.str();
            return out;
        }

        friend std::istream& operator>>(std::istream& in, SmartString& string) {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        int findSubstring(SmartString& target) {
            for(int i = 0; i < stringSize; i++) {
                if(target[0] == backingString[i]) {
                    bool match = true;
                    for(int j = 1; j < target.length(); j++) {
                        if(i+j >= stringSize || target[j] != backingString[i+j]) {
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

        template<typename T>
        int findSubstring(T target) {
            SmartString targ(target);
            return findSubstring(targ);
        }

        bool contains(const std::string& target) {
            return findSubstring(target) >= 0;
        }

        bool remove(SmartString& target) {
            SmartString blank = "";
            return replace(target, blank);
        }

        template<typename T>
        bool remove(T target) {
            SmartString targ(target);
            return remove(targ);
        }

        bool removeAll(SmartString& target) {
            bool result = false;
            while(remove(target)) {
                result = true;
            }
            return result;
        }

        template<typename T>
        bool removeAll(T target) {
            SmartString targ(target);
            return removeAll(targ);
        }

        bool replace(SmartString& target, SmartString& newSubstring) {
            int newSize = stringSize + newSubstring.length() - target.length();
            char* tempPointer = new char[newSize+1];

            int location = findSubstring(target);
            if(location < 0) {
                return false;
            }

            for(int i = 0; i < location; i++) {
                tempPointer[i] = backingString[i];
            }
            for(int i = 0; i < newSubstring.length(); i++) {
                tempPointer[location + i] = newSubstring[i];
            }
            for(int i = location + target.length(); i < stringSize; i++) {
                tempPointer[i + newSubstring.length() - target.length()] = backingString[i];
            }
            tempPointer[newSize] = '\0';

            destroy();
            initialize(newSize, tempPointer);

            return true;
        }

        template<typename T, typename U>
        bool replace(T target, U newSubstring) {
            SmartString targ(target); SmartString newSubstr(newSubstring);
            return replace(targ, newSubstr);
        };

        bool replaceAll(SmartString& target, SmartString& newSubstring) {
            bool result = false;
            while(replace(target, newSubstring)) {
                result = true;
            }
            return result;
        }

        template<typename T, typename U>
        bool replaceAll(T target, U newSubstring) {
            SmartString targ(target); SmartString newSubstr(newSubstring);
            return replaceAll(targ, newSubstr);
        };

        SmartString format(...) {
            int numArgs = getNumArguments(*this);
            va_list arguments;
            va_start(arguments, numArgs);
            for(int i = 0; i < numArgs; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                replaceAll(target.str(), argument);
            }
            va_end(arguments);

            return *this;
        }

        SmartString format(int count, ...) {
            va_list arguments;
            va_start(arguments, count);
            for(int i = 0; i < count; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                replaceAll(target.str(), argument);
            }
            va_end(arguments);

            return *this;
        }

        template<typename T>
        T getFormatted(...) {
            SmartString result(*this);
            int numArgs = getNumArguments(result);
            va_list arguments;
            va_start(arguments, numArgs);
            for(int i = 0; i < numArgs; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                result.replaceAll(target.str(), argument);
            }
            va_end(arguments);

            return (T) result;
        }

        template<typename T>
        T getFormatted(int count, ...) {
            SmartString result(*this);
            va_list arguments;
            va_start(arguments, count);
            for(int i = 0; i < count; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                result.replaceAll(target.str(), argument);
            }
            va_end(arguments);

            return (T) result;
        }

        template<typename T, typename U> static
        T format(U str, ...) {
            SmartString result(str);
            int location = -1;
            int count = 0;
            do {
                SmartString arg;
                arg << "{" << count << "}";
                location = result.findSubstring(arg);
                if(location >= 0) {
                    count++;
                }
            } while(location >= 0);

            va_list(arguments);
            va_start(arguments, count);
            for(int i = 0; i < count; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                result.replaceAll(target.str(), argument);
            }
            va_end(arguments);

            return (T) result;
        }

        std::string str() {
            return std::string(backingString);
        }

        char* c_str() {
            char* result = new char[stringSize+1];
            for(int i = 0; i < stringSize+1; i++) {
                result[i] = backingString[i];
            }
            return result;
        }

        int length() {
            return stringSize;
        }
    };
}

#endif //UTILITYCODE_SMARTSTRING_H
