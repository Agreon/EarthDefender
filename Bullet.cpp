#include "Bullet.h"


Bullet::Bullet(cGraphics *graphics, string texture, int posX, int posY, int width, int height)
	: m_VelX(0), m_VelY(1), m_Speed(0.5)
{
	m_Graphics = graphics;
	m_Image = texture;
	m_Position = Vec2D( posX, posY );
	m_Width = width;
	m_Height = height;
	
	m_Rotation = 0;
	m_Destroyed = false;
}


Bullet::~Bullet()
{
}

void Bullet::Update( double delta )
{
	m_Position += Vec2D( m_VelX * m_Speed * delta, m_VelY * m_Speed * delta );
}

void Bullet::Draw()
{
	m_Graphics->drawTexture( m_Image, m_Position.getX(), m_Position.getY(), m_Rotation );
}

void Bullet::setVelX( double velX )
{
	m_VelX = velX;
}

void Bullet::setVelY( double velY )
{
	m_VelY = velY;
}

double Bullet::getVelX()
{
	return m_VelX;
}

double Bullet::getVelY()
{
	return m_VelY;
}