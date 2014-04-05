#pragma once

#include "cLog.h"

enum
{
	STATE_NULL,
	STATE_EXIT,
	STATE_INTRO,
	STATE_MENU,
	STATE_CREDITS,
	STATE_PROLOG,
	STATE_GAME,
	STATE_POINTS
};

extern const int	SCREEN_WIDTH;
extern const int	SCREEN_HEIGHT;
extern string		gameMode;		
extern bool			survived;
extern int			player_points;

extern cLog* Log;

extern string itos( int number );

extern bool collision( int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2 );