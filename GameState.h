#pragma once

#include "AgreonLibrary/cGraphics.h"
#include "AgreonLibrary/cAnimation.h"
#include "AgreonLibrary/cInput.h"
#include "AgreonLibrary/cEntity.h"
#include "AgreonLibrary/cSound.h"
#include "AgreonLibrary/cLog.h"
#include "AgreonLibrary/cTimer.h"

class GameState
{
protected:
	cGraphics			*m_Graphics;
	cAnimationManager	*m_AnimationManager;
	cInput				*m_Input;
	cSound				*m_Sound;
public:
	virtual int Update( double delta ) = 0;
	virtual void Draw() = 0;
	virtual ~GameState(){};
};