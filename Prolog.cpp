#include "Prolog.h"


Prolog::Prolog(cGraphics *graphics, cInput *input, cSound *sound) 
	: m_Counter(0)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;
}


Prolog::~Prolog()
{
}

int Prolog::Update( double delta )
{
	if( m_Counter < 10 )
	{
		m_Counter++;
		return STATE_NULL;
	}

	if( m_Input->isKeyPressed(SDLK_SPACE) ) return STATE_GAME;

	return STATE_NULL;
}

void Prolog::Draw()
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

	m_Graphics->drawText("Invaders from another star are attacking the earth!",120,140);
	m_Graphics->drawTexture("boss",(SCREEN_WIDTH-128)/2,20);

	m_Graphics->drawText("They want to blow up the planet with an alien bomb.",120,200);
	m_Graphics->drawText("You have to return it back in space to save the Earth.",120,260);
	m_Graphics->drawText("But be ready for everything.",120,320);
	m_Graphics->drawText("The invaders are smarter than they seem.",120,380);

	m_Graphics->drawText("Press Space if you are ready!",250,550);

	m_Graphics->drawTexture("player",(SCREEN_WIDTH-128)/2,620);

	m_Graphics->drawTexture("city",0,SCREEN_HEIGHT-100);
}
