#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath> 
#include <math.h>
#include "planet.cpp"
#include "linkedlist.cpp"
using namespace std;

static char characters[] = "ABCDEFGHIJ";
planet planets[10];          // array of planets
double matrix[10][10];       // adjacency matrix of planets
LinkedList<int> list[10];    // adjacency list of planets

void getPlanetDetails();
void initAdjancencyMatrix();
void addEdge(int a, int b, double value);
void printAdjacencyMatrix();
void calculatePlanetDistance();
void generateDistance();
void initAdjacencyList();
void printAdjacencyList();
 
int main() {

    getPlanetDetails();
    initAdjancencyMatrix();
    calculatePlanetDistance();
    printAdjacencyMatrix();
    generateDistance();

    initAdjacencyList();
    printAdjacencyList();
    return 0;
}

// read planet details from the generated data
void getPlanetDetails() {

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

// initialize the map
void initAdjancencyMatrix() {

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

    printAdjacencyMatrix();
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix() {
    cout << " ";
    for (int i = 0; i < 10; i++) {
        cout << " " << setw(9) << characters[i];
    }
    cout << endl;
    for (int j = 0; j < 10; j++) {
        cout << characters[j] << " ";
        for (int i = 0; i < 10; i++) {
            cout << setw(9) << matrix[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

// calculate planet distance from the initialized matrix
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

// generate planet distance to a .txt file
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

void initAdjacencyList() {
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                list[j].insert(i, matrix[j][i]);
            }
        }
    }
}

// print adjacency list
void printAdjacencyList() {
    for (int i = 0; i < 10; i++) {
        cout << characters[i] << "-   ";
        cout << list[i] << endl;
    }
}