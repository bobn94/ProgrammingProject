// SoundManager.cpp

#include "SoundManager.h"
#include "SoundClip.h"
#include "MusicClip.h"
#include <SDL_mixer.h>


SoundManager::SoundManager() {
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer :: Mix_OpenAudio %s\n", Mix_GetError());
	};

};

SoundManager::~SoundManager() {
	for (int i = 0; i<m_axSoundClips.size(); i++) {
		delete m_axSoundClips[i];
		m_axSoundClips[i] = nullptr;
	}
	m_axSoundClips.clear();

	for (int i = 0; i<m_axMusicClips.size(); i++) {
		delete m_axMusicClips[i];
		m_axMusicClips[i] = nullptr;
	}
	m_axMusicClips.clear();

	{std::map<std::string, Mix_Chunk*>::iterator xIt = m_axSounds.begin();
	while(xIt != m_axSounds.end()) {
		Mix_FreeChunk(xIt->second);
		xIt->second = nullptr;
		xIt++;
	}
	m_axSounds.clear();
	}

	{std::map<std::string, Mix_Music*>::iterator xIt = m_axMusic.begin();
	while(xIt != m_axMusic.end()) {
		Mix_FreeMusic(xIt->second);
		xIt->second = nullptr;
		xIt++;
	}
	m_axMusic.clear();
}
};

MusicClip* SoundManager::CreateMusic(std::string p_sPath) {
	MusicClip* xRet = nullptr;
	std::map<std::string, Mix_Music*>::iterator xIt = m_axMusic.find(p_sPath);
	if(xIt == m_axMusic.end()) { // Did not find the music clup in the map
		Mix_Music* xMusic = Mix_LoadMUS(p_sPath.c_str());
		std::pair<std::string, Mix_Music*> xPair;
		xPair = std::make_pair(p_sPath, xMusic);
		m_axMusic.insert(xPair);
		xRet = new MusicClip(xMusic);
	} else {
		xRet = new MusicClip(xIt->second);
	}

	m_axMusicClips.push_back(xRet);
	return xRet;
};

SoundClip* SoundManager::CreateSound(std::string p_sPath) {
	SoundClip* xRet = nullptr;
	std::map<std::string, Mix_Chunk*>::iterator xIt = m_axSounds.find(p_sPath);
	if(xIt == m_axSounds.end()) { // Did not find the sound chunk clup in the map
		Mix_Chunk* xSound = Mix_LoadWAV(p_sPath.c_str());
		std::pair<std::string, Mix_Chunk*> xPair;
		xPair = std::make_pair(p_sPath, xSound);
		m_axSounds.insert(xPair);
		xRet = new SoundClip(xSound);
	} else {
		xRet = new SoundClip(xIt->second);
	}

	m_axSoundClips.push_back(xRet);
	return xRet;
};

void SoundManager::PlayPause()
{
	if(m_axMusicClips[m_current]!=nullptr)
	{
		m_axMusicClips[m_current]->Pause();
	}
	
}

void SoundManager::Stop()
{
	m_axMusicClips[m_current]->Stop();
}


void SoundManager::PlayNext()
{
	m_axMusicClips[m_current]->Stop();
	m_current = (m_current + 1) % m_axMusicClips.size();
	m_axMusicClips[m_current]->Play();


}
void SoundManager::PlayPrev()
{

	m_axMusicClips[m_current]->Stop();
	m_current = (m_current - 1) % m_axMusicClips.size();
	m_axMusicClips[m_current]->Play();


}


MusicClip* SoundManager::GetMusicClip()
{
	return m_axMusicClips[m_current];    
}