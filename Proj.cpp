//CSCI 115 Project, Abdulaziz Al-Said, Dr. Cecotti, M W F 9-950am
//using namespace std;
#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <fstream>
#include <sstream>
#include<iomanip>
#include "Proj.h"
int mRow[] = { -1, 0, 1 ,0 };
int mCol[] = { 0, 1 ,0, -1 };
//Player class
Player::Player()
{
	position.x = NULL;
	position.y = NULL;
	p = ' ';
	cType = " ";
	work = 0;
}

Player::~Player()
{
}

//Map class
Map::Map(Graph * g)
{
	game = g;
}

Map::~Map()
{
}

void Map::addWeight(char m, int pn) //function to add weight to a players 'work' to keep track of during travel
{
	if (m == 'w') 
	{ // if going up
		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == 'x') 
		{//checks to make sure that the vertex we are moving to is our destination 
			cout << "Congrats! You made it to your goal! Your total travel effort is " << myPlayers[pn].work << "!" << endl;
				return;
		
		}

		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == 't') 
		{//checks to make sure that the vertex we are moving to is a forest
			myPlayers[pn].work += 2;
			return;
		}
		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == '-') 
		{//checks to make sure that the vertex we are moving to is a plain
			myPlayers[pn].work += 1;
			return;
		}
		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == '@') 
		{//checks to make sure that the vertex we are moving to is a teleporter

			for(int  i= 0; i< game->R + 1; i++)
			{//nested for loops to scan through matrix
				for (int j = 0; j < game->C + 1; j++) 
				{
					if (game->M[i][j] == '@' && i!=myPlayers[pn].position.x && j!= myPlayers[pn].position.y)
					{ // if matrix at scan is a teleporter and if its not a teleporter we are currently looking at then teleport!
						game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = myPlayers[pn].p;
						myPlayers[pn].position.x = i;
						myPlayers[pn].position.y = j;
						myPlayers[pn].position.x++;
						return;
					}
					
				}
				
			}
		}

		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == '^') 
		{//checks to make sure that the vertex we are moving to is a mountain

			if (myPlayers[pn].cType == "Hiker") 
			{//if youre a hiker you can go over mountains! else gotta find a different path!
				myPlayers[pn].work += 5;
				return;
			}
			else 
			{
				cout << "Impassible terrain! Find a different path!" << endl;
				myPlayers[pn].position.x++;
				return;
			}
			
		}

		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == '~') 
		{//checks to make sure that the vertex we are moving to is a desert
			myPlayers[pn].work += 3;
			return;
		}

		if (game->M[myPlayers[pn].position.x - 1][myPlayers[pn].position.y] == 'w') 
		{//checks to make sure that the vertex we are moving to is a swamp

			if (myPlayers[pn].cType == "Bogmaster")
			{//if youre a bogmaster you can traverse swamps as easy as a plain! You get reduced weight cost!
				myPlayers[pn].work += 1;
				return;
			}
			else 
			{
				myPlayers[pn].work += 4;
				return;
			}
		}
	}
///////////////////////////////////////////////
	if (m == 'a') 
	{// if going down

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == 'x') 
		{//checks to make sure that the vertex we are moving to is our destination 
			cout << "Congrats! You made it to your goal! Your total travel effort is " << myPlayers[pn].work << "!" << endl;

			return;

		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == 't') 
		{//checks to make sure that the vertex we are moving to is a forest
			myPlayers[pn].work += 2;
			return;
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == '-') 
		{//checks to make sure that the vertex we are moving to is a plain
			myPlayers[pn].work += 1;
			return;
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == '@') 
		{//checks to make sure that the vertex we are moving to is a teleporter

			for (int i = 0; i < game->R + 1; i++) 
			{//nested for loops to scan through matrix
				for (int j = 0; j < game->C + 1; j++) 
				{
					if (game->M[i][j] == '@' && i != myPlayers[pn].position.x && j != myPlayers[pn].position.y)
					{// if matrix at scan is a teleporter and if its not a teleporter we are currently looking at then teleport!
						
						game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = myPlayers[pn].p;
						myPlayers[pn].position.x = i;
						myPlayers[pn].position.y = j;
						myPlayers[pn].position.y++;
						return;
					}

				}
		
			}
		}
		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == '^') 
		{//checks to make sure that the vertex we are moving to is a mountain

			if (myPlayers[pn].cType == "Hiker") 
			{//if youre a hiker you can go over mountains! else gotta find a different path!
				myPlayers[pn].work += 5;
				return;
			}
			else {
				cout << "Impassible terrain! Find a different path!" << endl;
				myPlayers[pn].position.y++;
				return;
			}
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == '~') 
		{//checks to make sure that the vertex we are moving to is a desert
			myPlayers[pn].work += 3;
			return;
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y - 1] == 'w') 
		{//checks to make sure that the vertex we are moving to is a swamp
			if (myPlayers[pn].cType == "Bogmaster") 
			{//if youre a bogmaster you can traverse swamps as easy as a plain! You get reduced weight cost!
				myPlayers[pn].work += 1;
				return;
			}
			else {
				myPlayers[pn].work += 4;
				return;
			}
			
		}

	}
