#pragma once
#include <string>
using namespace std;

class Cell {
private:
	bool containsMine {};
	bool visibility {};
	int value {};

public:
	// Constructors
	Cell();
	Cell(bool containsMine, bool isVisible, int value);

	bool getContainsMine();
	bool getVisibility();
	int getValue();

	void setVisibility(bool newSetting);
	void setContainsMine(bool newSetting);
	void setValue(int newValue);
};