/**
*	@file cLog.h
*
*	@brief This file contains the cLog class.
*/
#pragma once
#include "Agreon.h"

/**
*	@brief Writes a log to a file of your choice.
*/
class cLog
{
private:
	ofstream	m_Stream;
	string		m_FileName;
public:
	/**
	*	Sets the default log file : log.txt
	*/
	cLog();
	~cLog();
	
	/**
	*	Adds a Timestamp and writes something to the log file. 
	*
	*	@param text The text to write to the log file.
	*/
	void write( string text );
		
	/**
	*	Adds a Timestamp and writes something to the log file. 
	*
	*	@param text The text to write to the log file.
	*/
	void operator<<( string text );

	/**
	*	Sets the log file.
	*
	*	@param filename The name of the log file.
	*/
	void setFile( string filename );
};