///////////////////////////////////////////////
	if (m == 's') 
	{// if going left

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y] == 'x') 
		{//checks to make sure that the vertex we are moving to is our destination 
			cout << "Congrats! You made it to your goal! Your total travel effort is " << myPlayers[pn].work << "!" << endl;

			return;

		}

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y ] == 't') 
		{//checks to make sure that the vertex we are moving to is a forest
			myPlayers[pn].work += 2;
			return;
		}

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y] == '-')
		{//checks to make sure that the vertex we are moving to is a plain
			myPlayers[pn].work += 1;
			return;
		}

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y] == '@') 
		{//checks to make sure that the vertex we are moving to is a teleporter
			for (int i = 0; i < game->R + 1; i++) {//nested for loops to scan through matrix
				for (int j = 0; j < game->C + 1; j++) {
					if (game->M[i][j] == '@' && i != myPlayers[pn].position.x && j != myPlayers[pn].position.y){// if matrix at scan is a teleporter and if its not a teleporter we are currently looking at then teleport!
						game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = myPlayers[pn].p;
						myPlayers[pn].position.x = i;
						myPlayers[pn].position.y = j;
						myPlayers[pn].position.x--;
						return;
					}

				}
			
			}
		}

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y] == '^') 
		{//checks to make sure that the vertex we are moving to is a mountain
			if (myPlayers[pn].cType == "Hiker") {//if youre a hiker you can go over mountains! else gotta find a different path!
				myPlayers[pn].work += 5;
				return;
			}
			else {
				cout << "Impassible terrain! Find a different path!" << endl;
				myPlayers[pn].position.x--;
				return;
			}
		}

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y] == '~') 
		{//checks to make sure that the vertex we are moving to is a desert
			myPlayers[pn].work += 3;
			return;
		}

		if (game->M[myPlayers[pn].position.x + 1][myPlayers[pn].position.y] == 'w') 
		{//checks to make sure that the vertex we are moving to is a swamp
			if (myPlayers[pn].cType == "Bogmaster") {//if youre a bogmaster you can traverse swamps as easy as a plain! You get reduced weight cost!
				myPlayers[pn].work += 1;
				return;
			}
			else {
				myPlayers[pn].work += 4;
				return;
			}
		}

	}
///////////////////////////////////////////////
	if (m == 'd') 
	{// if going right

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == 'x') 
		{//checks to make sure that the vertex we are moving to is our destination 
			cout << "Congrats! You made it to your goal! Your total travel effort is " << myPlayers[pn].work << "!" << endl;

			return;

		}
		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == 't') 
		{//checks to make sure that the vertex we are moving to is a forest
			myPlayers[pn].work += 2;
			return;
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == '-') 
		{//checks to make sure that the vertex we are moving to is a plain
			myPlayers[pn].work += 1;
			return;
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == '@') 
		{//checks to make sure that the vertex we are moving to is a teleporter

			for (int i = 0; i < game->R + 1; i++) 
			{//nested for loops to scan through matrix
				for (int j = 0; j < game->C + 1; j++) 
				{
					if (game->M[i][j] == '@' && i != myPlayers[pn].position.x && j != myPlayers[pn].position.y)
					{// if matrix at scan is a teleporter and if its not a teleporter we are currently looking at then teleport!
						game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = myPlayers[pn].p;
						myPlayers[pn].position.x = i;
						myPlayers[pn].position.y = j;
						myPlayers[pn].position.y--;
						return;
					}

				}
			
			}
		}
		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == '^') 
		{//checks to make sure that the vertex we are moving to is a mountain
			if (myPlayers[pn].cType == "Hiker") 
			{//if youre a hiker you can go over mountains! else gotta find a different path!
				myPlayers[pn].work += 5;
				return;
			}
			else 
			{
				cout << "Impassible terrain! Find a different path!" << endl;
				myPlayers[pn].position.y--;
				return;
			}
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == '~') 
		{//checks to make sure that the vertex we are moving to is a desert
			myPlayers[pn].work += 3;
			return;
		}

		if (game->M[myPlayers[pn].position.x][myPlayers[pn].position.y + 1] == 'w') 
		{//checks to make sure that the vertex we are moving to is a swamp
			if (myPlayers[pn].cType == "Bogmaster") 
			{//if youre a bogmaster you can traverse swamps as easy as a plain! You get reduced weight cost!
				myPlayers[pn].work += 1;
				return;
			}
			else 
			{
				myPlayers[pn].work += 4;
				return;
			}
		}
	}

	
}

