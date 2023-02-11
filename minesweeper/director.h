#pragma once
#include <vector>
using namespace std;

class Director {
private:
	int width = 8;
	int height = 8;
	int mineCount = 10; 

public:
	// Constructors
	Director(); // for standard game rules
	Director(vector<int> board, int width, int height, int mineCount); // for alternate game rules
	
	int getWidth() const;
	int getHeight() const;
	int getMineCount() const;
	
	vector<int> board;

	
	vector<int> distributeMines(vector<int> board, int width, int height, int mineCount);

	void displayBoard(vector<int> board, int width, int height);

	void checkAdjacentCells();

};