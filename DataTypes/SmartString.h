//
// Created by molberding on 9/15/2017.
//

#ifndef UTILITYCODE_SMARTSTRING_H
#define UTILITYCODE_SMARTSTRING_H

#include <cstring>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>


namespace Utilities
{

    class SmartString
    {
    private:
        char* backingString;
        int stringSize;
        int precision;
        int memorySize;

        void destroy()
        {
            if(backingString != nullptr)
            {
                delete[] backingString;
                stringSize    = 0;
                backingString = nullptr;
                memorySize    = 0;
            }
        }

        void initialize(const int size)
        {
            destroy();
            stringSize                = size;
            backingString             = new char[stringSize + 1];
            backingString[stringSize] = '\0';
            memorySize                = stringSize + 1;
        }

        void extend(const int charsToAdd, const bool addToFront)
        {
            if(charsToAdd <= 0)
            {
                return;
            }

            int newSize            = stringSize + charsToAdd + 1;
            char* newBackingString = nullptr;

            if(memorySize <= newSize)
            {
                if(memorySize <= 0)
                {
                    memorySize = 1;
                }
                while(memorySize <= newSize)
                {
                    memorySize *= 2;
                }
                newBackingString = new char[memorySize];
            }

            if(newBackingString != nullptr)
            {
                int offset = addToFront ? charsToAdd : 0;
                for(int i = offset; i < stringSize + offset; i++)
                {
                    newBackingString[i] = backingString[i - offset];
                }
                newBackingString[stringSize + offset] = '\0';
                delete[] backingString;
                backingString = newBackingString;
            }
            else if(addToFront)
            {
                for(int i = stringSize; i >= 0; i--)
                {
                    backingString[i + charsToAdd] = backingString[i];
                }
            }

            stringSize += charsToAdd;
        }

        inline void extend(const int charsToAdd)
        {
            extend(charsToAdd, false);
        }

        inline int calculateSize(const std::string& str) const
        {
            return str.length();
        }

        inline int calculateSize(const SmartString& str) const
        {
            return str.length();
        }

        int calculateSize(const char* str) const
        {
            int size = 0;
            while(str[size] != '\0')
            {
                size++;
            }
            return size;
        }

        inline char digitToChar(const int digit) const
        {
            return static_cast<char>(digit + static_cast<int>('0'));
        }

        static inline int charToDigit(const char c)
        {
            return static_cast<char>(static_cast<int>(c) - static_cast<int>('0'));
        }

        template <typename T>
        inline T abs(const T val) const
        {
            return val < 0 ? val * -1 : val;
        }

        int getNumArguments() const
        {
            int location;
            int count = 0;
            do {
                SmartString arg;
                arg << "{" << count << "}";
                location = findSubstring(arg);
                if(location >= 0)
                {
                    count++;
                }
            } while(location >= 0);
            return count;
        }

        // create the pre-processing table for the Knuth-Morris-Pratt algorithm
        std::vector<int> createTable(const SmartString& targetWord) const
        {
            std::vector<int> table(targetWord.length(), 0);
            table[0]             = -1;
            int currentPosition  = 1;
            int currentCandidate = 0;

            while(currentPosition < targetWord.length())
            {
                if(targetWord[currentPosition] == targetWord[currentCandidate])
                {
                    table[currentPosition] = table[currentCandidate];
                }
                else
                {
                    table[currentPosition] = currentCandidate;
                    currentCandidate       = table[currentCandidate];

                    while(currentCandidate >= 0 && targetWord[currentCandidate] != targetWord[currentPosition])
                    {
                        currentCandidate = table[currentCandidate];
                    }
                }
                currentCandidate++;
                currentPosition++;
            }

            return table;
        }

        template <typename T>
        void formatHelper(const int depth, const T& t)
        {
            SmartString target;
            target << "{" << depth << "}";
            replaceAll(target, t);
        }

        template <typename T, typename... Args>
        void formatHelper(const int depth, const T& t, Args... args)
        {
            SmartString target;
            target << "{" << depth << "}";
            replaceAll(target, t);
            formatHelper(depth + 1, args...);
        }

