/*
 * sleepCycle.cpp
 *
 *  Created on: Apr 1, 2014
 *      Author: Dan
 */

#include "sleepCycle.h"

SleepCycle::SleepCycle(float fStart, float fEnd)
{
	this->startId = fStart;
	this->endId = fEnd;
	this->length = fStart - fEnd;
}

SleepCycle::~SleepCycle()
{
	return;
}



