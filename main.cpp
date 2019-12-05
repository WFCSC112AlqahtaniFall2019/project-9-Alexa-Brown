/*
 * Alexa Brown
 * CSC 112
 * Project 9
 * Comparing four sorting algorithms and their efficiency in sorting a data set of 100,000 entries
 */

#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cassert>
#include <ctime>
using namespace std;

template <class T>
int breakApart(vector<T>& numbers, int i, int k);
template <class T>
void quickSort(vector<T>& numbers, int i, int k);
template <typename T>
void mergeSortedLists(vector<T>& a, vector<T>& tmp, int leftPos, int rightPos, int rightEnd);
template <class T>
void mergeSort(vector<T>& a, vector<T>& tmp, int left, int right);
template <class T, typename U>
void bubbleSort(vector<T>& a, U n);
template <class T>
void selectionSort(vector<T>& a, int n);

template <class T>
int breakApart(vector<T>& numbers, int start, int end) { //started with code from Zybooks, chapter 15.8- Quicksort
    /* Pick middle value as pivot */
    int midpoint = start + (end - start) / 2;
    T pivot = numbers.at(midpoint);
    bool done = false;

    /* Initialize variables */
    int l = start;
    int h = end;

    while (!done) {
        // Increment l if the pivot is greater than the higher value
        while (numbers.at(l) < pivot) {
            l++;
        }
        // Decrement h if the pivot is less than the higher value
        while (pivot < numbers.at(h)) {
            h--;
        }
        if (l >= h) { //already broken apart if there is one or no elements left
            done = true;
        }
        else {
            //swap left and right numbers then update
            T temp = numbers.at(l);
            numbers.at(l) = numbers.at(h);
            numbers.at(h) = temp;

            l++;
            h--;
        }
    }
    return h;
}

template <class T>
void quickSort(vector<T>& numbers, int i, int k) {
    int j;

    if (i >= k) { //if 1 or 0 elements, already sorted
        return;
    }
    j = breakApart(numbers, i, k); //continues to break apart the array and midpoint is at the end

    quickSort(numbers, i, j); //sorts low and high sections
    quickSort(numbers, j + 1, k);
}

