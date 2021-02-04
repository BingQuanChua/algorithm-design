#include <iostream>
#include <string>
#include <fstream>
#include <cmath> 
#include <math.h>
#include "planet.cpp"
using namespace std;

static char characters[] = "ABCDEFGHIJ";
planet planets[10];
double matrix[10][10];

void getPlanetDetails();
void initAdjancencyMatrix();
void addEdge(int a, int b, double value);
void printAdjancencyMatrix();
void calculatePlanetDistance();
void generateDistance();

int main() {

    getPlanetDetails();
    initAdjancencyMatrix();
    calculatePlanetDistance();
    printAdjancencyMatrix();

    generateDistance();
    return 0;
}

void getPlanetDetails() {
    // read planet details from the folder

    string details;
    ifstream file("generated-data/A2planets.txt");
    for (int i = 0; i < 10; i++) {
        planet p;
        file >> details;
        p.name = details;
        file >> details;
        p.x = stoi(details);
        file >> details;
        p.y = stoi(details);
        file >> details;
        p.z = stoi(details);
        file >> details;
        p.weight = stoi(details);
        file >> details;
        p.profit = stoi(details);
        
        // stores each planet into the array
        planets[i] = p;
    }
    file.close();
}

void initAdjancencyMatrix() {
    // setting the map
    addEdge(0, 3, 1); // AD
    addEdge(0, 5, 1); // AF
    addEdge(0, 7, 1); // AH
    addEdge(0, 9, 1); // AJ
    addEdge(3, 9, 1); // DJ
    addEdge(7, 9, 1); // HJ
    addEdge(5, 7, 1); // FH
    addEdge(1, 3, 1); // BD
    addEdge(6, 9, 1); // GJ
    addEdge(7, 8, 1); // HI
    addEdge(2, 5, 1); // CF
    addEdge(1, 6, 1); // BG
    addEdge(6, 8, 1); // GI
    addEdge(2, 8, 1); // CI
    addEdge(1, 4, 1); // BE
    addEdge(4, 6, 1); // EG
    addEdge(4, 8, 1); // EI
    addEdge(2, 4, 1); // CE

    printAdjancencyMatrix();
}

void addEdge(int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

void printAdjancencyMatrix() {
    cout << " ";
    for (int i = 0; i < 10; i++) {
        cout << " " << characters[i];
    }
    cout << endl;
    for (int j = 0; j < 10; j++) {
        cout << characters[j] << " ";
        for (int i = 0; i < 10; i++) {
            cout << matrix[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void calculatePlanetDistance() {
    for (int j = 0; j < 10; j++) {
        for (int i = j; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                double distance = sqrt(pow((planets[j].x - planets[i].x),2) 
                + pow((planets[j].y - planets[i].y),2) 
                + pow((planets[j].z - planets[i].z),2));

                addEdge(i, j, distance);
            }
        }
    }
}

void generateDistance() {
    ofstream file;
    file.open("generated-data/planet-distances.txt");
    
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            file << matrix[j][i] << " ";
        }
        file << endl;
    }
    file << endl;

    file.close();
}