/**
*	@file cSound.cpp
*
*	@brief This file contains the cSound functions.
*/
#include "cSound.h"


cSound::cSound()
{
	int audio_rate = 44800;
	Uint16 audio_format = MIX_DEFAULT_FORMAT; 
	int audio_channels = 2;
	int audio_buffers = 2048;

	Mix_OpenAudio( audio_rate, audio_format, audio_channels, audio_buffers );

	(*Log) << "Initialized Sound.";
}


cSound::~cSound()
{
	(*Log) << "Shutting down Sound...";
	m_Chunks.clear();
	m_Music.clear();
	Mix_CloseAudio();
}

bool cSound::loadSound(const char* path, string name)
{
	Mix_Chunk* tmp = Mix_LoadWAV(path);
	if(tmp == NULL) 
	{
		(*Log) << string("ERROR: Could not load Sound file! Path: ")+path;
		return false; 
	}

	m_Chunks[name] = tmp;
	(*Log) << string("Loaded Sound file successful. ")+name+" | "+path;
	return true;
}

bool cSound::loadMusic(const char* path, string name)
{
	Mix_Music* tmp = Mix_LoadMUS(path);
	if(tmp == NULL) 
	{
		(*Log) << string("ERROR: Could not load Music file! Path: ")+path;
		return false;
	}
	m_Music[name] = tmp;
	(*Log) << string("Loaded Music file successful. ")+name+" | "+path;
	return true;
}


int cSound::playSound(string name)
{
	map<string, Mix_Music*>::iterator iterMusic = m_Music.find(name);
	map<string, Mix_Chunk*>::iterator iterChunk = m_Chunks.find(name);

	if (iterChunk != m_Chunks.end())
	{
		return Mix_PlayChannel(-1,m_Chunks[name],0);
	}
	else if(iterMusic != m_Music.end())
	{
		Mix_PlayMusic(m_Music[name],1);
		return 0;
	}
	else
	{
		(*Log) << string("ERROR: Could not play Sound with unkown ID! Name: ")+name;
		return 0;
	}
}


void cSound::pauseSound(string name)
{
	map<string, Mix_Chunk*>::iterator iterChunk = m_Chunks.find(name);
	map<string, Mix_Music*>::iterator iterMusic = m_Music.find(name);

	if (iterChunk != m_Chunks.end())
	{
		Mix_HaltChannel(1);
	}
	else if(iterMusic != m_Music.end())
	{
		Mix_PauseMusic();
	}
}


void cSound::resumeSound(string name)
{
	map<string, Mix_Chunk*>::iterator iterChunk = m_Chunks.find(name);
	map<string, Mix_Music*>::iterator iterMusic = m_Music.find(name);

	if (iterChunk != m_Chunks.end())
	{
		Mix_Resume(1);
	}
	else if(iterMusic != m_Music.end())
	{
		Mix_ResumeMusic();
	}
}

void cSound::muteSound(string name)
{
	map<string, Mix_Chunk*>::iterator iterChunk = m_Chunks.find(name);
	map<string, Mix_Music*>::iterator iterMusic = m_Music.find(name);

	if (iterChunk != m_Chunks.end())
	{
		if(Mix_Volume(1,-1) == 0) Mix_Volume(1,128);
		else Mix_Volume(1,0);
	}
	else if(iterMusic != m_Music.end())
	{
		Mix_VolumeMusic(0);
	}
}

void cSound::setVolume( string name, int vol )
{
	map<string, Mix_Chunk*>::iterator iterChunk = m_Chunks.find(name);
	map<string, Mix_Music*>::iterator iterMusic = m_Music.find(name);

	if (iterChunk != m_Chunks.end())
	{
		Mix_VolumeChunk(m_Chunks[name],vol);
	}
	else if(iterMusic != m_Music.end())
	{
	}
}

void cSound::setVolume(int vol)
{
	Mix_VolumeMusic(vol);
	Mix_Volume( -1, vol );
}


void cSound::pauseSounds()
{
	Mix_Pause(-1);
}

void cSound::resumeSounds()
{
	Mix_Resume(-1);
}

void cSound::muteSounds()
{
	if(Mix_Volume(-1,-1) == 0) Mix_Volume(-1,128);
	else Mix_Volume(-1,0);
}


Mix_Music* cSound::getSound( string name )
{
	map<string, Mix_Music*>::iterator iterMusic = m_Music.find(name);

	if(iterMusic != m_Music.end())
	{
		return m_Music[ name ];
	}
	return 0;
}

Mix_Chunk* cSound::getChunk( string name )
{
	map<string, Mix_Chunk*>::iterator iterChunk = m_Chunks.find(name);

	if(iterChunk != m_Chunks.end())
	{
		return m_Chunks[ name ];
	}
	return 0;
}