template <typename T>
//mergeSort
void mergeSortedLists(vector<T>& a, vector<T>& tmp, int leftPos, int rightPos, int rightEnd) {
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
template <class T>
void mergeSort(vector<T>& a, vector<T>& tmp, int left, int right) {
    if (left < right) {
        int center = ( left + right ) / 2;
        mergeSort(a, tmp, left, center);
        mergeSort(a, tmp, center + 1, right);
        mergeSortedLists(a, tmp, left, center + 1, right);
    }
}
template <typename T>
// Swap function (called within bubblesort)
void swap(T *a, T *b) {
    T temp = *a; // save the value of num1
    *a = *b; // copy over num2 to num1
    *b = temp; // copy the saved value of num1 --- switching their values not their pointers
}

template <class T>
void selectionSort(vector<T>& a, int n){
    int i, j, min;

    // One by one move boundary of unsorted subarray
    for (i = 0; i < n-1; i++){
        // Find the minimum element in unsorted array
        min = i;
        for (j = i+1; j < n; j++)
            if (a.at(j)< a.at(min))
                min = j;

        // Swap the found minimum element with the first element
        swap(&a.at(min), &a.at(i));
    }
}

template <class T, typename U>
void bubbleSort(vector<T>& a, U n) {
    bool swapped = true;
    while (swapped) { // continue until there is no swap
        swapped = false;
        for (int k = 0; k < n - 1; k++) {
            if (a.at(k) > a.at(k + 1)) {
                swap(a.at(k), a.at(k + 1));
                swapped = true; // if there is at least one swap make swapped true
            }
        }
    }
}

int main() {
    ifstream inFile;
    ofstream outFile;
    int length;
    cout << "Input length of vector to use: "<< endl;
    cin >> length;

    vector <Data> dataV;
    vector <Data> dataV_B; //bubble sort
    vector <Data> dataV_S; //selection sort
    vector <Data> dataV_Q; //quick sort
    vector <Data> dataV_M; //merge sort
    vector<Data> datatemp; //temp to send to merge sort
    vector <int> intV;
    vector <int> intV_B; //bubble sort
    vector <int> intV_S; //selection sort
    vector <int> intV_Q; //quick sort
    vector <int> intV_M; //merge sort
    vector <int> temp;

    inFile.open("winemag-data_first150k.csv");

    if (!inFile.is_open()) {
        cout << "The input file did not open" << endl;
    }
    cout << "The file opened" << endl;

    int i = 0;
    while (i<length){
        //getline will go until the comma then will move on
        string r, c, p, reg;
        getline(inFile, r, ','); //rank
        getline(inFile, c, ','); //country
        getline(inFile, p, ','); //points
        getline(inFile, reg, '\n'); //region

        int rank = stoi(r); //change into integer
        int points = stod(p); //change into integer
        Data info = Data(rank, c, points, reg); //creating the Data object with the information
        // cout << "Hi" ;
        dataV.push_back(info);
        //  cout << "hello";
        i++;
    }

    //copy the Data vectors
    dataV_B = dataV;
    dataV_M = dataV;
    dataV_Q = dataV;
    dataV_S = dataV;
    datatemp = dataV;

    srand(time(0));

    for (int j = 0; j < length; ++j) {
        int a= rand() % 100;
        intV.push_back(a);
        //cout << intV.at(j) << " ";
    }

    //copy the vectors
    intV_B = intV;
    intV_M = intV;
    intV_Q = intV;
    intV_S = intV;
    temp = intV;
    cout << endl;

  // for (int n = 100000; n >= 0; n= n-10000) {
   // cout << "N = " << n << endl;

   cout << "INTEGERS" << endl;
        clock_t start_intselectionSort = clock();
        selectionSort(intV_S, intV_S.size());
        clock_t end_intselectionSort = clock();
        double intelapsed_selectionSort = double(end_intselectionSort - start_intselectionSort) / CLOCKS_PER_SEC;
        cout << "Time for int selection sort: " << intelapsed_selectionSort << endl;

        clock_t start_intselectionSort2 = clock();
        selectionSort(intV_S, intV_S.size());
        clock_t end_intselectionSort2 = clock();
        double intelapsed_selectionSort2 = double(end_intselectionSort2 - start_intselectionSort2) / CLOCKS_PER_SEC;
        cout << "Time for int selection sort again: " << intelapsed_selectionSort2 << endl;

        clock_t start_intbubbleSort = clock();
        bubbleSort(intV_B, intV_B.size());
        clock_t end_intbubbleSort = clock();
        double elapsed_intbubbleSort = double(end_intbubbleSort - start_intbubbleSort) / CLOCKS_PER_SEC;
        cout << "Time for int bubble sort: " << elapsed_intbubbleSort << endl;

        clock_t start_intbubbleSort2 = clock();
        bubbleSort(intV_B, intV_B.size());
        clock_t end_intbubbleSort2 = clock();
        double elapsed_intbubbleSort2 = double(end_intbubbleSort2 - start_intbubbleSort2) / CLOCKS_PER_SEC;
        cout << "Time for int bubble sort again: " << elapsed_intbubbleSort2 << endl;

        clock_t start_intquickSort = clock();
        quickSort(intV_Q, 0, intV_Q.size() - 1);
        clock_t end_intquickSort = clock();
        double elapsed_intquickSort = double(end_intquickSort - start_intquickSort) / CLOCKS_PER_SEC;
        cout << "Time for int quick sort: " << elapsed_intquickSort << endl;

        clock_t start_intquickSort2 = clock();
        quickSort(intV_Q, 0, intV_Q.size() - 1);
        clock_t end_intquickSort2 = clock();
        double elapsed_intquickSort2 = double(end_intquickSort2 - start_intquickSort2) / CLOCKS_PER_SEC;
        cout << "Time for int quick sort again: " << elapsed_intquickSort2 << endl;

        clock_t start_intmergeSort = clock();
        mergeSort(intV_M, temp, 0, intV_M.size() - 1);
        clock_t end_intmergeSort = clock();
        double elapsed_intmergeSort = double(end_intmergeSort - start_intmergeSort) / CLOCKS_PER_SEC;
        cout << "Time for int merge sort: " << elapsed_intmergeSort << endl;

        clock_t start_intmergeSort2 = clock();
        mergeSort(intV_M, temp, 0, intV_M.size() - 1);
        clock_t end_intmergeSort2 = clock();
        double elapsed_intmergeSort2 = double(end_intmergeSort2 - start_intmergeSort2) / CLOCKS_PER_SEC;
        cout << "Time for int merge sort again: " << elapsed_intmergeSort2 << endl;

    cout << "DATA" << endl;

        clock_t start_quickSort = clock();
        quickSort(dataV_Q, 0, dataV_Q.size() - 1);
        clock_t end_quickSort = clock();
        double elapsed_quickSort = double(end_quickSort - start_quickSort) / CLOCKS_PER_SEC;
        cout << "Time for data quick sort: " << elapsed_quickSort << endl;
        //unit test for quick sort
        for (int i = 1; i < dataV.size() - 1; i++) {
            assert(dataV_Q.at(i - 1) <= dataV_Q.at(i));
        }

        clock_t start_quickSort2 = clock();
        quickSort(dataV_Q, 0, dataV_Q.size() - 1);
        //quickSort(dataV_Q, 0, dataV_Q.size()-1);
        clock_t end_quickSort2 = clock();
        double elapsed_quickSort2 = double(end_quickSort2 - start_quickSort2) / CLOCKS_PER_SEC;
        cout << "Time for data quick sort again: " << elapsed_quickSort2 << endl;

        clock_t start_selectionSort = clock();
        selectionSort(dataV_S, dataV_S.size() - 1);
        clock_t end_selectionSort = clock();
        double elapsed_selectionSort = double(end_selectionSort - start_selectionSort) / CLOCKS_PER_SEC;
        cout << "Time for data selection sort: " << elapsed_selectionSort << endl;
        //unit test for selection sort
        for (int i = 1; i < dataV.size() - 1; i++) {
            assert(dataV_S.at(i - 1) <= dataV_S.at(i));
        }

        clock_t start_selectionSort2 = clock();
        selectionSort(dataV_S, dataV_S.size() - 1);
        clock_t end_selectionSort2 = clock();
        double elapsed_selectionSort2 = double(end_selectionSort2 - start_selectionSort2) / CLOCKS_PER_SEC;
        cout << "Time for data selection sort again: " << elapsed_selectionSort2 << endl;

        clock_t start_bubbleSort = clock();
        bubbleSort(dataV_B, dataV_B.size() - 1);
        clock_t end_bubbleSort = clock();
        double elapsed_bubbleSort = double(end_bubbleSort - start_bubbleSort) / CLOCKS_PER_SEC;
        cout << "Time for data bubble sort: " << elapsed_bubbleSort << endl;
        //unit test for bubble sort
        for (int i = 1; i < dataV.size() - 1; i++) {
            assert(dataV_B.at(i - 1) <= dataV_B.at(i));
        }

        clock_t start_bubbleSort2 = clock();
        bubbleSort(dataV_B, dataV_B.size() - 1);
        clock_t end_bubbleSort2 = clock();
        double elapsed_bubbleSort2 = double(end_bubbleSort2 - start_bubbleSort2) / CLOCKS_PER_SEC;
        cout << "Time for data bubble sort again: " << elapsed_bubbleSort2 << endl;


        clock_t start_mergeSort = clock();
        mergeSort(dataV_M, datatemp, 0, dataV_M.size() - 1);
        clock_t end_mergeSort = clock();
        double elapsed_mergeSort = double(end_mergeSort - start_mergeSort) / CLOCKS_PER_SEC;
        cout << "Time for data merge sort: " << elapsed_mergeSort << endl;
        //unit test for merge sort
        for (int i = 1; i < dataV.size() - 1; i++) {
            assert(dataV_M.at(i - 1) <= dataV_M.at(i));
        }

        clock_t start_mergeSort2 = clock();
        mergeSort(dataV_M, datatemp, 0, dataV_M.size() - 1);
        clock_t end_mergeSort2 = clock();
        double elapsed_mergeSort2 = double(end_mergeSort2 - start_mergeSort2) / CLOCKS_PER_SEC;
        cout << "Time for data merge sort again: " << elapsed_mergeSort2 << endl;


    inFile.close();
     cout << "Files are closed." << endl;

    return 0;
}