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
    rank = 0;
    country = "";
    points = 0;
    region = " ";
}
Data::Data(int r, string c, int p, string reg) { //alternate constructor
    rank = r;
    country = c;
    points = p;
    region = reg;
}


bool operator > (const Data &d, const Data & d2) { // > overloader
    return d.rank > d2.rank;
    /*if (this->happinessRank < d.happinessRank){
        return false;
    }
    else return this->happinessRank > d.happinessRank;
*/
}
/*
bool operator = (const Data &d, const Data & d2) { // = overloader
    return d.rank == d2.rank;

}*/
bool operator <= (const Data &d, const Data &d2){
    return d.rank <= d2.rank;
}


bool operator < (const Data &d, const Data &d2){ // < overloader
    return d.rank < d2.rank;
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

Data& Data::operator = (const Data &copy){
    Data tmp (copy);
    swap(tmp.rank, rank);
    swap(tmp.region, region);
    swap(tmp.points, points);
    swap(tmp.country, country);

    return *this;

}

ostream& operator << (ostream& os, const Data a){ //overloaded to print to the files
    os << "Country: " << a.country << " Region: " << a.region <<  "  Rank: " << a.rank << "  Points: " << a.points << endl;
    cout << "Printing" << endl; // to check that it is printing when called
    return os;
}
