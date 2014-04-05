/**
*	@file cInput.h
*
*	@brief This file contains the cInput class.
*/
#pragma once

#include "Agreon.h"

/**
*	@brief Handles the Input.
*	
*	
*/
class cInput
{
private:
	SDL_Event m_Evt;

	int m_MouseX;
	int m_MouseY;

	bool m_Keys[ 525 ];
	bool m_LeftMouse;
	bool m_RightMouse;
public:
	cInput();
	~cInput();

	/**
	*	Pulls the Input from the eventlist.
	*/
	bool handleInput();

	/**
	*	Checks if a key is pressed.
	*
	*	@param key	A key in SDL format.
	*	@returns if key is pressed.
	*/
	bool isKeyPressed( SDLKey key );

	/**
	*	@returns if the left mouse is pressed.
	*/
	bool leftMousePressed();
	
	/**
	*	@returns if the right mouse is pressed.
	*/
	bool rightMousePressed();

	/**
	*	@returns the x coordinate of the mouse.
	*/
	int getMousePositionX();

	/**
	*	@returns the y coordinate of the mouse.
	*/
	int getMousePositionY();

};

