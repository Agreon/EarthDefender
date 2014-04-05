#pragma once

#include "centity.h"

class Bullet :
	public cEntity
{
private:
	double m_VelX;
	double m_VelY;
	double m_Speed;
public:
	Bullet(cGraphics *graphics, string texture, int posX, int posY, int width, int height);
	~Bullet();

	void Update( double delta );
	void Draw();

	void setVelX( double velX );
	void setVelY( double velY );

	double getVelX();
	double getVelY();
};

