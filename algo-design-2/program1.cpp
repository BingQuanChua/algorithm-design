#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath> 
#include <math.h>
#include "planet.cpp"
#include "linkedlist.cpp"
using namespace std;

const int N = 10;

void getPlanetDetails(Planet *planets);
void initAdjancencyMatrix(double matrix[][N]);
void addEdge(double matrix[][N], int a, int b, double value);
void printAdjacencyMatrix(double matrix[][N]);
void calculatePlanetDistance(Planet *planets, double matrix[][N]);
void generateDistance(double matrix[][N]);
void initAdjacencyList(LinkedList<int> *list, double matrix[][N]);
void printAdjacencyList(LinkedList<int> *list);
 
int main() {

    Planet planets[N];          // array of planets
    double matrix[N][N] = {0};  // adjacency matrix of planets
    LinkedList<int> list[N];    // adjacency list of planets

    // read planet details from file
    getPlanetDetails(planets);

    // initialize the adjacency matrix, calculate distance
    initAdjancencyMatrix(matrix);
    calculatePlanetDistance(planets, matrix);
    printAdjacencyMatrix(matrix);
    generateDistance(matrix);

    // initialize the adjacency list from the adjacency matrix
    initAdjacencyList(list, matrix);
    printAdjacencyList(list);
    return 0;
}

// read planet details from the generated data
void getPlanetDetails(Planet *planets) {

    string details;
    ifstream file("generated-data/A2planets.txt");
    for (int i = 0; i < 10; i++) {
        Planet p;
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
void initAdjancencyMatrix(double matrix[][N]) {

    addEdge(matrix, 0, 3, 1); // AD
    addEdge(matrix, 0, 5, 1); // AF
    addEdge(matrix, 0, 7, 1); // AH
    addEdge(matrix, 0, 9, 1); // AJ
    addEdge(matrix, 3, 9, 1); // DJ
    addEdge(matrix, 7, 9, 1); // HJ
    addEdge(matrix, 5, 7, 1); // FH
    addEdge(matrix, 1, 3, 1); // BD
    addEdge(matrix, 6, 9, 1); // GJ
    addEdge(matrix, 7, 8, 1); // HI
    addEdge(matrix, 2, 5, 1); // CF
    addEdge(matrix, 1, 6, 1); // BG
    addEdge(matrix, 6, 8, 1); // GI
    addEdge(matrix, 2, 8, 1); // CI
    addEdge(matrix, 1, 4, 1); // BE
    addEdge(matrix, 4, 6, 1); // EG
    addEdge(matrix, 4, 8, 1); // EI
    addEdge(matrix, 2, 4, 1); // CE

    printAdjacencyMatrix(matrix);
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(double matrix[][N], int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix(double matrix[][N]) {
    char characters[] = "ABCDEFGHIJ";

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
void calculatePlanetDistance(Planet *planets, double matrix[][N]) {
    for (int j = 0; j < 10; j++) {
        for (int i = j; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                double distance = sqrt(pow((planets[j].x - planets[i].x),2) 
                + pow((planets[j].y - planets[i].y),2) 
                + pow((planets[j].z - planets[i].z),2));

                addEdge(matrix, i, j, distance);
            }
        }
    }
}

// generate planet distance to a .txt file
void generateDistance(double matrix[][N]) {
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

// initialize adjacency list
void initAdjacencyList(LinkedList<int> *list, double matrix[][N]) {
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                double temp = matrix[j][i];
                list[j].insert(i, temp);
            }
        }
    }
}

// print adjacency list
void printAdjacencyList(LinkedList<int> *list) {
    char characters[] = "ABCDEFGHIJ";

    for (int i = 0; i < 10; i++) {
        cout << characters[i] << "-   ";
        cout << list[i] << endl;
    }
}