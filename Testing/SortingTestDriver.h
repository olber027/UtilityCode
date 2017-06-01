//
// Created by molberding on 5/30/2017.
//
#include "../SortingAlgorithms/Sort.h"
#include "TestDriver.h"
#include <random>
#include <ctime>
#include <cstdlib>

class SortingTestDriver : public TestDriver {
private:
    char* str;
    int* ints;
    double* doubles;
    int size;

    template<typename T> bool isSorted(T* array) {
        for(int i = 0; i < size-1; i++) {
            if(array[i] > array[i+1]) {
                return false;
            }
        }
        return true;
    }

public:
    SortingTestDriver() {
        passed = 0;
        failed = 0;
        total = 0;
        size = 20;
        str = new char[size];
        ints = new int[size];
        doubles = new double[size];
        srand(time(NULL));

        for(int i = 0; i < 80; i++) {
            output << "=";
        }
        output << std::endl << "Start of Sorting Testing\n";
        for(int i = 0; i < 80; i++) {
            output << "=";
        }
        output << std::endl;
    }

    ~SortingTestDriver() {
        delete str;
        delete ints;
        delete doubles;
    }

    void verifyQuickSort() {
        output << "Checking Quicksort functionality..." << std::endl;
        output << "\tChecking with characters" << std::endl;
        int iterations = 50;
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                str[j] = (char) ((rand() % 26) + 97);
            }
            Sort::quicksort<char>(str, size);
            assert(true, isSorted<char>(str));
        }
        output << "\tChecking with ints" << std::endl;
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            Sort::quicksort<int>(ints, size);
            assert(true, isSorted<int>(ints));
        }
    }

    void verifyBubbleSort() {
        output << "Checking bubblesort functionality..." << std::endl;
        int iterations = 50;
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            Sort::bubblesort<int>(ints, size);
            assert(true, isSorted<int>(ints));
        }
    }

    void verifyInsertionSort() {
        output << "Checking insertionsort functionality..." << std::endl;
        int iterations = 50;
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            Sort::insertionsort<int>(ints, size);
            assert(true, isSorted<int>(ints));
        }
    }

    void compareTimings() {

        int iterations = 50;
        int arraySize = 2000;

        int* arr = new int[arraySize];

        clock_t quicksortTime = clock();

        for (int i = 0; i < iterations; i++) {
            for (int j = 0; j < arraySize; j++) {
                arr[j] = rand() % 2000;
            }
            Sort::quicksort<int>(arr, arraySize);
        }

        quicksortTime = (clock() - quicksortTime);

        clock_t bubblesortTime = clock();

        for (int i = 0; i < iterations; i++) {
            for (int j = 0; j < arraySize; j++) {
                arr[j] = rand() % 2000;
            }
            Sort::bubblesort<int>(arr, arraySize);
        }

        bubblesortTime = (clock() - bubblesortTime);

        clock_t insertionsortTime = clock();

        for (int i = 0; i < iterations; i++) {
            for (int j = 0; j < arraySize; j++) {
                arr[j] = rand() % 2000;
            }
            Sort::insertionsort<int>(arr, arraySize);
        }

        insertionsortTime = (clock() - insertionsortTime);

        output << "quicksort time was: " << quicksortTime << std::endl;
        output << "bubblesort time was: " << bubblesortTime << std::endl;
        output << "insertionsort time was: " << insertionsortTime << std::endl;
    }

    void run() {
        verifyQuickSort();
        verifyBubbleSort();
        verifyInsertionSort();

        compareTimings();
    }
};
