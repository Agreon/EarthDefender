#pragma once

#include "centity.h"
#include "Ball.h"
#include "AgreonLibrary/cSound.h"

class Boss :
	public cEntity
{
private:
	Ball	*m_Ball;
	double	m_Speed;
	cSound  *m_Sound;
public:
	Boss(cGraphics *graphics, Ball *ball, cSound *sound, string texture, int posX, int posY, int width, int height);
	~Boss();

	void Update( double delta );
};

