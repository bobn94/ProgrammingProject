#pragma once

#include "Sprite.h"
#include <vector>

class Animation : public Sprite {
public:
	Animation(SDL_Surface *surface, SDL_Texture *texture, int x, int y, int width, int height);


	struct Frame {
		float duration;
		int x, y, width, height;
	};


	void Update(float deltatime);
	void AddFrame(Frame &frame);

private:
	float m_time;
	int m_current_frame;
	std::vector<Frame> m_animation;
};
