#include "Credits.h"


Credits::Credits(cGraphics *graphics, cInput *input, cSound *sound)
	: m_ViewY(0), m_State(0), m_Counter(0)
{
	m_Graphics	= graphics;
	m_Input		= input;
	m_Sound		= sound;
}


Credits::~Credits()
{
}

int Credits::Update( double delta )
{
	if( m_Input->isKeyPressed(SDLK_ESCAPE) ) return STATE_MENU;

	if(m_Counter < 60) 
	{
		m_Counter++;
		return STATE_NULL;
	}

	if( m_ViewY < -640 )
	{
		m_State = 1;
		m_Counter = 0;
	}
	else if( m_ViewY >= 0 ) m_State = 0;

	if(m_State == 0)	m_ViewY -= 1;
	else m_ViewY += 1;

	return STATE_NULL;
}

void Credits::Draw()
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

	glTranslatef(0,m_ViewY,0);

	m_Graphics->setFontSize(80);
	m_Graphics->drawText("Credits",280,100);

	m_Graphics->setFontSize(60);
	m_Graphics->drawText("Programming",50, 200);
	m_Graphics->drawText("Design",50, 250);
	m_Graphics->drawText("Daniel Huth",450, 220);

	m_Graphics->setFontSize(70);
	m_Graphics->drawText("Textures and Sounds",110,380);
	m_Graphics->setFontSize(50);
	m_Graphics->drawText("Dravenx",150,450);
	m_Graphics->drawText("Retimer",150,550);
	m_Graphics->drawText("CGeffex",150,650);
	m_Graphics->drawText("Jobro",535,450);
	m_Graphics->drawText("Wanna73",450,550);
	m_Graphics->drawText("Tomlija",510,650);
	m_Graphics->drawText("Sbed",150,750);
	m_Graphics->drawText("Lorc",150,850);
	m_Graphics->drawText("Suonho",510,750);
	m_Graphics->drawText("Timbre",510,850);
	m_Graphics->drawText("MillionthVector",270,940);

	m_Graphics->setFontSize(70);
	m_Graphics->drawText("Music",320,1100);
	m_Graphics->setFontSize(50);
	m_Graphics->drawText("Insert no Coins - Razor1911",150,1180);
	m_Graphics->drawText("Icarus - Trash80",220,1260);
	m_Graphics->drawText("Chaoz fantasy - Paragonx9",150,1340);
	

	glLoadIdentity();
}