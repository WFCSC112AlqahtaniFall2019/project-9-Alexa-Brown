#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "time.h"
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
void bubbleSort(T a, T n) {
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
    vector <Data> dataV_B(length, Data());
    vector <Data> dataV_S(length, Data());
    vector <Data> dataV_Q(length, Data());
    vector <Data> dataV_M(length, Data());
    vector <int> intV(20);
    vector <int> intV_B(20);
    vector <int> intV_S(20);
    vector <int> intV_Q(20);
    vector <int> intV_M(20);
    vector <int> temp(20);
    int i;

    srand(time(0));
    for (int j = 0; j < 20; ++j) {
        intV.at(j) = rand() % 100;
        cout << intV.at(j) << " " << endl;
    }


    //bubbleSort(intV_B, 20);
   // mergeSort(intV_M,temp, 0, intV_M.size() - 1);


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
    cout << "Hi" ;
    //dataV.at(i) = info;
    cout << "hello";
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