//
// Created by molberding on 11/17/2017.
//

#ifndef UTILITYCODE_DICTIONARY_H
#define UTILITYCODE_DICTIONARY_H

#include "TypeTraits.h"
#include <exception>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <vector>

namespace Utilities
{
    template <typename T>
    class InvalidIndexException : public std::runtime_error
    {
    private:
        T index;
        std::string message;

    public:
        explicit InvalidIndexException(const T& idx) : runtime_error("Invalid index"), index(idx)
        {
            std::stringstream stream;
            stream << "Invalid Index : " << index;
            message = stream.str();
        }
        const char* what() const noexcept override
        {
            return message.c_str();
        }
        T getIndex() const
        {
            return index;
        }
    };

    template <typename T, typename U>
    class Dictionary
    {
        static_assert(is_less_than_comparable<T>::value, "Type T must be comparable with the < operator");
        static_assert(is_equal_comparable<T>::value, "Type T must be comparable with the == operator");
        static_assert(is_equal_comparable<U>::value, "Type U must be comparable with the == operator");

    private:
        T* keys;
        U* values;
        int size;
        int memorySize;

        // The list will already be sorted when this is called, except for (potentially)
        // the last element. So all we need to do is get the last element in the right place.
        void sort()
        {
            int i = size - 1;
            while(i > 0 && keys[i] < keys[i - 1])
            {
                swap(i, i - 1);
                i--;
            }
        }

        void swap(int from, int to)
        {
            T tempKey    = keys[from];
            U tempVal    = values[from];
            keys[from]   = keys[to];
            values[from] = values[to];
            keys[to]     = tempKey;
            values[to]   = tempVal;
        }

        void move(int from, int to)
        {
            keys[to]   = keys[from];
            values[to] = values[from];
        }

        // Do a binary search on the list to speed up lookup times.
        int getKeyIndex(const T& target, int left, int right) const
        {
            if(right < left)
            {
                return -1;
            }

            int middle = left + ((right - left) / 2);
            if(keys[middle] == target)
            {
                return middle;
            }
            if(target < keys[middle])
            {
                return getKeyIndex(target, left, middle - 1);
            }
            else
            {
                return getKeyIndex(target, middle + 1, right);
            }
        }

        int getKeyIndex(const T& target) const
        {
            return getKeyIndex(target, 0, size - 1);
        }

        int getValueIndex(const U& value) const
        {
            for(int i = 0; i < size; i++)
            {
                if(values[i] == value)
                {
                    return i;
                }
            }
            return -1;
        }

        void increaseMemorySize()
        {
            memorySize *= 2;
            T* newKeyArray   = new T[memorySize];
            U* newValueArray = new U[memorySize];

            for(int i = 0; i < size; i++)
            {
                newKeyArray[i]   = keys[i];
                newValueArray[i] = values[i];
            }

            if(size > 0)
            {
                delete[] keys;
                delete[] values;
            }

            keys   = newKeyArray;
            values = newValueArray;
        }

        void allocateEntryMemory()
        {
            if((memorySize - size) <= 1)
            {
                increaseMemorySize();
            }
        }

        void destroy()
        {
            if(size > 0)
            {
                delete[] keys;
                delete[] values;
                size       = 0;
                memorySize = 1;
            }
        }

    public:
        Dictionary() : keys(nullptr), values(nullptr), size(0), memorySize(1) {}
        Dictionary(const T* Keys, const U* Values, int size) : Dictionary()
        {
            for(int i = 0; i < size; i++)
            {
                addEntry(Keys[i], Values[i]);
            }
        }
        Dictionary(const std::vector<T>& Keys, const std::vector<U>& Values) : Dictionary()
        {
            if(Keys.size() != Values.size())
            {
                throw std::length_error("The size of the given Keys and Values did not match.");
            }
            for(int i = 0; i < Keys.size(); i++)
            {
                addEntry(Keys[i], Values[i]);
            }
        }
        Dictionary(const Dictionary<T, U>& other) : Dictionary()
        {
            if(&other != this)
            {
                size       = other.size;
                memorySize = other.memorySize;
                keys       = new T[memorySize];
                values     = new U[memorySize];
                for(int i = 0; i < size; i++)
                {
                    keys[i]   = other.keys[i];
                    values[i] = other.values[i];
                }
            }
        }
        Dictionary(Dictionary<T, U>&& other) noexcept
        {
            keys             = other.keys;
            values           = other.values;
            size             = other.size;
            memorySize       = other.memorySize;
            other.keys       = nullptr;
            other.values     = nullptr;
            other.size       = 0;
            other.memorySize = 0;
        }
        ~Dictionary()
        {
            destroy();
        }

        Dictionary<T, U>& operator=(const Dictionary<T, U>& rhs)
        {
            if(this != &rhs)
            {
                destroy();
                for(int i = 0; i < rhs.length(); i++)
                {
                    addEntry(rhs.keys[i], rhs.values[i]);
                }
            }
        }
        Dictionary<T, U>& operator=(Dictionary<T, U>&& rhs) noexcept
        {
            keys           = rhs.keys;
            values         = rhs.values;
            size           = rhs.size;
            memorySize     = rhs.memorySize;
            rhs.keys       = nullptr;
            rhs.values     = nullptr;
            rhs.size       = 0;
            rhs.memorySize = 1;
        }

        U& operator[](const T& index) const
        {
            return getValue(index);
        }

        void addEntry(const T& key, const U& value)
        {
            if(size > 0)
            {
                int keyIndex = getKeyIndex(key);
                if(keyIndex >= 0)
                {
                    values[keyIndex] = value;
                    return;
                }
            }
            allocateEntryMemory();
            keys[size]     = key;
            values[size++] = value;
            sort();
        }

        bool containsKey(const T& key) const
        {
            return getKeyIndex(key) >= 0;
        }

        bool containsValue(const U& value) const
        {
            return getValueIndex(value) >= 0;
        }

        T& getKey(const U& value) const
        {
            int index = getValueIndex(value);
            if(index < 0)
            {
                throw InvalidIndexException<U>(value);
            }
            return keys[index];
        }

        U& getValue(const T& key) const
        {
            int keyIndex = getKeyIndex(key);
            if(keyIndex < 0)
            {
                throw InvalidIndexException<T>(key);
            }
            return values[keyIndex];
        }

        std::vector<T> getKeys() const
        {
            return std::vector<T>(keys, keys + size);
        }

        std::vector<U> getValues() const
        {
            return std::vector<U>(values, values + size);
        }

        void remove(const T& key)
        {
            int index = getKeyIndex(key);
            if(index < 0)
            {
                throw InvalidIndexException<T>(key);
            }

            for(int i = index + 1; i < size; i++, index++)
            {
                move(i, index);
            }
            size--;
        }

        void remove(const U& value)
        {
            int index = getValueIndex(value);
            if(index < 0)
            {
                throw InvalidIndexException<U>(value);
            }

            for(int i = index + 1; i < size; i++, index++)
            {
                move(i, index);
            }
            size--;
        }

        int length() const
        {
            return size;
        }

        void clear()
        {
            destroy();
        }

        void printDictionary()
        {
            std::cout << "number of entries: " << size << std::endl;
            std::cout << "current max size : " << memorySize << std::endl;
            for(int i = 0; i < size; i++)
            {
                std::cout << "\t" << keys[i] << " : " << values[i] << std::endl;
            }
        }
    };
}// namespace Utilities

#endif//UTILITYCODE_DICTIONARY_H
