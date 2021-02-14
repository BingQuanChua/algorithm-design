#include <iostream>
#include <string>
using namespace std;

struct Planet
{
    string name;
    int x;
    int y;
    int z;
    int weight;
    int profit;

    double calculateValue() 
    {
        return profit/weight;
    }
};