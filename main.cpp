#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
template <typename T>

//mergeSort
void mergeSortedLists(vector<T>& a, vector<T>& tmp, T leftPos, T rightPos, T rightEnd) {
    int leftEnd = rightPos - 1;
    int tempPos = leftPos;
    int numElements = rightEnd - leftPos + 1;

    while (leftPos <= leftEnd && rightPos <= rightEnd) {
        if (a[leftPos] <= a[rightPos]) {
            tmp[tempPos++] = a[leftPos++];
        } else {
            tmp[tempPos++] = a[rightPos++];
        }
    }
    while (leftPos <= leftEnd) {
        tmp[tempPos++] = a[leftPos++];
    }
    while (rightPos <= rightEnd) {
        tmp[tempPos++] = a[rightPos++];
    }
    for (int i = 0; i < numElements; i++, --rightEnd) {
        a[rightEnd] = tmp[rightEnd];
    }
}

template <typename T>
void mergeSort(vector<T>& a, vector<T>& tmp, T left, T right) {
    if (left < right) {
        int center = ( left + right ) / 2;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        mergeSortedLists(a, tmp, left, center + 1, right);
    }
}

template <typename T>
// Swap function (call within bubblesort)
void swap(T *a, T *b) {
    T temp = *a; // save the value of num1
    *a = *b; // copy over num2 to num1
    *b = temp; // copy the saved value of num1 --- switching their values not their pointers
}

template <typename T>
void bubbleSort(T *a, T n) {
    bool swapped = true;
    while (swapped) { // continue until there is no swap
        swapped = false;
        for (int k = 0; k < n - 1; k++) {
            if (a[k] > a[k + 1]) {
                swap(a[k], a[k + 1]);
                swapped = true; // if there is at least one swap make swapped true
            }
        }
    }
}

int main() {
    ifstream inFile;
    ofstream outFile;
    cout << "Hello, World!" << endl;
    return 0;
}