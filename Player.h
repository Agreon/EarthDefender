#pragma once

#include "centity.h"
#include "AgreonLibrary/cInput.h"
#include "AgreonLibrary/cAnimation.h"
#include "AgreonLibrary/cSound.h"
#include "Bullet.h"

class Player :
	public cEntity
{
private:
	cInput	*m_Input;
	cAnimationManager *m_Animations;
	cSound *m_Sound;
	double	m_Speed;
	int		m_Lives;
	int		m_Points;
	vector<Bullet*> *m_Bullets;
	bool	m_PlayBurner;
	int		m_MusicChannel;

public:
	Player( cGraphics *graphics, cAnimationManager *animationManager, cInput *input, cSound *sound, vector<Bullet*> *bullets, string texture, int posX, int posY, int width, int height, double speed );
	~Player();

	void Update( double delta );
	void Draw();

	int getLives();
	int getPoints();
	
	void setLives( int l );
	void incLive();
	void decLive();

	void setPoints( int p );
	void incPoints( int p );
	void decPoints( int p );
};

