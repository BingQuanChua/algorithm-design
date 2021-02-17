#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cmath>
using namespace std;

struct Planet
{
    string name;
    int x;
    int y;
    int z;
    int weight;
    int profit;
};

struct KruskalPlanet
{
    int planet1;
    int planet2;
};

class PlanetMap
{
	public:
        int node, edge;
        typedef pair<int, int> planetName;
        vector< pair<double, planetName> > edgePair;

        PlanetMap(int node, int edge);
        void addEdge(int planetOne, int planetTwo, double weight);
        KruskalPlanet* kruskal();
};

struct DisjointSets
{
	int *parent, *rnk;
	int node;

	DisjointSets(int node)
	{
		this->node = node;
		parent = new int[node+1];
		rnk = new int[node+1];

		for (int i = 0; i <= node; i++)
		{
			rnk[i] = 0;
			parent[i] = i;
		}
	}

	int find(int planet)
	{
		if (planet != parent[planet])
			parent[planet] = find(parent[planet]);
		return parent[planet];
	}

	void merge(int set1, int set2)
	{
		set1 = find(set1), set2 = find(set2);

		if (rnk[set1] > rnk[set2])
			parent[set2] = set1;
		else
			parent[set1] = set2;

		if (rnk[set1] == rnk[set2])
			rnk[set2]++;
	}
};

PlanetMap:: PlanetMap(int node, int edge)
{
    this->node = node;
    this->edge = edge;
}

void PlanetMap::addEdge(int planetOne, int planetTwo, double weight)
{
    edgePair.push_back({weight, {planetOne, planetTwo}});
}

KruskalPlanet* PlanetMap::kruskal()
{
	sort(edgePair.begin(), edgePair.end());
	static KruskalPlanet kp[10];
	int i = 0;

	DisjointSets ds(node);

	vector< pair<double, planetName> >::iterator a;

	for (a=edgePair.begin(); a!=edgePair.end(); a++)
	{
        double eWeight = a->first;
        int pOne = a->second.first;
        int pTwo = a->second.second;

        int set_pOne = ds.find(pOne);
        int set_pTwo = ds.find(pTwo);

        if (set_pOne != set_pTwo)
        {
            kp[i].planet1 = pOne;
            kp[i].planet2 = pTwo;
            cout << char(65+pOne) << " - " << char(65+pTwo) << "\t Weight = " << eWeight <<endl;
            //cout << pOne << " - " << pTwo << "\t " << i << endl;
            ds.merge(set_pOne, set_pTwo);
            i++;
        }
	}

	return kp;
}

double getWeight(Planet one, Planet two)
{
    double weight;

    weight = sqrt(pow((two.x - one.x),2) + pow((two.y - one.y),2) + pow((two.z - one.z),2));

    return weight;
}

void initmap(char g[7][13])
{
    for (int i=0; i<7; i++)
    {
        for (int j=0; j<13; j++)
        {
            g[i][j] = ' ';
        }
    }

    g[0][6] = 'A';
    g[4][0] = 'B';
    g[4][12] = 'C';
    g[2][0] = 'D';
    g[6][6] = 'E';
    g[2][12] = 'F';
    g[4][3] = 'G';
    g[2][9] = 'H';
    g[4][9] = 'I';
    g[2][3] = 'J';
}

void displayGraph(char g[7][13])
{
    cout << endl;
    for (int i=0; i<7; i++)
    {
        cout << "  ";
        for (int j=0; j<13; j++)
           cout << g[i][j];
        cout << endl;
    }
}

