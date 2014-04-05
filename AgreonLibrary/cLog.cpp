/**
*	@file cLog.cpp
*
*	@brief This file contains the cLog functions.
*/
#include "cLog.h"

cLog::cLog()
{
	m_FileName = "log.txt";
	m_Stream.open( m_FileName );
	m_Stream.close();
}

cLog::~cLog()
{
}

void cLog::write( string text )
{
	m_Stream.open( m_FileName, ios::out | ios::app );
	
	if( !m_Stream.is_open() )
	{
		return;
	}	
		
	time_t t = time( 0 );  
	struct tm * now = localtime( & t );
	m_Stream << "[ ";
	
	if( now->tm_hour < 10 )
	{
		m_Stream << "0";
	}
	m_Stream << now->tm_hour << ":";

	if( now->tm_min < 10 )
	{
		m_Stream << "0";
	}
	m_Stream << now->tm_min << ":";
	
	if( now->tm_sec < 10 )
	{
		m_Stream << "0";
	}
	m_Stream << now->tm_sec << " ] ";

	m_Stream << text << endl;
	m_Stream.close();
}

void cLog::operator<<( string text )
{
	write( text );
}

void cLog::setFile( string filename )
{
	m_FileName = filename;
	m_Stream.open( m_FileName );
	m_Stream.close();
}