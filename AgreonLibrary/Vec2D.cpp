/**
*	@file Vec2D.cpp
*
*	@brief This file contains the Vec2D functions.
*/
#include "Vec2D.h"

Vec2D::Vec2D()
{
	m_X = 0;
	m_Y = 0;
}

Vec2D::~Vec2D()
{
}

Vec2D::Vec2D( double x, double y )
{
	m_X = x;
	m_Y = y;
}

Vec2D& Vec2D::operator=( Vec2D& vec )
{
	if( this != &vec )
	{
		m_X = vec.getX();
		m_Y = vec.getY();
	}
	return *this;
}

bool Vec2D::operator==( Vec2D& vec )
{
	if( m_X == vec.getX() && m_Y == vec.getY() )
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Vec2D::operator!=( Vec2D& vec )
{
	if( m_X != vec.getX() || m_Y != vec.getY() )
	{
		return true;
	}
	else
	{
		return false;
	}
}


Vec2D Vec2D::operator+( Vec2D& vec )
{
	Vec2D tmp = *this;
	tmp += vec;
	return tmp;
}

void Vec2D::operator+=( Vec2D& vec )
{
	m_X += vec.getX();
	m_Y += vec.getY();
}


Vec2D Vec2D::operator-( Vec2D& vec )
{
	Vec2D tmp = *this;
	tmp -= vec;
	return tmp;
}

void Vec2D::operator-=( Vec2D& vec )
{
	m_X -= vec.getX();
	m_Y -= vec.getY();
}


Vec2D Vec2D::operator*( Vec2D& vec )
{
	Vec2D tmp = *this;
	tmp *= vec;
	return tmp;
}

Vec2D Vec2D::operator*( double number )
{
	Vec2D tmp = *this;
	tmp *=  number;
	return tmp;
}

void Vec2D::operator*=( Vec2D& vec )
{
	m_X *= vec.getX();
	m_Y *= vec.getY();
}

void Vec2D::operator*=( double number )
{
	m_X *= number;
	m_Y *= number;
}


Vec2D Vec2D::operator/( Vec2D& vec )
{
	Vec2D tmp = *this;
	tmp /= vec;
	return tmp;
}

void Vec2D::operator/=( Vec2D& vec )
{
	m_X /= vec.getX();
	m_Y /= vec.getY();
}

double Vec2D::length()
{
	return sqrt( m_X * m_X + m_Y * m_Y );
}

void Vec2D::normalize()
{
	double len = length();
	if( len != 0)
	{
		m_X /= len;
		m_Y /= len;
	}
}

double Vec2D::dotProdukt( Vec2D vec )
{
	return ( m_X * vec.getX() + m_Y * vec.getY() );
}

Vec2D crossProdukt( Vec2D vec )
{
	return vec;
}

void Vec2D::addX( double x )
{
	m_X += x;
}

void Vec2D::addY( double y )
{
	m_Y += y;
}

void Vec2D::setX( double x )
{
	m_X = x;
}

void Vec2D::setY( double y )
{
	m_Y = y;
}

void Vec2D::setXY( double x, double y )
{
	m_X = x;
	m_Y = y;
}

double Vec2D::getX()
{
	return m_X;
}

double Vec2D::getY()
{
	return m_Y;
}