//
// Created by molberding on 9/15/2017.
//

#ifndef UTILITYCODE_SMARTSTRING_H
#define UTILITYCODE_SMARTSTRING_H

#include <string>
#include <cstdarg>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>


namespace smart_string {

    class SmartString {
    private:
        char* backingString;
        int stringSize;
        int precision;
        int memorySize;

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
            memorySize = stringSize+1;
        }

        void extend(const int charsToAdd, const bool addToFront) {
            if(charsToAdd <= 0) {
                return;
            }

            int newSize = stringSize + charsToAdd + 1;
            char* newBackingString = nullptr;

            if(memorySize <= newSize) {
                if (memorySize <= 0) {
                    memorySize = 1;
                }
                while (memorySize <= newSize) {
                    memorySize *= 2;
                }
                newBackingString = new char[memorySize];
            }

            if(newBackingString != nullptr) {
                int offset = 0;
                if(addToFront) {
                    offset += charsToAdd;
                }
                int i = offset;
                for (i; i < stringSize + offset; i++) {
                    newBackingString[i] = backingString[i - offset];
                }
                newBackingString[i] = '\0';
                delete[] backingString;
                backingString = newBackingString;
            } else if(addToFront) {
                for(int i = stringSize; i >= 0; i--) {
                    backingString[i + charsToAdd] = backingString[i];
                }
            }

            stringSize += charsToAdd;
        }

        void extend(const int charsToAdd) {
            extend(charsToAdd, false);
        }

        int calculateSize(const std::string& str) const {
            return str.length();
        }

        int calculateSize(const SmartString& str) const {
            return str.length();
        }

        int calculateSize(const char* str) const {
            int size = 0;
            while(str[size] != '\0') {
                size++;
            }
            return size;
        }

        char digitToChar(const int digit) const {
            return (char) (digit + ((int) '0'));
        }

        static int charToDigit(const char c) {
            return ((int) c) - ((int) '0');
        }

        template<typename T>
        T abs(const T val) const {
            if(val < 0) {
                return (val * -1);
            }
            return val;
        }

