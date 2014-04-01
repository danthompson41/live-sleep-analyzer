/*
 * sleepCycle.h
 *
 *  Created on: Apr 1, 2014
 *      Author: Dan
 */

#ifndef SLEEPCYCLE_H_
#define SLEEPCYCLE_H_

class SleepCycle {

public:
	SleepCycle(float, float);
	~SleepCycle();


protected:
	float startId;
	float endId;
	float length;
};



#endif /* SLEEPCYCLE_H_ */