    public:
        SmartString() : backingString(nullptr), stringSize(0), precision(5), memorySize(0) {}
        SmartString(const std::string& init) : SmartString()
        {
            if(init.length() != 0)
            {
                initialize(init.length());
                std::memcpy(backingString, init.data(), stringSize);
            }
        }
        SmartString(std::string&& init) : SmartString()
        {
            if(init.length() != 0)
            {
                initialize(init.length());
                std::memcpy(backingString, init.data(), stringSize);
            }
        }
        SmartString(const char init) : SmartString()
        {
            initialize(1);
            stringSize       = 1;
            backingString[0] = init;
        }
        SmartString(const char* init) : SmartString()
        {
            if(init != nullptr)
            {
                initialize(calculateSize(init));
                std::memcpy(backingString, init, stringSize);
            }
        }
        SmartString(const std::stringstream& init) : SmartString()
        {
            std::string str = init.str();
            if(str.length() != 0)
            {
                initialize(str.length());
                std::memcpy(backingString, str.data(), stringSize);
            }
            precision = init.precision();
        }
        SmartString(std::stringstream&& init) : SmartString()
        {
            std::string str = init.str();
            if(str.length() != 0)
            {
                initialize(str.length());
                std::memcpy(backingString, str.data(), stringSize);
            }
            precision = init.precision();
        }
        explicit inline SmartString(const int init) : SmartString()
        {
            append(init);
        }
        explicit inline SmartString(const double init) : SmartString()
        {
            append(init);
        }
        explicit inline SmartString(const float init) : SmartString()
        {
            append(init);
        }
        SmartString(const int numChars, const char fill) : SmartString()
        {
            initialize(numChars);
            for(int i = 0; i < numChars; i++)
            {
                backingString[i] = fill;
            }
        }
        SmartString(const SmartString& other) : SmartString()
        {
            initialize(other.stringSize);
            std::memcpy(backingString, other.backingString, stringSize);
            precision = other.precision;
        }
        SmartString(SmartString&& other) noexcept
        {
            backingString       = other.backingString;
            stringSize          = other.stringSize;
            precision           = other.precision;
            memorySize          = other.memorySize;
            other.precision     = 5;
            other.stringSize    = 0;
            other.backingString = nullptr;
        }
        ~SmartString()
        {
            destroy();
        }

        explicit inline operator std::string() const { return str(); }
        explicit inline operator char*() const { return c_str(); }
        explicit operator std::stringstream() const
        {
            std::stringstream result;
            result << backingString;
            return result;
        }

        SmartString& operator=(const SmartString& rhs)
        {
            if(&rhs != this)
            {
                initialize(rhs.stringSize);
                for(int i = 0; i < stringSize; i++)
                {
                    backingString[i] = rhs.backingString[i];
                }
                precision = rhs.precision;
            }
            return *this;
        }

        SmartString& operator=(SmartString&& rhs) noexcept
        {
            if(&rhs != this)
            {
                destroy();
                precision         = rhs.precision;
                stringSize        = rhs.stringSize;
                backingString     = rhs.backingString;
                rhs.precision     = 5;
                rhs.stringSize    = 0;
                rhs.backingString = nullptr;
            }
            return *this;
        }

        SmartString& operator=(const std::string& rhs)
        {
            initialize(rhs.length());
            std::memcpy(backingString, rhs.data(), stringSize);
            return *this;
        }

        SmartString& operator=(std::string&& rhs)
        {
            initialize(rhs.length());
            std::memcpy(backingString, rhs.data(), stringSize);
            return *this;
        }

        SmartString& operator=(const char* rhs)
        {
            int size = calculateSize(rhs);
            initialize(size);
            std::memcpy(backingString, rhs, stringSize);
            return *this;
        }

        inline SmartString& operator=(const std::stringstream& rhs)
        {
            return (*this = rhs.str());
        }

        inline SmartString& operator=(std::stringstream&& rhs)
        {
            return (*this = rhs.str());
        }

        template <typename T>
        SmartString& append(const T& str)
        {
            int numCharactersToAdd = calculateSize(str);
            int initialSize        = stringSize;
            extend(numCharactersToAdd);
            for(int i = initialSize; i < stringSize; i++)
            {
                backingString[i] = str[i - initialSize];
            }
            backingString[stringSize] = '\0';
            return *this;
        }

        template <typename T>
        SmartString& prepend(const T& str)
        {
            int numCharactersToAdd = calculateSize(str);
            extend(numCharactersToAdd, true);
            for(int i = 0; i < numCharactersToAdd; i++)
            {
                backingString[i] = str[i];
            }
            return *this;
        }