        int getNumArguments() const {
            int location;
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
        SmartString() : backingString(nullptr), stringSize(0), precision(5), memorySize(0) { }
        SmartString(const std::string& init) : SmartString() {
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
        SmartString(const std::stringstream& init) : SmartString() {
            std::string str = init.str();
            if(str.length() != 0) {
                initialize(str.length());
                for(int i = 0; i < stringSize; i++) {
                    backingString[i] = str[i];
                }
            }
            precision = init.precision();
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
        SmartString(SmartString&& other) noexcept : SmartString() {
            backingString = other.backingString;
            stringSize = other.stringSize;
            precision = other.precision;
            other.precision = 5;
            other.stringSize = 0;
            other.backingString = nullptr;
        }
        ~SmartString() {
            destroy();
        }

        explicit operator std::string() const { return str(); }
        explicit operator char*() const { return c_str(); }
        explicit operator std::stringstream() const {
            std::stringstream result;
            result << str();
            return result;
        }

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

        SmartString& operator=(SmartString&& rhs) noexcept {
            if(&rhs != this) {
                destroy();
                precision = rhs.precision;
                stringSize = rhs.stringSize;
                backingString = rhs.backingString;
                rhs.precision = 5;
                rhs.stringSize = 0;
                rhs.backingString = nullptr;
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

        SmartString& operator=(const std::stringstream& rhs) {
            destroy();
            std::string str = rhs.str();
            initialize(str.length());
            for(int i = 0; i < stringSize; i++) {
                backingString[i] = str[i];
            }
            return *this;
        }

        template<typename T>
        SmartString& append(const T& str) {
            int numCharactersToAdd = calculateSize(str);
            int initialSize = stringSize;
            extend(numCharactersToAdd);
            for(int i = initialSize; i < stringSize; i++) {
                backingString[i] = str[i-initialSize];
            }
            backingString[stringSize] = '\0';
            return *this;
        }

        template<typename T>
        SmartString& prepend(const T& str) {
            int numCharactersToAdd = calculateSize(str);
            int initialSize = stringSize;
            extend(numCharactersToAdd, true);
            for(int i = 0; i < numCharactersToAdd; i++) {
                backingString[i] = str[i];
            }
            return *this;
        }

        SmartString& append(const SmartString& str) {
            int initialSize = stringSize;
            extend(str.length());
            for(int i = initialSize; i < stringSize; i++) {
                backingString[i] = str[i-initialSize];
            }
            backingString[stringSize] = '\0';
            return *this;
        }

        SmartString& prepend(const SmartString& str) {
            int initialSize = stringSize;
            extend(str.length(), true);
            for(int i = 0; i < str.length(); i++) {
                backingString[i] = str[i];
            }
            return *this;
        }

        SmartString& append(const char c) {
            extend(1);
            backingString[stringSize-1] = c;
            backingString[stringSize] = '\0';

            return *this;
        }

        SmartString& prepend(const char c) {
            extend(1, true);
            backingString[0] = c;

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
                temp.prepend('-');
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
            if(getLast() == '0') {
                rstrip('0');
            }
            if(getLast() == '.') {
                append('0');
            }
            return *this;
        }

        SmartString& prepend(const double val, const int precision) {
            SmartString temp("");
            temp.append(val, precision);
            return prepend(temp);
        }

        SmartString& prepend(const double val) {
            SmartString temp("");
            temp.append(val);
            return prepend(temp);
        }

        SmartString& append(const float val, const int precision) {
            SmartString temp("");
            int leftOfDecimal = (int) abs(val);

            if(val < 0) {
                temp.append("-");
            }
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
            append(val, precision);
            if(getLast() == '0') {
                rstrip('0');
            }
            if(getLast() == '.') {
                append('0');
            }
            return *this;
        }

        SmartString& prepend(const float val, const int precision) {
            SmartString temp("");
            temp.append(val, precision);
            return prepend(temp);
        }

        SmartString& prepend(const float val) {
            SmartString temp("");
            temp.append(val);
            return prepend(temp);
        }

        template<typename T>
        SmartString& operator<<(const T& t) {
            append(t);
            return *this;
        }

        SmartString& operator<<(const SmartString& str) {
            append(str);
            return *this;
        }

        template<typename T>
        SmartString& operator+=(const T& t) {
            append(t);
        }

        SmartString& operator+=(const SmartString& str) {
            return append(str);
        }

        template<typename T>
        SmartString operator+(const T& t) const {
            SmartString result(*this);
            result.append(t);
            return result;
        }

        SmartString operator+(const SmartString& str) const {
            SmartString result(*this);
            result.append(str);
            return result;
        }

        bool operator!=(const SmartString& str) const {
            return !(*this == str);
        }

        template<typename T>
        bool operator!=(const T& str) const {
            SmartString rhs = str;
            return (*this != rhs);
        }

        bool operator==(const SmartString& str) const {
            return this->str() == str.str();
        }

        template<typename T>
        bool operator==(const T& str) const {
            SmartString rhs = str;
            return (*this == rhs);
        }

        bool operator<(const SmartString& str) const {
            return (this->str() < str.str());
        }

        template<typename T>
        bool operator<(const T& str) const {
            SmartString rhs = str;
            return (*this < rhs);
        }

        bool operator<=(const SmartString& str) const {
            return (this->str() <= str.str());
        }

        template<typename T>
        bool operator<=(const T& str) const {
            SmartString rhs = str;
            return (*this <= rhs);
        }

        bool operator>(const SmartString& str) const {
            return (this->str() > str.str());
        }

        template<typename T>
        bool operator>(const T& str) const {
            SmartString rhs = str;
            return (*this > rhs);
        }

        bool operator>=(const SmartString& str) const {
            return (this->str() >= str.str());
        }

        template<typename T>
        bool operator>=(const T& str) const {
            SmartString rhs = str;
            return (*this >= rhs);
        }

        char& operator[](const int index) const {
            return backingString[index];
        }

        template<typename T> friend
        T operator+(const T left, const SmartString& right) {
            SmartString result(left);
            result.append(right);
            return (T) result;
        }

        template<typename T> friend
        bool operator==(const T& left, const SmartString& right) {
            return (right == left);
        }

        template<typename T> friend
        bool operator!=(const T& left, const SmartString& right) {
            return (right != left);
        }

        template<typename T> friend
        bool operator<(const T& left, const SmartString& right) {
            return (right > left);
        }

        template<typename T> friend
        bool operator>(const T& left, const SmartString& right) {
            return (right < left);
        }

        template<typename T> friend
        bool operator<=(const T& left, const SmartString& right) {
            return (right >= left);
        }

        template<typename T> friend
        bool operator>=(const T& left, const SmartString& right) {
            return (right <= left);
        }

        friend std::ostream& operator<<(std::ostream& out, const SmartString& string) {
            out << string.str();
            return out;
        }

        friend std::istream& operator>>(std::istream& in, SmartString& string) {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        friend std::ofstream& operator<<(std::ofstream& out, const SmartString& string) {
            out << string.str();
            return out;
        }

        friend std::ifstream& operator>>(std::ifstream& in, SmartString& string) {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        friend std::fstream& operator<<(std::fstream& out, const SmartString& string) {
            out << string.str();
            return out;
        }

        friend std::fstream& operator>>(std::fstream& in, SmartString& string) {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        friend std::stringstream& operator<<(std::stringstream& out, const SmartString& string) {
            out << string.str();
            return out;
        }

        friend std::stringstream& operator>>(std::stringstream& in, SmartString& string) {
            std::string temp;
            in >> temp;
            string = temp;
            return in;
        }

        bool setPrecision(const int newPrecision) {
            if(newPrecision >= 0) {
                precision = newPrecision;
                return true;
            }
            return false;
        }

        int getPrecision() const {
            return precision;
        }

        char getLast() const {
            if(stringSize > 0) {
                return backingString[stringSize-1];
            }
            return '\0';
        }

        char getFirst() const {
            if(stringSize > 0) {
                return backingString[0];
            }
            return '\0';
        }

        // start and end are both inclusive.
        SmartString getSubstring(const int start, const int end) const {
            SmartString result("");
            for(int i = start; i <= end; i++) {
                result.append(backingString[i]);
            }
            return result;
        }

        template<typename T>
        T getSubstring(const int start, const int end) const {
            return (T) getSubstring(start, end);
        }

        int findSubstring(const int startingLocation, const SmartString& target) const {
            for(int i = startingLocation; i < stringSize && i >= 0; i++) {
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

        int findSubstring(const SmartString& target) const {
            return findSubstring(0, target);
        }

        template<typename T>
        int findSubstring(const T& target) const {
            SmartString targ(target);
            return findSubstring(0, targ);
        }

        template<typename T>
        bool contains(const T& target) const {
            return findSubstring(target) >= 0;
        }

        template<typename T>
        int count(const T& target) const {
            int numInstances = 0;
            SmartString targ(target);
            int location = findSubstring(targ);
            while(location < length()) {
                numInstances++;
                SmartString temp = getSubstring(++location, length());
                int newLocation = temp.findSubstring(targ);
                if(newLocation >= 0) {
                    location += newLocation;
                } else {
                    break;
                }
            }
            return numInstances;
        }

        template<typename T, typename U>
        std::vector<T> split(const U& target) const {
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
        T join(const std::vector<U>& list, const V& separator) {
            SmartString temp("");
            for(int i = 0; i < list.size()-1; i++) {
                temp.append(list[i]);
                temp.append(separator);
            }
            temp.append(list[list.size()-1]);
            return (T) temp;
        }

        template<typename T, typename U, typename V> static
        T join(const U* list, int listSize, const V& separator) {
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
        SmartString& lstrip(const T& chars) {
            SmartString toStrip = chars;
            int index = 0;
            while(index < stringSize && toStrip.contains(backingString[index])) {
                index++;
            }
            remove(0, index-1);
            return *this;
        }

        template<typename T>
        SmartString& rstrip(const T& chars) {
            SmartString toStrip = chars;
            int index = stringSize-1;
            while(index >= 0 && toStrip.contains(backingString[index])) {
                index--;
            }
            remove(index+1, stringSize-1);
            return *this;
        }

        template<typename T>
        SmartString& strip(const T& chars) {
            lstrip(chars);
            rstrip(chars);
            return *this;
        }

        // start and end are both inclusive.
        SmartString& remove(const int start, const int end) {
            SmartString temp("");
            for(int i = 0; i < length(); i++) {
                if(i < start || i > end) {
                    temp.append(backingString[i]);
                }
            }
            *this = temp;
            return *this;
        }

        SmartString& remove(const SmartString& target) {
            SmartString blank = "";
            return replace(target, blank);
        }

        template<typename T>
        SmartString& remove(const T& target) {
            SmartString targ(target);
            return remove(targ);
        }

        SmartString& removeAll(const SmartString& target) {
            bool changed = false;
            do {
                SmartString old = *this;
                remove(target);
                changed = (old != *this);
            } while(changed);
            return *this;
        }

        template<typename T>
        SmartString& removeAll(const T& target) {
            SmartString targ(target);
            return removeAll(targ);
        }

        SmartString& replace(const SmartString& target, const SmartString& newSubstring) {
            int location = findSubstring(target);
            if(location < 0 || isEmpty() || target.isEmpty()) {
                return *this;
            }

            int newSize = stringSize + newSubstring.length() - target.length();
            while(memorySize <= newSize) {
                memorySize *= 2;
            }
            char* tempPointer = new char[memorySize];

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

            delete [] backingString;
            backingString = tempPointer;
            stringSize = newSize;

            return *this;
        }

        template<typename T, typename U>
        SmartString& replace(const T& target, const U& newSubstring) {
            SmartString targ(target); SmartString newSubstr(newSubstring);
            return replace(targ, newSubstr);
        }

        SmartString& replaceAll(const SmartString& target, const SmartString& newSubstring) {
            bool changed = false;
            do {
                SmartString old = *this;
                replace(target, newSubstring);
                changed = (old != *this);
            } while(changed);

            return *this;
        }

        template<typename T, typename U>
        SmartString& replaceAll(const T& target, const U& newSubstring) {
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

        SmartString format(const int count, ...) {
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
        T getFormatted(...) const {
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
        T getFormatted(const int count, ...) const {
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
        T format(const U& str, ...) {
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

        // Assumes a-z and A-Z are contiguous. will break if they aren't.
        SmartString& toUpper() {
            int a = (int) 'a';
            int A = (int) 'A';
            int z = (int) 'z';
            for(int i = 0; i < length(); i++) {
                int letterVal = (int) backingString[i];
                if(letterVal >= a && letterVal <= z) {
                    backingString[i] = (char) (letterVal - a + A);
                }
            }
            return *this;
        }

        // Assumes a-z and A-Z are contiguous. will break if they aren't.
        SmartString& toLower() {
            int a = (int) 'a';
            int A = (int) 'A';
            int Z = (int) 'Z';
            for(int i = 0; i < length(); i++) {
                int letterVal = (int) backingString[i];
                if(letterVal >= A && letterVal <= Z) {
                    backingString[i] = (char) (letterVal - A + a);
                }
            }
            return *this;
        }

        template<typename T> static
        bool tryConvert(const T& source, double& out) {
            SmartString src = source;
            if(src.isEmpty()) {
                return false;
            }
            int sign = 1;
            if(src[0] == '-') {
                sign = -1;
                src.lstrip("-");
            }

            SmartString leftOfDecimal;
            SmartString rightOfDecimal;
            std::vector<SmartString> results = src.split<SmartString>(".");
            double answer = 0;

            if(results.size() > 2 || results.size() < 1) {
                return false;
            } else if(results.size() == 2) {
                rightOfDecimal = results[1];
            }
            leftOfDecimal = results[0];

            int multiplier = 1;
            for(int i = leftOfDecimal.length() - 1; i >= 0; i--) {
                int num = charToDigit(leftOfDecimal[i]);
                if(num > 9 || num < 0) {
                    return false;
                }
                answer += (num * multiplier);
                multiplier *= 10;
            }

            double divisor = 10;
            for(int i = 0; i < rightOfDecimal.length(); i++) {
                int num = charToDigit(rightOfDecimal[i]);
                if(num > 9 || num < 0) {
                    return false;
                }
                answer += (num / divisor);
                divisor *= 10;
            }

            out = answer * sign;
            return true;
        }

        template<typename T> static
        bool tryConvert(const T& source, float& out) {
            double temp;
            bool result = tryConvert(source, temp);
            if(result) {
                out = (float) temp;
            }
            return result;
        }

        template<typename T> static
        bool tryConvert(const T& source, int& out) {
            double temp;
            bool result = tryConvert(source, temp);
            if(result) {
                out = (int) temp;
            }
            return result;
        }

        template<typename T, typename U> static
        T convert(const U& source) {
            T temp;
            bool result = tryConvert(source, temp);
            if(result) {
                return temp;
            }
            throw std::invalid_argument("source string was not a valid number");
        };

        template<typename T>
        bool tryConvert(T& out) const {
            return tryConvert(*this, out);
        }

        template<typename T>
        T convert() const {
            T temp;
            bool result = this->tryConvert(temp);
            if(result) {
                return temp;
            }
            throw std::invalid_argument("string was not a valid number");
        };

        static SmartString whitespace() {
            SmartString result = " \t\n\r\x0b\x0c";
            return result;
        }

        template<typename T> static
        T whitespace() {
            SmartString result = " \t\n\r\x0b\x0c";
            return (T) result;
        }

        std::string str() const {
            return std::string(backingString);
        }

        char* c_str() const {
            char* result = new char[stringSize+1];
            for(int i = 0; i < stringSize+1; i++) {
                result[i] = backingString[i];
            }
            return result;
        }

        std::stringstream sstream() const {
            std::stringstream result;
            result << this->str();
            return result;
        }

        int length() const {
            return stringSize;
        }

        bool isEmpty() const {
            if(stringSize == 0) {
                return true;
            }
            return false;
        }

        size_t memoryFootPrint() const {
            return memorySize*sizeof(char);
        }
    };
}

#endif //UTILITYCODE_SMARTSTRING_H
