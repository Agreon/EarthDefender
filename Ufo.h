#pragma once

#include "centity.h"

class Ufo :
	public cEntity
{
public:
	Ufo(cGraphics *graphics, string texture, int posX, int posY, int width, int height);
	~Ufo();

	void Update( double delta );

	static char m_Direction;
};

