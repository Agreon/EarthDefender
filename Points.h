#pragma once
#include "gamestate.h"
class Points :
	public GameState
{
public:
	Points(cGraphics *graphics, cAnimationManager *animations, cInput *input, cSound *sound);
	~Points();

	int Update( double delta );
	void Draw();

	void	saveHighScore();
	string	getHighScore();
	bool	getGlobalHighScore();
private:
	int m_Counter;
	int m_TimeCounter;
	int m_MenuPoint;
	int m_HighScore;
	int m_WorldRank;
	bool m_NewHighScore;
	bool m_Connection;
	long m_lCounter;
};

