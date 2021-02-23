#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <cmath>
#include <math.h>

using namespace std;

const int NUM_VERTEX = 10; // declare the number of vertex
const int GRAPH_COL = 13;

void getDistance(double matrix[][NUM_VERTEX]); // read planet distances from the text file
void readPlanetEdges(double matrix[][NUM_VERTEX],char graphBefore[][GRAPH_COL]); // read planet edges from the text file
void addEdge(double matrix[][NUM_VERTEX],int a, int b, double value); // (for adjacency matrix) adds a new edge in the map
void printAdjacencyMatrix(double matrix[][NUM_VERTEX]); // display the adjacency matrix
void printShortestDistance(double distance[]); // print the constructed distance array
void minDistance(double distance[],bool sptSet[]); // find the vertex with minimum distance value
void dijkstra(double matrix[][NUM_VERTEX],char graphAfter[][GRAPH_COL],int source); //function that implements Dijkstra's algorithm by using adjacency matrix representation
void initmap(char graph[][GRAPH_COL]);
void displayGraph(char graph[][GRAPH_COL]);
void connect(char graph[][GRAPH_COL], int a, int b);

int main() {

    char graphBefore[7][13];
	char graphAfter[7][13];
    double matrix[10][10];   // adjacency matrix of planets
    cout << "**********************************Before applying Dijkstra Algorithm**********************************" << endl;

    initmap(graphBefore);
	initmap(graphAfter);
    readPlanetEdges(matrix,graphBefore);
    getDistance(matrix);
    cout << "The graph of the planet location:";
    displayGraph(graphBefore);
    printAdjacencyMatrix(matrix);
    cout << "**********************************After applying Dijkstra Algorithm**********************************" << endl;
    dijkstra(matrix,graphAfter,0);
    cout << "The graph representing the shortest paths: " << endl;
    displayGraph(graphAfter);
    return 0;
}

// read planet distances from the text file
void getDistance(double matrix[][NUM_VERTEX]) {
    string details;
    ifstream file("generated-data/planet-distances.txt");
    if(file){
        for (int i = 0; i < 10; i++) {
            for(int j = 0; j < 10; j++){
            // read in the value of distance into the matrices
                file >> matrix[i][j];
            }
        }
        file.close();
    }
    else{
        cout << "Unable to open the file." << endl;
    }
}

//Initialize the graph map
void initmap(char graph[][GRAPH_COL]){

    for (int i=0; i<7; i++)
    {
        for (int j=0; j<13; j++)
        {
            graph[i][j] = ' ';
        }
    }

    graph[0][6] = 'A';
    graph[4][0] = 'B';
    graph[4][12] = 'C';
    graph[2][0] = 'D';
    graph[6][6] = 'E';
    graph[2][12] = 'F';
    graph[4][3] = 'G';
    graph[2][9] = 'H';
    graph[4][9] = 'I';
    graph[2][3] = 'J';
}

//Read planet edges from the text file
void readPlanetEdges(double matrix[][NUM_VERTEX],char graphBefore[][GRAPH_COL]) {
    int numOfEdges;
    int p1, p2;
    ifstream file("generated-data/planet-edges.txt");
    file >> numOfEdges;
    if(file){
        for (int i = 0; i < numOfEdges; i++) {
            file >> p1 >> p2;
            // initialize the map
            addEdge(matrix, p1, p2, 1);
            // initial graph before finding the shortest path
            connect(graphBefore,p1,p2);
        }
    file.close();
    }
    else{
        cout << "Unable to open the file." << endl;
    }
}

// (for adjacency matrix) adds a new edge in the map
void addEdge(double matrix[][NUM_VERTEX],int a, int b, double value) {
    matrix[a][b] = value;
    matrix[b][a] = value;
}