        inline SmartString& append(const std::stringstream& strm)
        {
            return append(strm.str());
        }

        inline SmartString& prepend(const std::stringstream& strm)
        {
            return prepend(strm.str());
        }

        SmartString& append(const SmartString& str)
        {
            int initialSize = stringSize;
            extend(str.length());
            for(int i = initialSize; i < stringSize; i++)
            {
                backingString[i] = str[i - initialSize];
            }
            backingString[stringSize] = '\0';
            return *this;
        }

        SmartString& append(SmartString&& str)
        {
            int initialSize = stringSize;
            extend(str.length());
            for(int i = initialSize; i < stringSize; i++)
            {
                backingString[i] = str[i - initialSize];
            }
            backingString[stringSize] = '\0';
            return *this;
        }

        SmartString& prepend(const SmartString& str)
        {
            int initialSize = stringSize;
            extend(str.length(), true);
            for(int i = 0; i < str.length(); i++)
            {
                backingString[i] = str[i];
            }
            return *this;
        }

        SmartString& prepend(SmartString&& str)
        {
            int initialSize = stringSize;
            extend(str.length(), true);
            for(int i = 0; i < str.length(); i++)
            {
                backingString[i] = str[i];
            }
            return *this;
        }

        SmartString& append(const char c)
        {
            extend(1);
            backingString[stringSize - 1] = c;
            backingString[stringSize]     = '\0';

            return *this;
        }

        SmartString& prepend(const char c)
        {
            extend(1, true);
            backingString[0] = c;

            return *this;
        }

        SmartString& append(const int val)
        {
            SmartString temp;
            bool isNegative = val < 0;
            int num         = abs(val);
            do {
                int digit = num % 10;
                temp.prepend(digitToChar(digit));
                num /= 10;
            } while(num > 0);
            if(isNegative)
            {
                temp.prepend('-');
            }
            return append(temp);
        }

        SmartString& prepend(const int val)
        {
            SmartString temp;
            temp.append(val);
            return prepend(temp);
        }

        SmartString& append(const double val, const int precision)
        {
            SmartString temp;
            int leftOfDecimal = static_cast<int>(val);

            temp.append(leftOfDecimal);
            temp.append('.');

            double rightOfDecimal = abs(val) - abs(leftOfDecimal);
            for(int i = 0; i < precision; i++)
            {
                int digit = static_cast<int>(rightOfDecimal * 10);
                temp.append(digitToChar(digit));
                rightOfDecimal = (rightOfDecimal * 10) - digit;
            }
            return append(temp);
        }

        SmartString& append(const double val)
        {
            /*
             * Any trailing zeroes will be removed when this method is used,
             * unless there are only trailing zeroes, in which case one zero
             * will be left. If you would like to include trailing zeroes,
             * use the append method which specifies the precision.
             */
            append(val, precision);
            if(getLast() == '0')
            {
                rstrip('0');
            }
            if(getLast() == '.')
            {
                append('0');
            }
            return *this;
        }

        SmartString& prepend(const double val, const int precision)
        {
            SmartString temp;
            temp.append(val, precision);
            return prepend(temp);
        }

        SmartString& prepend(const double val)
        {
            SmartString temp;
            temp.append(val);
            return prepend(temp);
        }

        SmartString& append(const float val, const int precision)
        {
            SmartString temp;
            int leftOfDecimal = static_cast<int>(abs(val));

            if(val < 0)
            {
                temp.append('-');
            }
            temp.append(leftOfDecimal);
            temp.append('.');

            float rightOfDecimal = val - leftOfDecimal;
            for(int i = 0; i < precision; i++)
            {
                int digit = (int) rightOfDecimal * 10;
                temp.append(digitToChar(digit));
                rightOfDecimal = (rightOfDecimal * 10) - digit;
            }
            return append(temp);
        }

        SmartString& append(const float val)
        {
            append(val, precision);
            if(getLast() == '0')
            {
                rstrip('0');
            }
            if(getLast() == '.')
            {
                append('0');
            }
            return *this;
        }

        SmartString& prepend(const float val, const int precision)
        {
            SmartString temp;
            temp.append(val, precision);
            return prepend(temp);
        }

