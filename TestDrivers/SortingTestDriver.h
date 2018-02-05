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
        init("Sorting");
        size = 2000;
        str = new char[size];
        ints = new int[size];
        doubles = new double[size];
        iterations = 50;
        srand(time(NULL));
    }

    ~SortingTestDriver() {
        delete str;
        delete ints;
        delete doubles;
    }

    void verifyQuickSort() {
        output << "Checking Quicksort functionality..." << std::endl;
        clock_t fastestTime = 1000000;
        clock_t slowestTime = 0;
        int average = 0;
        clock_t totalTime = clock();
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            clock_t time = clock();
            Sort::quicksort<int>(ints, size);
            time = clock() - time;
            if(time < fastestTime) {
                fastestTime = time;
            }
            if(time > slowestTime) {
                slowestTime = time;
            }
            average += (int) time;
            assert(true, isSorted<int>(ints));
        }
        totalTime = clock() - totalTime;
        output << "\tFastest: " << fastestTime << std::endl;
        output << "\tSlowest: " << slowestTime << std::endl;
        output << "\tAverage: " << (double) average / (double) iterations << std::endl;
        output << "\tTotal: " << totalTime << std::endl;
    }

    void verifyBubbleSort() {
        output << "Checking bubblesort functionality..." << std::endl;
        clock_t fastestTime = 1000000;
        clock_t slowestTime = 0;
        int average = 0;
        clock_t totalTime = clock();
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            clock_t time = clock();
            Sort::bubblesort<int>(ints, size);
            time = clock() - time;
            if(time < fastestTime) {
                fastestTime = time;
            }
            if(time > slowestTime) {
                slowestTime = time;
            }
            average += (int) time;
            assert(true, isSorted<int>(ints));
        }
        totalTime = clock() - totalTime;
        output << "\tFastest: " << fastestTime << std::endl;
        output << "\tSlowest: " << slowestTime << std::endl;
        output << "\tAverage: " << (double) average / (double) iterations << std::endl;
        output << "\tTotal: " << totalTime << std::endl;
    }

    void verifyInsertionSort() {
        output << "Checking insertionsort functionality..." << std::endl;
        clock_t fastestTime = 1000000;
        clock_t slowestTime = 0;
        int average = 0;
        clock_t totalTime = clock();
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            clock_t time = clock();
            Sort::insertionsort<int>(ints, size);
            time = clock() - time;
            if(time < fastestTime) {
                fastestTime = time;
            }
            if(time > slowestTime) {
                slowestTime = time;
            }
            average += (int) time;
            assert(true, isSorted<int>(ints));
        }
        totalTime = clock() - totalTime;
        output << "\tFastest: " << fastestTime << std::endl;
        output << "\tSlowest: " << slowestTime << std::endl;
        output << "\tAverage: " << (double) average / (double) iterations << std::endl;
        output << "\tTotal: " << totalTime << std::endl;
    }

    void verifyMergeSort() {
        output << "Checking mergesort functionality..." << std::endl;
        clock_t fastestTime = 1000000;
        clock_t slowestTime = 0;
        int average = 0;
        clock_t totalTime = clock();
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            clock_t time = clock();
            Sort::mergesort<int>(ints, size);
            time = clock() - time;
            if(time < fastestTime) {
                fastestTime = time;
            }
            if(time > slowestTime) {
                slowestTime = time;
            }
            average += (int) time;
            assert(true, isSorted<int>(ints));
        }
        totalTime = clock() - totalTime;
        output << "\tFastest: " << fastestTime << std::endl;
        output << "\tSlowest: " << slowestTime << std::endl;
        output << "\tAverage: " << (double) average / (double) iterations << std::endl;
        output << "\tTotal: " << totalTime << std::endl;
    }

    void verifyRadixSort() {
        output << "Checking radixsort functionality..." << std::endl;
        clock_t fastestTime = 1000000;
        clock_t slowestTime = 0;
        int average = 0;
        clock_t totalTime = clock();
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            clock_t time = clock();
            Sort::radixsort<int>(ints, size);
            time = clock() - time;
            if(time < fastestTime) {
                fastestTime = time;
            }
            if(time > slowestTime) {
                slowestTime = time;
            }
            average += (int) time;
            assert(true, isSorted<int>(ints));
        }
        totalTime = clock() - totalTime;
        output << "\tFastest: " << fastestTime << std::endl;
        output << "\tSlowest: " << slowestTime << std::endl;
        output << "\tAverage: " << (double) average / (double) iterations << std::endl;
        output << "\tTotal: " << totalTime << std::endl;
    }

    void verifyShellSort() {
        output << "Checking shellsort functionality..." << std::endl;
        clock_t fastestTime = 1000000;
        clock_t slowestTime = 0;
        int average = 0;
        clock_t totalTime = clock();
        for(int i = 0; i < iterations; i++) {
            for(int j = 0; j < size; j++) {
                ints[j] = rand();
            }
            clock_t time = clock();
            Sort::shellsort<int>(ints, size);
            time = clock() - time;
            if(time < fastestTime) {
                fastestTime = time;
            }
            if(time > slowestTime) {
                slowestTime = time;
            }
            average += (int) time;
            assert(true, isSorted<int>(ints));
        }
        totalTime = clock() - totalTime;
        output << "\tFastest: " << fastestTime << std::endl;
        output << "\tSlowest: " << slowestTime << std::endl;
        output << "\tAverage: " << (double) average / (double) iterations << std::endl;
        output << "\tTotal: " << totalTime << std::endl;
    }

    void run() {
        verifyQuickSort();
        verifyBubbleSort();
        verifyInsertionSort();
        verifyMergeSort();
        verifyRadixSort();
        verifyShellSort();
    }
};
