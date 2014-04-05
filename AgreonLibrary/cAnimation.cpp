#include "cAnimation.h"

cAnimation::cAnimation( int repeat, int fps, int rotation, int x, int y, int fw, int fh, bool active)
{
	m_Fps = fps;
	m_Rotation = rotation;
	m_X = x;
	m_Y = y;
	m_FrameWidth = fw;
	m_FrameHeight = fh;
	m_Active = active;

	if(repeat != -1) m_Repeatations = repeat - 1;
	else m_Repeatations = -1;

	m_Currentframe = 0;
	m_Lastupdate = SDL_GetTicks();
	m_IsDone = false;
	m_IsPaused = false;
}

void cAnimation::setTexture( string texture, uint ID )
{
	m_Texture = texture;

	/// Get the number of frames
	int tmpW;
	glBindTexture(GL_TEXTURE_2D,ID);
	glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &tmpW);
	m_Frames = tmpW / m_FrameWidth;
}

void cAnimation::update()
{
	if(m_IsPaused || m_Active == false) return;

	if( 1000 / m_Fps < (SDL_GetTicks() - m_Lastupdate))
	{
		m_Currentframe++;
		m_Lastupdate = SDL_GetTicks();

		if(m_Currentframe >= m_Frames)
		{
			if( m_Repeatations != -1)
			{
				if(m_Repeatations == 0)
				{
					m_IsDone = true;
				}
				else
				{
					m_Repeatations--;
				}
			}
			m_Currentframe = 0;
		}
	}
}


void cAnimation::show(cGraphics* Graphics)
{
	if(m_Active == false) return;
	Graphics->drawSection( m_Texture, m_Currentframe * m_FrameWidth, 0, m_FrameWidth, m_FrameHeight, m_X, m_Y, m_Rotation);
}


void cAnimation::stop()
{
	m_IsDone = true;
}


void cAnimation::pause()
{
	m_IsPaused = true;
}


void cAnimation::resume()
{
	m_IsPaused = false;
}


void cAnimation::activate()
{
	m_Active = true;
}


void cAnimation::deactivate()
{
	m_Active = false;
}


bool cAnimation::isDone()
{
	return m_IsDone;
}


bool cAnimation::isPaused()
{
	return m_IsPaused;
}


bool cAnimation::isActive()
{
	return m_Active;
}


void cAnimation::setX(int x)
{
	m_X = x;
}


void cAnimation::setY(int y)
{
	m_Y = y;
}


void cAnimation::setXY(int x, int y)
{
	m_X = x;
	m_Y = y;
}

void cAnimation::setRotation(int rotation)
{
	m_Rotation = rotation;
}

int cAnimation::getRotation()
{
	return m_Rotation;
}

//----------------------------------------------//
//				AnimationManager				//
//----------------------------------------------//

cAnimationManager::cAnimationManager(cGraphics* Graphics)
{
	m_Graphics = Graphics;
}


void cAnimationManager::createAnimation(string name, string texture, int repeats, int speed, int rotation, int x, int y, int fw, int fh)
{
	uint textureID = m_Graphics->getUint(texture);

	m_Animations[name] = new cAnimation( repeats,speed,rotation,x,y,fw,fh,true);
	m_Animations[name]->setTexture( texture, textureID );
}

void cAnimationManager::updateAll()
{

	for(std::map<string, cAnimation*>::iterator it=m_Animations.begin(); it!=m_Animations.end(); it++)
	{
		if( !m_Animations[it->first]->isDone() ) m_Animations[it->first]->update();
	}
}


void cAnimationManager::showAll()
{
	for(std::map<string, cAnimation*>::iterator it=m_Animations.begin(); it!=m_Animations.end(); it++)
	{
		if( !m_Animations[it->first]->isDone() ) m_Animations[it->first]->show( m_Graphics );
	}
}


void cAnimationManager::stopAll()
{
	for(std::map<string, cAnimation*>::iterator it=m_Animations.begin(); it!=m_Animations.end(); it++)
	{
		if( !m_Animations[it->first]->isDone() ) m_Animations[it->first]->stop();
	}
}


void cAnimationManager::pauseAll()
{
	for(std::map<string, cAnimation*>::iterator it=m_Animations.begin(); it!=m_Animations.end(); it++)
	{
		if( !m_Animations[it->first]->isDone() ) m_Animations[it->first]->pause();
	}
}


void cAnimationManager::resumeAll()
{
	for(std::map<string, cAnimation*>::iterator it=m_Animations.begin(); it!=m_Animations.end(); it++)
	{
		m_Animations[it->first]->resume();
	}
}


void cAnimationManager::shutdown()
{
	for (std::map<string, cAnimation*>::iterator it=m_Animations.begin(); it!=m_Animations.end();)
	{
		m_Animations.erase(it++);
	}
}


void cAnimationManager::update(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->update();
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to update with this ID! ID: ")+ID;
	}
}


void cAnimationManager::show(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->show( m_Graphics );
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to show with this ID! ID: ")+ID;
	}
}


void cAnimationManager::stop(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->stop();
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to stop with this ID! ID: ")+ID;
	}
}


void cAnimationManager::pause(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->pause();
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to pause with this ID! ID: ")+ID;
	}
}


void cAnimationManager::resume(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->resume();
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to resume with this ID! ID: ")+ID;
	}
}


void cAnimationManager::destroy(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
			delete m_Animations[ID];
			m_Animations.erase(ID);
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to destroy with this ID! ID: ")+ID;
	}
}


void cAnimationManager::activate(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->activate();
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to activate with this ID! ID: ")+ID;
	}
}


void cAnimationManager::deactivate(string ID)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->deactivate();
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to deactivate with this ID! ID: ")+ID;
	}
}


void cAnimationManager::setX(string ID, int x)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->setX(x);
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to setX with this ID! ID: ")+ID;
	}
}


void cAnimationManager::setY(string ID, int y)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->setY(y);
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to setY with this ID! ID: ")+ID;
	}
}


void cAnimationManager::setPosition(string ID, int x, int y)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->setXY(x,y);
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to setXY with this ID! ID: ")+ID;
	}
}

void cAnimationManager::setRotation(string ID, int rotation)
{
	map<string, cAnimation*>::iterator iter = m_Animations.find(ID);
	if (iter != m_Animations.end() )
	{
		m_Animations[ID]->setRotation(rotation);
	}
	else
	{
		(*Log) << string("ERROR: There is no Animation to set rotation with this ID! ID: ")+ID;
	}
}

int cAnimationManager::getRotation(string ID)
{
	return m_Animations[ID]->getRotation();
}