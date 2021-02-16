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

class planetMap
{
	public:
        int node, edge;
        typedef pair<int, int> planetName;
        vector< pair<double, planetName> > edgePair;

        planetMap(int node, int edge);
        void addEdge(int planetOne, int planetTwo, double weight);
        void kruskal();
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

planetMap:: planetMap(int node, int edge)
{
    this->node = node;
    this->edge = edge;
}

void planetMap::addEdge(int planetOne, int planetTwo, double weight)
{
    edgePair.push_back({weight, {planetOne, planetTwo}});
}

void planetMap::kruskal()
{
	sort(edgePair.begin(), edgePair.end());

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
			cout << char(65+pOne) << " - " << char(65+pTwo) << "\t Weight = " << eWeight <<endl;
			ds.merge(set_pOne, set_pTwo);
		}
	}
}

double getWeight(Planet one, Planet two)
{
    double weight;

    weight = sqrt(pow((two.x - one.x),2) + pow((two.y - one.y),2) + pow((two.z - one.z),2));

    return weight;
}

int main()
{
    Planet planetList[10];
    string tempName;
    int tempX, tempY, tempZ, tempWeight, tempProfit;
    fstream planetFile;
	planetMap map(10, 18);

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

    cout << "The edges of original map: " <<endl;

    map.addEdge(0, 3, getWeight(planetList[0],planetList[3]));
    cout << "A - D \t Weight = "  << getWeight(planetList[0],planetList[3]) << endl;
    map.addEdge(0, 9, getWeight(planetList[0],planetList[9]));
    cout << "A - J \t Weight = "  << getWeight(planetList[0],planetList[9]) << endl;
    map.addEdge(0, 7, getWeight(planetList[0],planetList[7]));
    cout << "A - H \t Weight = "  << getWeight(planetList[0],planetList[7]) << endl;
    map.addEdge(0, 5, getWeight(planetList[0],planetList[5]));
    cout << "A - F \t Weight = "  << getWeight(planetList[0],planetList[5]) << endl;
    map.addEdge(3, 1, getWeight(planetList[3],planetList[1]));
    cout << "D - B \t Weight = "  << getWeight(planetList[3],planetList[1]) << endl;
    map.addEdge(9, 6, getWeight(planetList[9],planetList[6]));
    cout << "J - G \t Weight = "  << getWeight(planetList[9],planetList[6]) << endl;
    map.addEdge(7, 8, getWeight(planetList[7],planetList[8]));
    cout << "H - I \t Weight = "  << getWeight(planetList[7],planetList[8]) << endl;
    map.addEdge(5, 2, getWeight(planetList[5],planetList[2]));
    cout << "F - C \t Weight = "  << getWeight(planetList[5],planetList[2]) << endl;
    map.addEdge(1, 4, getWeight(planetList[1],planetList[4]));
    cout << "B - E \t Weight = "  << getWeight(planetList[1],planetList[4]) << endl;
    map.addEdge(6, 4, getWeight(planetList[6],planetList[4]));
    cout << "G - E \t Weight = "  << getWeight(planetList[6],planetList[4]) << endl;
    map.addEdge(8, 4, getWeight(planetList[8],planetList[4]));
    cout << "I - E \t Weight = "  << getWeight(planetList[8],planetList[4]) << endl;
    map.addEdge(2, 4, getWeight(planetList[2],planetList[4]));
    cout << "C - E \t Weight = "  << getWeight(planetList[2],planetList[4]) << endl;
    map.addEdge(3, 9, getWeight(planetList[3],planetList[9]));
    cout << "D - J \t Weight = "  << getWeight(planetList[3],planetList[9]) << endl;
    map.addEdge(9, 7, getWeight(planetList[9],planetList[7]));
    cout << "J - H \t Weight = "  << getWeight(planetList[9],planetList[7]) << endl;
    map.addEdge(7, 5, getWeight(planetList[7],planetList[5]));
    cout << "H - F \t Weight = "  << getWeight(planetList[7],planetList[5]) << endl;
    map.addEdge(1, 6, getWeight(planetList[1],planetList[6]));
    cout << "B - G \t Weight = "  << getWeight(planetList[1],planetList[6]) << endl;
    map.addEdge(6, 8, getWeight(planetList[6],planetList[8]));
    cout << "G - I \t Weight = "  << getWeight(planetList[6],planetList[8]) << endl;
    map.addEdge(8, 2, getWeight(planetList[8],planetList[2]));
    cout << "I - C \t Weight = "  << getWeight(planetList[8],planetList[2]) << endl;

	cout << "\nEdges of Minimum Spanning Tree are: " << endl;;
	map.kruskal();

	return 0;
}
