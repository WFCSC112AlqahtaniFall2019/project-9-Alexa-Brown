#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "time.h"
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
// Swap function (call within bubblesort)
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
    cout << "Input length"<< endl;
    cin >> length;

    vector <Data> dataV (length, Data());
    vector <Data> dataV_B(length, Data()); //bubble sort
    vector <Data> dataV_S(length, Data()); //selection sort
    vector <Data> dataV_Q(length, Data()); //quick sort
    vector <Data> dataV_M(length, Data()); //merge sort
    vector<Data> datatemp (length, Data()); //temp to send to merge sort
    vector <int> intV(length);
    vector <int> intV_B(length); //bubble sort
    vector <int> intV_S(length); //selection sort
    vector <int> intV_Q(length); //quick sort
    vector <int> intV_M(length); //merge sort
    vector <int> temp(length);
    //int i = 0;

    srand(time(0));
    for (int j = 0; j < length; ++j) {
        int a= rand() % 100;
        intV.at(j) = a;
        intV_B.at(j) = a;
        intV_M.at(j)= a;
        intV_Q.at(j) = a;
        intV_S.at(j) = a;
        //cout << intV.at(j) << " ";
    }
    cout << endl;
    clock_t start_intselectionSort = clock();
    selectionSort(intV_S, intV_S.size());
    clock_t end_intselectionSort = clock();
    double intelapsed_selectionSort = double(end_intselectionSort - start_intselectionSort) / CLOCKS_PER_SEC;
    cout << "Time for int selection sort: " << intelapsed_selectionSort << endl;
    //cout << "data selection sort done";

    clock_t start_intbubbleSort = clock();
    bubbleSort(intV_B, intV_B.size());
    clock_t end_intbubbleSort = clock();
    double elapsed_intbubbleSort = double(end_intbubbleSort - start_intbubbleSort) / CLOCKS_PER_SEC;
    cout << "Time for int bubble sort: " << elapsed_intbubbleSort << endl;

    clock_t start_intquickSort = clock();
    quickSort(intV_Q, 0, intV_Q.size() - 1);
    clock_t end_intquickSort = clock();
    double elapsed_intquickSort = double(end_intquickSort - start_intquickSort) / CLOCKS_PER_SEC;
    cout << "Time for int quick sort: " << elapsed_intquickSort << endl;

    clock_t start_intmergeSort = clock();
    mergeSort(intV_M,temp, 0, intV_M.size() - 1);
    clock_t end_intmergeSort = clock();
    double elapsed_intmergeSort = double(end_intmergeSort - start_intmergeSort) / CLOCKS_PER_SEC;
    cout << "Time for int merge sort: " << elapsed_intquickSort << endl;

 /*  cout << "bubble sorted\n";
    for (int j = 0; j < 20; j++) {
        cout << intV_B.at(j) << " ";
    }
    cout << endl;
    cout << "selection sorted\n";
    for (int j = 0; j < 20; j++) {
        cout << intV_S.at(j) << " ";
    }
    cout << endl;
    cout << "merge sorted\n";
    for (int j = 0; j < 20; j++) {
        cout << intV_M.at(j) << " ";
    }
    cout << endl;
    cout << "quick sorted\n";
    for (int j = 0; j < 20; j++) {
        cout << intV_Q.at(j) << " ";
    }
    cout << endl;  */
    inFile.open("winemag-data_first150k.csv");

    if (!inFile.is_open()) {
        cout << "The input file did not open" << endl;
    }
    cout << "The file opened" << endl;

int i = 0;
    while (i<length){
    // while (!inFile.eof()) {

    //cout << "hi" <<endl;

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
    dataV.at(i) = info;
    dataV_B.at(i) = info;
    dataV_M.at(i) = info;
    dataV_Q.at(i) = info;
    dataV_S.at(i) = info;
  //  cout << "hello";
    i++;
    // cout << info.getCountry() << info.getRank() << info.getRegion();
}

    clock_t start_quickSort = clock();
    //quickSort(dataV_Q, 0, );
    quickSort(dataV_Q, 0, dataV_Q.size()-1);
    clock_t end_quickSort = clock();
    double elapsed_quickSort = double(end_quickSort - start_quickSort) / CLOCKS_PER_SEC;
    cout << "Time for data quick sort: " << elapsed_quickSort << endl;

    cout << "quick sort ran" << endl;
    clock_t start_quickSort2 = clock();
    quickSort(dataV_Q, 0, dataV_Q.size()-1);
    //quickSort(dataV_Q, 0, dataV_Q.size()-1);
    clock_t end_quickSort2 = clock();
    double elapsed_quickSort2 = double(end_quickSort2 - start_quickSort2) / CLOCKS_PER_SEC;
    cout << "Time for data quick sort again: " << elapsed_quickSort2 << endl;

    clock_t start_selectionSort = clock();
    selectionSort(dataV_S, dataV_S.size() - 1);
    clock_t end_selectionSort = clock();
    double elapsed_selectionSort = double(end_selectionSort - start_selectionSort) / CLOCKS_PER_SEC;
    cout << "Time for data selection sort: " << elapsed_selectionSort << endl;
    //cout << "data selection sort done";

    clock_t start_bubbleSort = clock();
    bubbleSort(dataV_B, dataV_B.size() - 1);
    clock_t end_bubbleSort = clock();
    double elapsed_bubbleSort = double(end_bubbleSort - start_bubbleSort) / CLOCKS_PER_SEC;
    cout << "Time for data bubble sort: " << elapsed_bubbleSort << endl;
    //cout << "data bubble sort done";


    mergeSort(dataV_M, datatemp, 0, dataV_M.size() - 1);
    cout << "mergesort ran" << endl;
/*
    for (int j = 0; j < 100; ++j) {
        cout << v[j];

    }*/

     inFile.close();
     cout << "Files are closed." << endl;

    return 0;
}