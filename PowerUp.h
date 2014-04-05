#pragma once

#include "centity.h"

enum Type
{
	POWERUP_HEALTH,
	POWERUP_EXPAND,
	POWERUP_SUPERBULLET,
	POWERUP_POINTS
};

class PowerUp :
	public cEntity
{
public:
	PowerUp( cGraphics *graphics, int type, int posX, int posY );
	~PowerUp();

	void Update( double delta );
	void Draw();

	int getType();

private:
	int m_Type;
	double m_Vel;
};

