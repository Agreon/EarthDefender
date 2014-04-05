/**
*	@file Vec2D.h
*
*	@brief This file contains the Vec2D class.
*/
#include <cmath>

/**
*	@brief A Vector2D class to store positions ,directions and forces.
*/
class Vec2D
{
private:
	double m_X;
	double m_Y;
public:
	Vec2D();
	Vec2D( double x, double y );
	~Vec2D();
	
	Vec2D& operator=( Vec2D& vec );
	bool operator==( Vec2D& vec );
	bool operator!=( Vec2D& vec );

	Vec2D operator+( Vec2D& vec );
	void operator+=( Vec2D& vec );

	Vec2D operator-( Vec2D& vec );
	void operator-=( Vec2D& vec );

	Vec2D operator*( Vec2D& vec );
	Vec2D operator*( double number );
	void operator*=( Vec2D& vec );
	void operator*=( double number );

	Vec2D operator/( Vec2D& vec );
	void operator/=( Vec2D& vec );
	
	/**
	*	Calculates the length of the Vector.
	*/
	double length();

	/**
	*	Normalizes the vector.
	*/
	void normalize();

	/**
	*	Caclulates the Dot Product of the vector.
	*/
	double dotProdukt( Vec2D vec );

	/**
	*	Caclulates the Cross Product of the vector.
	*/
	Vec2D crossProdukt( Vec2D vec );

	void addX( double x );
	void addY( double y );
	
	void setX( double x );
	void setY( double y );
	void setXY( double x, double y );
	
	double getX();
	double getY();
};