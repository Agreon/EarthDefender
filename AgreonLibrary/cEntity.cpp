/**
*	@file cEntity.cpp
*
*	@brief This file contains the cEntity functions.
*/
#include "cEntity.h"

cEntity::cEntity()
{
	m_Graphics = 0;
	m_Position = Vec2D(0,0);
	m_Image = "";
	m_Width = 0;
	m_Height = 0;
	m_Rotation = 0;
	m_Destroyed = false;
}


cEntity::~cEntity()
{
}

void cEntity::draw()
{
	m_Graphics->drawTexture( m_Image,m_Position.getX(), m_Position.getY(), m_Rotation );
}

void cEntity::setX( double x )
{
	m_Position.setX( x );
}

void cEntity::setY( double y )
{
	m_Position.setY( y );
}

void cEntity::setPosition( Vec2D vec )
{
	m_Position = vec;
}

void cEntity::setImage( string name )
{
	m_Image = name;
}

void cEntity::setWidth( int width )
{
	m_Width = width;
}

void cEntity::setHeight( int height )
{
	m_Height = height;
}

void cEntity::setRotation( int rotation )
{
	m_Rotation = rotation;
}

void cEntity::setDestroyed( bool destroyed )
{
	m_Destroyed = destroyed;
}


bool cEntity::collision( cEntity* entity )
{
	if(m_Position.getY() >= entity->getY() + entity->getHeight()) return false;
	if(m_Position.getX() >= entity->getX() + entity->getWidth()) return false;
	if(m_Position.getY() + m_Height <= entity->getY()) return false;
	if(m_Position.getX() + m_Width <= entity->getX()) return false;

	return true;
}

double cEntity::getX()
{
	return m_Position.getX();
}

double cEntity::getY()
{
	return m_Position.getY();
}

Vec2D cEntity::getPosition()
{
	return m_Position;
}

string cEntity::getImage()
{
	return m_Image;
}

int cEntity::getWidth()
{
	return m_Width;
}

int cEntity::getHeight()
{
	return m_Height;
}

int cEntity::getRotation()
{
	return m_Rotation;
}

bool cEntity::isDestroyed()
{
	return m_Destroyed;
}
