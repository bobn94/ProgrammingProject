// MusicClip.h

#pragma once
#ifndef MUSICCLIP_H_INCLUDED
#define MUSICCLIP_H_INCLUDED

#include <SDL_mixer.h>

class MusicClip {
public:
	MusicClip();
	~MusicClip();
	MusicClip(Mix_Music* p_xClip);
	void Play();
	void Pause();
	void Stop();
private:
	Mix_Music* m_xClip;
	int m_iChannel;
};

#endif