// print adjacency matrix
void printAdjacencyMatrix(double matrix[][NUM_VERTEX]) {
    char characters[] = "ABCDEFGHIJ";
    cout << "Adjacency Matrix(distances as weights of the edges):" << endl;
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

//Connect the edges of the graph
void connect(char graph[][GRAPH_COL], int a, int b){
    switch (a) {
    case 0:     // A
        if (b == 3)     // connect to D
        {
            graph[0][0] = '+';
            graph[0][1] = '-';
            graph[0][2] = '-';
            graph[0][3] = '+';
            graph[0][4] = '-';
            graph[0][5] = '-';
            graph[1][0] = '|';
        }
        if (b == 5)     // connect to F
        {
            graph[0][12] = '+';
            graph[0][11] = '-';
            graph[0][10] = '-';
            graph[0][9] = '+';
            graph[0][8] = '-';
            graph[0][7] = '-';
            graph[1][12] = '|';
        }
        if (b == 9)     // connect to J
        {
            graph[0][3] = '+';
            graph[0][4] = '-';
            graph[0][5] = '-';
            graph[1][3] = '|';
        }
        if (b == 7)      // connect to H
        {
            graph[0][9] = '+';
            graph[0][8] = '-';
            graph[0][7] = '-';
            graph[1][9] = '|';
        }
        break;
    case 1:     // B
        if (b == 3)     // connect to D
        {
            graph[3][0] = '|';
        }
        if (b == 4)     // connect to E
        {
            graph[6][0] = '+';
            graph[6][1] = '-';
            graph[6][2] = '-';
            graph[6][3] = '+';
            graph[6][4] = '-';
            graph[6][5] = '-';
            graph[5][0] = '|';
        }
        if (b == 6)     // connect to G
        {
            graph[4][1] = '-';
            graph[4][2] = '-';
        }
        break;
    case 2:     // C
        if (b == 4)     // connect to E
        {
            graph[6][12] = '+';
            graph[6][11] = '-';
            graph[6][10] = '-';
            graph[6][9] = '+';
            graph[6][8] = '-';
            graph[6][7] = '-';
            graph[5][12] = '|';
        }
        if (b == 5)     // connect to F
        {
            graph[3][12] = '|';
        }

        if (b == 8)     // connect to I
        {
            graph[4][10] = '-';
            graph[4][11] = '-';
        }
        break;
    case 3:     // D
        if (b == 1)     // connect to B
        {
            graph[3][0] = '|';
        }
        if (b == 9)     // connect to J
        {
            graph[2][1] = '-';
            graph[2][2] = '-';
        }
        break;
    case 4:     //E
        if (b == 1)     // connect to B
        {
            graph[6][0] = '+';
            graph[6][1] = '-';
            graph[6][2] = '-';
            graph[6][3] = '+';
            graph[6][4] = '-';
            graph[6][5] = '-';
            graph[5][0] = '|';
        }
        if (b == 2)     // connect to C
        {
            graph[6][12] = '+';
            graph[6][11] = '-';
            graph[6][10] = '-';
            graph[6][9] = '+';
            graph[6][8] = '-';
            graph[6][7] = '-';
            graph[5][12] = '|';
        }
        if (b == 6)     // connect to G
        {
            graph[6][3] = '+';
            graph[6][4] = '-';
            graph[6][5] = '-';
            graph[5][3] = '|';
        }
        if (b == 8)     // connect to I
        {
            graph[6][9] = '+';
            graph[6][8] = '-';
            graph[6][7] = '-';
            graph[5][9] = '|';
        }
        break;

    case 5:     // F
        if (b == 2)     // connect to C
        {
            graph[3][12] = '|';
        }


        if (b == 7)     // connect to H
        {
            graph[2][10] = '-';
            graph[2][11] = '-';
        }
        break;
    case 6:     // G
        if (b == 1)     // connect to B
        {
            graph[4][1] = '-';
            graph[4][2] = '-';
        }

        if (b == 4)     // connect to E
        {
            graph[6][3] = '+';
            graph[6][4] = '-';
            graph[6][5] = '-';
            graph[5][3] = '|';
        }
        if (b == 8)     // connect to I
        {
            graph[4][4] = '-';
            graph[4][5] = '-';
            graph[4][6] = '-';
            graph[4][7] = '-';
            graph[4][8] = '-';
        }
        if (b == 9)     // connect to J
        {
            graph[3][3] = '|';
        }
        break;
    case 7:     // H
        if (b == 5)     // connect to F
        {
            graph[2][10] = '-';
            graph[2][11] = '-';
        }
        if (b == 8)     // connect to I
        {
            graph[3][9] = '|';
        }
        if (b == 9)     // connect to J
        {
            graph[2][4] = '-';
            graph[2][5] = '-';
            graph[2][6] = '-';
            graph[2][7] = '-';
            graph[2][8] = '-';
        }
        break;
    case 8:     //I
        if (b == 2)     // connect to C
        {
            graph[4][10] = '-';
            graph[4][11] = '-';
        }

        if (b == 4)     // connect to E
        {
            graph[6][9] = '+';
            graph[6][8] = '-';
            graph[6][7] = '-';
            graph[5][9] = '|';
        }
        if (b == 6)     // connect to G
        {
            graph[4][4] = '-';
            graph[4][5] = '-';
            graph[4][6] = '-';
            graph[4][7] = '-';
            graph[4][8] = '-';
        }
        if (b == 7)     // connect to H
        {
            graph[3][9] = '|';
        }
        break;
    case 9:     // J
        if (b == 3)     // connect to D
        {
            graph[2][1] = '-';
            graph[2][2] = '-';
        }
        if (b == 6)     // connect to G
        {
            graph[3][3] = '|';
        }
        if (b == 7)     // connect to H
        {
            graph[2][4] = '-';
            graph[2][5] = '-';
            graph[2][6] = '-';
            graph[2][7] = '-';
            graph[2][8] = '-';
        }
        break;
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

// print the constructed distance array
void printShortestDistance(double distance[]){
    char characters[] = "ABCDEFGHIJ";
    cout << "\n\nThe shortest distance to each planet:\n";
    cout<<"Planets\t\tDistance from source"<<endl;
	for(int i=0;i<NUM_VERTEX;i++){
		//char c=65+i;
		cout<<"Planet_" <<characters[i]<<"\t"<<distance[i]<<endl;
	}
	cout << endl;
}

//function that implements Dijkstra's algorithm by using adjacency matrix representation
void dijkstra(double matrix[][NUM_VERTEX],char graphAfter[][GRAPH_COL],int source){
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
             connect(graphAfter,path[j],j);
             j=path[j];
             cout<<"<-"<<characters[j];

          }while(j!=source);
        }
    }
    // print the constructed distance array
    printShortestDistance(distance);
}

//Display the graph
void displayGraph(char graph[][GRAPH_COL]){

    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<13; j++)
           cout << graph[i][j];
        cout << endl;
    }
    cout << endl;
}

