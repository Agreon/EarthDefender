#include "Player.h"


Player::Player( cGraphics *graphics, cAnimationManager *animationManager, cInput *input, cSound *sound, vector<Bullet*> *bullets, string texture, int posX, int posY, int width, int height, double speed )
	: m_Animations(animationManager),
	  m_Input( input ),
	  m_Sound(sound), 
	  m_Speed( 0.5 ), 
	  m_Lives( 3 ), 
	  m_Points( 0 ), 
	  m_Bullets( bullets ), 
	  m_PlayBurner( false ),
	  m_MusicChannel( 0 )
{
	m_Graphics = graphics;
	m_Image = texture;
	m_Position = Vec2D(posX,posY);
	m_Height = height;
	m_Width = width;

	m_Animations->createAnimation("fire_anim","fire_anim",-1,16,90,0,0,15,25);
	m_Animations->deactivate("fire_anim");
	Mix_Chunk *tmpChunk = m_Sound->getChunk("burner");
	m_MusicChannel = Mix_PlayChannel(-1,tmpChunk,-1);
}


Player::~Player()
{
}

void Player::Update( double delta )
{
	if(m_Input->isKeyPressed(SDLK_LEFT))
	{
		m_Position += Vec2D( -1* m_Speed * delta , 0 );
		m_Animations->activate("fire_anim");
		m_Animations->setRotation("fire_anim",-90);
		m_Animations->setPosition("fire_anim",m_Position.getX()+m_Width-6,m_Position.getY()+12);
		m_PlayBurner = true;
	}
	else if(m_Input->isKeyPressed(SDLK_RIGHT))
	{
		m_Position += Vec2D( m_Speed * delta , 0 );
		m_Animations->activate("fire_anim");
		m_Animations->setRotation("fire_anim",90);
		m_Animations->setPosition("fire_anim",m_Position.getX()-15+6,m_Position.getY()+12);
		m_PlayBurner = true;
	}
	else
	{
		m_Animations->deactivate("fire_anim");
		m_PlayBurner = false;
	}

	if( m_PlayBurner ) Mix_Volume(m_MusicChannel,30);
	else Mix_Volume(m_MusicChannel,0);

	if( m_Lives< 2 ) 
	{
		m_Animations->activate("fire_anim2");
		m_Animations->activate("fire_anim2.2");
		m_Animations->activate("fire_anim2.3");
	}



	if( m_Position.getX() < 0 ) m_Position.setX(0);
	if( m_Position.getX() > SCREEN_WIDTH - m_Width ) m_Position.setX( SCREEN_WIDTH - m_Width ); 

	if( m_Position.getY() < SCREEN_HEIGHT / 2 ) m_Position.setY( 400 ); 
	if( m_Position.getY() > SCREEN_HEIGHT-120 - m_Height ) m_Position.setY( SCREEN_HEIGHT-120 - m_Height ); 

	for( int i = 0; i < m_Bullets->size(); i++ )
	{
		if( collision( m_Bullets->at(i)) )
		{
			m_Bullets->erase( m_Bullets->begin() + i );
			m_Points -= 200;
			break;
		}
	}
}

void Player::Draw()
{
	m_Graphics->drawTexture(m_Image, m_Position.getX(), m_Position.getY());
}

int Player::getLives()
{
	return m_Lives;
}

int Player::getPoints()
{
	return m_Points;
}

void Player::setLives( int l )
{
	m_Lives = l;
}

void Player::incLive()
{
	m_Lives++;
}

void Player::decLive()
{
	m_Lives--;
}

void Player::setPoints( int p )
{
	m_Points = p;
}

void Player::incPoints( int p )
{
	m_Points += p;
}