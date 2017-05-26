//
// Created by molberding on 5/26/2017.
//

#ifndef UTILITYCODE_SORT_H
#define UTILITYCODE_SORT_H

#include <cstdlib>

class Sort {
private:
    Sort() {}
    template<typename T> static void quicksortHelper(T* array, int left, int right) {
        if (left > right) {
            return;
        }
        int pivotValue = array[right];
        int i = left;
        int j = right-1;
        while(i <= j) {
            if(array[i] <= pivotValue) {
                i++;
            } else {
                T temp = array[j];
                array[j] = array[i];
                array[i] = temp;
                j--;
            }
        }
        T temp = array[i];
        array[right] = temp;
        array[i] = pivotValue;

        quicksortHelper<T>(array, 0, i-1);
        quicksortHelper<T>(array, i+1, right);
    }

public:
    template<typename T> static void quicksort(T* array, int size) {
        int left = 0;
        int right = size-1;
        quicksortHelper<T>(array, left, right);
    }
};

#endif //UTILITYCODE_SORT_H