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
//	void Play(int amount, int duration);
	void Pause();
	void Stop();
//	void Fade (int from, int to, int duration); Example
private:
	Mix_Music* m_xClip;
	int m_iChannel;
};

#endif