void Map::movePlayer(char m, int pn) //function to move a player
{

	game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = myPlayers[pn].p; //  remembers the vertex we are sitting on

	//game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = myPlayers[pn].p;

	if (m == 'w') //if input is up
	{
		if ((myPlayers[pn].position.x-1) == -1) //checks the up vertex to make sure its not out of bounds
		{
			cout << "Oops you'll fall into void! Better to choose a different direction!" << endl;
				return;
		}
		addWeight('w', pn); //add weight
		myPlayers[pn].position.x--; // move into vertex

	}
	if (m == 'a') //if input is down
	{
		if ((myPlayers[pn].position.y-1) == -1) 
		{
			cout << "Oops you'll fall into void! Better to choose a different direction!" << endl;
			return;
		}
		addWeight('a', pn);
		myPlayers[pn].position.y--;
	}
	if (m == 's') //if input is left
	{
		if ((myPlayers[pn].position.x+1) == game->R) 
		{
			cout << "Oops you'll fall into void! Better to choose a different direction!" << endl;
			return;
		}
		addWeight('s', pn);

		myPlayers[pn].position.x++;
	}
	if (m == 'd') //if input is right
	{
		if ((myPlayers[pn].position.y+1) == game->C) 
		{
			cout << "Oops you'll fall into void! Better to choose a different direction!" << endl;
			return;
		}
		addWeight('d', pn);
		myPlayers[pn].position.y++;
	}

	myPlayers[pn].p = game->M[myPlayers[pn].position.x][myPlayers[pn].position.y];

	// prints our character as different symbols based on type
	if (myPlayers[pn].cType == "Hiker")
	{
		game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = 'H';
	}
	if (myPlayers[pn].cType == "Tourist") 
	{
		game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = 'o';
	}
	if (myPlayers[pn].cType == "Bogmaster") 
	{
		game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = 'B';
	}
	//if moving into our destination then removes character from the game since they are finished!
	if (myPlayers[pn].p == 'x') 
	{
		game->M[myPlayers[pn].position.x][myPlayers[pn].position.y] = 'x';
	}
	DisplayMap(); // redisplays our map 
}

void Map::placePlayer(Coord c, int pn) //places our player!
{

	myPlayers[pn].p = game->M[c.x-1][c.y-1]; // sets the starting vertex to the players 'sitting on' variable

	//places
	if (myPlayers[pn].cType == "Hiker") 
	{
		game->M[c.x - 1][c.y - 1] = 'H';
	}
	if (myPlayers[pn].cType == "Tourist") 
	{
		game->M[c.x - 1][c.y - 1] = 'o';
	}
	if (myPlayers[pn].cType == "Bogmaster") 
	{
		game->M[c.x - 1][c.y - 1] = 'B';
	}
	myPlayers[pn].position.x  = c.x-1;
	myPlayers[pn].position.y = c.y-1;
	
}

void Map::DisplayMap() //displayes our map
{ 
	int i, j;
	for (i = 0; i < game->R; i++)
	{
		for (j = 0; j < game->C; j++)
		{
			std::cout << setw(2) << game->M[i][j];
		}
		cout << endl;
	}
}

//Graph class
Graph::Graph(string s) //Graph constructor for our dynamic arrays, also reads the inputed map and sets the Matrix array to its rows + 1 and columns + 1; 
{

	readMap(s);

	vis = new bool* [R+1];
	myArray = new int* [R+1];
	weight = new int* [R + 1];
	


	for (int i = 0; i < R+1; i++) 
	{
		myArray[i] = new int[C+1];
		vis[i] = new bool[C+1];
		weight[i] = new int[C + 1];
	}

	for (int i = 0; i < R + 1; i++) 
	{
		for (int j = 0; j < C + 1; j++) 
		{
			vis[i][j] = false;
		}
	}

	
	createWeightMatrix(); // creates matrix copy but with weight values not chars
}

Graph::~Graph() 
{
	
}

bool Graph::isValid(int row, int col)//utility function to check if our next vertex is a valid one for the BFS
{
	if (row < 0 || col < 0 || row >= R|| col >= C)
		return false;

	if (vis[row][col])
		return false;

	return true;
}

int** Graph::BFS(Coord start, Coord goal) //BFS tried to addapt for shortest path
{
	//fixes coords to be 0-(R-1) instead of 1-R for matrix accessing purposes
	start.x -= 1;
	start.y -= 1;
	goal.x -= 1;
	goal.y -= 1;

	int direction[4][2] = { {0,1}, {0,-1}, {1,0}, {-1,0} }; //direction matrix to check directions

	queue<Coord> q;
	int x, y;
	int a = 0;
	int b = 0;

	//moves starting vertex onto stack
	q.push(start);
	vis[start.x][start.y] = true;
	
	//while queue not empty
	while (!q.empty())
	{
		Coord d = q.front();//push starting vertex
		x = d.x;
		y = d.y;
		myArray[a][b] = M[x][y];

		if (b == C-1)//checks to make sure we are moving row to row
		{
			a++;
			b = -1;
		}
		b++;
		
		q.pop();


		for (int i = 0; i < 4; i++) //supposed to check all  directions
		{
			int adjx = x + mRow[i];
			int adjy = y + mCol[i];

			if (isValid(adjx, adjy)) //sees if its in bounds
			{
				Coord t;
				t.x = adjx;
				t.y = adjy;
				q.push(t);
				vis[adjx][adjy] = true;
			}

		}
	}
	
	//prints
	for (int i = 0; i < R; i++)
	{
		for (int j = 0; j < C; j++)
		{
			std::cout << setw(2) << myArray[i][j];
		}
		cout << endl;
	}
	return myArray;
}
 
