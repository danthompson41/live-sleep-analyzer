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
#include <vector>
#include <string>
#include <numeric>
#include <sleepControl.h>
#include <sleepEntry.h>
#include <sleepCycle.h>


using namespace std;

bool inSleepCycle = true;

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

void SleepControl::saveDeriv(string filename)
{

	ofstream outFile(filename.c_str());

	for (unsigned int i = 1; i < this->sleepEntries.size(); i++)
	{
		SleepEntry sleepEntry = this->GetEntry(i);
		int iId = sleepEntry.getID();
		outFile << iId << "," << this->GetXSlopeBetween(iId, iId-1) << "," << this->GetYSlopeBetween(iId, iId-1) << "," << this->GetZSlopeBetween(iId, iId-1) << "\n";
	}

	outFile.close();
}

void SleepControl::analyze()
{
	int timeoutCheck = 0;
//	int
	for (int i = 0; i < this->sleepEntries.size(); i++)
	{
		// perform after the fact analysis
		SleepEntry sEntry = this->GetEntry(i);
		if (sEntry.getMovement() > 500 || sEntry.getX() > 300 || sEntry.getY() > 300 || sEntry.getZ() > 300)
		{

//			cout << "Spike at " << i << " at " << this->GetEntry(i).getMovement() << endl;
			printf("Spike at %i  -  Total: %i  -  XJump: %i  -  YJump: %i  -  ZJump: %i  \n", i, sEntry.getMovement(), sEntry.getX(), sEntry.getY(), sEntry.getZ() );

			timeoutCheck = 0;
		}
	}

	return;
}

void SleepControl::analyze2()
{
	ofstream outFile("..\\outdata\\sums.txt");
	std::vector<int> lastEntries;

	for (int i = 0; i < this->sleepEntries.size(); i++)
	{
		// perform after the fact analysis
		SleepEntry sEntry = this->GetEntry(i);

		if (lastEntries.size() >= 15)
		{
			lastEntries.pop_back();
		}
		lastEntries.insert(lastEntries.begin(), sEntry.getMovement());

		double sum = 0;
		sum = accumulate(lastEntries.begin(), lastEntries.end(), 0);

		outFile << sum << endl;
		if (inSleepCycle)
		{
			if (sum >= 3600)
			{
				cout << "SleepCycle Exited at " << i << "  Sum: " << sum << endl;
				inSleepCycle = false;
				// last15.clear();
			}
			continue;
		}
		if (!inSleepCycle)
		{
			if (sum <= 2500)
			{
				cout << "Entered New SleepCycle at " << i << " Sum :" << sum << endl;
				inSleepCycle = true;
			}
		}
	}
	outFile.close();
	return;
}
