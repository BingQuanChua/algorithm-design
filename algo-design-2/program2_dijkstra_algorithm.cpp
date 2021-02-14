#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;

static char characters[] = "ABCDEFGHIJ";
double matrix[10][10];   // adjacency matrix of planets
int numVertex = 10; // declare the number of vertex
void getDistance(); // read planet distances from the text file
void initAdjancencyMatrix(); // initialize the map
void addEdge(int a, int b, double value); // (for adjacency matrix) adds a new edge in the map
void printAdjacencyMatrix(); // display the adjacency matrix
void printShortestDistance(double distance[]); // print the constructed distance array
void minDistance(double distance[],bool sptSet[]); // find the vertex with minimum distance value
void dijkstra(int source); //function that implements Dijkstra's algorithm by using adjacency matrix representation

int main() {

    initAdjancencyMatrix();
    getDistance();
    printAdjacencyMatrix();
    dijkstra(0);
    return 0;
}

// read planet distances from the text file
void getDistance() {

    string details;
    ifstream file("generated-data/planet-distances.txt");
    for (int i = 0; i < 10; i++) {
        for(int j = 0; j < 10; j++){
        // read in the value of distance into the matrices
            file >> matrix[i][j];
        }
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
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix() {
    cout << "Adjacency Matrix:" << endl;
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

// print the constructed distance array
void printShortestDistance(double distance[]){
    cout << "\n\nThe shortest distance to each planet:\n";
    cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i=0;i<numVertex;i++){
		//char c=65+i;
		cout<<characters[i]<<"\t\t"<<distance[i]<<endl;
	}
}

// find the vertex with minimum distance value
int minimumDistance(double distance[],bool sptSet[]){
    int minDistance = INT_MAX,minIndex;
    for(int i = 0;i<numVertex;i++){
        if(sptSet[i]==false){
            if(distance[i]<=minDistance)
            {
                minDistance=distance[i];
                minIndex=i;
            }
        }
    }
    return minIndex;
}

//function that implements Dijkstra's algorithm by using adjacency matrix representation
void dijkstra(int source){

    int path[numVertex];
    double distance[numVertex];
    bool sptSet[numVertex];

    for (int i = 0; i < numVertex; i++){
        // Initialize the variables
        distance[i] = INT_MAX;
        sptSet[i] = false;
        path[i] = source;
    }
    //initialize the source vertex distance to zero
    distance[source] = 0;

    for (int i = 0; i < numVertex; i++) {

        int u = minimumDistance(distance, sptSet);
        // Mark the picked vertex as visited
        sptSet[u] = true;

        for (int v = 0; v < numVertex; v++){
            // update the minimum distance
            if (!sptSet[v] && matrix[u][v] && distance[u] != INT_MAX
                && distance[u] + matrix[u][v] < distance[v]){

                distance[v] = distance[u] + matrix[u][v];
                path[v] = u;
            }
        }
    }

    cout << "The shortest paths from Planet A to the other planets:";
    for(int i = 0;i < numVertex;i++){
        if(i!=source) {
          int j = 0;
          cout<<"\nPath = "<<characters[i];
          j = i;
          do {
             j=path[j];
             cout<<"<-"<<characters[j];
          }while(j!=source);
        }
    }
    // print the constructed distance array
    printShortestDistance(distance);
}
