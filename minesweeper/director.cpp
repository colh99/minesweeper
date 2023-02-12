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
	 cout << "   X  ";
	 for (int i = 0; i < width; i++)
	 {
		cout << i + 1 << "   "; // X axis labels
	 }
	 
	 cout << endl;
	 cout << " Y  ";
	 for (int i = 0; i < width; i++)
	 {
		cout << " _ _";
	 }
	 
	 int rows = 0;
	 for (int i = 0; i < width * height; i++)
	 {
		 if (i % width == 0) // Checks for beginning of the row
		 {
			 cout << endl;
			 rows++;
			 if (rows > 9)
			 {
				 cout << "" << rows << "  |"; // Y axis labels
			 }
			 else
			 {
				cout << " " << rows << "  |"; // Y axis labels
			 }
			 
		 }

		

		 if (board[i].getVisibility() == true)
		 {
			 if (board[i].getContainsMine() == true)
			 {
				 cout << "_X_";
				 cout << "|";
			 }
			 else if (board[i].getValue() == 0)
			 {
				 cout << "_-_";
				 cout << "|";
			 }
			 else
			 {
				 cout << "_" << board[i].getValue() << "_";
				 cout << "|";
			 }
		 }
		 else
		 {
			 cout << "_ _"; // Not visible cells should display as blank
			 cout << "|";
		 }
	 }

	 cout << endl;
 }

 vector<Cell> Director::checkAdjacentCells(Director director, vector<Cell> board, int chosenCell)
 {
	 if (board[chosenCell].getVisibility() == true) // Return immediately if it's already been checked
	 {
		 return board;
	 }

	 board[chosenCell].setVisibility(true);

	 int up = director.getWidth() * -1;
	 int down = director.getWidth();
	 int left = -1;
	 int right = 1;

	 vector<int> directions;

	 if (chosenCell + 1 > director.getWidth()) // Check up for edge
	 {
		 directions.push_back(chosenCell + up);
	 }

	 if (chosenCell < board.size() - director.getWidth()) // Check down for edge
	 {
		 directions.push_back(chosenCell + down);
	 }

	 if (chosenCell % width != 0) // Check left for edge
	 {
		 directions.push_back(chosenCell + left);
	 }

	 if (chosenCell % width != width - 1) // Check right for edge
	 {
		 directions.push_back(chosenCell + right);
	 }

	 if (directions.size() == 4) // If all previous are included, add all diagonals
	 {
		 directions.push_back(chosenCell + down + right);
		 directions.push_back(chosenCell + down + left);
		 directions.push_back(chosenCell + up + right);
		 directions.push_back(chosenCell + up + left);
	 }
	 else // Check for diagonals
	 {
		 if (chosenCell + 1 > director.getWidth() && chosenCell % width != 0) // Check up-left
		 {
			 directions.push_back(chosenCell + up + left);
		 }

		 if (chosenCell + 1 > director.getWidth() && chosenCell % width != width - 1) // Check up-right
		 {
			 directions.push_back(chosenCell + up + right);
		 }

		 if (chosenCell < board.size() - director.getWidth() && chosenCell % width != 0) // Check for down-left
		 {
			 directions.push_back(chosenCell + down + left);
		 }

		 if (chosenCell < board.size() - director.getWidth() && chosenCell % width != width - 1) // Check for down-right
		 {
			 directions.push_back(chosenCell + down + right);
		 }

	 }

	 for (int i = 0; i < directions.size(); i++) // Check each direction that we added to the directions vector, for mines
	 {
		 if (board[directions[i]].getContainsMine() == true)
		 {
			 board[chosenCell].setValue(board[chosenCell].getValue() + 1);
		 }
	 }

	 if (board[chosenCell].getValue() == 0) // Recursive
	 {
		 for (int i = 0; i < directions.size() - 1; i++) 
		 {
			 if (board[directions[i]].getValue() == 0)
			 {
				 board = checkAdjacentCells(director, board, directions[i]);
			 }
		 }
	 }

	 return board;
 }


// Clicking a cell begins a recursive function. First it checks if the clicked cell has a mine (value of -1).
// The function finds the value based on the number of adjacent mines, and displays it.
// If an adjacent cell value = 0, check that cell for adjacent mines (use recursion)