int** Graph::DFS(Coord start, Coord goal) //Depth first search that i implemented for the labs
{
	stack<Coord> st;
	int x, y;
	int a = 0;
	int b = 0;

	st.push(start);

	while (!st.empty()) {
		Coord s = st.top();
		st.pop();
		x = s.x;
		y = s.y;

		if (!isValid(x, y)) {
			continue;
		}

		vis[x][y] = true;
		myArray[a][b] = M[x][y];

		if (b == C) {
			a++;
			b = -1;
		}
		b++;

		for (int i = 0; i < 4; i++) {
			int adjx = x + mRow[i];
			int adjy = y + mCol[i];
			Coord t;
			t.x = adjx;
			t.y = adjy;
			st.push(t);
		}

	}
	
	return myArray;
}

void Graph::readMap(string s) //reads our maps and saves them to the neccesary members
{

	std::ifstream file(s);
	string str;
	int i, j;
	string temp;

	//check first line which is row value
	getline(file, str);
	std::istringstream iss1(str);
	iss1 >> R;
	
	//check second line which is column value
	getline(file, str);
	std::istringstream iss2(str);
	iss2 >> C;
		
	
	//allocates our member dynamic matrix
	M = new char* [R+1];
	for (i = 0; i < R+1; i++) 
	{
		M[i] = new char[C+1];
	}
	
	i = 0;
	//reads the entire matrix
	while (getline(file, str)) 
	{
		 j = 0;
		std::istringstream iss(str);
		while (iss) 
		{
			iss >> M[i][j];
				j++;
		}
		i++;
	}

}

void Graph::createAdjMatrix() {
	int n = R * C; // nodes or vertices
	int m = (R - 1) * C + (C - 1) * R; // edges
	adj = new int* [n + 1];
	for (int i = 0; i < n + 1; i++) {
		adj[i] = new int[n + 1];
		for (int j = 0; j < n + 1; j++) {
			adj[i][j] = 0;
		}
	}
	for (int i = 0; i < R; i++) {
		for (int j = 0; j < C; j++) {
			int localIndex = i * (R-1) + j;


			if (i > 0) {//checks - x bounds
				int travIndex = (i-1) * (R - 1) + j;

				int w = weight[i-1][j];
				adj[localIndex][travIndex] = w;
			}

			if (i < R) {//checks +X bounds
				int travIndex = (i + 1) * (R - 1) + j;

				int w = weight[i + 1][j];
				adj[localIndex][travIndex] = w;
			}

			if (j > 0) { //checks - y bounds
				int travIndex = i * (R - 1) + (j-1);

				int w = weight[i][j-1];
				adj[localIndex][travIndex] = w;
			}
			if (j < C) {//checks + y bounds
				int travIndex = i * (R - 1) + (j+1);

				int w = weight[i][j+1];
				adj[localIndex][travIndex] = w;
			}
			if (M[i][j] == '@') {//checks teleporters
				for (int a = 0; a < R; a++) {
					for (int b = 0; b < C; b++) {
						if (M[a][b] == '@' && a != i && b != j) {
							int travIndex = a * (R - 1) + b;
							adj[localIndex][travIndex] = 0;
						}
						
					}
				}
			}
			
		}
	}


	for (int q = 0; q < n+1; q++) {
		for (int o = 0; o < n+1; o++) {
			cout << adj[q][o] << " ";
		}
		cout << endl;
	}
}

/*void Graph::addEdge(int i, int j) {
	adj[i][j] = true;
	adj[j][i] = true;
}
*/

void Graph::createWeightMatrix() //converts all char values in map to their weight value
{
	for (int i = 0; i < R; i++) 
	{
		for (int j = 0; j < C; j++) 
		{
			if (M[i][j] == '^')
			{
				weight[i][j] = 5;
			}
			else if (M[i][j] == 'w') 
			{
				weight[i][j] = 4;
			}
			else if (M[i][j] == '~') 
			{
				weight[i][j] = 3;
			}
			else if (M[i][j] == 't') 
			{
				weight[i][j] = 2;
			}
			else if (M[i][j] == '-') 
			{
				weight[i][j] = 1;
			}
			else if (M[i][j] == '@') 
			{
				weight[i][j] = 0;
			}
			else if (M[i][j] == 'x')
			{
				weight[i][j] = -1;
			}
			else {
				weight[i][j] = -88;
			}
			//cout << weight[i][j] << " ";
		}
		//cout << endl;
	}
}

/*int Graph::minDistance(int dist[], bool sptSet[])
{

	// Initialize min value
	int min = INT_MAX, min_index = 0;

	for (int v = 0; v < R; v++)
		if (sptSet[v] == false &&
			dist[v] <= min)
			min = dist[v], min_index = v;

	return min_index;
}*/

