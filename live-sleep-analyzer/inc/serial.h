/*
 * serial.h
 *
 *  Created on: Mar 1, 2014
 *      Author: Dan
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#include <windows.h>


#define FC_DTRDSR       0x01
#define FC_RTSCTS       0x02
#define FC_XONXOFF      0x04
#define ASCII_BEL       0x07
#define ASCII_BS        0x08
#define ASCII_LF        0x0A
#define ASCII_CR        0x0D
#define ASCII_XON       0x11
#define ASCII_XOFF      0x13

class CSerial
{

public:
	CSerial();
	~CSerial();

	bool Open( int nPort = 2, int nBaud = 9600 );
	bool Close( void );

	int ReadData( void *, int );
	int SendData( const char *, int );
	int ReadDataWaiting( void );
	int ReadLine(char * );

	bool IsOpened( void ){ return( m_bOpened ); }

protected:
	bool WriteCommByte( unsigned char );

	HANDLE m_hIDComDev;
	OVERLAPPED m_OverlappedRead, m_OverlappedWrite;
	bool m_bOpened;

};


#endif /* SERIAL_H_ */
