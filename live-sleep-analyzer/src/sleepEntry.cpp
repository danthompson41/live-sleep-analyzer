/*
 * sleepEntry.cpp
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */
#include <iostream>
#include <cmath>
#include <sleepEntry.h>

using namespace std;

SleepEntry::SleepEntry(int id, int xVal, int yVal, int zVal)
{
	this->id   = id;
	this->xVal = xVal;
	this->yVal = yVal;
	this->zVal = zVal;
}

SleepEntry::~SleepEntry(void)
{
	return;
}


void SleepEntry::Print(void)
{
	std::cout << "ID:"  << this->id;
	std::cout << "  X:" << this->xVal;
	std::cout << "  Y:" << this->yVal;
	std::cout << "  Z:" << this->zVal << std::endl;
}

int SleepEntry::getX()
{
	return this->xVal;
}

int SleepEntry::getY()
{
	return this->yVal;
}

int SleepEntry::getZ()
{
	return this->zVal;
}

unsigned int SleepEntry::getID()
{
	return this->id;
}

int SleepEntry::getMovement()
{
	int retVal;
	retVal = abs(this->getX()) + abs(this->getY()) + abs(this->getZ());
	return retVal;

}