/*void Graph::printPath(int parent[], int j)
{

	// Base Case : If j is source
	if (parent[j] == -1)
		return;

	printPath(parent, parent[j]);

	printf("%d ", j);
}*/

/*void Graph::printSolution(int dist[], int n, int parent[])
{
	int src = 0;
	printf("Vertex\t Distance\tPath");
	for (int i = 1; i < R; i++)
	{
		printf("\n%d -> %d \t\t %d\t\t%d ",
			src, i, dist[i], src);
		printPath(parent, i);
	}
}*/

/*void Graph::dijkstra(int src)
{

	// The output array. dist[i]
	// will hold the shortest
	// distance from src to i
	int *dist = new int [vertices];

	// sptSet[i] will true if vertex
	// i is included / in shortest
	// path tree or shortest distance 
	// from src to i is finalized
	bool* sptSet = new bool[vertices];

	// Parent array to store
	// shortest path tree
	int *parent = new int[vertices];

	// Initialize all distances as 
	// INFINITE and stpSet[] as false
	for (int i = 0; i < vertices; i++)
	{
		parent[0] = -1;
		dist[i] = INT_MAX;
		sptSet[i] = false;
	}

	// Distance of source vertex 
	// from itself is always 0
	dist[src] = 0;

	// Find shortest path
	// for all vertices
	for (int count = 0; count < vertices - 1; count++)
	{
		// Pick the minimum distance
		// vertex from the set of
		// vertices not yet processed. 
		// u is always equal to src
		// in first iteration.
		int u = minDistance(dist, sptSet);

		// Mark the picked vertex 
		// as processed
		sptSet[u] = true;

		// Update dist value of the 
		// adjacent vertices of the
		// picked vertex.
		for (int v = 0; v < vertices; v++)

			// Update dist[v] only if is
			// not in sptSet, there is
			// an edge from u to v, and 
			// total weight of path from
			// src to v through u is smaller
			// than current value of
			// dist[v]
			if (!sptSet[v] && adj[u][v] &&
				dist[u] + adj[u][v] < dist[v])
			{
				parent[v] = u;
				dist[v] = dist[u] + adj[u][v];
			}
	}


// print the constructed
// distance array
printSolution(dist, R, parent);
}

*/


char getCnum() //utility function to get character numbers from UI
{
	char cnum;
	std::cout << "How many characters do you want to play with? Choose 1-3: ";
	std::cin >> cnum;
	if (cnum != '1' && cnum != '2' && cnum != '3') {
		std::cout << "Invalid input! Please try again!" << endl;
		getCnum();
	}
	
	
	return cnum;
}

char getMnum() //utility function to get map number from UI
{
	char mnum;
	std::cout << "Enter map number 1 or 2 :): ";
	std::cin >> mnum;

	if (mnum != '1' && mnum != '2') {
		std::cout << "Invalid input! Please try again!" << endl;
		getMnum();
	}
	return mnum;
}

TwoNames getCname() // utility function that gets name for character type from UI
{ 
	TwoNames cname;
		std::cout << "Choose your character! Tourist, Hiker, or Bogmaster! ";
		std::cin >> cname.one;
		if (cname.one != "Tourist" && cname.one != "Hiker" && cname.one != "Bogmaster") {
			std::cout << "Invalid input! Please try again!" << endl;
			getCname();
		}
	
	return cname;
}

TwoNames getCnames() // utility function that gets two names for character types from UI
{
	TwoNames cnames;
	std::cout << "Choose two characters! Tourist, Hiker, or Bogmaster! ";
	std::cin >> cnames.one;
	if (cnames.one != "Tourist" && cnames.one != "Hiker" && cnames.one != "Bogmaster") {
		std::cout << "Invalid input! Please try again!" << endl;
		getCnames();
	}
	std::cin >> cnames.two;
	 if(cnames.two != "Tourist" && cnames.two != "Hiker" && cnames.two != "Bogmaster") {
		std::cout << "Invalid input! Please try again!" << endl;
		getCnames();
	}
	return cnames;
}

