#include "Ufo.h"

char Ufo::m_Direction = 'l';

Ufo::Ufo(cGraphics *graphics, string texture, int posX, int posY, int width, int height)
{
	m_Graphics = graphics;
	m_Image = texture;
	m_Position = Vec2D( posX, posY );
	m_Width = width;
	m_Height = height;
}


Ufo::~Ufo()
{
}

void Ufo::Update( double delta )
{
	if( m_Direction == 'l' ) m_Position -= Vec2D( 0.1 * delta, 0);
	else  m_Position += Vec2D( 0.1 * delta, 0 );
}
