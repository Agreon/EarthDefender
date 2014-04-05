#pragma once

#include "centity.h"
#include "Player.h"
#include "Ufo.h"
#include "PowerUp.h"
#include "AgreonLibrary/cAnimation.h"
#include "AgreonLibrary/cSound.h"

class Ball :
	public cEntity
{
private:
	double	m_VelX;
	double	m_VelY;
	double	m_Speed;
	bool	m_Super;
	Player* m_Player;
	vector<Ufo*> *m_Ufos;
	vector<PowerUp*> *m_PowerUps;
	cAnimationManager *m_AnimationManager;
	cSound	*m_Sound;
public:
	Ball(cGraphics *graphics, cAnimationManager *animManager, cSound *sound, Player *player, vector<Ufo*> *ufos, vector<PowerUp*> *powerups, string texture, int posX, int posY, int width, int height);
	~Ball();

	void Update( double delta );
	void CheckCollision();
	void Draw();
	void Reset();

	void setVelX( double velX );
	void setVelY( double velY );

	double	getVelX();
	double	getVelY();
	bool	isSuper();

	void setDestroyed( bool b );
	void setSuper( bool b );
};

