/**
*	@file cInput.cpp
*
*	@brief This file contains the cInput functions.
*/
#include "cInput.h"

cInput::cInput()
{
	m_MouseX = 0;
	m_MouseY = 0;

	for( int i = 0; i < 525; i++ )
	{
		m_Keys[ i ] = false;
	}

	m_LeftMouse	= false;
	m_RightMouse = false;
}


cInput::~cInput()
{
}

bool cInput::handleInput()
{
	while (SDL_PollEvent( &m_Evt ) )
	{
		switch( m_Evt.type )
		{
		case SDL_QUIT:
			return true;
			break;
		case SDL_KEYDOWN:
			m_Keys[ m_Evt.key.keysym.sym ] = true;
			break;
		case SDL_KEYUP:
			m_Keys[ m_Evt.key.keysym.sym ] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			if( m_Evt.button.button == SDL_BUTTON_LEFT )
			{
				m_LeftMouse = true;
			}
			else
			{
				m_RightMouse = true;
			}
			m_MouseX = m_Evt.button.x;
			m_MouseY = m_Evt.button.y;
			break;
		case SDL_MOUSEBUTTONUP:
			if( m_Evt.button.button == SDL_BUTTON_LEFT )
			{
				m_LeftMouse = false;
			}
			else
			{
				m_RightMouse = false;
			}
			m_MouseX = m_Evt.button.x;
			m_MouseY = m_Evt.button.y;
			break;
		case SDL_MOUSEMOTION:
			m_MouseX = m_Evt.motion.x;
			m_MouseY = m_Evt.motion.y;
			break;
		}
	}
	return false;
}

bool cInput::isKeyPressed( SDLKey key )
{
	return m_Keys[ key ];
}


bool cInput::leftMousePressed()
{
	return m_LeftMouse;
}


bool cInput::rightMousePressed()
{
	return m_RightMouse;
}


int cInput::getMousePositionX()
{
	return m_MouseX;
}


int cInput::getMousePositionY()
{
	return m_MouseY;
}