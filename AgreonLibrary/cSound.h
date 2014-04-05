/**
*	@file cSound.h
*
*	@brief This file contains the cSound class.
*/
#pragma once

#include "Agreon.h"
#include "globals.h"

/**
*	@brief Manages the sound.
*
*	You can either load a Sound or Music. Contains many functions to manage the sound.
*/
class cSound
{
private:
	map< string, Mix_Chunk* > m_Chunks;
	map< string, Mix_Music* > m_Music;
public:
	/**
	*	Initializes the Sound.
	*/
	cSound();

	/**
	*	Deletes the data.
	**/
	~cSound();
	
	/**
	*	Loads a sound file in .wav format.
	*	
	*	@param	path	The path of the sound file.
	*	@param	name	The name of the sound.
	*/
	bool loadSound( const char* path, string name );

	/**
	*	Loads a music file in .mp3 format.
	*	
	*	@param	path	The path of the music file.
	*	@param	name	The name of the music.
	*/
	bool loadMusic( const char* path, string name );

	/**
	*	Plays a sound or music.
	*	
	*	@param name The name of the sound or music.
	*
	*	@returns the channel of the sound or music
	*/
	int playSound( string name );

	/**
	*	Pauses a sound or music.
	*	
	*	@param name The name of the sound or music.
	*/
	void pauseSound( string name );

	/**
	*	Resumes a sound or music.
	*	
	*	@param name The name of the sound or music.
	*/
	void resumeSound( string name );

	/**
	*	Mutes a sound or music.
	*	
	*	@param name The name of the sound or music.
	*/
	void muteSound( string name );

	/**
	*	Sets the volume of a sound or music.
	*	
	*	@param name The name of the sound or music.
	*	@param vol	The volume.
	*/
	void setVolume( string name, int vol );

	/**
	*	Pauses all Sounds.
	*/
	void pauseSounds();

	/**
	*	Resumes all Sounds.
	*/
	void resumeSounds();

	/**
	*	Mutes all Sounds.
	*/
	void muteSounds();

	/**
	*	Sets the main volume.
	*
	*	@param vol The volume.
	*/
	void setVolume( int vol);

	/**
	*	@param name	The name of the sound.
	*	@returns the sound object.
	*/
	Mix_Music* getSound( string name );

	/**
	*	@param name	The name of the chunk.
	*	@returns the chunk object.
	*/
	Mix_Chunk* getChunk( string name );

};

