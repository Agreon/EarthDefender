#include "Points.h"


Points::Points(cGraphics *graphics, cAnimationManager *animations, cInput *input, cSound *sound)
	: m_Counter(0), 
	m_MenuPoint(0), 
	m_TimeCounter(0),
	m_WorldRank(0), 
	m_NewHighScore(false), 
	m_Connection(false), 
	m_lCounter(0)
{
	m_Graphics			= graphics;
	m_AnimationManager	= animations;
	m_Input				= input;
	m_Sound				= sound;

	if( survived == false )
	{
		m_AnimationManager->createAnimation("fire_anim2","fire_anim2",-1,10,0,0,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.2","fire_anim2",-1,20,0,75,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.3","fire_anim2",-1,10,0,150,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.4","fire_anim2",-1,30,0,225,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.5","fire_anim2",-1,20,0,300,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.6","fire_anim2",-1,5,0,375,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.7","fire_anim2",-1,10,0,450,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.8","fire_anim2",-1,20,0,525,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.9","fire_anim2",-1,25,0,600,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.10","fire_anim2",-1,7,0,675,SCREEN_HEIGHT-100,128,128);
		m_AnimationManager->createAnimation("fire_anim2.11","fire_anim2",-1,10,0,750,SCREEN_HEIGHT-100,128,128);

		m_AnimationManager->createAnimation("explosion_animation_ground","explosion_anim",-1,20,0,0,SCREEN_HEIGHT-120,160,120);
		m_Sound->setVolume("sirens",128);
		m_Sound->playSound("sirens");
	}
	else
	{
		m_Sound->playSound("yeah");
	}	
	saveHighScore();
}


Points::~Points()
{
	m_AnimationManager->stopAll();
	m_Sound->pauseSound("sirens");
}

int Points::Update( double delta )
{
	m_lCounter++;

	if( m_lCounter == 1 )
	{
		m_Connection = getGlobalHighScore();
	}

	if( m_Input->isKeyPressed(SDLK_SPACE) )
	{
		switch(m_MenuPoint)
		{
		case 0: return STATE_MENU;
		case 1: 
			if( survived )
			{
				gameMode = "Survival";
				return STATE_GAME;
			}
			else
			{
				return STATE_GAME;
			}
		case 2: return STATE_EXIT;
		}
	}

	if( m_Input->isKeyPressed(SDLK_LEFT) && m_TimeCounter == 0 )
	{
		if( m_MenuPoint > 0 ) m_MenuPoint--;
		m_TimeCounter = 10;
	}
	if( m_Input->isKeyPressed(SDLK_RIGHT) && m_TimeCounter == 0 )
	{
		if( m_MenuPoint < 2 ) m_MenuPoint++;
		m_TimeCounter = 10;
	}

	if( survived == false )
	{
		if( m_Counter > 170 )
		{
			int ran = rand() % SCREEN_WIDTH;
			m_AnimationManager->setX("explosion_animation_ground",ran);
			m_Sound->playSound("explosion2");
			m_Counter = 0;
		}
		else m_Counter++;
	}

	m_AnimationManager->updateAll();

	if( m_TimeCounter > 0 ) m_TimeCounter--;

	return STATE_NULL;
}

void Points::Draw()
{
	glBegin(GL_QUADS);
		glColor4f(0,0,0,0.4);
		glVertex2f(0,0);
		glColor4f(0,0,0.3,0.4);
		glVertex2f(0,SCREEN_HEIGHT);
		glVertex2f(SCREEN_WIDTH,SCREEN_HEIGHT);
		glColor4f(0,0,0,0.4);
		glVertex2f(SCREEN_WIDTH,0);
	glEnd();
	glColor4f(1,1,1,1);

	string points = "Points: "+itos(player_points);
	string highscore = "Highscore: "+getHighScore();
	string rank = "Global Rank: "+itos(m_WorldRank);

    if( survived == false )	
	{
		m_Graphics->drawText("You could not save the earth!",250,150);
		
		m_Graphics->drawText(points.c_str(), 150, 300 );
		m_Graphics->drawText(highscore.c_str(), 150, 350 );
		if( m_NewHighScore ) m_Graphics->drawText("New Highscore!",500,300);
		if( m_Connection ) m_Graphics->drawText(rank.c_str(),500,350);
		else m_Graphics->drawText("No connection!",500,350);
		if( m_lCounter == 0 ) m_Graphics->drawText("Loading Database",500,350);
	}
	else 
	{
		m_Graphics->drawText("Congratulations!",100,150);
		m_Graphics->drawText("You saved the earth from these wretched invaders!",100,200);
		m_Graphics->drawText("If you want, you can test your skill in the Survival-Mode!",100,250);

		m_Graphics->drawText(points.c_str(), 100, 350 );
		m_Graphics->drawText(highscore.c_str(), 100, 400 );
		if( m_NewHighScore ) m_Graphics->drawText("New Highscore!",500,350);
		if( m_Connection ) m_Graphics->drawText(rank.c_str(),500,400);
		else m_Graphics->drawText("No connection!",500,400);
		if( m_lCounter == 0 ) m_Graphics->drawText("Loading Database",500,350);
	}

	for( int i = 0; i < 3; i++ )
	{
		if( m_MenuPoint == i )
		{
			m_Graphics->drawTexture("menupoint_small_active",120+(i*200),500);
			continue;
		}
		m_Graphics->drawTexture("menupoint_small",120+(i*200),500);
	}

	m_Graphics->drawText("Menu",170,555);
	if( survived ) m_Graphics->drawText("Survival",360,555);
	else m_Graphics->drawText("Retry",375,555);
	m_Graphics->drawText("Exit",580,555);

	m_Graphics->drawTexture("city",0,SCREEN_HEIGHT-100);
	if( survived == false ) m_AnimationManager->showAll();
}

void Points::saveHighScore()
{
	ifstream in("data/game.cfg");
	string line;
	vector<string> lines;
	
	if(!in.is_open())
	{
		(*Log) << "ERROR: Could not open game.cfg!";
		return;
	}
	while( getline( in, line )) lines.push_back(line);

	if( gameMode == "Story" ) m_HighScore = stoi(lines[1].c_str());
	else m_HighScore = stoi(lines[2].c_str());

	if( m_HighScore <= player_points )
	{
		m_HighScore = player_points;
		in.close();
		ofstream out("data/game.cfg");

		out << lines[0]<< endl;

		if( gameMode == "Story" ) out << itos(m_HighScore) << endl << lines[2];
		else out << lines[1] << endl << itos(m_HighScore);

		out.close();
		m_NewHighScore = true;
	}
}

string Points::getHighScore()
{
	return itos(m_HighScore);
}

bool Points::getGlobalHighScore()
{
	MYSQL *conn;
	MYSQL_RES *result;
	MYSQL_ROW row;
	MYSQL_FIELD *field;

	conn = mysql_init(NULL);
	if( !conn )
	{
		(*Log) << mysql_error(conn);
		return false;
	}
	// Connect to the database
	/* Deleted data for you ;) */
	if( mysql_real_connect(conn, "", "", "", "", 3306, NULL, 0) == NULL )
	{
		(*Log) << mysql_error(conn);
		return false;
	}

	// Check the local UserID
	ifstream in("data/highscore.cfg");
	int last_id;

	if( !in )
	{
		if( mysql_query(conn,"INSERT INTO user(Name) VALUES('NULL')") )
		{
			(*Log) << mysql_error(conn);
			return false;
		}
		last_id = mysql_insert_id(conn);
		ofstream out("data/highscore.cfg");
		out << last_id;
		out << endl;
	}
	else
	{
		string line;
		vector<string> lines;

		while( getline(in, line) )
		{
			lines.push_back(line);
		}
		last_id = atoi(lines[0].c_str());
	}
	
	// Check if user is already in Scoreboard
	ostringstream ss;
	ss << "SELECT * FROM "<<gameMode<<" WHERE ID_User ='" << last_id << "'";
	if( mysql_query( conn, ss.str().c_str() ))
	{
		(*Log) << mysql_error(conn);
		return false;
	}
	result = mysql_store_result(conn);
	if( mysql_num_rows(result) > 0 )
	{
		row = mysql_fetch_row( result );
		if( atoi(row[1]) < m_HighScore )
		{
			ostringstream ss2;
			ss2 << "UPDATE "<<gameMode<<" SET Score = '"<<m_HighScore<<"' WHERE ID_User ='"<<last_id<<"'";
			if( mysql_query( conn, ss2.str().c_str() ))
			{
				(*Log) << mysql_error(conn);
				return false;
			}
		}
	}
	else
	{
		ostringstream ss2;
		ss2 << "INSERT INTO "<<gameMode<<" (ID_User,Score) VALUES ('"<<last_id<<"','"<<m_HighScore<<"')";
		if( mysql_query( conn, ss2.str().c_str() ))
		{
			(*Log) << mysql_error(conn);
			return false;
		}
	}

	ostringstream ss3;
	ss3 << "SELECT * FROM "<<gameMode<<" WHERE Score > '"<<m_HighScore<<"' ORDER BY 'Score'";
	if( mysql_query( conn, ss3.str().c_str() ))
	{
		(*Log) << mysql_error(conn);
		return false;
	}
	result = mysql_store_result(conn);
	m_WorldRank = mysql_num_rows(result) + 1;

	return true;
}
