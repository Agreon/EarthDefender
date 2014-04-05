#include "PowerUp.h"


PowerUp::PowerUp( cGraphics *graphics, int type, int posX, int posY )
	: m_Type(type), m_Vel(3)
{
	m_Graphics	= graphics;
	m_Position	= Vec2D( posX, posY );
	m_Width		= 48;
	m_Height	= 48;
	switch( type )
	{
	case POWERUP_HEALTH:
		m_Image = "health_up";
		break;
	case POWERUP_EXPAND:
		m_Image = "expand";
		break;
	case POWERUP_SUPERBULLET:
		m_Image = "super_bullet";
		break;
	case POWERUP_POINTS:
		m_Image = "points";
		break;
	}

}


PowerUp::~PowerUp()
{
}

void PowerUp::Update( double delta )
{
	m_Position.setY( m_Position.getY() + m_Vel );
}

void PowerUp::Draw()
{
	m_Graphics->drawTexture(m_Image,m_Position.getX(), m_Position.getY() );
}

int PowerUp::getType()
{
	return m_Type;
}