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

int main (int argc, char* argv[])
{
	// welcome
	std::cout << "\n\n*** Live Sleep Analyzer ***\n";

	// command line args initial check
	 if (argc <= 1)
	{
		std::cout << "\n* FORMAT: arduino-simulator.exe [COMX]";
		return 1;
	}

	// Get Comport Number
	int iComport;
	if (sscanf (argv[1], "%i", &iComport) != 1)
	{
		std::cout << "ERROR: Comport must be an integer";
	}

	std::cout << "  COMPort: COM" << iComport << std::endl;

	// Set up Master Sleep Control
	SleepControl * sCTRL = new SleepControl();

	// Open up the file
	std::ifstream inputFile;
	inputFile.open("C:\\Users\\Dan\\git\\arduino-simulator\\sleepdata.txt");
	if (!inputFile.is_open()) {
		std::cout << "Error, couldn't open file!";
		return 0;
	}


	// Read Each Line
	std::string line;
	while (std::getline(inputFile, line))
	{
		int iId, iX, iY, iZ;
		const char * cpLine = line.c_str();
		if (std::sscanf(cpLine, "%i,%i,%i,%i", &iId, &iX, &iY, &iZ) != EOF)
		{
			SleepEntry * sE = new SleepEntry(iId, iX, iY, iZ);
			sCTRL->addSleepEntry(*sE);
		}
		else {
			std::cout << "Ignored the garbage: " << cpLine << std::endl;
		}
		free(&cpLine); // is this necessary?
	}


	// Analysis
	std::cout << "Average: " << sCTRL->GetXAverage() << std::endl;

	sCTRL->GetBiggestXSpike();




	/*
	CSerial serial;
	if (!serial.Open(iComport,9600))
	{
		std::cout << "ERROR: Could not open serial";
		return 0;
	}

	char * line;

	while (serial.ReadLine(line))
	{
		std::cout<<line;
	}

	*/

	return 1;


}

