#include "director.h"
#include <vector>
#include <iostream>
#include <set>
#include <cassert>

using namespace std;


// CONSTRUCTORS
Director::Director() 
{
}


Director::Director(vector<int> board, int width, int height, int mineCount)
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
 vector<int> Director::distributeMines(vector<int> board, int width, int height, int mineCount)
{
	 int expectedSize = width * height;
	 assert(("MESSAGE: There should be enough cells to fit all the mines", mineCount < expectedSize));

	 // Pick random numbers to determine mine locations
	 std::set<int> mineLocations;
	 srand(time(0)); 
	 while (mineLocations.size() < mineCount) 
	 {
		 mineLocations.insert(rand() % expectedSize); // mineLocations is a set so duplicates are discarded.
	 }

	 // The mineLocations set is emptied into the board. Indices where a mine exists are assigned a value of -1
	 while (board.size() < expectedSize)
	 {
		 if (mineLocations.size() != 0)
		 {
			auto setIterator = mineLocations.begin(); // Always checks the front of the set for O(1), rather than searching at O(log n), because the set is already ordered!

			if (board.size() == *setIterator)
			{
				board.push_back(-1); // -1 denotes a mine!
				mineLocations.erase(mineLocations.begin());
			}
			else
			{
				board.push_back(0);
			}
		 }
		 else 
		 {
			board.push_back(0); // For now, 0 denotes no mine at this index. Later, this will change to represent the number of adjacent mines.
		 }
	 }

	 return board;
}


 void Director::displayBoard(vector<int> board, int width, int height)
 {
	 for (int i = 0; i < width * height; i++)
	 {
		 if (i % 8 == 0)
		 {
			 cout << endl;
		 }
		 cout << board[i];
		 
	 }
 }


// Clicking a cell begins a recursive function. First it checks if the clicked cell has a mine (value of -1).
// The function finds the value based on the number of adjacent mines, and displays it.
// If an adjacent cell value = 0, check that cell for adjacent mines (use recursion)