#include "director.h"
#include "cell.h"
#include <vector>
#include <iostream>
#include <set>
#include <cassert>

using namespace std;


// CONSTRUCTORS
Director::Director() 
{
}


Director::Director(int width, int height, int mineCount)
{
}


// GETTERS
int Director::getWidth() const
{
	return width;
}


int Director::getHeight() const
{
	return height;
}


int Director::getMineCount() const
{
	return mineCount;
}


// GAMEPLAY
 vector<Cell> Director::distributeMines(Director director)
{
	 int width = director.getWidth();
	 int height = director.getHeight();
	 int mineCount = director.getMineCount();
	 
	 int expectedSize = width * height;
	 assert(("MESSAGE: There should be enough cells to fit all the mines", mineCount < expectedSize));

	 // Pick random numbers to determine mine locations
	 std::set<int> mineLocations;
	 srand(time(0)); 
	 while (mineLocations.size() < mineCount) 
	 {
		 mineLocations.insert(rand() % expectedSize); // mineLocations is a set so duplicates are discarded.
	 }

	 vector<Cell> board;

	 // The mineLocations set is emptied into the board.
	 while (board.size() < expectedSize)
	 {
		 if (mineLocations.size() != 0)
		 {
			auto setIterator = mineLocations.begin(); // Always checks the front of the set for O(1), rather than searching at O(log n), because the set is already ordered!

			if (board.size() == *setIterator)
			{
				Cell cell = Cell(true, false, 0);
				board.push_back(cell); 
				mineLocations.erase(mineLocations.begin());
			}
			else
			{
				Cell cell = Cell(false, false, 0);
				board.push_back(cell);
			}
		 }
		 else 
		 {
			Cell cell = Cell(false, false, 0);
			board.push_back(cell); // For now, 0 denotes no mine at this index. Later, this will change to represent the number of adjacent mines.
		 }
	 }

	 return board;
}


 void Director::displayBoard(vector<Cell> board, int width, int height)
 {
	 cout << "     1  2  3  4  5  6  7  8  " << endl; // X axis labels
	 cout << "     _  _  _  _  _  _  _  _  ";

	 for (int i = 0; i < width * height; i++)
	 {
		 if (i % 8 == 0) // Determines end of line
		 {
			 cout << endl;
			 cout << " " << i / 8 << "  "; // Y axis labels
		 }

		 if (board[i].getVisibility() == true)
		 {
			 if (board[i].getContainsMine() == true)
			 {
				 cout << "|X|";

			 }
			 else
			 {
				 cout << "|" << board[i].getValue() << "|";
			 }
		 }
		 else
		 {
			 wcout << L"|_|"; // Not visible cells should display as blank
		 }

		 
	 }
 }



// Clicking a cell begins a recursive function. First it checks if the clicked cell has a mine (value of -1).
// The function finds the value based on the number of adjacent mines, and displays it.
// If an adjacent cell value = 0, check that cell for adjacent mines (use recursion)