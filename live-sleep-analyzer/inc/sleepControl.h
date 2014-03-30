/*
 * sleepControl.h
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */

#ifndef SLEEPCONTROL_H_
#define SLEEPCONTROL_H_


#include <sleepEntry.h>
#include <sleepControl.h>
#include <vector>

class SleepControl {

public:
	SleepControl();
	~SleepControl();

	bool addSleepEntry(SleepEntry slpEntry);
	SleepEntry GetEntry(int);

	// Analysis
	int GetXAverage();
	int GetBiggestXSpike();
	double GetXSlopeBetween(int, int);
	double GetYSlopeBetween(int, int);
	double GetZSlopeBetween(int, int);

	// Debug
	void Print();


protected:
	std::vector<SleepEntry> sleepEntries;
};


#endif /* SLEEPCONTROL_H_ */