void connect(char g[7][13], int a, int b)
{
    switch (a) {
    case 0:     // A
        if (b == 3)     // connect to D
        {
            g[0][0] = '+';
            g[0][1] = '-';
            g[0][2] = '-';
            g[0][3] = '+';
            g[0][4] = '-';
            g[0][5] = '-';
            g[1][0] = '|';
        }
        if (b == 5)     // connect to F
        {
            g[0][12] = '+';
            g[0][11] = '-';
            g[0][10] = '-';
            g[0][9] = '+';
            g[0][8] = '-';
            g[0][7] = '-';
            g[1][12] = '|';
        }
        if (b == 9)     // connect to J
        {
            g[0][3] = '+';
            g[0][4] = '-';
            g[0][5] = '-';
            g[1][3] = '|';
        }
        if (b == 7)      // connect to H
        {
            g[0][9] = '+';
            g[0][8] = '-';
            g[0][7] = '-';
            g[1][9] = '|';
        }
        break;
    case 1:     // B
        if (b == 4)     // connect to E
        {
            g[6][0] = '+';
            g[6][1] = '-';
            g[6][2] = '-';
            g[6][3] = '+';
            g[6][4] = '-';
            g[6][5] = '-';
            g[5][0] = '|';
        }
        if (b == 6)     // connect to G
        {
            g[4][1] = '-';
            g[4][2] = '-';
        }
        break;
    case 2:     // C
        if (b == 4)     // connect to E
        {
            g[6][12] = '+';
            g[6][11] = '-';
            g[6][10] = '-';
            g[6][9] = '+';
            g[6][8] = '-';
            g[6][7] = '-';
            g[5][12] = '|';
        }
        break;
    case 3:     // D
        if (b == 1)     // connect to B
        {
            g[3][0] = '|';
        }
        if (b == 9)     // connect to J
        {
            g[2][1] = '-';
            g[2][2] = '-';
        }
        break;
    case 5:     // F
        if (b == 2)     // connect to C
        {
            g[3][12] = '|';
        }
        break;
    case 6:     // G
        if (b == 4)     // connect to E
        {
            g[6][3] = '+';
            g[6][4] = '-';
            g[6][5] = '-';
            g[5][3] = '|';
        }
        if (b == 8)     // connect to I
        {
            g[4][4] = '-';
            g[4][5] = '-';
            g[4][6] = '-';
            g[4][7] = '-';
            g[4][8] = '-';
        }
        break;
    case 7:     // H
        if (b == 5)     // connect to F
        {
            g[2][10] = '-';
            g[2][11] = '-';
        }
        if (b == 8)     // connect to I
        {
            g[3][9] = '|';
        }
        break;
    case 8:     //I
        if (b == 2)     // connect to C
        {
            g[4][10] = '-';
            g[4][11] = '-';
        }
        if (b == 4)     // connect to E
        {
            g[6][9] = '+';
            g[6][8] = '-';
            g[6][7] = '-';
            g[5][9] = '|';
        }
        break;
    case 9:     // J
        if (b == 6)     // connect to G
        {
            g[3][3] = '|';
        }
        if (b == 7)     // connect to H
        {
            g[2][4] = '-';
            g[2][5] = '-';
            g[2][6] = '-';
            g[2][7] = '-';
            g[2][8] = '-';
        }
    }

}