        SmartString& prepend(const float val)
        {
            SmartString temp;
            temp.append(val);
            return prepend(temp);
        }

        template <typename T>
        SmartString& operator<<(const T& t)
        {
            append(t);
            return *this;
        }

        SmartString& operator<<(const SmartString& str)
        {
            append(str);
            return *this;
        }

        template <typename T>
        inline SmartString& operator+=(const T& t)
        {
            return append(t);
        }

        inline SmartString& operator+=(const SmartString& str)
        {
            return append(str);
        }

        template <typename T>
        SmartString operator+(const T& t) const
        {
            SmartString result(*this);
            result.append(t);
            return result;
        }

        SmartString operator+(const SmartString& str) const
        {
            SmartString result(*this);
            result.append(str);
            return result;
        }

        inline bool operator!=(const SmartString& str) const
        {
            return !(*this == str);
        }

        template <typename T>
        inline bool operator!=(const T& str) const
        {
            return !(*this == str);
        }

        bool operator==(const SmartString& str) const
        {
            if(stringSize != str.stringSize)
            {
                return false;
            }
            for(int i = 0; i < stringSize; i++)
            {
                if(str.backingString[i] != backingString[i])
                {
                    return false;
                }
            }
            return true;
        }

        inline bool operator==(const std::stringstream& str) const
        {
            return (*this == str.str());
        }

        bool operator==(const std::string str) const
        {
            if(stringSize != str.size())
            {
                return false;
            }
            for(int i = 0; i < stringSize; i++)
            {
                if(str[i] != backingString[i])
                {
                    return false;
                }
            }
            return true;
        }

        bool operator==(const char* str) const
        {
            if(stringSize != calculateSize(str))
            {
                return false;
            }
            for(int i = 0; i < stringSize; i++)
            {
                if(str[i] != backingString[i])
                {
                    return false;
                }
            }
            return true;
        }

        template <typename T>
        bool operator==(const T& str) const
        {
            SmartString rhs = str;
            return (*this == rhs);
        }

        bool operator<(const SmartString& str) const
        {
            if(stringSize == 0) return true;
            if(str.stringSize == 0) return false;

            int min = stringSize < str.stringSize ? stringSize : str.stringSize;
            int i   = 0;
            while(i < min && backingString[i] == str.backingString[i]) { i++; }

            return backingString[i] < str.backingString[i];
        }

        template <typename T>
        bool operator<(const T& str) const
        {
            SmartString rhs = str;
            return (*this < rhs);
        }

        inline bool operator<=(const SmartString& str) const
        {
            return (this->str() <= str.str());
        }

        template <typename T>
        inline bool operator<=(const T& str) const
        {
            SmartString rhs = str;
            return (*this <= rhs);
        }

        inline bool operator>(const SmartString& str) const
        {
            return (this->str() > str.str());
        }

        template <typename T>
        bool operator>(const T& str) const
        {
            SmartString rhs = str;
            return (*this > rhs);
        }

        inline bool operator>=(const SmartString& str) const
        {
            return (this->str() >= str.str());
        }

        template <typename T>
        bool operator>=(const T& str) const
        {
            SmartString rhs = str;
            return (*this >= rhs);
        }

        inline char& operator[](const int index) const
        {
            return backingString[index];
        }

        template <typename T>
        friend T operator+(const T left, const SmartString& right)
        {
            SmartString result(left);
            result.append(right);
            return static_cast<T>(result);
        }

        template <typename T>
        inline friend bool operator==(const T& left, const SmartString& right)
        {
            return (right == left);
        }

        template <typename T>
        inline friend bool operator!=(const T& left, const SmartString& right)
        {
            return (right != left);
        }

        template <typename T>
        inline friend bool operator<(const T& left, const SmartString& right)
        {
            return (right > left);
        }

        template <typename T>
        inline friend bool operator>(const T& left, const SmartString& right)
        {
            return (right < left);
        }

        template <typename T>
        inline friend bool operator<=(const T& left, const SmartString& right)
        {
            return (right >= left);
        }

        template <typename T>
        inline friend bool operator>=(const T& left, const SmartString& right)
        {
            return (right <= left);
        }

        friend std::ostream& operator<<(std::ostream& out, const SmartString& string)
        {
            out << string.backingString;
            return out;
        }

