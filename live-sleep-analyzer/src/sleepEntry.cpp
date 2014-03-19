/*
 * sleepEntry.cpp
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */
#include <iostream>
#include <sleepEntry.h>
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
