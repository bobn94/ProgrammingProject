#include "AnimatedSprite.h"

AnimatedSprite::AnimatedSprite(SDL_Surface *surface, SDL_Texture *texture, int x, int y, int width, int height)
: Sprite(surface, texture, x, y, width, height) {
	m_time = 0.0f;
	m_current_frame = 0;
};

void AnimatedSprite::Update(float deltatime) {
	m_time += deltatime;
	if(m_time >= m_animation[m_current_frame].duration) {
		m_time = 0.0f;
		m_current_frame = ++m_current_frame % m_animation.size();

		Frame &frame = m_animation[m_current_frame];
		m_x = frame.x;
		m_y = frame.y;
		m_width = frame.width;
		m_height = frame.height;
	};
};

void AnimatedSprite::AddFrame(Frame &frame) {
	m_animation.push_back(frame);
};