#include "Pathfinder.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

// #################################################################################################################
// ##																											  ##
// ##											To String Function 											  	  ##
// ##																											  ##
// #################################################################################################################


	string Pathfinder::toString() const {

		// Create our stringstream object
		stringstream ss;
		int stop = 4;

		// Loop through height, width and depth
		for (int k = 0; k <= stop; k++) {
			for (int j = 0; j <= stop; j++) {
				for (int i = 0; i <= stop; i++) {

						// Space if we aren't on the last part
						if (i < stop) {
							ss << maze[i][j][k] << " ";
						}

						// Otherwise the last part doesn't need a space
						else {
							ss << maze[i][j][k];
						}
				}
				// Endline
				ss << endl;
			}
			// In between
			if (k < stop) {
				ss << endl;
			}
		}
		// Return the string stream object
		return ss.str();
  }

// #################################################################################################################
// ##																											  ##
// ##											Create a Random Maze 											  ##
// ##																											  ##
// #################################################################################################################

	void Pathfinder::createRandomMaze() {

		// Stop value
		int stop = 4;

		// Loop through the entire maze (as always)
		for (int k = 0; k <= stop; k++) {
			for (int j = 0; j <= stop; j++) {
				for (int i = 0; i <= stop; i++) {

					// Random 1 or zero
					maze[i][j][k] = rand() % 2;
				}
			}
		}

		// HAVE TO HAVE FIRST AND LAST BE A 1
		maze[0][0][0] = 1;
		maze[4][4][4] = 1;
		return;
	}

	// #################################################################################################################
	// ##																											  ##
	// ##											Import the Maze 											  	  ##
	// ##																											  ##
	// #################################################################################################################

	bool Pathfinder::importMaze(string file_name) {

		// Create a temporary maze to use
		int tempMaze[5][5][5];
		int stop = 4;

		// If stream open
		ifstream reading;
		reading.open(file_name);

		// Same loop through everything as always
		for (int z = 0; z <= stop; z++){
			for (int y = 0; y <= stop; y++) {
				for (int x = 0; x <= stop; x++) {

					// Create a string val and read it
					string string_val;
					reading >> string_val;

					// If it isn't a 1 or 0 then it is an invalid maze
					if (string_val != "1" && string_val != "0") {
						return false;
					}

					// STRING TO INTEGER
					tempMaze[x][y][z] = stoi(string_val);
				}
			}
		}

		// Control for more out of range stuff
		while (!(reading.eof())) {

			// Create out of range variable
			string OOR;
			reading >> OOR;

			// Newline and space
			if (OOR != "\n" && OOR != " ") {
				return false;
			}
		}

		// Final Check, first and last need to be a 1
		if (tempMaze[0][0][0] == 1 && tempMaze[4][4][4] == 1) {

			// Same silly loopy
			for (int i = 0; i <= stop; i++) {
				for (int j = 0; j <= stop; j++) {
					for (int k = 0; k <= stop; k++) {

						// Assign the value
						maze[k][j][i] = tempMaze[k][j][i];
					}
				}
			}
		}

		// If the quality control isn't passed
		else {
			return false;
		}

		// Otherwise we finally have a working maze
		return true;
	}

	// #################################################################################################################
	// ##																											  ##
	// ##											Solve Maze (Easy Part) 											  ##
	// ##																											  ##
	// #################################################################################################################

	vector<string> Pathfinder::solveMaze() {

		// Clear the pre-existing pathways
		pathways.clear();
		int stop = 5;

		// Find the pathway (recursion)
		recursiveWay(0,0,0);

		// Same silly loop to reassign everything back to 1
		for (int k = 0; k < stop; k++) {
			for (int j = 0; j < stop; j++) {
				for (int i = 0; i < stop; i++) {
					if (maze[i][j][k] == 2) {
						maze[i][j][k] = 1;
					}
				}
			}
		}

		// Return the path that we found
		return pathways;
	}

	// #################################################################################################################
	// ##																											  ##
	// ##											Find the Path 												 	  ##
	// ##																											  ##
	// #################################################################################################################

	bool Pathfinder::recursiveWay(int x, int y, int z) {

		// Stop value
		int stop = 4;

		// If it is out bounds
		if (x < 0 || x > stop || y < 0 || y > stop || z < 0 || z > stop) {
			return false;
		}

		// If it is a zero or we've already been there
		if (maze[z][y][x]==0 || maze[z][y][x]==2 ) {
			return false;
		}

		// If we are at the very end
		if (x == stop && y == stop && z == stop ) {

			// Push the val back and return true
			pathways.push_back("(4, 4, 4)");
			return true;
		}

		// Add a string version of the spot to the path
		pathways.push_back("(" + to_string(z) + ", " + to_string(y) + ", " + to_string(x) + ")");

		// Give it a 2 since we have already been there
		maze[z][y][x] = 2;

		// Check row - 1 and row + 1
		if (recursiveWay(x - 1, y, z)) {
			return true;
		}
		else if (recursiveWay(x + 1, y, z)) {
			return true;
		}

		// Check col - 1 and col + 1
		else if (recursiveWay(x, y - 1, z)) {
			return true;
		}
		else if (recursiveWay(x, y + 1, z)) {
			return true;
		}

		// Check depth - 1 and depth + 1
		else if (recursiveWay(x, y, z - 1)) {
			return true;
		}
		else if (recursiveWay(x, y, z + 1)) {
			return true;
		}

		// Otherwise if nothing worked then return false
		else {
			pathways.pop_back();
			return false;
		}
	}
