#pragma once
#include "PathfinderInterface.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Pathfinder : public PathfinderInterface {

public:

	// #################################################################################################################
	// ##																											  ##
	// ##										Constructor and Destructor 										  	  ##
	// ##																											  ##
	// #################################################################################################################


	// Maze and height instantiations
	int maze[5][5][5];
	int HEIGHT;
	int WIDTH;
	int DEPTH;

	// Contructor creates a 5 by 5 maze of all 1's
	Pathfinder() {

		// Each of our values
		HEIGHT = 5;
		WIDTH = 5;
		DEPTH = 5;

		// Loop through every row column and depth
		for (int k = 0; k < HEIGHT; k++) {
			for (int j = 0; j < WIDTH; j++) {
				for (int i = 0; i < DEPTH; i++) {

					// Assign the value
					maze[i][j][k] = 1;
				}
			}
		}
	}

	// Destructor
	~Pathfinder() {}

	// #################################################################################################################
	// ##																											  ##
	// ##											All of my functions 											  ##
	// ##																											  ##
	// #################################################################################################################

	// Create a random maze
	void createRandomMaze();

	// Read in a maze - returns true or false
	bool importMaze(string file_name);

	// Finds a viable path (recursion?)
	bool recursiveWay(int x, int y, int z);

	// Returns a string representing the current maze
	string toString() const;

	// Solve:)
	vector<string> solveMaze();

	// Vector of Pathway Strings
private:
	vector<string> pathways;
};
