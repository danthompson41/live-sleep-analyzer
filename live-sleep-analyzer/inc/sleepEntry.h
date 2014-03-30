/*
 * sleepEntry.h
 *
 *  Created on: Mar 19, 2014
 *      Author: Dan
 */

#ifndef SLEEPENTRY_H_
#define SLEEPENTRY_H_


class SleepEntry {

public:
	SleepEntry(int id, int xVal, int yVal, int zVal);
	~SleepEntry();
	void Print();

	int getX();
	int getY();
	int getZ();
	int getID();

protected:
	unsigned int id;
	int xVal;
	int yVal;
	int zVal;

};



#endif /* SLEEPENTRY_H_ */
