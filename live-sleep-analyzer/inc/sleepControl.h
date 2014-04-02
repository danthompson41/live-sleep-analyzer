/*
 * sleepControl.h
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */

#ifndef SLEEPCONTROL_H_
#define SLEEPCONTROL_H_


#include <sleepEntry.h>
#include <sleepCycle.h>
#include <sleepControl.h>

#include <vector>
#include <string>

class SleepControl {

public:
	SleepControl();
	~SleepControl();

	bool addSleepEntry(SleepEntry slpEntry);
	SleepEntry GetEntry(int);
	void save(std::string);
	void saveDeriv(std::string);

	// Analysis
	void analyze();
	void analyze2();
	int GetXAverage();
	int GetBiggestXSpike();
	double GetXSlopeBetween(int, int);
	double GetYSlopeBetween(int, int);
	double GetZSlopeBetween(int, int);

	// Debug
	void Print();

protected:
	std::vector<SleepEntry> sleepEntries;
	std::vector<SleepCycle> sleepCycles;

};


#endif /* SLEEPCONTROL_H_ */
