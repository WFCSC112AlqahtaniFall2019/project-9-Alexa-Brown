/*
 * Alexa Brown
 * CSC 112
 * Project 9
 */
#ifndef PROJECT9_DATA_H
#define PROJECT9_DATA_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class Data {
    friend ostream& operator << (ostream& os, Data a);
public:
    int rank;
    string country;
    int points;
    string region;

    Data();
    Data(int rank, string country, int points, string region);

    friend bool operator > (const Data &d, const Data & d2);
    friend bool operator < (const Data &d, const Data & d2);
    friend bool operator <= (const Data &d, const Data &d2);
    Data& operator = (const Data &copy);

    void setCountry (string c){
        country = c;
    }
    string getCountry(){
        return country;
    }
    void setRank (int r){
        rank = r;
    }
    int getRank(){
        return rank;
    }
    void setPoints (int p){
        points = p;
    }
    int getPoints(){
        return points;
    }
    void setRegion(string reg){
        region = reg;
    }
    string getRegion(){
        return region;
    }


};


#endif //PROJECT9_DATA_H
