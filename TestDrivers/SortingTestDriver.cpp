//
// Created by olber on 2/20/2021.
//
#include "SortingTestDriver.h"

SortingTestDriver::SortingTestDriver() : TestDriver("Sorting")
{
    size       = 2000;
    str        = new char[size];
    ints       = new int[size];
    doubles    = new double[size];
    iterations = 50;
    srand(time(nullptr));
}

SortingTestDriver::~SortingTestDriver()
{
    delete str;
    delete ints;
    delete doubles;
}

void SortingTestDriver::verifyQuickSort()
{
    output << "Checking Quicksort functionality..." << std::endl;
    clock_t fastestTime = 1000000;
    clock_t slowestTime = 0;
    int average         = 0;
    clock_t totalTime   = clock();
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ints[j] = rand();
        }
        clock_t time = clock();
        Sorting::quicksort<int>(ints, size);
        time = clock() - time;
        if(time < fastestTime)
        {
            fastestTime = time;
        }
        if(time > slowestTime)
        {
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

void SortingTestDriver::verifyBubbleSort()
{
    output << "Checking bubblesort functionality..." << std::endl;
    clock_t fastestTime = 1000000;
    clock_t slowestTime = 0;
    int average         = 0;
    clock_t totalTime   = clock();
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ints[j] = rand();
        }
        clock_t time = clock();
        Sorting::bubblesort<int>(ints, size);
        time = clock() - time;
        if(time < fastestTime)
        {
            fastestTime = time;
        }
        if(time > slowestTime)
        {
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

void SortingTestDriver::verifyInsertionSort()
{
    output << "Checking insertionsort functionality..." << std::endl;
    clock_t fastestTime = 1000000;
    clock_t slowestTime = 0;
    int average         = 0;
    clock_t totalTime   = clock();
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ints[j] = rand();
        }
        clock_t time = clock();
        Sorting::insertionsort<int>(ints, size);
        time = clock() - time;
        if(time < fastestTime)
        {
            fastestTime = time;
        }
        if(time > slowestTime)
        {
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

void SortingTestDriver::verifyMergeSort()
{
    output << "Checking mergesort functionality..." << std::endl;
    clock_t fastestTime = 1000000;
    clock_t slowestTime = 0;
    int average         = 0;
    clock_t totalTime   = clock();
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ints[j] = rand();
        }
        clock_t time = clock();
        Sorting::mergesort<int>(ints, size);
        time = clock() - time;
        if(time < fastestTime)
        {
            fastestTime = time;
        }
        if(time > slowestTime)
        {
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

void SortingTestDriver::verifyRadixSort()
{
    output << "Checking radixsort functionality..." << std::endl;
    clock_t fastestTime = 1000000;
    clock_t slowestTime = 0;
    int average         = 0;
    clock_t totalTime   = clock();
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ints[j] = rand();
        }
        clock_t time = clock();
        Sorting::radixsort<int>(ints, size);
        time = clock() - time;
        if(time < fastestTime)
        {
            fastestTime = time;
        }
        if(time > slowestTime)
        {
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

void SortingTestDriver::verifyShellSort()
{
    output << "Checking shellsort functionality..." << std::endl;
    clock_t fastestTime = 1000000;
    clock_t slowestTime = 0;
    int average         = 0;
    clock_t totalTime   = clock();
    for(int i = 0; i < iterations; i++)
    {
        for(int j = 0; j < size; j++)
        {
            ints[j] = rand();
        }
        clock_t time = clock();
        Sorting::shellsort<int>(ints, size);
        time = clock() - time;
        if(time < fastestTime)
        {
            fastestTime = time;
        }
        if(time > slowestTime)
        {
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

void SortingTestDriver::run()
{
    verifyQuickSort();
    verifyBubbleSort();
    verifyInsertionSort();
    verifyMergeSort();
    verifyRadixSort();
    verifyShellSort();
}