int playGame() // gets all our values and then starts the game
{
	bool finish = false;

	char cnum;
	char mnum;
	TwoNames cnames;

	string fileName = "map";

	Player one;
	Player two;
	Player three;
	Coord S = { 0, 0 };
	Coord S1 = { 0, 0 };
	Coord S2 = { 0, 0 };
	//Coord D;

	cnum = getCnum();// get number of players
	mnum = getMnum();//gets map number

	//makes our input into a 'mapx-x.txt' format to be read
	fileName += cnum; 
	fileName += '-';
	fileName += mnum;
	fileName += ".txt";

	// makes dynamic graph
	Graph* myGame = new Graph(fileName);
	//myGame->createAdjMatrix();
	//makes map
	Map myMap(myGame);
	myMap.myPlayers[0].active = true;//sets player 1 to default active player
	myMap.myPlayers[1].active = false;
	myMap.myPlayers[2].active = false;

	///////////////////////////////////////////////////////////////////////
	if (cnum == '1') //if playing with one player
	{
		cnames = getCname();
		myMap.myPlayers[0].cType = cnames.one; // makes player ones type to UI

		myMap.DisplayMap();//displays basic map without players
		cout << "This map is a " << myMap.game->R << " by " << myMap.game->C << ". Where would you like your character to start? Enter response as 'number number'!";
		cin >> S.x >> S.y;

		//D = { 6, 6 };
		myMap.placePlayer(S, 0);

		//cout << S.x << " " << S.y ;
		myMap.DisplayMap();//redisplays after getting starting position

		while (!finish)// gets UI for movement and for restarting
		{
			char input;
			std::cin >> input;
			system("cls"); // clear the commandline (to refresh the screen)
			switch (input)
			{
			case 'q':// ends process after freeing memory
				for (int i = 0; i < myGame->R + 1; i++) 
				{
					delete[] myGame->M[i];
					delete[] myGame->myArray[i];
					delete[] myGame->vis[i];
					//delete[] myGame->adj[i];
					delete[] myGame->weight[i];
				}
				delete[] myGame->M;
				delete[] myGame->vis;
				delete[] myGame->myArray;
				//delete[] myGame->adj;
				delete[] myGame->weight;
				delete myGame;

				finish = true;
				break;

			case 'f':; break;//shortest path
			case 'r':playGame(); break; // restarts the game
			case 'w':myMap.movePlayer('w', 0); break; // move up
			case 'a':myMap.movePlayer('a', 0); break; // move down
			case 's':myMap.movePlayer('s', 0); break; // move left
			case 'd':myMap.movePlayer('d', 0); break; // move right

			}
		}
	}
	///////////////////////////////////////////////////////////////////////
	if (cnum == '2') 
	{
		cnames = getCnames();
		myMap.myPlayers[0].cType = cnames.one;
		myMap.myPlayers[1].cType = cnames.two;

		myMap.DisplayMap();
		cout << "This map is a " << myMap.game->R << " by " << myMap.game->C << ". Where would you like character one to start? Enter response as 'number number'!";
		cin >> S.x >> S.y;
		cout << "Where would you like character two to start ? Enter response as 'number number'!";
		cin >> S1.x >> S1.y;


		myMap.placePlayer(S, 0);
		myMap.placePlayer(S1, 1);

		myMap.DisplayMap();

		while (!finish)
		{
			char input;
			std::cin >> input;
			system("cls"); // clear the commandline (to refresh the screen)
			switch (input)
			{
			case 'q':
				for (int i = 0; i < myGame->R + 1; i++) {
					delete[] myGame->M[i];
					delete[] myGame->myArray[i];
					delete[] myGame->vis[i];
				//	delete[] myGame->adj[i];
					delete[] myGame->weight[i];

				}
				delete[] myGame->M;
				delete[] myGame->vis;
				delete[] myGame->myArray;
			//	delete[] myGame->adj;
				delete[] myGame->weight;
				delete myGame;

				finish = true;
				break;

			case 'f':; break;//shortest path
			case 'r':playGame(); break;


			case '1'://switches active player to player one and deavtives the others
				myMap.myPlayers[0].active = true;
				myMap.myPlayers[1].active = false;
				myMap.DisplayMap();
				break;

			case '2'://switches active player to player two and deactivates the others
				myMap.myPlayers[0].active = false;
				myMap.myPlayers[1].active = true;
				myMap.DisplayMap();

				break;

			case 'w'://move up
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('w', 0);
				}
				else 
				{
					myMap.movePlayer('w', 1);
				}
				break;

			case 'a'://move down
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('a', 0);
				}
				else 
				{
					myMap.movePlayer('a', 1);
				}
				break;

			case 's'://move left
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('s', 0);
				}
				else 
				{
					myMap.movePlayer('s', 1);
				}
				break;

			case 'd'://move right
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('d', 0);
				}
				else 
				{
					myMap.movePlayer('d', 1);
				}
				break;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////
	if (cnum == '3') {
		myMap.myPlayers[0].cType = "Tourist";
		myMap.myPlayers[1].cType = "Hiker";
		myMap.myPlayers[2].cType = "Bogmaster";

		myMap.DisplayMap();
		cout << "This map is a " << myMap.game->R << " by " << myMap.game->C << ". Where would you like the Tourist to start? Enter response as 'number number'!";
		cin >> S.x >> S.y;

		cout << "Where would you like the Hiker to start ? Enter response as 'number number'!";
		cin >> S1.x >> S1.y;

		cout << "Where would you like the Bogmaster to start ? Enter response as 'number number'!";
		cin >> S2.x >> S2.y;

		myMap.placePlayer(S, 0);
		myMap.placePlayer(S1, 1);
		myMap.placePlayer(S2, 2);
		//cout << S.x << " " << S.y ;
		myMap.DisplayMap();

		while (!finish)
		{
			char input;
			std::cin >> input;
			system("cls"); // clear the commandline (to refresh the screen)
			switch (input)
			{
			case 'q':
				for (int i = 0; i < myGame->R + 1; i++) 
				{
					delete[] myGame->M[i];
					delete[] myGame->myArray[i];
					delete[] myGame->vis[i];
					//delete[] myGame->adj[i];
					delete[] myGame->weight[i];

				}
				delete[] myGame->M;
				delete[] myGame->vis;
				delete[] myGame->myArray;
				//delete[] myGame->adj;
				delete[] myGame->weight;
				delete myGame;

				finish = true;
				break;

			case 'f':; break;//shortest path
			case 'r':playGame(); break;


			case '1':
				myMap.myPlayers[0].active = true;
				myMap.myPlayers[1].active = false;
				myMap.myPlayers[2].active = false;
				myMap.DisplayMap();

				break;

			case '2':
				myMap.myPlayers[0].active = false;
				myMap.myPlayers[1].active = true;
				myMap.myPlayers[2].active = false;
				myMap.DisplayMap();


				break;
			case '3':
				myMap.myPlayers[0].active = false;
				myMap.myPlayers[1].active = false;
				myMap.myPlayers[2].active = true;
				myMap.DisplayMap();

				break;

			case 'w':
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('w', 0);
				}
				if (myMap.myPlayers[1].active == true) 
				{
					myMap.movePlayer('w', 1);
				}
				if (myMap.myPlayers[2].active == true)
				{
					myMap.movePlayer('w', 2);
				}
				break;

			case 'a':
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('a', 0);
				}
				if (myMap.myPlayers[1].active == true) 
				{
					myMap.movePlayer('a', 1);
				}
				if (myMap.myPlayers[2].active == true)
				{
					myMap.movePlayer('a', 2);
				}
				break;

			case 's':
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('s', 0);
				}
				if (myMap.myPlayers[1].active == true) 
				{
					myMap.movePlayer('s', 1);
				}
				if(myMap.myPlayers[2].active == true)
				{
					myMap.movePlayer('s', 2);
				}
				break;

			case 'd':
				if (myMap.myPlayers[0].active == true) 
				{
					myMap.movePlayer('d', 0);
				}
				if (myMap.myPlayers[1].active == true) 
				{
					myMap.movePlayer('d', 1);
				}
				if (myMap.myPlayers[2].active == true)
				{
					myMap.movePlayer('d', 2);
				}
				break;

			}
		}
	}
	return 0;
}

