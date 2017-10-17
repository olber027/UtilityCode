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
        int precision = 5;

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

        int charToDigit(char c) {
            return ((int) c) - 48;
        }

        template<typename T>
        T abs(T val) {
            if(val < 0) {
                val *= -1;
            }
            return val;
        }

        int getNumArguments() {
            int location = -1;
            int count = 0;
            do {
                SmartString arg;
                arg << "{" << count << "}";
                location = this->findSubstring(arg);
                if(location >= 0) {
                    count++;
                }
            } while(location >= 0);
            return count;
        }

    public:
        SmartString() : backingString(nullptr), stringSize(0), precision(5) { }
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
                precision = other.precision;
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
                precision = rhs.precision;
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

        SmartString& append(SmartString& str) {
            return append(str.str());
        }

        SmartString& prepend(SmartString& str) {
            return prepend(str.str());
        }

        SmartString& append(const std::string& str) {
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

        SmartString& prepend(const std::string& str) {
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
            SmartString temp("");
            temp.append(val);
            return prepend(temp);
        }

        SmartString& append(const double val, const int precision) {
            SmartString temp("");
            int leftOfDecimal = (int) val;

            temp.append(leftOfDecimal);
            temp.append(".");

            double rightOfDecimal = abs(val) - abs(leftOfDecimal);
            for(int i = 0; i < precision; i++) {
                int digit = (int) (rightOfDecimal * 10);
                temp.append(digitToChar(digit));
                rightOfDecimal = (rightOfDecimal*10) - digit;
            }
            return append(temp);
        }

        SmartString& append(const double val) {
            /*
             * Any trailing zeroes will be removed when this method is used,
             * unless there are only trailing zeroes, in which case one zero
             * will be left. If you would like to include trailing zeroes,
             * use the append method which specifies the precision.
             */
            append(val, precision);
            char lastDigit = backingString[stringSize-1];
            if(lastDigit == '0') {
                rstrip(lastDigit);
            }
            return *this;
        }

        SmartString& prepend(const double val, const int precision) {
            SmartString temp("");
            temp.append(val, precision);
            return prepend(temp);
        }

        SmartString& prepend(const double val) {
            return prepend(val, 5);
        }

        SmartString& append(const float val, const int precision) {
            SmartString temp("");
            int leftOfDecimal = (int) val;

            temp.append(leftOfDecimal);
            temp.append(".");

            float rightOfDecimal = val - leftOfDecimal;
            for(int i = 0; i < precision; i++) {
                int digit = (int) rightOfDecimal * 10;
                temp.append(digitToChar(digit));
                rightOfDecimal = (rightOfDecimal*10) - digit;
            }
            return append(temp);
        }

        SmartString& append(const float val) {
            return append(val, 5);
        }

        SmartString& prepend(const float val, const int precision) {
            SmartString temp("");
            temp.append(val, precision);
            return prepend(temp);
        }

        SmartString& prepend(const float val) {
            return prepend(val, 5);
        }

        template<typename T>
        SmartString& operator<<(const T& t) {
            append(t);
            return *this;
        }

        SmartString& operator<<(SmartString& str) {
            append(str);
            return *this;
        }

        template<typename T>
        SmartString& operator+=(const T& t) {
            append(t);
        }

        SmartString& operator+=(SmartString& str) {
            return append(str);
        }

        template<typename T>
        SmartString operator+(const T& t) {
            SmartString result(backingString);
            result.append(t);
            return result;
        }

        SmartString operator+(SmartString& str) {
            SmartString result(backingString);
            result.append(str);
            return result;
        }

        bool operator!=(SmartString& str) {
            return !(*this == str);
        }

        template<typename T>
        bool operator!=(T str) {
            SmartString rhs = str;
            return (*this != rhs);
        }

        bool operator==(SmartString& str) {
            return this->str() == str.str();
        }

        template<typename T>
        bool operator==(T str) {
            SmartString rhs = str;
            return (*this == rhs);
        }

        bool operator<(SmartString& str) {
            return (this->str() < str.str());
        }

        template<typename T>
        bool operator<(T str) {
            SmartString rhs = str;
            return (*this < rhs);
        }

        bool operator<=(SmartString& str) {
            return (this->str() <= str.str());
        }

        template<typename T>
        bool operator<=(T str) {
            SmartString rhs = str;
            return (*this <= rhs);
        }

        bool operator>(SmartString& str) {
            return (this->str() > str.str());
        }

        template<typename T>
        bool operator>(T str) {
            SmartString rhs = str;
            return (*this > rhs);
        }

        bool operator>=(SmartString& str) {
            return (this->str() >= str.str());
        }

        template<typename T>
        bool operator>=(T str) {
            SmartString rhs = str;
            return (*this >= rhs);
        }

        char& operator[](const int index) {
            return backingString[index];
        }

        template<typename T> friend
        T operator+(const T left, SmartString& right) {
            SmartString result(left);
            result.append(right);
            return (T) result;
        }

        template<typename T> friend
        bool operator==(const T left, SmartString& right) {
            return (right == left);
        }

        template<typename T> friend
        bool operator!=(const T left, SmartString& right) {
            return (right != left);
        }

        template<typename T> friend
        bool operator<(const T left, SmartString& right) {
            return (right > left);
        }

        template<typename T> friend
        bool operator>(const T left, SmartString& right) {
            return (right < left);
        }

        template<typename T> friend
        bool operator<=(const T left, SmartString& right) {
            return (right >= left);
        }

        template<typename T> friend
        bool operator>=(const T left, SmartString& right) {
            return (right <= left);
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

        bool setPrecision(int newPrecision) {
            if(newPrecision >= 0) {
                precision = newPrecision;
                return true;
            }
            return false;
        }

        int getPrecision() {
            return precision;
        }

        // start and end are both inclusive.
        SmartString getSubstring(int start, int end) {
            SmartString result("");
            for(int i = start; i <= end; i++) {
                result.append(backingString[i]);
            }
            return result;
        }

        template<typename T>
        T getSubstring(int start, int end) {
            return (T) getSubstring(start, end);
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

        template<typename T>
        bool contains(T target) {
            return findSubstring(target) >= 0;
        }

        template<typename T>
        int count(T target) {
            int numInstances = 0;
            SmartString temp(*this);
            SmartString targ(target);
            int location = temp.findSubstring(targ);
            while(location >= 0) {
                numInstances++;
                temp.remove(0, location + targ.length() - 1);
                location = temp.findSubstring(targ);
            }
            return numInstances;
        }

        template<typename T, typename U>
        std::vector<T> split(U target) {
            std::vector<T> result = std::vector<T>();
            SmartString temp(*this);
            SmartString targ(target);
            int location = temp.findSubstring(targ);
            while(location >= 0) {
                result.push_back(temp.getSubstring<T>(0, location-1));
                temp.remove(0, location + targ.length() - 1);
                location = temp.findSubstring(targ);
            }
            if(temp.length() > 0) {
                result.push_back((T) temp);
            }
            return result;
        }

        template<typename T, typename U, typename V> static
        T join(std::vector<U> list, V separator) {
            SmartString temp("");
            for(int i = 0; i < list.size()-1; i++) {
                temp.append(list[i]);
                temp.append(separator);
            }
            temp.append(list[list.size()-1]);
            return (T) temp;
        }

        template<typename T, typename U, typename V> static
        T join(U* list, int listSize, V separator) {
            SmartString temp("");
            for(int i = 0; i < listSize-1; i++) {
                temp.append(list[i]);
                temp.append(separator);
            }
            temp.append(list[listSize-1]);
            return (T) temp;
        }

        SmartString& lstrip() {
            lstrip(whitespace());
            return *this;
        }

        SmartString& rstrip() {
            rstrip(whitespace());
            return *this;
        }

        SmartString& strip() {
            lstrip(whitespace());
            rstrip(whitespace());
            return *this;
        }

        template<typename T>
        SmartString& lstrip(T chars) {
            SmartString toStrip = chars;
            int index = 0;
            while(index < stringSize && toStrip.contains(backingString[index])) {
                index++;
            }
            remove(0, index-1);
            return *this;
        }

        template<typename T>
        SmartString& rstrip(T chars) {
            SmartString toStrip = chars;
            int index = stringSize-1;
            while(index >= 0 && toStrip.contains(backingString[index])) {
                index--;
            }
            remove(index+1, stringSize-1);
            return *this;
        }

        template<typename T>
        SmartString& strip(T chars) {
            lstrip(chars);
            rstrip(chars);
            return *this;
        }

        // start and end are both inclusive.
        SmartString& remove(int start, int end) {
            SmartString temp("");
            for(int i = 0; i < length(); i++) {
                if(i < start || i > end) {
                    temp.append(backingString[i]);
                }
            }
            *this = temp;
            return *this;
        }

        SmartString& remove(SmartString& target) {
            SmartString blank = "";
            return replace(target, blank);
        }

        template<typename T>
        SmartString& remove(T target) {
            SmartString targ(target);
            return remove(targ);
        }

        SmartString& removeAll(SmartString& target) {
            bool changed = false;
            do {
                SmartString old = *this;
                remove(target);
                changed = (old != *this);
            } while(changed);
            return *this;
        }

        template<typename T>
        SmartString& removeAll(T target) {
            SmartString targ(target);
            return removeAll(targ);
        }

        SmartString& replace(SmartString& target, SmartString& newSubstring) {
            int newSize = stringSize + newSubstring.length() - target.length();
            char* tempPointer = new char[newSize+1];

            int location = findSubstring(target);
            if(location < 0) {
                return *this;
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

            return *this;
        }

        template<typename T, typename U>
        SmartString& replace(T target, U newSubstring) {
            SmartString targ(target); SmartString newSubstr(newSubstring);
            return replace(targ, newSubstr);
        }

        SmartString& replaceAll(SmartString& target, SmartString& newSubstring) {
            bool changed = false;
            do {
                SmartString old = *this;
                replace(target, newSubstring);
                changed = (old != *this);
            } while(changed);

            return *this;
        }

        template<typename T, typename U>
        SmartString& replaceAll(T target, U newSubstring) {
            SmartString targ(target); SmartString newSubstr(newSubstring);
            return replaceAll(targ, newSubstr);
        }

        SmartString format(...) {
            int numArgs = getNumArguments();
            va_list arguments;
            va_start(arguments, nullptr);
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
            int numArgs = result.getNumArguments();
            va_list arguments;
            va_start(arguments, nullptr);
            for(int i = 0; i < numArgs; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                result.replaceAll(target, argument);
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
                result.replaceAll(target, argument);
            }
            va_end(arguments);

            return (T) result;
        }

        template<typename T, typename U> static
        T format(U str, ...) {
            SmartString result(str);
            int count = result.getNumArguments();

            va_list(arguments);
            va_start(arguments, str);
            for(int i = 0; i < count; i++) {
                SmartString target;
                target << "{" << i << "}";
                char* argument = va_arg(arguments, char*);
                result.replaceAll(target, argument);
            }
            va_end(arguments);

            return (T) result;
        }

        SmartString& toUpper() {
            for(int i = 0; i < length(); i++) {
                int letterVal = (int) backingString[i];
                if(letterVal > 96 && letterVal < 123) {
                    backingString[i] = (char) (letterVal - 32);
                }
            }
            return *this;
        }

        SmartString& toLower() {
            for(int i = 0; i < length(); i++) {
                int letterVal = (int) backingString[i];
                if(letterVal > 64 && letterVal < 91) {
                    backingString[i] = (char) (letterVal + 32);
                }
            }
            return *this;
        }

        static SmartString whitespace() {
            SmartString result = " \t\n\r\x0b\x0c";
            return result;
        }

        template<typename T> static
        T whitespace() {
            SmartString result = " \t\n\r\x0b\x0c";
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
