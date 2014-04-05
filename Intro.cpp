#include "Intro.h"


Intro::Intro(cGraphics *graphics, cInput  *input, cSound *sound)
	: m_Counter(0)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;
}


Intro::~Intro()
{
}

int Intro::Update( double delta )
{
	if( m_Counter >= 200 || m_Input->isKeyPressed(SDLK_SPACE) ) return STATE_MENU;
	m_Counter++;

	return STATE_NULL;
}

void Intro::Draw()
{
	m_Graphics->drawTexture("logo",0,100);
}