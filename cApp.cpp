#include "cApp.h"


cApp::cApp() 
	: m_NextState(STATE_NULL), musicIt(0)
{
}


cApp::~cApp()
{
}


void cApp::Run()
{
	if(!Init())
	{
		return;
	}

	m_StateID = STATE_INTRO;
	m_CurrentState = new Intro(m_Graphics,m_Input,m_Sound);

	while( m_Running )
	{
		if(m_Input->handleInput())
		{
			break;
		}

		if( !Mix_PlayingMusic() )
		{			
			m_Sound->playSound(music[musicIt]);
			musicIt++;
			if( musicIt > 2 ) musicIt = 0;
		}
			

		m_Timer->update();

		int delta = m_Timer->getDelta();
		if( delta > 24 ) delta = 24;

		m_NextState = m_CurrentState->Update( delta );
		ChangeState();

		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glClearColor(0,0,0,1);

		m_CurrentState->Draw();

		SDL_GL_SwapBuffers();

		SDL_Delay(16);
	}
	Shutdown();
}

bool cApp::Init()
{
	(*Log) << "Initialize Game";
	m_Graphics			= new cGraphics();
	m_AnimationManager	= new cAnimationManager(m_Graphics);
	m_Input				= new cInput();
	m_Sound				= new cSound();
	m_Timer				= new cTimer();

	m_Graphics->init(SCREEN_WIDTH, SCREEN_HEIGHT, "Earth Defender", NULL);
	SDL_ShowCursor(0);
	m_Sound->setVolume(128);

	if(!LoadData())
	{
		return false;
	}

	srand((unsigned) time(NULL));

	m_Sound->setVolume(100);

	return true;
}

void cApp::Shutdown()
{
	(*Log) << "Free Manager";

	delete m_Sound;
	m_Sound = 0;

	delete m_Timer;
	m_Timer = 0;

	delete m_Input;
	m_Input = 0;

	delete m_Graphics;
	m_Graphics = 0;

	(*Log) << "Manager deleted. Shutting down...";

	delete	Log;
	Log = 0;
}

bool cApp::LoadData()
{
	ifstream in("data/textures.dat");
	string line;
	string item;
	vector<string> lines;
	vector<string> elements;


	if( !in.is_open() )
	{
		(*Log) << "ERROR: Could not open textures.dat!";
		return false;
	}

	while( getline(in,line) )
	{
		lines.push_back( line );
	}

	for( int i = 0; i < lines.size(); i++ )
	{
		stringstream ss(lines[i]);
		while( getline(ss,item,';') )
		{
			elements.push_back(item);
		}
		if( !m_Graphics->loadTexture(elements[1].c_str(),elements[0]) ) return false;
		elements.clear();
	}
	

	if(	!m_Graphics->loadFont("data/font/astron_boy.ttf","astron")			||
		!m_Graphics->loadFont("data/font/astron_boy_w.ttf","astron_w")		||
		!m_Graphics->loadFont("data/font/Roboto-Light.ttf","roboto_light")	||		
		!m_Sound->loadSound("data/sound/explosion1.wav","explosion1")		||		
		!m_Sound->loadSound("data/sound/explosion2.wav","explosion2")		||		
		!m_Sound->loadSound("data/sound/yeah.wav","yeah")					||		
		!m_Sound->loadSound("data/sound/bounce.wav","bounce")				||		
		!m_Sound->loadSound("data/sound/burner.wav","burner")				||		
		!m_Sound->loadSound("data/sound/fire_laser.wav","fire_laser")		||		
		!m_Sound->loadSound("data/sound/get_powerup.wav","get_powerup")		||		
		!m_Sound->loadSound("data/sound/sirens.wav","sirens")				||	
		!m_Sound->loadSound("data/sound/button.wav","button")				||	
		!m_Sound->loadSound("data/sound/ball_shot.wav","ball_shot")			||		
		!m_Sound->loadMusic("data/sound/no_coins.ogg","no_coins")			||		
		!m_Sound->loadMusic("data/sound/icarus.ogg","icarus")				||		
		!m_Sound->loadMusic("data/sound/chaos.ogg","chaos") )	
	{
		return false;
	}

	music.push_back("no_coins");
	music.push_back("icarus");
	music.push_back("chaos");

	return true;
}

void cApp::ChangeState()
{
	if( m_NextState == STATE_EXIT )
	{
		m_Running = false;
		return;
	}
	if(m_NextState != STATE_NULL)
	{
        if(m_NextState != STATE_EXIT)
		{
			delete m_CurrentState;
        }
        switch(m_NextState)
		{
            case STATE_MENU:
				m_CurrentState = new Menu(m_Graphics,m_Input,m_Sound);
                break;
			case STATE_PROLOG:
				m_CurrentState = new Prolog(m_Graphics,m_Input,m_Sound);
                break;
            case STATE_GAME:
				m_CurrentState = new Game(m_Graphics,m_AnimationManager,m_Input,m_Sound);
                break;
			case STATE_CREDITS:
				m_CurrentState = new Credits(m_Graphics,m_Input,m_Sound);
				break;
			case STATE_POINTS:
				m_CurrentState = new Points(m_Graphics,m_AnimationManager,m_Input,m_Sound);
        }
		m_StateID = m_NextState;
        m_NextState = STATE_NULL;
    }
}

int main( int argc, char* args[] )
{
	cApp app;
	app.Run();

	return 0;
}