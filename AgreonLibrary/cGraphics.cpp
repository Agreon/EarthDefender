/**
*	@file cGraphics.cpp
*
*	@brief This file contains the cGraphics functions.
*/

#include "cGraphics.h"

cGraphics::cGraphics( void )
{
}


cGraphics::~cGraphics( void )
{
}


void cGraphics::init( int screen_width, int screen_height, const char* windowTitle, const char* iconSrc )
{
	m_Screen_Width	= screen_width;
	m_Screen_Height = screen_height;

	SDL_Init( SDL_INIT_EVERYTHING );

	if( iconSrc != NULL )
	{
		SDL_Surface* icon = SDL_LoadBMP( iconSrc );
		SDL_WM_SetIcon( icon, NULL );
	}

	m_Screen = SDL_SetVideoMode( m_Screen_Width, m_Screen_Height, 32, SDL_SWSURFACE|SDL_OPENGL );

	if( windowTitle != NULL )
	{
		SDL_WM_SetCaption( windowTitle, windowTitle );
	}

	initOpenGL();

	(*Log) << "Initialized Window and OpenGL.";
}


void cGraphics::initOpenGL()
{
	glViewport(0, 0 ,m_Screen_Width, m_Screen_Height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, m_Screen_Width, m_Screen_Height, 0, 0, 1);
    glMatrixMode(GL_MODELVIEW);
    glDisable(GL_DEPTH_TEST);
    glClearColor(0.5, 0.5, 0.5, 1.0);

	glShadeModel(GL_SMOOTH);
	glClearColor(0.5f, 0.5f, 0.5f, 0.0f);
	glClearDepth( 0.0f);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_ALWAYS);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glDisable(GL_LIGHTING);

	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_SCISSOR_TEST);
}


bool cGraphics::loadTexture( const char* path, string name )
{
	uint id = 0;
    SDL_Surface* img = IMG_Load( path );
    if( img == NULL )
    {
       (*Log) << string("ERROR: Texture was not loaded! Path: ")+path;
       glDisable( GL_TEXTURE_2D );
       return false;
    }
		
    SDL_PixelFormat form = {NULL,32,4,0,0,0,0,0,0,0,0,0xff000000,0x00ff0000,0x0000ff00,0x000000ff,0,255};

    SDL_Surface* img2 = SDL_ConvertSurface( img, &form, SDL_SWSURFACE );

	if( img2 == NULL )
	{
		(*Log) << string("ERROR: Texture was not loaded! Path: ")+path;
		glDisable( GL_TEXTURE_2D );
		return false;
	}

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_2D, id);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img->w, img->h, 0, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, img2->pixels);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    SDL_FreeSurface(img);
    SDL_FreeSurface(img2);
	
	m_Textures[ name ] = id;
	(*Log) << string("Loaded texture successful. ")+name+" | "+path;
	return true;
}


void cGraphics::drawTexture( string ID, int x, int y )
{
	drawTexture( ID, x, y, 0, 1 );
}


void cGraphics::drawTexture( string ID, int x, int y, int rotation )
{
	drawTexture( ID, x, y, rotation, 1 );
}


void cGraphics::drawTexture( string ID, int x, int y, int rotation, double scale )
{
	int w;
	int h;

	if( m_Textures[ ID ] == NULL )
	{
		(*Log) << string("ERROR: Can't draw texture with unkown ID! ID: ")+ID;
		return;
	}

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, m_Textures[ ID ] );

	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &w );
	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &h );

	glPushMatrix();

	glScalef( scale, scale , 0 );

	/// Rotation
	glTranslatef(x + w/2, y + h/2, 0);
	glRotatef( rotation, 0, 0, 1 );
	glTranslatef(-x - w/2, -y - h/2, 0);

	glBegin( GL_QUADS );
		glTexCoord2f(0,0); glVertex2f(x,y);
		glTexCoord2f(1,0); glVertex2f(x+w,y);
		glTexCoord2f(1,1); glVertex2f(x+w,y+h);
		glTexCoord2f(0,1); glVertex2f(x,y+h);
	glEnd();
	glDisable( GL_TEXTURE_2D );

	glPopMatrix();
}


void cGraphics::drawSection( string texture, int rectX, int rectY, int rectW, int rectH, int posX, int posY, int rotation )
{
	uint id= getUint( texture );
	int textureWidth;
	int textureHeight;

	glEnable( GL_TEXTURE_2D );
	glBindTexture( GL_TEXTURE_2D, id );

	
	// Get width and height of the texture
	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth );
	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight );


	double texLeft = (double)rectX / (double)textureWidth;
	double texRight = ((double)rectX + (double)rectW) / (double)textureWidth;
	double texTop = (double)rectY / (double)textureHeight;
	double texBottom = ((double)rectY + (double)rectH) / (double)textureHeight;

	glPushMatrix();

	// Rotation
	glTranslatef(posX + rectW/2,posY + rectH/2,0);
	glRotatef(rotation,0,0,1);
	glTranslatef(-posX - rectW/2,-posY - rectH/2,0);

	glBegin( GL_QUADS );
		glTexCoord2f(texLeft,texTop); glVertex2f( posX, posY );
		glTexCoord2f(texRight,texTop); glVertex2f( posX+rectW, posY );
		glTexCoord2f(texRight,texBottom); glVertex2f( posX+rectW, posY+rectH );
        glTexCoord2f(texLeft,texBottom); glVertex2f( posX, posY+rectH );
	glEnd();
	glDisable( GL_TEXTURE_2D );

	glPopMatrix();
	glLoadIdentity();

}

