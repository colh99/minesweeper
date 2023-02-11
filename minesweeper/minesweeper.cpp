// minesweeper.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "director.h"

int main()
{
    std::cout << "MINESWEEPER" << endl;

    Director director = Director();
    
    vector<int> board = director.distributeMines(director.board, director.getWidth(), director.getHeight(), director.getMineCount());
    
    director.displayBoard(board, director.getWidth(), director.getHeight());

    

}
