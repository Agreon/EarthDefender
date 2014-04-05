#pragma once

#include "gamestate.h"

class Prolog :
	public GameState
{
public:
	Prolog(cGraphics *graphics, cInput *input, cSound *sound);
	~Prolog();

	int Update( double delta );
	void Draw();

private:
	int	m_Counter;
};

