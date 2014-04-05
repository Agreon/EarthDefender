#include "globals.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;
string		gameMode	= "Story";
bool		survived	= false;
int			player_points = 0;

cLog* Log = new cLog();

string itos( int number )
{
   stringstream ss;
   ss << number;
   return ss.str();
}

bool collision( int x1, int y1, int w1, int h1, int x2, int y2, int w2, int h2 )
{
	if( y1 >= y2 + h2) return false;
	if( x1 >= x2 + w2) return false;
	if( y1 + h1 <=  y2) return false;
	if( x1 + w1 <= x2) return false;

	return true;
}