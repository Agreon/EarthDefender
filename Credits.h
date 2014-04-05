#pragma once

#include "gamestate.h"

class Credits :
	public GameState
{
public:
	Credits(cGraphics *graphics, cInput *input, cSound *sound);
	~Credits();

	int Update( double delta );
	void Draw();
private:
	int m_ViewY;
	int m_State;
	int m_Counter;
};

