/**
*	@file cTimer.h
*
*	@brief This file contains the cTimer class.
*/
#include "Agreon.h"

/** 
*	@brief Handles the time and manages the deltatime.
*
*	Source : cTimer
*/
class cTimer
{
	private:
		clock_t m_LastTime;
		clock_t m_CurrentTime; 
		clock_t m_DeltaTime; 
	public:
		/**
		*	Saves the start time of the program.
		*/
		cTimer();
		~cTimer();

		/**
		*	Updates the time and calculates the differnece since the last timestamp.
		*/
		void update();

		/**
		*	@returns the DeltaTime.
		*/
		int getDelta();
};