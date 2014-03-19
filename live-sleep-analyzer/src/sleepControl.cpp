/*
 * sleepControl.cpp
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */

#include <iostream>
#include <cmath>
#include <sleepControl.h>
#include <sleepEntry.h>


SleepControl::SleepControl(void)
{
	this->entryCount = 0;
	return;
}

SleepControl::~SleepControl(void)
{
	return;
}

bool SleepControl::addSleepEntry(SleepEntry slpEntry)
{
	this->sleepEntries.push_back(slpEntry);
	this->entryCount++;
	return true;
}

void SleepControl::Print (void)
{
	std::cout << "Count: " << this->entryCount << std::endl;
}

int SleepControl::GetXAverage(void)
{
	float average = 0;
	for (int i = 0; i < this->entryCount; i++)
	{
		SleepEntry tmp = this->GetEntry(i);
		float xVal = tmp.xVal;
		average += xVal;
	}
	average = average / this->entryCount;
	return average;
}

SleepEntry SleepControl::GetEntry(int i)
{
	return this->sleepEntries[i];
}

int SleepControl::GetBiggestXSpike(void)
{
	int biggestDiff = 0;
	int biggestDiffIndex = 0;

	for (int i = 1; i < this->entryCount; i++)
	{
		SleepEntry tmp1 = this->GetEntry(i - 1);
		SleepEntry tmp2 = this->GetEntry(i);

		int diff = 0;
		diff = std::abs(tmp1.xVal - tmp2.xVal);
		if (diff > biggestDiff)
		{
			biggestDiff = diff;
			biggestDiffIndex = tmp1.id;
		}
	}

	std::cout << "The biggest Diff is " << biggestDiff << std::endl;
	std::cout << "It was observed at " << biggestDiffIndex << std::endl;

	return biggestDiff;

}