        friend std::istream& operator>>(std::istream& in, SmartString& string)
        {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        friend std::ofstream& operator<<(std::ofstream& out, const SmartString& string)
        {
            out << string.backingString;
            return out;
        }

        friend std::ifstream& operator>>(std::ifstream& in, SmartString& string)
        {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        friend std::fstream& operator<<(std::fstream& out, const SmartString& string)
        {
            out << string.backingString;
            return out;
        }

        friend std::fstream& operator>>(std::fstream& in, SmartString& string)
        {
            std::string temp;
            in >> temp;
            string = SmartString(temp);
            return in;
        }

        friend std::stringstream& operator<<(std::stringstream& out, const SmartString& string)
        {
            out << string.backingString;
            return out;
        }

        friend std::stringstream& operator>>(std::stringstream& in, SmartString& string)
        {
            string.append(in.str());
            return in;
        }

        bool setPrecision(const int newPrecision)
        {
            if(newPrecision >= 0)
            {
                precision = newPrecision;
                return true;
            }
            return false;
        }

        inline int getPrecision() const
        {
            return precision;
        }

        char getLast() const
        {
            if(stringSize > 0)
            {
                return backingString[stringSize - 1];
            }
            return '\0';
        }

        char getFirst() const
        {
            if(stringSize > 0)
            {
                return backingString[0];
            }
            return '\0';
        }

        // start and end are both inclusive.
        SmartString getSubstring(const int startLocation, const int endLocation) const
        {
            if(startLocation < 0) throw std::out_of_range("Given start location is less than 0");
            if(endLocation > stringSize) throw std::out_of_range("Given end location is greater than the string size");

            int substringSize = endLocation - startLocation + 1;
            SmartString result;
            result.initialize(substringSize);
            std::memcpy(result.backingString, backingString + startLocation, substringSize);
            result[substringSize] = '\0';
            return result;
        }

        template <typename T>
        inline T getSubstring(const int startLocation, const int endLocation) const
        {
            return static_cast<T>(getSubstring(startLocation, endLocation));
        }

        // Uses the Knuth-Morris-Pratt algorithm for finding the substring
        int findSubstring(const int startingLocation, const SmartString& target) const
        {
            if(startingLocation < 0)
            {
                return -1;
            }

            std::vector<int> table = createTable(target);
            int currentLocation    = startingLocation;
            int targetLocation     = 0;

            while(currentLocation < stringSize)
            {
                if(target[targetLocation] == backingString[currentLocation])
                {
                    targetLocation++;
                    currentLocation++;
                    if(targetLocation == target.length())
                    {
                        return currentLocation - targetLocation;
                    }
                }
                else
                {
                    targetLocation = table[targetLocation];
                    if(targetLocation < 0)
                    {
                        currentLocation++;
                        targetLocation++;
                    }
                }
            }
            return -1;
        }

        inline int findSubstring(const SmartString& target) const
        {
            return findSubstring(0, target);
        }

        template <typename T>
        inline int findSubstring(const T& target) const
        {
            return findSubstring(0, SmartString(target));
        }

        template <typename T>
        inline bool contains(const T& target) const
        {
            return findSubstring(target) >= 0;
        }

        template <typename T>
        int count(const T& target) const
        {
            int numInstances = 0;
            SmartString targ(target);
            int location = findSubstring(targ);
            while(location >= 0 && location < length())
            {
                numInstances++;
                location = findSubstring(location + 1, targ);
            }
            return numInstances;
        }

        template <typename T, typename U>
        std::vector<T> split(const U& target) const
        {
            std::vector<T> result = std::vector<T>();
            SmartString temp(*this);
            SmartString targ(target);
            int location = temp.findSubstring(targ);
            while(location >= 0)
            {
                result.push_back(temp.getSubstring<T>(0, location - 1));
                temp.remove(0, location + targ.length() - 1);
                location = temp.findSubstring(targ);
            }
            if(temp.length() > 0)
            {
                result.push_back(static_cast<T>(temp));
            }
            return result;
        }

        template <typename T, typename U, typename V>
        static T join(const std::vector<U>& list, const V& separator)
        {
            SmartString temp;
            for(int i = 0; i < list.size() - 1; i++)
            {
                temp.append(list[i]);
                temp.append(separator);
            }
            temp.append(list[list.size() - 1]);
            return static_cast<T>(temp);
        }

        template <typename T, typename U, typename V>
        static T join(const U* list, int listSize, const V& separator)
        {
            SmartString temp;
            for(int i = 0; i < listSize - 1; i++)
            {
                temp.append(list[i]);
                temp.append(separator);
            }
            temp.append(list[listSize - 1]);
            return static_cast<T>(temp);
        }

        inline SmartString& lstrip()
        {
            lstrip(whitespace());
            return *this;
        }

        inline SmartString& rstrip()
        {
            rstrip(whitespace());
            return *this;
        }

        inline SmartString& strip()
        {
            lstrip(whitespace());
            rstrip(whitespace());
            return *this;
        }

        template <typename T>
        SmartString& lstrip(const T& chars)
        {
            SmartString toStrip = chars;
            int index           = 0;
            while(index < stringSize && toStrip.contains(backingString[index]))
            {
                index++;
            }
            remove(0, index - 1);
            return *this;
        }

        template <typename T>
        SmartString& rstrip(const T& chars)
        {
            SmartString toStrip = chars;
            int index           = stringSize - 1;
            while(index >= 0 && toStrip.contains(backingString[index]))
            {
                index--;
            }
            remove(index + 1, stringSize - 1);
            return *this;
        }

        template <typename T>
        inline SmartString& strip(const T& chars)
        {
            lstrip(chars);
            rstrip(chars);
            return *this;
        }

        // start and end are both inclusive.
        SmartString& remove(const int startLocation, const int endLocation)
        {
            SmartString temp;
            for(int i = 0; i < length(); i++)
            {
                if(i < startLocation || i > endLocation)
                {
                    temp.append(backingString[i]);
                }
            }
            *this = temp;
            return *this;
        }

        inline SmartString& remove(const SmartString& target)
        {
            return replace(target, "");
        }

        template <typename T>
        inline SmartString& remove(const T& target)
        {
            return remove(SmartString(target));
        }

        SmartString& removeAll(const SmartString& target)
        {
            bool changed = false;
            do {
                SmartString old = *this;
                remove(target);
                changed = (old != *this);
            } while(changed);
            return *this;
        }

        template <typename T>
        inline SmartString& removeAll(const T& target)
        {
            return removeAll(SmartString(target));
        }

        SmartString& replace(const SmartString& target, const SmartString& newSubstring)
        {
            int location = findSubstring(target);
            if(location < 0 || isEmpty() || target.isEmpty())
            {
                return *this;
            }

            int newSize = stringSize + newSubstring.length() - target.length();
            while(memorySize <= newSize)
            {
                memorySize *= 2;
            }
            char* tempPointer = new char[memorySize];

            for(int i = 0; i < location; i++)
            {
                tempPointer[i] = backingString[i];
            }
            for(int i = 0; i < newSubstring.length(); i++)
            {
                tempPointer[location + i] = newSubstring[i];
            }
            for(int i = location + target.length(); i < stringSize; i++)
            {
                tempPointer[i + newSubstring.length() - target.length()] = backingString[i];
            }
            tempPointer[newSize] = '\0';

            delete[] backingString;
            backingString = tempPointer;
            stringSize    = newSize;

            return *this;
        }

        template <typename T, typename U>
        inline SmartString& replace(const T& target, const U& newSubstring)
        {
            return replace(SmartString(target), SmartString(newSubstring));
        }

        SmartString& replaceAll(const SmartString& target, const SmartString& newSubstring)
        {
            bool changed = false;
            do {
                SmartString old = *this;
                replace(target, newSubstring);
                changed = (old != *this);
            } while(changed);

            return *this;
        }

        template <typename T, typename U>
        inline SmartString& replaceAll(const T& target, const U& newSubstring)
        {
            return replaceAll(SmartString(target), SmartString(newSubstring));
        }

        template <typename... Args>
        inline SmartString& format(Args... args)
        {
            formatHelper(0, args...);
            return *this;
        }

        template <typename T, typename... Args>
        inline T getFormatted(Args... args) const
        {
            SmartString result(*this);
            result.formatHelper(0, args...);
            return static_cast<T>(result);
        }

        template <typename T, typename U, typename... Args>
        static T format(const U& source, Args... args)
        {
            SmartString result(source);
            result.formatHelper(0, args...);
            return static_cast<T>(result);
        }

        // Assumes a-z and A-Z are contiguous. will break if they aren't.
        SmartString& toUpper()
        {
            int a = static_cast<int>('a');
            int A = static_cast<int>('A');
            int z = static_cast<int>('z');
            for(int i = 0; i < length(); i++)
            {
                int letterVal = static_cast<int>(backingString[i]);
                if(letterVal >= a && letterVal <= z)
                {
                    backingString[i] = static_cast<char>(letterVal - a + A);
                }
            }
            return *this;
        }

        // Assumes a-z and A-Z are contiguous. will break if they aren't.
        SmartString& toLower()
        {
            int a = static_cast<int>('a');
            int A = static_cast<int>('A');
            int Z = static_cast<int>('Z');
            for(int i = 0; i < length(); i++)
            {
                int letterVal = static_cast<int>(backingString[i]);
                if(letterVal >= A && letterVal <= Z)
                {
                    backingString[i] = static_cast<char>(letterVal - A + a);
                }
            }
            return *this;
        }

        template <typename T>
        static bool tryConvert(const T& source, double& out)
        {
            SmartString src(source);
            if(src.isEmpty())
            {
                return false;
            }
            int sign = 1;
            if(src[0] == '-')
            {
                sign = -1;
                src.lstrip("-");
            }

            SmartString leftOfDecimal;
            SmartString rightOfDecimal;
            std::vector<SmartString> results = src.split<SmartString>(".");
            double answer = 0;

            if(results.size() > 2 || results.empty())
            {
                return false;
            }
            else if(results.size() == 2)
            {
                rightOfDecimal = results[1];
            }
            leftOfDecimal = results[0];

            int multiplier = 1;
            for(int i = leftOfDecimal.length() - 1; i >= 0; i--)
            {
                int num = charToDigit(leftOfDecimal[i]);
                if(num > 9 || num < 0)
                {
                    return false;
                }
                answer += (num * multiplier);
                multiplier *= 10;
            }

            double divisor = 10;
            for(int i = 0; i < rightOfDecimal.length(); i++)
            {
                int num = charToDigit(rightOfDecimal[i]);
                if(num > 9 || num < 0)
                {
                    return false;
                }
                answer += (num / divisor);
                divisor *= 10;
            }

            out = answer * sign;
            return true;
        }

        template <typename T>
        static bool tryConvert(const T& source, float& out)
        {
            double temp;
            bool result = tryConvert(source, temp);
            if(result)
            {
                out = static_cast<float>(temp);
            }
            return result;
        }

        template <typename T>
        static bool tryConvert(const T& source, int& out)
        {
            double temp;
            bool result = tryConvert(source, temp);
            if(result)
            {
                out = static_cast<int>(temp);
            }
            return result;
        }

        template <typename T, typename U>
        static T convert(const U& source)
        {
            T temp;
            bool result = tryConvert(source, temp);
            if(result)
            {
                return temp;
            }
            std::stringstream errorStream;
            errorStream << "The given string could not be parsed into a valid number: " << source;
            throw std::invalid_argument(errorStream.str());
        };

        template <typename T>
        inline bool tryConvert(T& out) const
        {
            return tryConvert(*this, out);
        }

        template <typename T>
        T convert() const
        {
            T temp;
            bool result = this->tryConvert(temp);
            if(result)
            {
                return temp;
            }
            std::stringstream errorStream;
            errorStream << "This string could not be parsed into a valid number: " << str();
            throw std::invalid_argument(errorStream.str());
        };

        inline static SmartString whitespace()
        {
            return SmartString(" \t\n\r\x0b\x0c");
        }

        template <typename T>
        inline static T whitespace()
        {
            return static_cast<T>(SmartString(" \t\n\r\x0b\x0c"));
        }

        inline std::string str() const
        {
            return std::string(backingString);
        }

        inline char* c_str() const
        {
            char* result = new char[stringSize + 1];
            std::memcpy(result, backingString, stringSize+1);
            return result;
        }

        inline std::stringstream sstream() const
        {
            std::stringstream result;
            result << *this;
            return result;
        }

        inline int length() const
        {
            return stringSize;
        }

        inline bool isEmpty() const
        {
            return stringSize == 0;
        }

        inline size_t memoryFootPrint() const
        {
            return memorySize * sizeof(char);
        }
    };
}// namespace Utilities

#endif//UTILITYCODE_SMARTSTRING_H
