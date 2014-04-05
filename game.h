#include "Player.h"
#include "GameState.h"
#include "Ufo.h"
#include "Bullet.h"
#include "Ball.h"
#include "Boss.h"
#include "PowerUp.h"

class Game :
	public GameState
{
public:
	Game(cGraphics *graphics, cAnimationManager *animationManager, cInput  *input, cSound *sound);
	~Game();

	bool	Init();
	int		Update( double delta );
	void	Draw();

	void	ChangeGameState();
	void	SendUfos();

private:
	Player			*m_Player;
	Ball			*m_Ball;
	Boss			*m_Boss;
	vector<Ufo*>	*m_Ufos;
	vector<Bullet*> *m_Bullets;
	vector<PowerUp*>*m_PowerUps;

	bool		m_SwitchState;
	bool		m_UfosActive;
	bool        m_Paused;
	int			m_TimeBuffer;
	int			m_Counter;
	int			m_StartCounter;
	int			m_BombDefends;
	bool		m_NearDeath;
};