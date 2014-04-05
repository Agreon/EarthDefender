#include "Boss.h"


Boss::Boss(cGraphics *graphics, Ball* ball, cSound *sound, string texture, int posX, int posY, int width, int height)
	: m_Ball(ball), m_Sound(sound), m_Speed(0.3)
{
	m_Graphics = graphics;
	m_Image = texture;
	m_Position = Vec2D( posX, posY );
	m_Width = width;
	m_Height = height;
}

Boss::~Boss()
{
}

void Boss::Update( double delta )
{
	if( m_Ball->isDestroyed() )
	{
		m_Ball->Reset();
		m_Ball->setPosition( Vec2D( m_Position.getX() + (m_Width / 2) - (m_Ball->getWidth() / 2), 64 ));
		m_Sound->playSound("ball_shot");
		return;
	}

	if( m_Ball->getVelY() > 0 ) return;

	if( m_Ball->getX() - m_Position.getX() > 20 || m_Ball->getX() - m_Position.getX() < -20 )
	{
		if( m_Ball->getX() > m_Position.getX() )
		{
			m_Position += Vec2D( m_Speed * delta, 0);
		}
		else
		{
			m_Position -= Vec2D( m_Speed * delta, 0);
		}
	}

	if( m_Position.getX() < 0 ) m_Position.setX(0);
	if( m_Position.getX() > SCREEN_WIDTH - m_Width ) m_Position.setX( SCREEN_WIDTH - m_Width );

	if( collision(m_Ball) )
	{
		if( m_Ball->getVelX() == 0 )
		{
			if( m_Position.getX() - m_Ball->getX() + ( m_Ball->getWidth()/2)> 0)
			{
				m_Ball->setVelX( -0.5 );
			}
			else
			{
				m_Ball->setVelX( 0.5 );
			}
		}
		m_Ball->setVelY( -m_Ball->getVelY() );
		m_Sound->playSound("bounce");
	}
}