#include "Menu.h"


Menu::Menu(cGraphics *graphics, cInput *input, cSound *sound) 
	: m_MenuPoint(0), m_SmallMenuPoint(0), m_TimeBuffer(5), m_StartDirect(false), m_ChooseGameMode(false)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;

	m_Graphics->setFont("astron");
	m_Graphics->setFontSize(30);

	if( !CheckDirectStart() ) m_StartDirect = true;
	//if( !Mix_PlayingMusic() ) m_Sound->playSound("no_coins");

	m_Sound->setVolume("bounce",80);
}


Menu::~Menu()
{
	//m_Sound->pauseSound("background");
}


int Menu::Update( double delta )
{
	if( m_TimeBuffer > 0 ) 
	{
		m_TimeBuffer--;
		return STATE_NULL;
	}

	if( m_Input->isKeyPressed(SDLK_SPACE) )
	{
		if( m_ChooseGameMode )
		{
			if( m_SmallMenuPoint == 0 ) gameMode = "Story"; 
			else gameMode = "Survival";
			if( m_StartDirect ) return STATE_GAME;
			else return STATE_PROLOG;
		}
		else
		{
			switch(m_MenuPoint)
			{
			case 0:
				m_ChooseGameMode = true;
				m_TimeBuffer = 10;
				break;
			case 1:
				return STATE_CREDITS;
			case 2:
				return STATE_EXIT;
			default:
				break;
			}
		}
	}

	if( m_Input->isKeyPressed(SDLK_UP) )
	{
		if( m_MenuPoint > 0 ) m_MenuPoint--;
		m_TimeBuffer = 10;
		m_Sound->playSound("button");
	}
	if( m_Input->isKeyPressed(SDLK_DOWN) )
	{
		if( m_MenuPoint < 2 ) m_MenuPoint++;
		m_TimeBuffer = 10;
		if( m_ChooseGameMode ) m_ChooseGameMode = false;
		m_Sound->playSound("button");
	}

	if( m_Input->isKeyPressed(SDLK_LEFT) && m_ChooseGameMode == true )
	{
		if( m_SmallMenuPoint > 0 ) m_SmallMenuPoint--;
		m_Sound->playSound("button");
	}
	if( m_Input->isKeyPressed(SDLK_RIGHT) && m_ChooseGameMode == true )
	{
		if( m_SmallMenuPoint < 2 ) m_SmallMenuPoint++;
		m_Sound->playSound("button");
	}

	return STATE_NULL;
}

void Menu::Draw()
{
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

	m_Graphics->drawTexture("game_logo",0,-20);

	if( m_ChooseGameMode )
	{
		if( m_SmallMenuPoint == 0 )
		{
			m_Graphics->drawTexture("menupoint_small_active",(SCREEN_WIDTH-358)/2,250);
			m_Graphics->drawTexture("menupoint_small",(SCREEN_WIDTH/2)+10,250);
		}
		else
		{
			m_Graphics->drawTexture("menupoint_small",(SCREEN_WIDTH-358)/2,250);
			m_Graphics->drawTexture("menupoint_small_active",(SCREEN_WIDTH/2) + 10,250);
		}

		for( int i = 1; i < 3; i++ )
		{
			m_Graphics->drawTexture("menupoint",(SCREEN_WIDTH-358)/2,250+(i*150));
		}
		m_Graphics->drawText("Story",275,305);
		m_Graphics->drawText("Survival",450,305);
	}
	else
	{
		for( int i = 0; i < 3; i++ )
		{
			if( m_MenuPoint == i )
			{
				m_Graphics->drawTexture("menupoint_active",(SCREEN_WIDTH-358)/2,250+(i*150));
				continue;
			}
			m_Graphics->drawTexture("menupoint",(SCREEN_WIDTH-358)/2,250+(i*150));
		}
		m_Graphics->drawText("Start Game",340,305);
	}
	
	m_Graphics->drawText("Credits",360,455);
	m_Graphics->drawText("Exit",380,605);

	m_Graphics->drawTexture("city",0,SCREEN_HEIGHT-100);
}

bool Menu::CheckDirectStart()
{
	ifstream in("data/game.cfg");

	string line;
	vector<string> lines;
	string playername;
	
	if(!in.is_open())
	{
		(*Log) << "ERROR: Could not open game.cfg!";
		return false;
	}

	while( getline(in, line) )
	{
		lines.push_back(line);
	}

	if( lines[0] == "1" ) return false;
	else
	{
		in.close();
		ofstream out("data/game.cfg");
		if(!out.is_open())
		{
			(*Log) << "ERROR: Could not open game.cfg!";
			return false;
		}
		out << "1"<< endl;
		out << lines[1] << endl;
		out << lines[2];
		out.close();
		return true;
	}
}