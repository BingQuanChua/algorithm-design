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

LinkedList<char> getPlanetDetails(Planet *planets, LinkedList<char> values);
void initAdjancencyMatrix(double matrix[][N]);
void addEdge(double matrix[][N], int a, int b, double value);
void printAdjacencyMatrix(double matrix[][N]);
LinkedList<Edge> calculatePlanetDistance(Planet *planets, double matrix[][N], LinkedList<Edge> edges);
void generateDistance(double matrix[][N]);
void initAdjacencyList(LinkedList<char> *list, double matrix[][N]);
void printAdjacencyList(LinkedList<char> *list);

int main() {

    Planet planets[N];           // array of planets
    double matrix[N][N] = {0};   // adjacency matrix of planets
    LinkedList<char> list[N];    // adjacency list of planets
    LinkedList<Edge> edges;      // list of planet distances
    LinkedList<char> values;   // list of planet values

    // read planet details from file
    values = getPlanetDetails(planets, values);

    // initialize the adjacency matrix, calculate distance
    initAdjancencyMatrix(matrix);
    edges = calculatePlanetDistance(planets, matrix, edges);
    printAdjacencyMatrix(matrix);
    generateDistance(matrix);

    // initialize the adjacency list from the adjacency matrix
    initAdjacencyList(list, matrix);
    printAdjacencyList(list);


    // does merge sort on edge
    // ascending order of distance
    cout << endl << "List of Planet Distances: " << endl;
    cout << edges << endl;

    edges.startMergeSort(0);

    cout << endl << "List of Planet Distances sorted ascendingly: " << endl;
    cout << edges << endl;

    
    // does merge sort on value
    // descending order of value
    cout << endl << "List of Planet Values: " << endl;
    cout << values << endl;

    values.startMergeSort(1);

    cout << endl << "List of Planet Values sorted descendingly: " << endl;
    cout << values << endl;


    return 0;
}

// read planet details from the generated data
LinkedList<char> getPlanetDetails(Planet *planets, LinkedList<char> values) {

    string details;
    ifstream file("generated-data/A2planets.txt");
    for (int i = 0; i < 10; i++) {
        Planet p;
        file >> details;
        p.name = details.at(0);
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
            values.insert(characters[i], value);
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
                double distance = sqrt(pow((planets[j].x - planets[i].x),2) 
                + pow((planets[j].y - planets[i].y),2) 
                + pow((planets[j].z - planets[i].z),2));

                // add an edge in the matrix
                addEdge(matrix, i, j, distance);

                // add edge in the Edge array
                Edge e;
                e.p1 = characters[i];
                e.p2 = characters[j];
                e.value = distance;
                //string edge = "";
                //edge += characters[j];
                //edge += characters[i];
                //cout << edge << ": " << distance << endl;
                edges.insert(e, distance);
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
void initAdjacencyList(LinkedList<char> *list, double matrix[][N]) {
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            if (matrix[j][i] > 0) {
                // there's an edge
                double temp = matrix[j][i];
                list[j].insert(characters[i], temp);
            }
        }
    }
}

// print adjacency list
void printAdjacencyList(LinkedList<char> *list) {
    cout << "The Adjacency List of the Planets:" << endl << endl;

    for (int i = 0; i < 10; i++) {
        cout << characters[i] << "-   ";
        cout << list[i] << endl;
    }
}

