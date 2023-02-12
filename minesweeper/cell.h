#pragma once
#include <string>
using namespace std;

class Cell {
private:
	bool containsMine {};
	bool visibility {};
	int value {};

public:
	// CONSTRUCTORS
	Cell();
	Cell(bool containsMine, bool isVisible, int value);

	// GETTERS
	bool getContainsMine();
	bool getVisibility();
	int getValue();

	// SETTERS
	void setVisibility(bool newSetting);
	void setContainsMine(bool newSetting);
	void setValue(int newValue);

	// DIRECTIONS
	/*
	Cell up(Cell cell);
	Cell down(Cell cell);
	Cell left(Cell cell);
	Cell right(Cell cell);
	*/
};