/*
void cGraphics::drawSection( uint texture, int section, int x, int y, int w, int h, int rotation )
{
	int textureWidth;
	int textureHeight;
	
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D,texture);

	// Get width and height of the texture
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &textureWidth);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &textureHeight);

	Rect clip;
	clip.x = section * w;
	clip.y = 0;
	clip.w = w;
	clip.h = h;

	double texLeft = 0;
	double texRight = 1;
	double texTop = 0;
	double texBottom = 1;

	texLeft = (double)clip.x / (double)textureWidth;
	texRight = (double)(clip.x + clip.w) / (double)textureWidth;
	texTop = (double)clip.y / (double)textureWidth;
	texBottom = 1;

	glPushMatrix();

	// Rotation
	glTranslatef(x + w/2,y + h/2,0);
	glRotatef(rotation,0,0,1);
	glTranslatef(-x - w/2,-y - h/2,0);

	glBegin(GL_QUADS);
		glTexCoord2f(texLeft,texTop); glVertex2f(x,y);
		glTexCoord2f(texRight,texTop); glVertex2f(x+w,y);
		glTexCoord2f(texRight,texBottom); glVertex2f(x+w,y+h);
        glTexCoord2f(texLeft,texBottom); glVertex2f(x,y+h);
	glEnd();
	glDisable(GL_TEXTURE_2D);

	glPopMatrix();
	glLoadIdentity();
}
*/
/**
*	Draws a section of a texture. Used mostly for Animation
*	
*	@see above	But with the name of the texture. 

void cGraphics::drawSection( string texture, int section, int x, int y, int w, int h, int rotation )
{
	uint id = getUint( texture );

	drawSection( id, section, x, y, w, h, rotation );
}
*/

void cGraphics::drawRectangle( int x, int y, int w, int h )
{
	glBegin( GL_QUADS );
		glVertex2f( x, y );
		glVertex2f( x + w, y );
		glVertex2f( x + w, y + h );
		glVertex2f( x, y + h );
	glEnd();
}


void cGraphics::setColor( double r, double g, double b, double a )
{
	glColor4d( r, g, b, a );
}


void cGraphics::bindTexture( string ID )
{
	glBindTexture( GL_TEXTURE_2D, m_Textures[ID] );
}


uint cGraphics::getUint( string ID )
{
	if(m_Textures[ID] == NULL)
	{
		(*Log) << string("ERROR: Can not get UINT of texture with unkown ID! ID: ")+ID;
		return m_Textures[0];
	}
	return m_Textures[ID];
}


int cGraphics::getTextureWidth( string ID )
{
	if(m_Textures[ID] == NULL)
	{
		(*Log) << string("ERROR: Can not get width of texture with unkown ID! ID: ")+ID;
		return m_Textures[0];
	}

	int width;

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, m_Textures[ID] );

	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width );

	glDisable(GL_TEXTURE_2D);

	return width;
}


int cGraphics::getTextureHeight( string ID )
{
	if(m_Textures[ID] == NULL)
	{
		(*Log) << string("ERROR: Can not get height of texture with unkown ID! ID: ")+ID;
		return m_Textures[0];
	}

	int height;

	glEnable(GL_TEXTURE_2D);
	glBindTexture( GL_TEXTURE_2D, m_Textures[ID] );

	glGetTexLevelParameteriv( GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height );

	glDisable(GL_TEXTURE_2D);

	return height;
}


void cGraphics::drawText( const char* text, int x, int y )
{
	glRasterPos2i( x, y );
	m_CurrentFont->Render( text );
}


void cGraphics::drawNumber( int num, int x, int y )
{
	char buf[33];
	int tmp = num;
	_itoa_s( tmp, buf, 10 );

	drawText( buf, x, y );
}


void cGraphics::setFont( string name )
{
	map<string, FTGLPixmapFont*>::iterator iter = m_Fonts.find( name );
	if( iter != m_Fonts.end() )
	{
		m_CurrentFont = m_Fonts[ name ];
	}
	else
	{
		(*Log) << string("ERROR: There is no font loaded with this name! Name: ")+name;
	}
}


bool cGraphics::loadFont( const char* font, string name )
{
	m_Fonts[ name ] = new FTGLPixmapFont( font );

	if(m_Fonts[ name ]->Error()) 
	{
		(*Log) << string("ERROR: Font was not loaded ! Path: ")+font;
		return false;
	}
	(*Log) << string("Loaded font file successful. ")+name+" | "+font;
	return true;
}


void cGraphics::setFontColor( double r, double g, double b )
{
	if( r > 0 ) r = -1 + r;
	else r = -1;

	if( g > 0 ) g = -1 + g;
	else g = -1;

	if( b > 0 ) b = -1 + b;
	else b = -1;

	glPixelTransferf( GL_RED_BIAS, r );
	glPixelTransferf( GL_GREEN_BIAS, g );
	glPixelTransferf( GL_BLUE_BIAS, b );
}


void cGraphics::setFontSize( int size )
{
	m_CurrentFont->FaceSize( size );
}



void cGraphics::shutdown()
{
	delete m_Screen;
	m_Screen = 0;

	delete m_CurrentFont;
	m_CurrentFont = 0;

	m_Fonts.clear();
	SDL_Quit();
}