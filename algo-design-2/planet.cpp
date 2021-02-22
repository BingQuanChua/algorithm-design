#include <iostream>
#include <string>
using namespace std;

struct Planet
{
    char name;
    int x;
    int y;
    int z;
    int weight;
    int profit;
    double value = 0;

    double calculateValue() 
    {
        value = 1.0*profit/weight;
        return value;
    }
};

ostream &operator<< (ostream &os, const Planet &p) {
    os << p.name;
    return os;
}