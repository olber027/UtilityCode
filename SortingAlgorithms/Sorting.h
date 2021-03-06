//
// Created by molberding on 5/26/2017.
//

#ifndef UTILITYCODE_SORTING_H
#define UTILITYCODE_SORTING_H

#include <cmath>
#include <cstdlib>

class Sorting
{
private:
    Sorting() = default;

    template <typename T>
    static void swap(T* array, const int i, const int j)
    {
        T temp   = array[j];
        array[j] = array[i];
        array[i] = temp;
    }

    template <typename T>
    static void quicksortHelper(T* array, const int left, const int right)
    {
        if(left >= right)
        {
            return;
        }
        T pivotValue = array[right];
        int i        = left;
        int j        = right - 1;
        while(i <= j)
        {
            if(array[i] <= pivotValue)
            {
                i++;
            }
            else
            {
                swap(array, i, j);
                j--;
            }
        }
        swap(array, i, right);

        quicksortHelper<T>(array, left, i - 1);
        quicksortHelper<T>(array, i + 1, right);
    }

    template <typename T>
    static T* mergesortHelper(T* array, const int size)
    {
        if(size <= 1)
        {
            return array;
        }
        int midpoint = size / 2;
        T* left      = new T[midpoint];
        T* right     = new T[size - midpoint];
        for(int i = 0; i < size; i++)
        {
            if(i < midpoint)
            {
                left[i] = array[i];
            }
            else
            {
                right[i - midpoint] = array[i];
            }
        }

        left      = mergesortHelper(left, midpoint);
        right     = mergesortHelper(right, size - midpoint);
        T* result = mergeArrays<T>(left, midpoint, right, size - midpoint);
        delete left;
        delete right;
        return result;
    }

    //merges the left and right arrays in sorted order.
    template <typename T>
    static T* mergeArrays(const T* left, const int leftSize, const T* right, const int rightSize)
    {
        int totalSize  = leftSize + rightSize;
        T* result      = new T[totalSize];
        int leftIndex  = 0;
        int rightIndex = 0;
        while((leftIndex + rightIndex < totalSize) && (leftIndex < leftSize) && (rightIndex < rightSize))
        {
            if(left[leftIndex] < right[rightIndex])
            {
                result[leftIndex + rightIndex] = left[leftIndex++];
            }
            else
            {
                result[leftIndex + rightIndex] = right[rightIndex++];
            }
        }
        while(leftIndex < leftSize)
        {
            result[leftIndex + rightIndex] = left[leftIndex++];
        }
        while(rightIndex < rightSize)
        {
            result[leftIndex + rightIndex] = right[rightIndex++];
        }

        return result;
    }

    //appends the right array to the left array and returns the result as a new array.
    template <typename T>
    static T* concatenateArray(const T* left, const int leftSize, const T* right, const int rightSize)
    {
        int totalSize = leftSize + rightSize;
        T* result     = new T[totalSize];
        int j         = 0;
        for(int i = 0; i < leftSize; i++, j++)
        {
            result[j] = left[i];
        }
        for(int i = 0; i < rightSize; i++, j++)
        {
            result[j] = right[i];
        }
        return result;
    }

    template <typename T>
    static void radixsortHelper(T* array, const int size, const int depth)
    {
        T** buckets      = new T*[10];
        int* bucketSizes = new int[10];
        for(int i = 0; i < 10; i++)
        {
            buckets[i]     = new T[size];
            bucketSizes[i] = 0;
        }
        int divisor = 1;
        for(int i = 0; i < depth; i++) divisor *= 10;

        for(int i = 0; i < size; i++)
        {
            int index = array[i] ? array[i] / divisor : 0;
            index     = index % 10;

            buckets[index][bucketSizes[index]] = array[i];
            bucketSizes[index] += 1;
        }

        int index = 0;
        for(int i = 0; i < 10; i++)
        {
            if(depth > 0 && bucketSizes[i] > 1)
            {
                radixsortHelper(buckets[i], bucketSizes[i], depth - 1);
            }
            for(int j = 0; j < bucketSizes[i]; j++)
            {
                array[index++] = buckets[i][j];
            }
            delete buckets[i];
        }

        delete buckets;
        delete bucketSizes;
    }

    template <typename T>
    static void shellsortHelper(T* array, const int size, const int* gapList, const int gapListSize)
    {
        for(int g = 0; g < gapListSize; g++)
        {
            int gap = gapList[g];
            for(int i = gap; i < size; i++)
            {
                int j;
                T temp = array[i];
                for(j = i; j >= gap && array[j - gap] > temp; j -= gap)
                {
                    array[j] = array[j - gap];
                }
                array[j] = temp;
            }
        }
    }

public:
    template <typename T>
    static void quicksort(T* array, const int size)
    {
        quicksortHelper<T>(array, 0, size - 1);
    }

    template <typename T>
    static void bubblesort(T* array, const int size)
    {
        bool swapped;
        do {
            swapped = false;
            for(int i = 0; i < size - 1; i++)
            {
                if(array[i] > array[i + 1])
                {
                    swap(array, i, i + 1);
                    swapped = true;
                }
            }
        } while(swapped);
    }

    template <typename T>
    static void insertionsort(T* array, const int size)
    {
        for(int i = 1; i < size; i++)
        {
            int j = i;
            while(j > 0 && array[j - 1] > array[j])
            {
                swap(array, j, j - 1);
                j--;
            }
        }
    }

    template <typename T>
    static void mergesort(T* array, const int size)
    {
        T* temp = mergesortHelper<T>(array, size);
        for(int i = 0; i < size; i++)
        {
            array[i] = temp[i];
        }
        delete temp;
    }

    template <typename T>
    static void radixsort(T* array, const int size)
    {
        int maxDepth = 0;
        T max        = array[0];
        int j        = 10;
        for(int i = 1; i < size; i++)
        {
            if(array[i] > max)
            {
                max = array[i];
            }
        }
        while(max / j > 0)
        {
            maxDepth++;
            j *= 10;
        }
        radixsortHelper(array, size, maxDepth);
    }

    template <typename T>
    static void shellsort(T* array, const int size)
    {
        int gapListSize = static_cast<int>((log(size) / log(2)) + 1);
        int* gapList    = new int[gapListSize];
        gapList[0]      = 1;
        for(int i = 1; i < gapListSize; i++)
        {
            gapList[i] = static_cast<int>(pow(2, i) + 1);
        }
        shellsortHelper(array, size, gapList, gapListSize);
    }

    template <typename T>
    static bool isSorted(const T* array, const int size)
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
};

#endif//UTILITYCODE_SORTING_H