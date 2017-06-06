//
// Created by molberding on 5/26/2017.
//

#ifndef UTILITYCODE_SORT_H
#define UTILITYCODE_SORT_H

#include <cstdlib>
#include <iostream>
#include <vector>

class Sort {
private:
    Sort() {}

    template<typename T> static void swap(T* array, int i, int j) {
        T temp = array[j];
        array[j] = array[i];
        array[i] = temp;
    }

    template<typename T> static void quicksortHelper(T* array, int left, int right) {
        if (left >= right) {
            return;
        }
        int pivotValue = array[right];
        int i = left;
        int j = right-1;
        while(i <= j) {
            if(array[i] <= pivotValue) {
                i++;
            } else {
                swap(array,i,j);
                j--;
            }
        }
        swap(array,i,right);

        quicksortHelper<T>(array, left, i-1);
        quicksortHelper<T>(array, i+1, right);
    }

    template<typename T> static T* mergesortHelper(T* array, int size) {
        if(size <= 1) {
            return array;
        }
        int midpoint = size/2;
        T* left = new T[midpoint];
        T* right = new T[size-midpoint];
        for(int i = 0; i < size; i++) {
            if(i < midpoint) {
                left[i] = array[i];
            } else {
                right[i-midpoint] = array[i];
            }
        }

        left = mergesortHelper(left, midpoint);
        right = mergesortHelper(right, size-midpoint);
        T* result = combineArrays<T>(left, midpoint, right, size-midpoint);
        delete left;
        delete right;
        return result;
    }

    template<typename T> static T* combineArrays(T* left, int leftSize, T* right, int rightSize) {
        int totalSize = leftSize + rightSize;
        T* result = new T[totalSize];
        int leftIndex = 0;
        int rightIndex = 0;
        while((leftIndex + rightIndex < totalSize) && (leftIndex < leftSize) && (rightIndex < rightSize)) {
            if(left[leftIndex] < right[rightIndex]) {
                result[leftIndex + rightIndex] = left[leftIndex++];
            } else {
                result[leftIndex + rightIndex] = right[rightIndex++];
            }
        }
        while(leftIndex < leftSize) {
            result[leftIndex + rightIndex] = left[leftIndex++];
        }
        while(rightIndex < rightSize) {
            result[leftIndex + rightIndex] = right[rightIndex++];
        }

        return result;
    }

public:
    template<typename T> static void quicksort(T* array, int size) {
        quicksortHelper<T>(array, 0, size-1);
    }

    template<typename T> static void bubblesort(T* array, int size) {
        bool swapped;
        do {
            swapped = false;
            for(int i = 0; i < size-1; i++) {
                if(array[i] > array[i+1]) {
                    swap(array, i, i+1);
                    swapped = true;
                }
            }
        } while(swapped);
    }

    template<typename T> static void insertionsort(T* array, int size) {
        for(int i = 1; i < size; i++) {
            int j = i;
            while(j > 0 && array[j-1] > array[j]) {
                swap(array,j, j-1);
                j--;
            }
        }
    }

    template<typename T> static void mergesort(T* array, int size) {
        T* temp = mergesortHelper<T>(array, size);
        for(int i = 0; i < size; i++) {
            array[i] = temp[i];
        }
        delete temp;
    }

    template<typename T> static bool isSorted(T* array, int size) {
        for(int i = 0; i < size-1; i++) {
            if(array[i] > array[i+1]) {
                return false;
            }
        }
        return true;
    }
};

#endif //UTILITYCODE_SORT_H