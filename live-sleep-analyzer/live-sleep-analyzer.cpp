//============================================================================
// Name        : live-sleep-analyzer.cpp
// Author      : Enabling Entrepreneurs
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C, Ansi-style
//============================================================================

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <serial.h>
#include <string.h>
#include "sleepEntry.h"
#include "sleepControl.h"

// set to 1 to use counter IDs instead of inFile IDs
#define OVERRIDE_SLP_ID 1

// PROCSESED is used to output the above file. This fixes the negative signed integer ID issue
#define INPUT_FILE "..\\samples\\newsleepdata.txt"
#define PROCESSED_OUTPUT_FILE "..\\outdata\\processedSleepData.txt"
#define DERIV_OUTPUT_FILE "..\\outdata\\derivSleep.txt"

using namespace std;

int main (int argc, char* argv[])
{
	// welcome
	cout << "\n\n*** Live Sleep Analyzer ***\n";

	// command line args initial check
	 if (argc <= 1)
	{
		cout << "\n* FORMAT: arduino-simulator.exe [COMX]";
		return 1;
	}

	// Get Comport Number
	int iComport;
	if (sscanf (argv[1], "%i", &iComport) != 1)
	{
		cout << "ERROR: Comport must be an integer";
	}

	cout << "  COMPort: COM" << iComport << endl;

	// Set up Master Sleep Control
	SleepControl * sCTRL = new SleepControl();

	// Open output / inputs
	ifstream inFile(INPUT_FILE);
	ofstream outFile(PROCESSED_OUTPUT_FILE);
	ofstream oDerivFile(DERIV_OUTPUT_FILE);

	// Check input / output errors
	if (!inFile.is_open()) {
		cout << "Error, couldn't open input file!";
		return 0;
	}

	// Read in each line into 'line'
	string line;
	float i = 0;
	while (getline(inFile, line))
	{
		int iId, iX, iY, iZ;
		const char * cpLine = line.c_str();

		// attempt to scan line for correct string format
		if (sscanf(cpLine, "%i,%i,%i,%i", &iId, &iX, &iY, &iZ) != EOF)
		{
			// Optional ID override if the input file has signed integer ID corruption (set outside main)
			#if OVERRIDE_SLP_ID
			  iId = i;
			#endif

			// Create then add new sleep entry
			SleepEntry * sE = new SleepEntry(iId, iX, iY, iZ);
			sCTRL->addSleepEntry(*sE);
			outFile << iId << "," << iX << "," << iY << "," << iZ << "\n";
			oDerivFile << iId << "," << sCTRL->GetXSlopeBetween(iId, iId-1) << "," << sCTRL->GetYSlopeBetween(iId, iId-1) << "," << sCTRL->GetZSlopeBetween(iId, iId-1) << "\n";
			//  free(&sE);
			i++;
		}
		else {
			// Otherwise, ignore line
			cout << "Ignored the garbage: " << cpLine << endl;
		}
	}

	outFile.close();
	oDerivFile.close();
	cout << "Closed, done.";

	// Analysis
	// cout << "Average: " << sCTRL->GetXAverage() << endl;
	// sCTRL->GetBiggestXSpike(); // couts included in function for now

	return 1;
}

