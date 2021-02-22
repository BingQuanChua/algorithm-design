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

LinkedList<Planet> readPlanetDetails(Planet *planets, LinkedList<Planet> values);
LinkedList<Edge> readPlanetEdges(Planet *planets, LinkedList<Edge> edges, double matrix[][N], LinkedList<Planet> *list);
void addEdge(double matrix[][N], int a, int b, double value);
void printAdjacencyMatrix(double matrix[][N]);
void printAdjacencyList(LinkedList<Planet> *list);
void writeDistance(double matrix[][N]);

int main() {

    Planet planets[N];           // array of planets
    LinkedList<Planet> values;   // list of planet values
    LinkedList<Edge> edges;      // list of planet distances
    double matrix[N][N] = {0};   // adjacency matrix of planets
    LinkedList<Planet> list[N];    // adjacency list of planets
    
    printAdjacencyMatrix(matrix);
    printAdjacencyList(list);
    // read planet details from file
    values = readPlanetDetails(planets, values);

    // read planet edges from file
    edges = readPlanetEdges(planets, edges, matrix, list);

    // print adjacency matrix
    printAdjacencyMatrix(matrix);
    
    // print adjacency list
    printAdjacencyList(list);

    // write planet distances to a text file
    writeDistance(matrix);  


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
LinkedList<Planet> readPlanetDetails(Planet *planets, LinkedList<Planet> values) {

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

LinkedList<Edge> readPlanetEdges(Planet *planets, LinkedList<Edge> edges, double matrix[][N], LinkedList<Planet> *list) {
    int numOfEdges;
    int p1, p2;
    ifstream file("generated-data/planet-edges.txt");
    file >> numOfEdges;
    for (int i = 0; i < numOfEdges; i++) {
        file >> p1 >> p2;

        // create new edge
        Edge e;
        e.p1 = planets[p1];
        e.p2 = planets[p2];

        double distance = e.calculateDistance();
        // insert edge into edges linkedlist
        edges.insert(e, distance);

        // insert into adjacency matrix
        addEdge(matrix, p1, p2, distance);

        // insert into adjacency list
        list[p1].insert(planets[p2], distance);
        list[p2].insert(planets[p1], distance);
    }

    return edges;
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

// print adjacency list
void printAdjacencyList(LinkedList<Planet> *list) {
    cout << "The Adjacency List of the Planets:" << endl << endl;

    for (int i = 0; i < 10; i++) {
        cout << characters[i] << "-   ";
        cout << list[i] << endl;
    }

    cout << endl;
}

// generate planet distance to a .txt file
void writeDistance(double matrix[][N]) {
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


