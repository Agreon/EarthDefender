#pragma once

#include "AgreonLibrary/Agreon.h"
#include "game.h"
#include "Menu.h"
#include "Prolog.h"
#include "Credits.h"
#include "Intro.h"
#include "Points.h"

class cApp
{
public:
	cApp();
	~cApp();

	void	Run();
	bool	Init();
	void	Shutdown();

	bool	LoadData();	

	void	ChangeState();
private:
	cGraphics			*m_Graphics;
	cAnimationManager	*m_AnimationManager;
	cInput				*m_Input;
	cSound				*m_Sound;
	cTimer				*m_Timer;

	GameState*	m_CurrentState;
	int			m_NextState;
	int			m_StateID;

	int		m_LastDelta;
	bool	m_Running;

	vector<string>	music;
	int				musicIt;
};

