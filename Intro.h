#pragma once

#include "gamestate.h"

class Intro :
	public GameState
{
public:
	Intro(cGraphics *graphics, cInput *input, cSound *sound);
	~Intro();

	int		Update( double delta );
	void	Draw();
private:
	int		m_Counter;
};

