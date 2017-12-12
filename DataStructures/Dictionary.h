//
// Created by molberding on 11/17/2017.
//

#ifndef UTILITYCODE_DICTIONARY_H
#define UTILITYCODE_DICTIONARY_H
#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

namespace dictionary {

    template <typename T>
    class InvalidIndexException : public std::runtime_error {
    private:
        T index;
        std::string message;
    public:
        explicit InvalidIndexException(const T& idx) : runtime_error("Invalid index"), index(idx) {
            std::stringstream stream;
            stream << "Invalid Index : " << index;
            message = stream.str();
        }
        virtual const char* what() const noexcept {
            return message.c_str();
        }
        T getIndex() const {
            return index;
        }
    };

    template<typename T, typename U>
    class Dictionary {
    private:

        T* keys;
        U* values;
        int size;
        int memorySize;

        void sort() {
            int i = size - 1;
            while(i > 0 && keys[i] < keys[i-1]) {
                swap(i, i--);
            }
        }

        void swap(const int from, const int to) {
            T tempKey = keys[from];
            U tempVal = values[from];
            keys[from] = keys[to];
            values[from] = values[to];
            keys[to] = tempKey;
            values[to] = tempVal;
        }

        void move(const int from, const int to) {
            keys[to] = keys[from];
            values[to] = values[from];
        }

        int getKeyIndex(const T& target, const int left, const int right) const {
            if(right >= left) {
                int middle = left + ((right - left)/2);
                if(keys[middle] == target) {
                    return middle;
                }
                if(keys[middle] > target) {
                    return getKeyIndex(target, left, middle-1);
                } else {
                    return getKeyIndex(target, middle+1, right);
                }
            }
            return -1;
        }

        int getKeyIndex(const T& target) const {
            return getKeyIndex(target, 0, size-1);
        }

        int getValueIndex(const U& value) const {
            for(int i = 0; i < size; i++) {
                if(values[i] == value) {
                    return i;
                }
            }
            return -1;
        }

        void increaseMemorySize() {
            memorySize *= 2;
            T* newKeyArray = new T[memorySize];
            U* newValueArray = new U[memorySize];

            for(int i = 0; i < size; i++) {
                newKeyArray[i] = keys[i];
                newValueArray[i] = values[i];
            }

            if(size > 0) {
                delete [] keys;
                delete [] values;
            }

            keys = newKeyArray;
            values = newValueArray;
        }

        void allocateEntryMemory() {
            if((memorySize - size) <= 1) {
                increaseMemorySize();
            }
        }

        void destroy() {
            if(size > 0) {
                delete [] keys;
                delete [] values;
                size = 0;
                memorySize = 1;
            }
        }

    public:
        Dictionary() : keys(nullptr), values(nullptr), size(0), memorySize(1) {}
        Dictionary(const Dictionary& other) : Dictionary() {
            if(&other != this) {
                size = other.size;
                memorySize = other.memorySize;
                keys = new T[memorySize];
                values = new U[memorySize];
                for(int i = 0; i < size; i++) {
                    keys[i] = other.keys[i];
                    values[i] = other.values[i];
                }
            }
        }
        Dictionary(Dictionary&& other) : Dictionary() {
            keys = other.keys;
            values = other.values;
            size = other.size;
            memorySize = other.memorySize;
            other.keys = nullptr;
            other.values = nullptr;
            other.size = 0;
            other.memorySize = 0;
        }
        ~Dictionary() {
            destroy();
        }

        U& operator[](const T& index) {
            return getValue(index);
        }

        void addEntry(const T& key, const U& value) {
            if(size > 0) {
                int keyIndex = getKeyIndex(key);
                if (keyIndex >= 0) {
                    values[keyIndex] = value;
                    return;
                }
            }
            allocateEntryMemory();
            keys[size] = key;
            values[size++] = value;
            sort();
        }

        bool containsKey(const T& key) const {
            return getKeyIndex(key) >= 0;
        }

        bool containsValue(const U& value) const {
            return getValueIndex(value) >= 0;
        }

        T& getKey(const U& value) const {
            int index = getValueIndex(value);
            if(index < 0) {
                throw InvalidIndexException<U>(value);
            } else {
                return keys[index];
            }
        }

        U& getValue(const T& key) const {
            int keyIndex = getKeyIndex(key);
            if(keyIndex < 0) {
                throw InvalidIndexException<T>(key);
            }
            return values[keyIndex];
        }

        std::vector<T> getKeys() const {
            std::vector<T> result;
            for(int i = 0; i < size; i++) {
                result.push_back(keys[i]);
            }
            return result;
        }

        std::vector<U> getValues() const {
            std::vector<U> result;
            for(int i = 0; i < size; i++) {
                result.push_back(values[i]);
            }
            return result;
        }

        void remove(const T& key) {
            int index = getKeyIndex(key);
            if(index < 0) {
                throw InvalidIndexException<T>(key);
            } else {
                for(int i = index + 1; i < size; i++, index++) {
                    move(i, index);
                }
                size--;
            }
        }

        void remove(const U& value) {
            int index = getValueIndex(value);
            if(index < 0) {
                throw InvalidIndexException<U>(value);
            } else {
                for(int i = index + 1; i < size; i++, index++) {
                    move(i, index);
                }
                size--;
            }
        }

        int length() const {
            return size;
        }

        void clear() {
            destroy();
        }

        void printDictionary() {
            std::cout << "number of entries: " << size << std::endl;
            std::cout << "current max size : " << memorySize << std::endl;
            for(int i = 0; i < size; i++) {
                std::cout << "\t" << keys[i] << " : " << values[i] << std::endl;
            }
        }
    };
}

#endif //UTILITYCODE_DICTIONARY_H
