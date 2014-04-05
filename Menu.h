#pragma once

#include "gamestate.h"

class Menu :
	public GameState
{
public:
	Menu(cGraphics *graphics, cInput *input, cSound *sound); 
	~Menu();

	int Update( double delta );
	void Draw();

	bool CheckDirectStart();
private:
	int	m_MenuPoint;
	int m_SmallMenuPoint;
	int	m_TimeBuffer;
	bool m_StartDirect;
	bool m_ChooseGameMode;
};

