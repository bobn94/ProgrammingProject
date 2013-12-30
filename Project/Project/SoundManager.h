#pragma once
#ifndef SOUNDMANAGER_H_INCLUDED
#define SOUNDMANAGER_H_INCLUDED

#include <SDL_mixer.h>
#include <vector>
#include <map>
#include <string>

class MusicClip;
class SoundClip;

class SoundManager {
public:
	SoundManager();
	~SoundManager();
	MusicClip* CreateMusic(std::string p_sPath);
	SoundClip* CreateSound(std::string p_sPath);
private:
	std::map<std::string, Mix_Music*> m_axMusic;
	std::map<std::string, Mix_Chunk*> m_axSounds;
	std::vector<MusicClip*> m_axMusicClips;
	std::vector<SoundClip*> m_axSoundClips;
};

#endif