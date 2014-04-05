#include "game.h"

Game::Game(cGraphics *graphics, cAnimationManager *animationManager, cInput  *input, cSound *sound) 
	: m_SwitchState(false), m_UfosActive(false), m_Paused(false), m_TimeBuffer(0), m_Counter(0), m_StartCounter(0), m_NearDeath(false), m_BombDefends(0)
{
	m_Graphics			= graphics;
	m_AnimationManager	= animationManager;
	m_Input				= input;
	m_Sound				= sound;

	Init();
}

Game::~Game()
{
	m_AnimationManager->stop("fire_anim");

	player_points = m_Player->getPoints();

	delete m_Player;
	m_Player = 0;

	delete m_Ufos;
	m_Ufos = 0;

	delete m_Bullets;
	m_Bullets = 0;
}


bool Game::Init()
{
	m_Ufos = new vector<Ufo*>;
	m_Bullets = new vector<Bullet*>;
	m_PowerUps = new vector<PowerUp*>;

	m_Player = new Player(m_Graphics,m_AnimationManager,m_Input,m_Sound,m_Bullets,"player",(SCREEN_WIDTH-128)/2,620,128,50,1);

	m_Ball = new Ball(m_Graphics, m_AnimationManager, m_Sound, m_Player, m_Ufos, m_PowerUps, "ball", SCREEN_WIDTH/2, 0, 47, 80);
	m_Ball->setDestroyed(true);

	m_Boss = new Boss(m_Graphics,m_Ball,m_Sound,"boss",(SCREEN_WIDTH-128)/2,20,128,55);

	m_AnimationManager->createAnimation("fire_anim2","fire_anim2",-1,10,0,100,SCREEN_HEIGHT-100,128,128);
	m_AnimationManager->createAnimation("fire_anim2.2","fire_anim2",-1,10,0,300,SCREEN_HEIGHT-100,128,128);
	m_AnimationManager->createAnimation("fire_anim2.3","fire_anim2",-1,10,0,555,SCREEN_HEIGHT-100,128,128);
	m_AnimationManager->deactivate("fire_anim2");
	m_AnimationManager->deactivate("fire_anim2.2");
	m_AnimationManager->deactivate("fire_anim2.3");

	m_Sound->setVolume("bounce",60);
	m_Sound->setVolume("explosion1",80);
	m_Sound->setVolume("explosion2",80);
	m_Sound->setVolume("fire_laser",70);
	m_Sound->setVolume("get_powerup",90);
	m_Sound->setVolume("ball_shot",70);

	return true;
}

int Game::Update( double delta )
{
	if( m_Input->isKeyPressed(SDLK_ESCAPE) )
	{
		return STATE_MENU;
	}
	
	if( m_TimeBuffer > 0 ) m_TimeBuffer--;

	if( m_Input->isKeyPressed(SDLK_p) && m_TimeBuffer == 0 )
	{
		if( m_Paused )
		{
			m_Paused = false;
			m_Sound->setVolume(100);
		}
		else 
		{
			m_Paused = true;
			m_Sound->setVolume(0);
		}
		m_TimeBuffer = 10;
	}

	if( m_Paused ) return STATE_NULL;

	m_AnimationManager->updateAll();

	m_Player->Update( delta );
	for( auto& bullet: (*m_Bullets) ) bullet->Update( delta );
	for( auto& powerup: (*m_PowerUps) ) powerup->Update( delta );

	//////////////////////
	//	PowerUp Update	//
	//////////////////////
	for( int i = 0; i < m_PowerUps->size(); i++ )
	{
		if( m_Player->collision( m_PowerUps->at(i)) )
		{
			switch ( m_PowerUps->at(i)->getType() )
			{
			case POWERUP_HEALTH:
				m_Player->incLive();
				break;
			case POWERUP_EXPAND:
				m_Player->setWidth(192);
				m_Player->setImage("player_expanded");
				break;
			case POWERUP_SUPERBULLET:
				m_Ball->setSuper(true);
				break;
			case POWERUP_POINTS:
				m_Player->incPoints(1000);
				break;
			}

			m_PowerUps->erase( m_PowerUps->begin() + i );
			m_Sound->playSound("get_powerup");
			break;
		}
	}

	if( m_StartCounter < 50 )
	{
		m_StartCounter++;
		return STATE_NULL;
	}

	if(m_SwitchState)
	{
		SendUfos();
		return STATE_NULL;
	}

	m_Boss->Update( delta );

	
	if( m_Player->getLives() == 0 )
	{
		survived = false;
		return STATE_POINTS;
	}

	//////////////////////
	//	Ufo Update		//
	//////////////////////

	for( int i = 0; i < m_Ufos->size(); i++ )
	{
		m_Ufos->at(i)->Update( delta );

		// Check if Ufos are below
		bool cont = false;
		for( int j = 0; j < m_Ufos->size(); j++)
		{
			if( j == i ) continue;
			if( m_Ufos->at(j)->isDestroyed() ) continue;
			if(collision(m_Ufos->at(i)->getX(), m_Ufos->at(i)->getY() + 64 , m_Ufos->at(i)->getHeight(), m_Ufos->at(i)->getWidth(),
				m_Ufos->at(j)->getX(), m_Ufos->at(j)->getY(), m_Ufos->at(j)->getWidth(), m_Ufos->at(j)->getHeight() ))
			{
				cont = true;
				break;
			}
		}
		if( cont ) continue;

		// If not, maybe shoot a bullet

		int r = rand() % 1000 + 1;

		if( r == 7 )
		{
			m_Bullets->push_back( new Bullet(m_Graphics, "bullet", m_Ufos->at(i)->getX()+15, m_Ufos->at(i)->getY() + m_Ufos->at(i)->getHeight(), 11, 28 ));
			m_Sound->playSound("fire_laser");
		}
	}

	/// Ufo-Wall Collision
	for( auto& ufo : (*m_Ufos) )
	{
		if( ufo->getX() <= 0 )
		{
			ufo->m_Direction = 'r';
			break;
		}
		if( ufo->getX() + ufo->getWidth() >= SCREEN_WIDTH )
		{
			ufo->m_Direction = 'l';
			break;
		}
	}
	
	//////////////////////
	//	Ball Update		//
	//////////////////////
	m_Ball->Update( delta );

	if( m_Ball->getY() < 0 )
	{
		m_SwitchState = true;
		m_UfosActive = false;
		m_Ball->setDestroyed(true);
		m_Ball->setSuper(false);
		m_BombDefends++;
		m_Player->incPoints(500);

		m_Player->setWidth(128);
		m_Player->setImage("player");

		if( m_BombDefends == 3 && gameMode == "Story" )
		{
			survived = true;
			return STATE_POINTS;
		}
	}

	return STATE_NULL;
}

