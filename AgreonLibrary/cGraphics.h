/**
*	@file cGraphics.h
*
*	@brief This file contains the cGraphics class.
*/
#pragma once

#include "Agreon.h"
#include "globals.h"

/** 
*	@brief Cares about OpenGL initialization, window handling and drawing.
*
*	This is a main class. Without it you can't run other managers, because they need openGL. 
*
*	You need this class to open a window, draw textures and to draw text or numbers.
*
*	Source : cGraphics.h
*
*	Source : cGraphics.cpp
*
*/
class cGraphics
{
private:
	SDL_Surface* m_Screen;
	int	m_Screen_Width;
	int	m_Screen_Height;

	FTGLPixmapFont* m_CurrentFont;

	map<string, uint> m_Textures;
	map<string, FTGLPixmapFont*> m_Fonts;
	vector<uint> m_TileTextures;
public:
	cGraphics();
	~cGraphics();

	/**
	*	Creates a window and initializes OpenGL.
	*
	*	@param screen_width		Width of the window.
	*	@param screen_height	Height of the window.
	*	@param flags			Flags for the creation of the Window.
	*	@param windowTitle		Title of the window.
	*	@param iconSrc			Source of the window icon.
	*/
	void init(int screen_width, int screen_height, const char* windowTitle, const char* iconSrc);

	/**
	*	Initializes OpenGL with default 2D options.
	*/
	void initOpenGL();

	/**
	*	Loads a texturefile from a given path and stores it in a map.
	*
	*	@param path	Path of the texturefile.
	*   @param name Name of the texture.
	*	@returns If the texture was successfull loaded.
	*/
	bool loadTexture(const char* path, string name);

	/**
	*	Draws a texture on the screen.
	*
	*	@param ID	The name of the texture.
	*	@param x	The x coordinate on the screen.
	*	@param y	The y coordinate on the screen.
	*/
	void drawTexture(string ID, int x, int y);

	/**
	*	Draws a texture on the screen.
	*
	*	@param ID		The name of the texture.
	*	@param x		The x coordinate on the screen.
	*	@param y		The y coordinate on the screen.
	*	@param rotation	The rotation of the texture.
	*/
	void drawTexture(string ID, int x, int y, int rotation );

	/**
	*	Draws a texture on the screen.
	*
	*	@param ID		The name of the texture.
	*	@param x		The x coordinate on the screen.
	*	@param y		The y coordinate on the screen.
	*	@param rotation	The rotation of the texture.
	*	@param scale	The scale of the texture.
	*/
	void drawTexture(string ID, int x, int y, int rotation, double scale );

	/**
	*	Draws a section of a texture.
	*	*
	*	@param texture	uint of the texture.
	*	@param rectX	The x coordinate of the source rectangle.
	*	@param rectY	The y coordinate of the source rectangle.
	*	@param rectW	The width of the source rectangel.
	*	@param rectH	The height of the source rectangel.
	*	@param posX		The x coordinate on the screen.
	*	@param posY		The y coordinate on the screen.
	*	@param rotation	The rotation of the texture.
	*/
	void drawSection( string texture, int rectX, int rectY, int rectW, int rectH, int posX, int posY, int rotation );

	/**
	*	Draws a rectangle on the screen.
	*
	*   @param x	The x coordinate of the Rectangle.
	*   @param y	The y coordinate of the Rectangle.
	*   @param w	The width of the Rectangle.
	*   @param h	The width of the Rectangle.
	*/
	void drawRectangle( int x, int y, int w, int h );

	/**
	*	Sets the color that will modify the textures
	*
	*	@param	r The red color.
	*	@param	g The green color.
	*	@param	b The blue color.
	*	@param	a The alpha value.
	*/
	void setColor( double r, double g, double b, double a );

	/**
	*	Selects a texture to work with.
	*	The light version of glBindTexture.
	*	
	*	@param	ID	The name of the texture.
	*/
	void bindTexture(string ID);

	/**
	*	Returns the system ID of a texture.
	*	*	
	*	@param		ID	The name of the texture.
	*	@returns	The system ID of the texture.
	*/
	uint getUint(string ID);

	/**
	*	Returns the width of a texture.
	*	*
	*	@param		ID	The name of the texture.
	*	@returns	The width of the texture.
	*/
	int	getTextureWidth(string ID);

	/**
	*	Returns the height of a texture.
	*	*
	*	@param		ID	The name of the texture.
	*	@returns	The height of the texture.
	*/
	int getTextureHeight(string ID);

	/**
	*	Draws a text on the screen.
	*	
	*	@param	text	The text.
	*	@param	x		The x coordinate.
	*	@param	y		The y coordinate.
	*/
	void drawText(const char* text, int x, int y);

	/**
	*	Draws a number on the screen.
	*	
	*	@param	num	The number.
	*	@param	x	The x coordinate.
	*	@param	y	The y coordinate.
	*/
	void drawNumber(int num, int x, int y);

	/**
	*	Sets the font face.
	*	
	*	@param	name	The name of the font.
	*/
	void setFont(string name);

	/**
	*	Loads a fontfile from a given path and stores it in a map.
	*
	*	@param path The	Path of the fontfile.
	*   @param name The Name of the font.
	*	@returns If the texture was successfull loaded.
	*/
	bool loadFont(const char* font, string name);

	/**
	*	Sets the font color.
	*	Values between 1 and 0.
	*	
	*	@param	r The red color of the font.
	*	@param	g The green color of the font.
	*	@param	b The blue color of the font.
	*/
	void setFontColor(double r, double g, double b);

	/**
	*	Sets the size of the font.
	*	
	*	@param	size The size of the font.
	*/
	void setFontSize(int size);

	/**
	*	Closes the Window and deletes the Pointers.
	*/
	void shutdown();
};
