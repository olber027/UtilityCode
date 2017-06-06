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
    int iterations;

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
        size = 50;
        str = new char[size];
        ints = new int[size];
        doubles = new double[size];
        iterations = 50;
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
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            Sort::insertionsort<int>(ints, size);
            assert(true, isSorted<int>(ints));
        }
    }

    void verifyMergeSort() {
        output << "Checking mergesort functionality..." << std::endl;
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            Sort::mergesort<int>(ints, size);
            assert(true, isSorted<int>(ints));
        }
    }

    void compareTimings() {

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

        clock_t mergesortTime = clock();

        for (int i = 0; i < iterations; i++) {
            for (int j = 0; j < arraySize; j++) {
                arr[j] = rand() % 2000;
            }
            Sort::mergesort<int>(arr, arraySize);
        }

        mergesortTime = (clock() - mergesortTime);

        output << "quicksort time was: " << quicksortTime << std::endl;
        output << "bubblesort time was: " << bubblesortTime << std::endl;
        output << "insertionsort time was: " << insertionsortTime << std::endl;
        output << "mergesort time was: " << mergesortTime << std::endl;
    }

    void run() {
        verifyQuickSort();
        verifyBubbleSort();
        verifyInsertionSort();
        verifyMergeSort();

        compareTimings();
    }
};
