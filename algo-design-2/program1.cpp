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

LinkedList<Planet> readPlanetDetails(Planet *planets, LinkedList<Planet> planetValues);
LinkedList<Edge> readPlanetEdges(Planet *planets, LinkedList<Edge> planetEdges, double adjMatrix[][N], LinkedList<Planet> *adjList);
void addEdge(double adjMatrix[][N], int a, int b, double value);
void printAdjacencyMatrix(double adjMatrix[][N]);
void printAdjacencyList(LinkedList<Planet> *adjList);
void writeDistance(double adjMatrix[][N]);

int main() {

    Planet planets[N];           // array of planets
    LinkedList<Planet> planetValues;   // list of planet values
    LinkedList<Edge> planetEdges;      // list of planet distances
    double adjMatrix[N][N] = {0};   // adjacency matrix of planets
    LinkedList<Planet> adjList[N];    // adjacency list of planets
    
    // read planet details from file
    planetValues = readPlanetDetails(planets, planetValues);
    
    // read planet edges from file
    planetEdges = readPlanetEdges(planets, planetEdges, adjMatrix, adjList);

    // print adjacency matrix
    printAdjacencyMatrix(adjMatrix);
    
    // print adjacency list
    printAdjacencyList(adjList);

    // write planet distances to a text file
    writeDistance(adjMatrix);  


    // list of planet distances
    cout << endl << "List of Planet Distances: " << endl;
    cout << planetEdges << endl;

    // does merge sort on edge
    // ascending order of distance
    planetEdges.startMergeSort(0);
    cout << endl << "List of Planet Distances sorted ascendingly: " << endl;
    cout << planetEdges << endl << endl;

    
    // list of planet values
    cout << endl << "List of Planet Values: " << endl;
    cout << planetValues << endl;

    // does merge sort on value
    // descending order of value
    planetValues.startMergeSort(1);
    cout << endl << "List of Planet Values sorted descendingly: " << endl;
    cout << planetValues << endl << endl << endl;


    return 0;
}

// read planet details from the generated planet data
LinkedList<Planet> readPlanetDetails(Planet *planets, LinkedList<Planet> planetValues) {
    
    string name;
    int x, y, z, weight, profit;
    int c = 0;
    double value = 0;
    ifstream file("generated-data/A2planets.txt");

    if(file) {
        cout << "\nPlanet details:" << endl << endl;
        cout << " Planet\t\t Coordinates\tWeight\tProfit\t Value" << endl;
        while(file >> name >> x >> y >> z >> weight >> profit){

            Planet p;
            p.name = name;
            p.planetCharacter = name.at(7);
            p.x = x;
            p.y = y;
            p.z = z;
            p.weight = weight;
            p.profit = profit;
            
            cout << name << "\t(" << x << "," << y << "," << z << ") \t" << setw(4) << weight << " \t" << setw(4) << profit;

            if(weight != 0) {
                // not planet A, it does not have weight
                // insert to planet values
                value = p.calculateValue();
                planetValues.insert(p, value);
            }
            
            // stores each planet into the array
            planets[c] = p;
            c++;

            cout << "\t" << setw(7) << value << endl;
        }
        file.close();
        cout << endl << endl;
    }
    else {
        cout << "\n<ERROR>\nFile A2planets.txt not found.\nPlease check /generated-data directory\n\n" << endl;
        exit(0);
    }    

    return planetValues;
}

// read planet details from the planet edges data
LinkedList<Edge> readPlanetEdges(Planet *planets, LinkedList<Edge> planetEdges, double adjMatrix[][N], LinkedList<Planet> *adjList) {
    
    int numOfEdges;
    int p1, p2;
    ifstream file("generated-data/planet-edges.txt");
    
    if (file) {
        cout << "Planet edges:" << endl << endl;
        file >> numOfEdges;
        for (int i = 0; i < numOfEdges; i++) {
            file >> p1 >> p2;

            // create new edge
            Edge e;
            e.p1 = planets[p1];
            e.p2 = planets[p2];

            double distance = e.calculateDistance();
            cout << e.p1 << e.p2 << ": " << distance << endl;


            // insert edge into edges linkedlist
            planetEdges.insert(e, distance);

            // insert into adjacency matrix
            addEdge(adjMatrix, p1, p2, distance);

            // insert into adjacency list
            adjList[p1].insert(planets[p2], distance);
            adjList[p2].insert(planets[p1], distance);
        }
        cout << endl << endl;
    }
    else {
        cout << "\n<ERROR>\nFile planet-edges.txt not found.\nPlease check /generated-data directory\n\n" << endl;
        exit(0);
    }

    return planetEdges;
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(double adjMatrix[][N], int a, int b, double value) {
    adjMatrix[a][b] = value;
    adjMatrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix(double adjMatrix[][N]) {
    cout << "Adjacency Matrix of the Planets:" << endl << endl;

    cout << " ";
    for (int i = 0; i < 10; i++) {
        cout << " " << setw(9) << characters[i];
    }
    cout << endl;
    for (int j = 0; j < 10; j++) {
        cout << characters[j] << " ";
        for (int i = 0; i < 10; i++) {
            cout << setw(9) << adjMatrix[j][i] << " ";
        }
        cout << endl;
    }
    cout << endl << endl;
}

// print adjacency list
void printAdjacencyList(LinkedList<Planet> *adjList) {
    cout << "Adjacency List of the Planets:" << endl << endl;

    for (int i = 0; i < 10; i++) {
        cout << characters[i] << "-   ";
        cout << adjList[i] << endl;
    }
    cout << endl << endl;
}

// generate planet distance to a text file
void writeDistance(double adjMatrix[][N]) {
    ofstream file;
    file.open("generated-data/planet-distances.txt"); 
    
    for (int j = 0; j < 10; j++) {
        for (int i = 0; i < 10; i++) {
            file << adjMatrix[j][i] << " ";
        }
        file << endl;
    }
    file << endl;

    file.close();
}


