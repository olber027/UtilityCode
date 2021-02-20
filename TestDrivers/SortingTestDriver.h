//
// Created by molberding on 5/30/2017.
//
#include "SortingAlgorithms/Sorting.h"
#include "TestDriver.h"
#include <cstdlib>
#include <ctime>
#include <random>

class SortingTestDriver : public TestDriver
{
private:
    char* str;
    int* ints;
    double* doubles;
    int size;
    int iterations;

    template <typename T>
    bool isSorted(T* array)
    {
        for(int i = 0; i < size - 1; i++)
        {
            if(array[i] > array[i + 1])
            {
                return false;
            }
        }
        return true;
    }

public:
    SortingTestDriver();

    ~SortingTestDriver();

    void verifyQuickSort();

    void verifyBubbleSort();

    void verifyInsertionSort();

    void verifyMergeSort();

    void verifyRadixSort();

    void verifyShellSort();

    void run() override;
};