int main() {

	std::cout << "CSci 115 - Project" << endl << endl;
	
	playGame();

	
	/*
	cnum = getCnum();
	mnum = getMnum();

	fileName += cnum;
	fileName += '-';
	fileName += mnum;
	fileName += ".txt";

	Graph * myGame = new Graph(fileName);
	Map myMap(myGame);
	myMap.myPlayers[0].active = true;
///////////////////////////////////////////////////////////////////////
	if (cnum == '1') {
		cnames = getCname();
		myMap.myPlayers[0].cType = cnames.one;

		myMap.DisplayMap();
		cout << "This map is a " << myMap.game->R << " by " << myMap.game->C << ". Where would you like your character to start? Enter response as 'number number'!";
		cin >> S.x >> S.y;
		D = { 6, 6 };
		myMap.placePlayer(S, 0);
		
		//cout << S.x << " " << S.y ;
		myMap.DisplayMap();

		while (!finish)
		{
			char input;
			std::cin >> input;
			system("cls"); // clear the commandline (to refresh the screen)
			switch (input)
			{
				case 'q':
					for (int i = 0; i < myGame->R + 1; i++) {
						delete[] myGame->M[i];
						delete[] myGame->myArray[i];
						delete[] myGame->vis[i];
					//	delete[] myGame->adj[i];
						delete[] myGame->weight[i];
					}
					delete[] myGame->M;
					delete[] myGame->vis;
					delete[] myGame->myArray;
				//	delete[] myGame->adj;
					delete[] myGame->weight;
					finish = true;
					break;

				case 'f':; break;//shortest path
				case 'w':myMap.movePlayer('w', 0); break;
				case 'a':myMap.movePlayer('a', 0); break;
				case 's':myMap.movePlayer('s', 0); break;
				case 'd':myMap.movePlayer('d', 0); break;

			}
		}
	}
///////////////////////////////////////////////////////////////////////
	if (cnum == '2') {
		cnames = getCnames();
		myMap.myPlayers[0].cType = cnames.one;
		myMap.myPlayers[1].cType = cnames.two;

		myMap.DisplayMap();
		cout << "This map is a " << myMap.game->R << " by " << myMap.game->C << ". Where would you like character one to start? Enter response as 'number number'!";
		cin >> S.x >> S.y;
		cout << "Where would you like character two to start ? Enter response as 'number number'!";
		cin >> S1.x >> S1.y;


		myMap.placePlayer(S, 0);
		myMap.placePlayer(S1, 1);
		
		myMap.DisplayMap();

		while (!finish)
		{
			char input;
			std::cin >> input;
			system("cls"); // clear the commandline (to refresh the screen)
			switch (input)
			{
				case 'q':
					for (int i = 0; i < myGame->R + 1; i++) {
						delete[] myGame->M[i];
						delete[] myGame->myArray[i];
						delete[] myGame->vis[i];
						//delete[] myGame->adj[i];
						delete[] myGame->weight[i];

					}
					delete[] myGame->M;
					delete[] myGame->vis;
					delete[] myGame->myArray;
					//delete[] myGame->adj;
					delete[] myGame->weight;
					finish = true;
					break;

				case 'f':; break;//shortest path

				case '1':	
					myMap.myPlayers[0].active = true;
					myMap.myPlayers[1].active = false;
					myMap.DisplayMap();
					break;

				case '2':	
					myMap.myPlayers[0].active = false;
					myMap.myPlayers[1].active = true;
					myMap.DisplayMap();

					break;

				case 'w':
					if (myMap.myPlayers[0].active == true) {
						myMap.movePlayer('w', 0);
					}
					else {
						myMap.movePlayer('w', 1); 
					}
					break;

				case 'a':
					if (myMap.myPlayers[0].active == true) {
					myMap.movePlayer('a', 0);
					}
					else {
					myMap.movePlayer('a', 1);
					}
					break;

				case 's':
					if (myMap.myPlayers[0].active == true) {
					myMap.movePlayer('s', 0);
					}
					else {
					myMap.movePlayer('s', 1);
					}
					break;

				case 'd':
					if (myMap.myPlayers[0].active == true) {
					myMap.movePlayer('d', 0);
					}
					else {
					myMap.movePlayer('d', 1);
					}
					break;
			}
		}
	}
	///////////////////////////////////////////////////////////////////////
	if (cnum == '3') {
		myMap.myPlayers[0].cType = "Tourist";
		myMap.myPlayers[1].cType = "Hiker";
		myMap.myPlayers[2].cType = "Bogmaster";

		myMap.DisplayMap();
		cout << "This map is a " << myMap.game->R << " by " << myMap.game->C << ". Where would you like the Tourist to start? Enter response as 'number number'!";
		cin >> S.x >> S.y;

		cout << "Where would you like the Hiker to start ? Enter response as 'number number'!";
		cin >> S1.x >> S1.y;

		cout << "Where would you like the Bogmaster to start ? Enter response as 'number number'!";
		cin >> S2.x >> S2.y;

		myMap.placePlayer(S, 1);
		//cout << S.x << " " << S.y ;
		myMap.DisplayMap();

		while (!finish)
		{
			char input;
			std::cin >> input;
			system("cls"); // clear the commandline (to refresh the screen)
			switch (input)
			{
				case 'q':
					for (int i = 0; i < myGame->R + 1; i++) {
						delete[] myGame->M[i];
						delete[] myGame->myArray[i];
						delete[] myGame->vis[i];
						//delete[] myGame->adj[i];
						delete[] myGame->weight[i];

					}
					delete[] myGame->M;
					delete[] myGame->vis;
					delete[] myGame->myArray;
					//delete[] myGame->adj;
					delete[] myGame->weight;


					finish = true;
					break;

				case 'f':; break;//shortest path

				case '1':
					myMap.myPlayers[0].active = true;
					myMap.myPlayers[1].active = false;
					myMap.myPlayers[2].active = false;
					myMap.DisplayMap();

					break;

				case '2':
					myMap.myPlayers[0].active = false;
					myMap.myPlayers[1].active = true;
					myMap.myPlayers[2].active = false;
					myMap.DisplayMap();


					break;
				case '3':
					myMap.myPlayers[0].active = false;
					myMap.myPlayers[1].active = false;
					myMap.myPlayers[2].active = true;
					myMap.DisplayMap();

					break;

				case 'w':
					if (myMap.myPlayers[0].active == true) {
						myMap.movePlayer('w', 0);
					}
					if (myMap.myPlayers[1].active == true) {
						myMap.movePlayer('w', 1);
					}
					else {
						myMap.movePlayer('w', 2);
					}
					break;

				case 'a':
					if (myMap.myPlayers[0].active == true) {
						myMap.movePlayer('a', 0);
					}
					if (myMap.myPlayers[1].active == true) {
						myMap.movePlayer('a', 1);
					}
					else {
						myMap.movePlayer('a', 2);
					}
					break;

				case 's':
					if (myMap.myPlayers[0].active == true) {
						myMap.movePlayer('s', 0);
					}
					if (myMap.myPlayers[1].active == true) {
						myMap.movePlayer('s', 1);
					}
					else {
						myMap.movePlayer('s', 2);
					}
					break;

				case 'd':
					if (myMap.myPlayers[0].active == true) {
						myMap.movePlayer('d', 0);
					}
					if (myMap.myPlayers[1].active == true) {
						myMap.movePlayer('d', 1);
					}
					else {
						myMap.movePlayer('d', 2);
					}
					break;

			}
		}
	}
	*/
}
