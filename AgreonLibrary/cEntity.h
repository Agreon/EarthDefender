/**
*	@file cEntity.h
*
*	@brief This file contains the cEntity class.
*/
#pragma once

#include "Agreon.h"
#include "cGraphics.h"

/** 
*	@brief A basis class for all the Entities in your game.
*
*	You should only inherit from this class to add entities to your game.
*	Don't use it itself.
*
*	Source : cEntity
*/
class cEntity
{
protected:
	cGraphics* m_Graphics;
	Vec2D m_Position;
	string m_Image;
	int m_Width;
	int m_Height;
	int m_Rotation;
	bool m_Destroyed;
public:
	cEntity();
	~cEntity();

	/**
	*	Draws the Entity on the screen.
	* 
	*/
	virtual void draw();

	void setX( double x );
	void setY( double y );
	void setPosition( Vec2D vec );
	void setImage( string name );
	void setWidth( int width );
	void setHeight( int height );
	void setRotation( int rotation );
	void setDestroyed( bool destroyed );
	bool collision( cEntity* entity );

	double getX();
	double getY();
	Vec2D getPosition();
	string getImage();
	int getWidth();
	int getHeight();
	int getRotation();
	bool isDestroyed();
};

