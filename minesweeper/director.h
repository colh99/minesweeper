#pragma once
#include <vector>
#include "cell.h"
using namespace std;

class Director {
private:
	int width = 8;
	int height = 8;
	int mineCount = 10; 

public:
	// Constructors
	Director(); // for standard game rules
	Director(int width, int height, int mineCount); // for alternate game rules
	
	int getWidth() const;
	int getHeight() const;
	int getMineCount() const;

	
	vector<Cell> distributeMines(Director director);

	void displayBoard(vector<Cell> board, int width, int height);

	void checkAdjacentCells();

};