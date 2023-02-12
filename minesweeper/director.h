#pragma once
#include <vector>
#include "cell.h"
using namespace std;

class Director {
private:
	int width = 8;
	int height = 8;
	int mineCount = 8; 

public:
	// Constructors
	Director(); // for standard game rules
	Director(int width, int height, int mineCount); // for alternate game rules
	
	int getWidth() const;
	int getHeight() const;
	int getMineCount() const;

	
	vector<Cell> distributeMines(Director director);

	void displayBoard(vector<Cell> board, int width, int height);

	vector<Cell> checkAdjacentCells(Director director, vector<Cell> board, int chosenCell);

};