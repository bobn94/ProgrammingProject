// SoundClip.h

#pragma once
#ifndef SOUNDCLIP_H_INCLUDED
#define SOUNDCLIP_H_INCLUDED

#include <SDL_mixer.h>

class SoundClip {
public:
	SoundClip();
	~SoundClip();
	SoundClip(Mix_Chunk* p_xClip);
	void Play();
	void Pause();
	void Stop();
private:
	Mix_Chunk* m_xClip;
	int m_iChannel;
};

#endif