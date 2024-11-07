#ifndef TRIP_H
#define TRIP_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <limits>
#include <tuple>
#include <cctype>
#include <algorithm>


using namespace std;

class Trip {
public:
    string from; //departure city
    string to; //arrival city
    string date; //departure date
    int price; 
    int available_seats;

    void addTrip();
    void removeTrip();
    void findTrip();
    void bookTrip();
};


#endif