int main()
{
    Planet planetList[10];
    string tempName;
    int tempX, tempY, tempZ, tempWeight, tempProfit;
    KruskalPlanet *kp;
    fstream planetFile;
	PlanetMap map(10, 18);

	char graph[7][13];
	char graphAfter[7][13];

	initmap(graph);
	initmap(graphAfter);

    planetFile.open("generated-data/A2planets.txt", ios::in);

    if(planetFile)
    {
        for(int i=0; i<10; i++)
        {
            Planet temp;
            planetFile >> tempName;
            temp.name = tempName;
            planetFile >> tempX;
            temp.x = tempX;
            planetFile >> tempY;
            temp.y = tempY;
            planetFile >> tempZ;
            temp.z = tempZ;
            planetFile >> tempWeight;
            temp.weight = tempWeight;
            planetFile >> tempProfit;
            temp.profit = tempProfit;

            planetList[i] = temp;
        }
        planetFile.close();
    }
    else
    {
        cout << "File not found" << endl;
    }

    cout << "Before applying Kruskal Algorithm" << endl;
    cout << "The edges of original map: " <<endl;

    map.addEdge(0, 3, getWeight(planetList[0],planetList[3]));
    connect(graph,0,3);     // A-D
    cout << "A - D \t Weight = "  << getWeight(planetList[0],planetList[3]) << endl;

    map.addEdge(0, 9, getWeight(planetList[0],planetList[9]));
    connect(graph,0,9);
    cout << "A - J \t Weight = "  << getWeight(planetList[0],planetList[9]) << endl;

    map.addEdge(0, 7, getWeight(planetList[0],planetList[7]));
    connect(graph,0,7);
    cout << "A - H \t Weight = "  << getWeight(planetList[0],planetList[7]) << endl;

    map.addEdge(0, 5, getWeight(planetList[0],planetList[5]));
    connect(graph,0,5);
    cout << "A - F \t Weight = "  << getWeight(planetList[0],planetList[5]) << endl;

    map.addEdge(3, 1, getWeight(planetList[3],planetList[1]));
    connect(graph,3,1);
    cout << "D - B \t Weight = "  << getWeight(planetList[3],planetList[1]) << endl;

    map.addEdge(9, 6, getWeight(planetList[9],planetList[6]));
    connect(graph,9,6);
    cout << "J - G \t Weight = "  << getWeight(planetList[9],planetList[6]) << endl;

    map.addEdge(7, 8, getWeight(planetList[7],planetList[8]));
    connect(graph,7,8);
    cout << "H - I \t Weight = "  << getWeight(planetList[7],planetList[8]) << endl;

    map.addEdge(5, 2, getWeight(planetList[5],planetList[2]));
    connect(graph,5,2);
    cout << "F - C \t Weight = "  << getWeight(planetList[5],planetList[2]) << endl;

    map.addEdge(1, 4, getWeight(planetList[1],planetList[4]));
    connect(graph,1,4);
    cout << "B - E \t Weight = "  << getWeight(planetList[1],planetList[4]) << endl;

    map.addEdge(6, 4, getWeight(planetList[6],planetList[4]));
    connect(graph,6,4);
    cout << "G - E \t Weight = "  << getWeight(planetList[6],planetList[4]) << endl;

    map.addEdge(8, 4, getWeight(planetList[8],planetList[4]));
    connect(graph,8,4);
    cout << "I - E \t Weight = "  << getWeight(planetList[8],planetList[4]) << endl;

    map.addEdge(2, 4, getWeight(planetList[2],planetList[4]));
    connect(graph,2,4);
    cout << "C - E \t Weight = "  << getWeight(planetList[2],planetList[4]) << endl;

    map.addEdge(3, 9, getWeight(planetList[3],planetList[9]));
    connect(graph,3,9);
    cout << "D - J \t Weight = "  << getWeight(planetList[3],planetList[9]) << endl;

    map.addEdge(9, 7, getWeight(planetList[9],planetList[7]));
    connect(graph,9,7);
    cout << "J - H \t Weight = "  << getWeight(planetList[9],planetList[7]) << endl;

    map.addEdge(7, 5, getWeight(planetList[7],planetList[5]));
    connect(graph,7,5);
    cout << "H - F \t Weight = "  << getWeight(planetList[7],planetList[5]) << endl;

    map.addEdge(1, 6, getWeight(planetList[1],planetList[6]));
    connect(graph,1,6);
    cout << "B - G \t Weight = "  << getWeight(planetList[1],planetList[6]) << endl;

    map.addEdge(6, 8, getWeight(planetList[6],planetList[8]));
    connect(graph,6,8);
    cout << "G - I \t Weight = "  << getWeight(planetList[6],planetList[8]) << endl;

    map.addEdge(8, 2, getWeight(planetList[8],planetList[2]));
    connect(graph,8,2);
    cout << "I - C \t Weight = "  << getWeight(planetList[8],planetList[2]) << endl;

    cout << "\n\nThe graph of the planet location: ";
    displayGraph(graph);

    cout << "\n\n------------------------------------------------------------------" << endl;
    cout << "After applying Kruskal Algorithm" << endl;
	cout << "Edges of Minimum Spanning Tree are: " << endl;;
	kp = map.kruskal();

	for(int i=0; i<sizeof(kp)+1;i++)
    {
        connect(graphAfter, kp[i].planet1, kp[i].planet2);
    }

    cout << "\n\nGraph of the Minimum Spanning Tree: ";
    displayGraph(graphAfter);

	return 0;
}
