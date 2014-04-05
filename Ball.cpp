#include "Ball.h"


Ball::Ball(cGraphics *graphics, cAnimationManager *animManager, cSound *sound, Player* player, vector<Ufo*> *ufos, vector<PowerUp*> *powerups, string texture, int posX, int posY, int width, int height)
	: m_VelX(0), m_VelY(1), m_Speed(0.5), m_Super(false), m_Player(player), m_Ufos(ufos), m_PowerUps(powerups), m_AnimationManager(animManager), m_Sound(sound)
{
	m_Graphics = graphics;
	m_AnimationManager = animManager;
	m_Player = player;
	m_Ufos = ufos;
	m_Image = texture;
	m_Position = Vec2D( posX, posY );
	m_Width = width;
	m_Height = height;

	m_Rotation = 0;
	m_Destroyed = false;

	m_AnimationManager->createAnimation("bomb_animation","bomb_anim",-1,8,0,10,10,47,80);

}


Ball::~Ball()
{
}

void Ball::Update( double delta )
{
	m_Position += Vec2D( m_VelX * m_Speed * delta, m_VelY * m_Speed * delta );

	CheckCollision();

	if( m_VelX == 0 )
	{
		if( m_VelY < 0 ) m_Rotation = 180;
		if ( m_VelY > 0 ) m_Rotation = 0;
	}
	else if( m_VelX == 0.5 )
	{
		if( m_VelY < 0 ) m_Rotation = 225;
		if ( m_VelY > 0 ) m_Rotation = -45;
	}
	else if( m_VelX == -0.5 )
	{
		if( m_VelY < 0 ) m_Rotation = -225;
		if ( m_VelY > 0 ) m_Rotation = 45;
	}
	else if( m_VelX == 0.25 )
	{
		if( m_VelY < 0 ) m_Rotation = 203;
		if ( m_VelY > 0 ) m_Rotation = -22;
	}
	else if( m_VelX == -0.25 )
	{
		if( m_VelY < 0 ) m_Rotation = -203;
		if ( m_VelY > 0 ) m_Rotation = 22;
	}	

	m_AnimationManager->setPosition( "bomb_animation", m_Position.getX(), m_Position.getY() );
	m_AnimationManager->setRotation( "bomb_animation", m_Rotation );
}

void Ball::CheckCollision()
{
	if( m_Position.getY() > SCREEN_HEIGHT + m_Height ) 
	{
		m_Destroyed = true;
		m_Player->decLive();

		m_AnimationManager->createAnimation("explosion_animation_ground","explosion_anim",1,32,0,m_Position.getX()-80,SCREEN_HEIGHT-60,160,120);
		m_AnimationManager->createAnimation("explosion_animation_ground2","explosion_anim",1,20,0,100,SCREEN_HEIGHT-80,160,120);
		m_AnimationManager->createAnimation("explosion_animation_ground3","explosion_anim",1,20,0,600,SCREEN_HEIGHT-60,160,120);
		m_Sound->playSound("explosion2");
		return;
	}

	// Wall Collision
	if( m_Position.getX() > SCREEN_WIDTH - m_Width ||  m_Position.getX() < 0)
	{
		m_VelX = -m_VelX;
		if( m_Position.getX() > SCREEN_WIDTH - m_Width ) m_Position.setX(SCREEN_WIDTH - m_Width);
		if( m_Position.getX() < 0 ) m_Position.setX(0);
	}

	// Player Collision
	if( collision(m_Player) )
	{
		int diff =  m_Player->getX()+(m_Player->getWidth()/2) - m_Position.getX()-(m_Width/2);

		/*if( diff < 10 && diff > -10 && m_VelX == 0 )
		{
			m_VelX = 0;
		}
		else*/ if( diff > 0)
		{
			//if( diff > 30 )
			{
				m_VelX = -0.5;
			}
			//else
			{
			//	m_VelX = -0.25;
			}		
		}
		else
		{
			//if( diff < -30 )
			{
				m_VelX = 0.5;
			}
			//else
			{
			//	m_VelX = 0.25;
			}
		}

		// On Side Collision Fix
		if( m_Position.getY() + m_Height - 12 < m_Player->getY() )
		{
			m_VelY = -m_VelY;
		}
		m_Sound->playSound("bounce");
	}

	// Ufo Collision
	for( int j = 0; j < m_Ufos->size(); j++ )
	{
		if( m_VelY > 0 ) continue;
		if( collision( m_Ufos->at(j) ))
		{
			if( m_Super == false )
			{
				if( m_Position.getY() < m_Ufos->at(j)->getY() + m_Ufos->at(j)->getHeight() -10 )
				{
					m_VelX = -m_VelX;
				}
				else
				{
					m_VelY = -m_VelY;
				}
			}

			m_AnimationManager->createAnimation("explosion_animation"+itos(j),"explosion_anim",1,32,0,m_Ufos->at(j)->getX(),m_Ufos->at(j)->getY(),160,120);
		
			int random = rand() % 10;
			if( random == 5 )
			{
				int rand2 = rand() % 4;
				m_PowerUps->push_back( new PowerUp( m_Graphics, rand2, m_Ufos->at(j)->getX() + 8 , m_Ufos->at(j)->getY() + m_Ufos->at(j)->getHeight() ) );
			}
			m_Player->incPoints(100);
			m_Sound->playSound("explosion1");

			m_Ufos->erase( m_Ufos->begin() + j);
			break;
		}
	}
}

void Ball::Draw()
{
	m_AnimationManager->show("bomb_animation");
}

void Ball::Reset()
{
	int tmp = rand() % (SCREEN_WIDTH - m_Width - 10) + 10;  
	m_Position = Vec2D( tmp, 0 );
	m_Destroyed = false;
	m_VelX = 0;
	m_VelY = 1;
	m_Speed = 0.5;
	m_Rotation = 0;
}

void Ball::setVelX( double velX )
{
	m_VelX = velX;
}

void Ball::setVelY( double velY )
{
	m_VelY = velY;
}

double Ball::getVelX()
{
	return m_VelX;
}

double Ball::getVelY()
{
	return m_VelY;
}

bool Ball::isSuper()
{
	return m_Super;
}

void Ball::setDestroyed( bool b )
{
	if( b ) m_AnimationManager->setPosition("bomb_animation",-100,0);

	m_Destroyed = b;
}

void Ball::setSuper( bool b )
{
	m_Super = b;
}