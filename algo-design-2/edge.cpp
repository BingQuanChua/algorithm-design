#include <iostream>
#include <string>
using namespace std;

struct Edge
{
    char p1;
    char p2;
    double value; // edge value: distance in this case   

};

ostream &operator<< (ostream &os, const Edge &e) {
    string edge = "";
    edge += e.p1;
    edge += e.p2;
    os << edge;
    return os;
}