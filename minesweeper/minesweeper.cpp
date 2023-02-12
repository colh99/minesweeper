// minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "director.h"
#include "cell.h"

int main()
{
    std::cout << "          MINESWEEPER" << endl;

    Director director = Director();
   
    vector<Cell> board = director.distributeMines(director);
    
    director.displayBoard(board, director.getWidth(), director.getHeight());

    

}
