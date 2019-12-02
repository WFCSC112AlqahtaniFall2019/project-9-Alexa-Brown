#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "time.h"
using namespace std;
template <class T>
int Partition(vector<T>& numbers, int i, int k);
template <class T>
void quickSort(vector<T>& numbers, int i, int k);
template <typename T>
void mergeSortedLists(vector<T>& a, vector<T>& tmp, T leftPos, T rightPos, T rightEnd);
template <class T>
void mergeSort(vector<T>& a, vector<T>& tmp, int left, int right);
//void mergeSort(vector<T>& a, vector<T>& tmp, T left, T right);
template <class T, typename U>
void bubbleSort(vector<T>& a, U n);


template <class T>
int Partition(vector<T>& numbers, int i, int k) { //started with code from Zybooks, chapter 15.8- Quicksort
    /* Pick middle value as pivot */
    T midpoint = i + (k - i) / 2;
    T pivot = numbers[midpoint];
    T done = false;

    /* Initialize variables */
    T l = i;
    T h = k;

    while (!done) {
        /* Increment l while numbers[l] < pivot */
        while (numbers[l] < pivot) {
            ++l;
        }
        /* Decrement h while pivot < numbers[h] */
        while (pivot < numbers[h]) {
            --h;
        }
        if (l >= h) { //already partitioned if there is one or no elements left
            done = true;
        }
        else {
            /* Swap numbers[l] and numbers[h],
                update l and h */
            T temp = numbers[l];
            numbers[l] = numbers[h];
            numbers[h] = temp;

            ++l;
            --h;
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
    j = Partition(numbers, i, k); //continues to break apart the array and midpoint is at the end

    quickSort(numbers, i, j); //sorts low and high sections
    quickSort(numbers, j + 1, k);
}

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

template <class T>
//void mergeSort(vector<Data>& a, vector<Data>& tmp, U left, U right) {
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
    int length = 100000;

    vector <Data> dataV (length, Data());
    vector <Data> dataV_B(length, Data()); //bubble sort
    vector <Data> dataV_S(length, Data()); //selection sort
    vector <Data> dataV_Q(length, Data()); //quick sort
    vector <Data> dataV_M(length, Data()); //merge sort
    vector <int> intV(20);
    vector <int> intV_B(20); //bubble sort
    vector <int> intV_S(20); //selection sort
    vector <int> intV_Q(20); //quick sort
    vector <int> intV_M(20); //merge sort
    vector <int> temp(20);
    int i = 0;

    srand(time(0));
    for (int j = 0; j < 20; ++j) {
        int a= rand() % 100;
        intV.at(j) = a;
        intV_B.at(j) = a;
        intV_M.at(j)= a;
        intV_Q.at(j) = a;
        intV_S.at(j) = a;
        cout << intV.at(j) << " ";
    }
    cout << endl;
    quickSort(intV_Q, 0, 19);

    bubbleSort(intV_B, 20);
    mergeSort(intV_M,temp, 0, intV_M.size() - 1);
   cout << "sorted\n";
    for (int j = 0; j < 20; j++) {
        cout << intV_B.at(j) << " ";
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
    cout << endl;
    inFile.open("winemag-data_first150k.csv");

    if (!inFile.is_open()) {
        cout << "The input file did not open" << endl;
    }
    cout << "The file opened" << endl;


     while (!inFile.eof()) {

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
/*
    for (int j = 0; j < 100; ++j) {
        cout << v[j];

    }*/

     inFile.close();
     cout << "Files are closed." << endl;

    return 0;
}