/*
 * sleepControl.cpp
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <sleepControl.h>
#include <sleepEntry.h>
#include <vector>
#include <string>

using namespace std;

SleepControl::SleepControl(void)
{
	// to make things simple, we automatically add 1 sleep entry of all zeros at the beginning.
	SleepEntry test(0,0,0,0);
	this->sleepEntries.push_back(test);
	return;
}

SleepControl::~SleepControl(void)
{
	return;
}

bool SleepControl::addSleepEntry(SleepEntry slpEntry)
{
	// extend the vector if we need to
	if (this->sleepEntries.capacity() < slpEntry.getID())
	{
		this->sleepEntries.reserve(slpEntry.getID());
	}
	this->sleepEntries.push_back(slpEntry);

	return true;
}

void SleepControl::Print (void)
{
	// used for debugging
}

SleepEntry SleepControl::GetEntry(int i)
{
	return this->sleepEntries[i];
}


/* Differential Functions */
double SleepControl::GetXSlopeBetween(int j, int k)
{
	// need to check that both exist. for now, just make sure they're within range
	if (j < 0 || k >= this->sleepEntries.size()) return 0;

	double retVal;

	int x1 = this->sleepEntries[j].getX();
	int x2 = this->sleepEntries[k].getX();

	retVal = ((x1 - x2) / (j - k));
	return retVal;
}

double SleepControl::GetYSlopeBetween(int j, int k)
{
	// need to check that both exist. for now, just make sure they're within range
	if (j < 0 || k >= this->sleepEntries.size()) return 0;

	double retVal;

	int x1 = this->sleepEntries[j].getY();
	int x2 = this->sleepEntries[k].getY();

	retVal = ((x1 - x2) / (j - k));
	return retVal;
}

double SleepControl::GetZSlopeBetween(int j, int k)
{
	// need to check that both exist. for now, just make sure they're within range
	if (j < 0 || k >= this->sleepEntries.size()) return 0;

	double retVal;

	int x1 = this->sleepEntries[j].getZ();
	int x2 = this->sleepEntries[k].getZ();

	retVal = ((x1 - x2) / (j - k));
	return retVal;
}


/* Sample Analysis Functions */
int SleepControl::GetXAverage(void)
{
	float average = 0;
	for (int i = 0; i < this->sleepEntries.size(); i++)
	{
		SleepEntry tmp = this->GetEntry(i);
		float xVal = tmp.getX();
		average += xVal;
	}
	average = average / this->sleepEntries.size();
	return average;
}

int SleepControl::GetBiggestXSpike(void)
{
	int biggestDiff = 0;
	int biggestDiffIndex = 0;

	for (int i = 1; i < this->sleepEntries.size(); i++)
	{
		SleepEntry tmp1 = this->GetEntry(i - 1);
		SleepEntry tmp2 = this->GetEntry(i);

		int diff = 0;
		diff = std::abs(tmp1.getX() - tmp2.getX());
		if (diff > biggestDiff)
		{
			biggestDiff = diff;
			biggestDiffIndex = tmp1.getID();
		}
	}

	std::cout << "The biggest Diff is " << biggestDiff << std::endl;
	std::cout << "It was observed at " << biggestDiffIndex << std::endl;

	return biggestDiff;
}

void SleepControl::save(string filename)
{

	ofstream outFile(filename.c_str());

	for (unsigned int i = 0; i < this->sleepEntries.size(); i++)
	{
		SleepEntry sleepEntry = this->GetEntry(i);
		int iId = sleepEntry.getID();
		int iX = sleepEntry.getX();
		int iY = sleepEntry.getY();
		int iZ = sleepEntry.getZ();
		outFile << iId << "," << iX << "," << iY << "," << iZ << "\n";
	}

	outFile.close();
}
