#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath> 
#include <math.h>
#include "planet.cpp"
#include "edge.cpp"
#include "linkedlist.cpp"
using namespace std;

const int N = 10;
char characters[] = "ABCDEFGHIJ";

LinkedList<Planet> getPlanetDetails(Planet *planets, LinkedList<Planet> values);
void initAdjancencyMatrix(double matrix[][N]);
void addEdge(double matrix[][N], int a, int b, double value);
void printAdjacencyMatrix(double matrix[][N]);
LinkedList<Edge> calculatePlanetDistance(Planet *planets, double matrix[][N], LinkedList<Edge> edges);
void generateDistance(double matrix[][N]);
void initAdjacencyList(LinkedList<Planet> *list, double matrix[][N], Planet *planets);
void printAdjacencyList(LinkedList<Planet> *list);

int main() {

    Planet planets[N];           // array of planets
    LinkedList<Planet> values;   // list of planet values
    LinkedList<Edge> edges;      // list of planet distances
    double matrix[N][N] = {0};   // adjacency matrix of planets
    LinkedList<Planet> list[N];    // adjacency list of planets
    
    // read planet details from file
    values = getPlanetDetails(planets, values);

    // initialize the adjacency matrix, calculate distance
    initAdjancencyMatrix(matrix);
    edges = calculatePlanetDistance(planets, matrix, edges);
    printAdjacencyMatrix(matrix);
    generateDistance(matrix);

    // initialize the adjacency list from the adjacency matrix
    initAdjacencyList(list, matrix, planets);
    printAdjacencyList(list);


    // list of planet distances
    cout << endl << "List of Planet Distances: " << endl;
    cout << edges << endl;

    // does merge sort on edge
    // ascending order of distance
    edges.startMergeSort(0);
    cout << endl << "List of Planet Distances sorted ascendingly: " << endl;
    cout << edges << endl;

    
    // list of planet values
    cout << endl << "List of Planet Values: " << endl;
    cout << values << endl;

    // does merge sort on value
    // descending order of value
    values.startMergeSort(1);
    cout << endl << "List of Planet Values sorted descendingly: " << endl;
    cout << values << endl;


    return 0;
}

// read planet details from the generated data
LinkedList<Planet> getPlanetDetails(Planet *planets, LinkedList<Planet> values) {

    string details;
    ifstream file("generated-data/A2planets.txt");
    for (int i = 0; i < 10; i++) {
        Planet p;
        file >> details;
        p.name = details;
        p.planetCharacter = details.at(7);
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
        
        if(i != 0) {
            // not planet A
            // planet A is unable to calculate value

            // insert to planet values
            double value = p.calculateValue();
            values.insert(p, value);
        }

        // stores each planet into the array
        planets[i] = p;
    }
    file.close();

    return values;
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

    // printAdjacencyMatrix(matrix);
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(double matrix[][N], int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix(double matrix[][N]) {
    cout << "The Adjacency Matrix of the Planets:" << endl << endl;

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
LinkedList<Edge> calculatePlanetDistance(Planet *planets, double matrix[][N], LinkedList<Edge> edges) {
    for (int j = 0; j < 10; j++) {
        for (int i = j; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                // create a new edge
                Edge e;
                e.p1 = planets[i];
                e.p2 = planets[j];

                double distance = e.calculateDistance();

                edges.insert(e, distance);

                // add an edge in the matrix
                addEdge(matrix, i, j, distance);
            }
        }
    }
    return edges;
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
void initAdjacencyList(LinkedList<Planet> *list, double matrix[][N], Planet *planets) {
    // generate adjacency list from the adjacency matrix
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                double distance = matrix[j][i]; // distance to planet
                list[j].insert(planets[i], distance);
            }
        }
    }
}

// print adjacency list
void printAdjacencyList(LinkedList<Planet> *list) {
    cout << "The Adjacency List of the Planets:" << endl << endl;

    for (int i = 0; i < 10; i++) {
        cout << characters[i] << "-   ";
        cout << list[i] << endl;
    }
}

