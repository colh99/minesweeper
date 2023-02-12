// minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "director.h"
#include "cell.h"
using namespace std;


int getUserInput(Director director);


int main()
{
    cout << "          MINESWEEPER" << endl;

    // Set up the game
    Director director = Director();

    vector<Cell> board = director.distributeMines(director);
    director.displayBoard(board, director.getWidth(), director.getHeight());

    // Main Game loop
    bool playingGame = true;
    while (playingGame == true)
    {
        int chosenCell = getUserInput(director);

        // Check for game over
        if (board[chosenCell].getContainsMine() == true)
        {
            for (int i = 0; i < board.size(); i++)
            {
                board = director.checkAdjacentCells(director, board, i);
            }
 
            cout << "          !!!GAME OVER!!!" << endl;
            playingGame = false;
        }
        else // Implement turn
        {
            board = director.checkAdjacentCells(director, board, chosenCell);

            // Check for win
            int cellsVisible = 0;
            for (int i = 0; i < board.size(); i++) 
            {
                if (board[i].getVisibility() == true)
                {
                    cellsVisible++;
                }
            }

            if (cellsVisible == board.size() - director.getMineCount())
            {
                cout << "          !!!YOU WON!!!" << endl;
                playingGame = false;
            }
        }


        director.displayBoard(board, director.getWidth(), director.getHeight());
    }
    

}


int getUserInput(Director director)
{ 
    int xCoord = 0;
    int yCoord = 0;
    bool validInput = false;

    while (validInput == false) 
    {
        cout << "Enter the X coordinate: ";
        cin >> xCoord;
        cout << "Enter the Y coordinate: ";
        cin >> yCoord;

        cout << endl;

        if (1 > xCoord or xCoord > director.getWidth() or 1 > yCoord or yCoord > director.getHeight()) // Both coordinates must be within bounds
        {
            validInput = false;
            cout << "Invalid input! Try again." << endl;
        }
        else // exit condition
        {
            validInput = true; 
        }
        
    }

    int chosenCell = xCoord + (yCoord * director.getWidth() - director.getWidth()) - 1; // Convert the input into an index value for the board vector

    return chosenCell;
}
