#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
using namespace std;

struct Coord // coordinate struct
{
	int x; int y;
}; 
struct TwoNames //struct for two strings for character select
{
	string one; string two;
};
struct queueNode // queue node struct for using a queue
{
	Coord pt;  // The cordinates of a cell
	int dist;  // cell's distance of from the source
};

class Graph {
private:


public:
	int R;// rows
	int C;//columns
	int vertices = R * C; // how many vertices are in the matrix
	char** M;//our matrix/map
	bool** vis;//visited array for searching
	int** myArray;// temp array
	int** adj; // adjacency matrix
	int** weight; // our matrix but in the form of the chars weight values

	Graph(std::string s); //constructor
	~Graph(); //destructor
	bool isValid(int row, int col);
	int** BFS(Coord start, Coord goal);
	int** DFS(Coord start, Coord goal);
	void readMap(std::string s);
	
	//void dijkstra(int src);
	//int minDistance(int dist[], bool sptSet[]);
	//void printPath(int parent[], int j);
	//void printSolution(int dist[], int n, int parent[]);
	void createAdjMatrix();
	//void addEdge(int i, int j);

	void createWeightMatrix();
};

class Player
{
public:
	Coord position; //current player position
	std::string cType; // our player type i.e. hiker, bogmaster, or tourist
	char p; //the vertex our player is currently sitting on
	int work; // amount of work accumulated while traveling to destination
	bool active; // is our player the active player for maps with multiple

	Player();
	~Player();
};

class Map
{
public:
	Graph * game; //  a copyt of our M for function purposes
	Player myPlayers[3]; // array of players
	Map(Graph * g);
	~Map();
	void placePlayer(Coord c, int pn);
	void DisplayMap();
	void movePlayer(char m, int pn);
	void addWeight(char w, int pn);

private:

};


