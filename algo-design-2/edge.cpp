#include <iostream>
#include <string>
using namespace std;

struct Edge
{
    Planet p1; 
    Planet p2;
    double distance; // distance in this case   

    double calculateDistance() {
        distance = sqrt(pow((p1.x - p2.x),2) 
                + pow((p1.y - p2.y),2) 
                + pow((p1.z - p2.z),2));
        return distance;
    }

};

ostream &operator<< (ostream &os, const Edge &e) {
    string edge = "";
    edge += e.p1.planetCharacter;
    edge += e.p2.planetCharacter;
    os << edge;
    return os;
}