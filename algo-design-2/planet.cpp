#include <iostream>
#include <string>
using namespace std;

struct Planet
{
    string name;            // planet full name: "Planet_X"
    char planetCharacter;   // planet character: "X"
    int x;                  // x coordinate 
    int y;                  // y coordinate 
    int z;                  // z coordinate 
    int weight;
    int profit;
    double value = 0;       // value calculated from profit/weight

    double calculateValue() 
    {
        value = 1.0*profit/weight;
        return value;
    }
};

// print the planet character ("X") when it is called
ostream &operator<< (ostream &os, const Planet &p) {
    os << p.planetCharacter;
    return os;
}