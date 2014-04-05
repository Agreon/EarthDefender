/**
*	@file cAnimation.h
*
*	@brief This file contains the cAnimation and the cAnimationManager class.
*/
#pragma once

#include "Agreon.h"
#include "cGraphics.h"

/** 
*	@brief Holds an Animation and handles the operations on it.
*
*	You should not use this class to create Animations. Use cAnimationManager instead.
*
*	Source : cAnimation.h
*
*	Source : cAnimation.cpp
*
*/
class cAnimation
{
private:
	string m_Texture;
	uint m_Currentframe;
	uint m_Frames;
	Uint32 m_Lastupdate;
	Uint32 m_Fps;

	bool m_IsDone, m_IsPaused, m_Active;

	int m_X, m_Y, m_FrameWidth, m_FrameHeight, m_Repeatations, m_Rotation;
public:
	cAnimation(int repeat, int fps, int rotation, int x, int y, int fw, int fh, bool active);

	void setTexture(string texture, uint ID );

	void update();
	void show(cGraphics* Graphics);
	void stop();
	void pause();
	void resume();
	void activate();
	void deactivate();

	bool isDone();
	bool isPaused();
	bool isActive();

	void setX(int y);
	void setY(int y);
	void setXY(int x, int y);
	void setRotation(int rotation);

	int getRotation();
};

/** 
*	@brief Stores all Animations and manages operations on them.
*
*	Use this class to easy create Animations.
*
*	Source : cAnimation.h
*
*	Source : cAnimation.cpp
*
*/
class cAnimationManager
{
private:
	map<string, cAnimation*> m_Animations;
	cGraphics* m_Graphics;
public:
	/**
	*	Constructor, this manager needs cGraphics to draw the Animations.
	*/
	cAnimationManager(cGraphics* Graphics);

	/**
	*	Creates a new animation.
	*	@param	name		The name of the animation.
	*	@param	texture		The name of the texture to use.
	*	@param	repeats		The repeatations of the animation. -1 is endless.
	*	@param	speed		The speed of the animation
	*	@param	rotation	The rotation of the animation.
	*	@param	x			The x coordinate of the animation.
	*	@param	y			The y coordinate of the animation.
	*	@param	fw			the width of the rectangle that should be shown.
	*	@param	fh			the height of the rectangle that should be shown.
	*/
	void createAnimation(string name, string texture, int repeats, int speed, int rotation, int x, int y, int fw, int fh );
	
	/**
	*	Updates all animations.
	*/
	void updateAll();	

	/**
	*	Shows all animations.
	*/
	void showAll(); 

	/**
	*	Stops all animations.
	*/
	void stopAll();

	/**
	*	Pauses all animations.
	*/
	void pauseAll();

	/**
	*	Resumes all animations.
	*/
	void resumeAll();

	/**
	*	Deletes all animations.
	*/
	void shutdown();

	/**
	*	Updates an animation.
	*/
	void update(string ID);	

	/**
	*	Shows an animation.
	*/
	void show(string ID);

	/**
	*	Stops an animation.
	*/
	void stop(string ID);

	/**
	*	Pauses an animation.
	*/
	void pause(string ID);

	/**
	*	Resumes an animation.
	*/
	void resume(string ID);

	/**
	*	Destroys an animation.
	*/
	void destroy(string ID);

	/**
	*	Activates an animation.
	*/
	void activate(string ID);

	/**
	*	Deactivates an animation.
	*/
	void deactivate(string ID);

	/**
	*	Sets the x coordinate of an animation.
	*/
	void setX(string ID, int x);

	/**
	*	Sets the y coordinate of an animation.
	*/
	void setY(string ID, int y);

	/**
	*	Sets the position of an animation.
	*/
	void setPosition(string ID, int x, int y);

	/**
	*	Sets the rotation of an animation.
	*/
	void setRotation(string ID, int rotation);

	/**
	*	Sets the texture of an animation.
	*/
	void setTexture( string ID, string texture );

	/**
	*	@returns the rotation of an animation.
	*/
	int getRotation(string ID);
};