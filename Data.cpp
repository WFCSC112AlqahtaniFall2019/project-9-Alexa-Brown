/*
 * Alexa Brown
 * CSC 112
 * Project 9
 */
#include "Data.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

Data::Data() { //default constructor
    country = "";
    happinessRank = 0;
    happinessScore = 0;
    GDP = 0;
}
Data::Data(string c, int rank, double score, double g) { //alternate constructor
    country = c;
    happinessRank = rank;
    happinessScore = score;
    GDP = g;
}


bool operator > (const Data &d, const Data & d2) { // > overloader
    return d.happinessRank > d2.happinessRank;
    /*if (this->happinessRank < d.happinessRank){
        return false;
    }
    elsereturn this->happinessRank > d.happinessRank;
*/
}


bool operator < (const Data &d, const Data &d2){ // < overloader
    return d.happinessRank < d2.happinessRank;
    /*
    if (d.happinessRank > d2.happinessRank){
        return false;
    }
    else if (d.happinessRank < d2.happinessRank){
        return true;
    }
    else {
        return false;
    }*/

}

ostream& operator << (ostream& os, const Data a){ //overloaded to print to the files
    os << "Country: " << a.country << "  Rank: " << a.happinessRank << "  Score: " << a.happinessScore << "  GDP: " << a.GDP << endl;
    cout << "Printing" << endl; // to check that it is printing when called
    return os;
}
