#include "SoundClip.h"

SoundClip::SoundClip() {
	m_xClip = nullptr;
	m_iChannel = -1;
};

SoundClip::~SoundClip() {
	m_xClip = nullptr;
	m_iChannel = -1;
};

SoundClip::SoundClip(Mix_Chunk* p_xClip) {
	m_xClip = nullptr;
	m_iChannel = -1;
};

void SoundClip::Play() {
	m_iChannel = Mix_PlayChannel(-1, m_xClip, 0);
};

void SoundClip::Pause() {
	if (m_iChannel == -1)
		return;

	if (Mix_Paused(m_iChannel))
	{
		Mix_Resume(m_iChannel);
	} else {
		Mix_Pause(m_iChannel);
	}
};

void SoundClip::Stop() {
	if (m_iChannel == -1)
	return;

	Mix_HaltChannel(m_iChannel);
	m_iChannel = -1;
};