void Game::SendUfos()
{
	if( m_Ufos->size() == 0 )
	{
		for( int i = 0; i < 6; i++ )
		{
			for( int j = 0; j < 2; j++ )
			{
				m_Ufos->push_back( new Ufo(m_Graphics, "ufo", 50 + (i*120), -320 + ( j*120), 81, 108 ));
			}
		}
		m_UfosActive = true;
	}
	else if( m_UfosActive == false )
	{
		if( m_Ufos->at(0)->getY() > -240 )
		{
			for( auto& ufo: (*m_Ufos) ) ufo->setY( ufo->getY() - 4 );
			return;
		}
		m_Ufos->clear();
		return;
	}

	if( m_Ufos->at(0)->getY() < 90 )
	{
		for( auto& ufo: (*m_Ufos) ) ufo->setY( ufo->getY() + 3 );
	}

	if( m_Boss->getX() < SCREEN_WIDTH/2 - m_Boss->getWidth()/2 ) m_Boss->setX( m_Boss->getX() + 2 );
	if( m_Boss->getX() > SCREEN_WIDTH/2 - m_Boss->getWidth()/2 ) m_Boss->setX( m_Boss->getX() - 2 );

	if( SCREEN_WIDTH/2 - m_Boss->getWidth()/2 - m_Boss->getX() > 5  ||
		SCREEN_WIDTH/2 - m_Boss->getWidth()/2 - m_Boss->getX() < -5 ||
		m_Ufos->at(0)->getY() < 90 )
	{
		return;
	}
	if( m_Counter < 20 )
	{
		m_Counter++;
		return;
	}

	m_SwitchState = false;
	m_Boss->Update(0);
}

void Game::Draw()
{
	// Background
	glBegin(GL_QUADS);
		glColor4f(0,0,0,0.4);
		glVertex2f(0,0);
		glColor4f(0,0,0.3,0.4);
		glVertex2f(0,SCREEN_HEIGHT);
		glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT);
		glColor4f(0,0,0,0.4);
		glVertex2f(SCREEN_WIDTH,0);
	glEnd();
	glColor4f(1,1,1,1);

	m_Graphics->drawTexture("city",0,700);

	m_Player->Draw();
	m_Boss->draw();

	for( auto& ufo : (*m_Ufos) ) ufo->draw();
	for( auto& bullet : (*m_Bullets) ) bullet->Draw();
	for( auto& powerup : (*m_PowerUps) ) powerup->Draw();

	if( m_Ball->isDestroyed() == false ) m_Ball->Draw();

	string defends = "Level: "+itos(m_BombDefends);
	m_Graphics->drawText(defends.c_str(),16,36);
	string lives = "Lives: "+itos(m_Player->getLives());
	m_Graphics->drawText(lives.c_str(),16,66);
	string points = "Points: "+itos(m_Player->getPoints());
	m_Graphics->drawText(points.c_str(),16,96);

	m_Graphics->drawText(gameMode.c_str(),SCREEN_WIDTH-100,36);

	m_AnimationManager->showAll();

	if( m_Paused ) m_Graphics->drawText("Paused", 360, 400 );
}
