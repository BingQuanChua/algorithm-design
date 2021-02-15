#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;

const int NUM_VERTEX = 10; // declare the number of vertex

void getDistance(double matrix[][NUM_VERTEX]); // read planet distances from the text file
void initAdjancencyMatrix(double matrix[][NUM_VERTEX]); // initialize the map
void addEdge(double matrix[][NUM_VERTEX],int a, int b, double value); // (for adjacency matrix) adds a new edge in the map
void printAdjacencyMatrix(double matrix[][NUM_VERTEX]); // display the adjacency matrix
void printShortestDistance(double distance[]); // print the constructed distance array
void minDistance(double distance[],bool sptSet[]); // find the vertex with minimum distance value
void dijkstra(double matrix[][NUM_VERTEX],int source); //function that implements Dijkstra's algorithm by using adjacency matrix representation

int main() {

    double matrix[10][10];   // adjacency matrix of planets
    initAdjancencyMatrix(matrix);
    getDistance(matrix);
    printAdjacencyMatrix(matrix);
    dijkstra(matrix,0);

    return 0;
}

// read planet distances from the text file
void getDistance(double matrix[][NUM_VERTEX]) {
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
void initAdjancencyMatrix(double matrix[][NUM_VERTEX]) {
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
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(double matrix[][NUM_VERTEX],int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix(double matrix[][NUM_VERTEX]) {
    char characters[] = "ABCDEFGHIJ";
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
    char characters[] = "ABCDEFGHIJ";
    cout << "\n\nThe shortest distance to each planet:\n";
    cout<<"Vertex\t\tDistance from source"<<endl;
	for(int i=0;i<NUM_VERTEX;i++){
		//char c=65+i;
		cout<<characters[i]<<"\t\t"<<distance[i]<<endl;
	}
}

// find the vertex with minimum distance value
int minimumDistance(double distance[],bool sptSet[]){
    int minDistance = INT_MAX,minIndex;
    for(int i = 0;i<NUM_VERTEX;i++){
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
void dijkstra(double matrix[][NUM_VERTEX],int source){
    char characters[] = "ABCDEFGHIJ";
    int path[NUM_VERTEX];
    double distance[NUM_VERTEX];
    bool sptSet[NUM_VERTEX];

    for (int i = 0; i < NUM_VERTEX; i++){
        // Initialize the variables
        distance[i] = INT_MAX;
        sptSet[i] = false;
        path[i] = source;
    }
    //initialize the source vertex distance to zero
    distance[source] = 0;

    for (int i = 0; i < NUM_VERTEX; i++) {

        int u = minimumDistance(distance, sptSet);
        // Mark the picked vertex as visited
        sptSet[u] = true;

        for (int v = 0; v < NUM_VERTEX; v++){
            // update the minimum distance
            if (!sptSet[v] && matrix[u][v] && distance[u] != INT_MAX
                && distance[u] + matrix[u][v] < distance[v]){

                distance[v] = distance[u] + matrix[u][v];
                path[v] = u;
            }
        }
    }

    cout << "The shortest paths from Planet A to the other planets:";
    for(int i = 0;i < NUM_VERTEX;i++){
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
