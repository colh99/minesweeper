#include "cell.h"

Cell::Cell()
{
}

Cell::Cell(bool contains_mine, bool valueIsVisible, int value)
{
	containsMine = contains_mine;
	visibility = valueIsVisible;
	this->value = value;
}

// GETTERS
bool Cell::getContainsMine()
{
	return containsMine;
}

bool Cell::getVisibility()
{
	return visibility;
}

int Cell::getValue()
{
	return value;
}


// SETTERS
void Cell::setVisibility(bool newSetting)
{
	visibility = newSetting;
}

void Cell::setContainsMine(bool newSetting)
{
	containsMine = newSetting;
}

void Cell::setValue(int newValue)
{
	value = newValue;
}