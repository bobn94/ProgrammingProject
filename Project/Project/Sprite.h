#pragma once

struct SDL_Texture;
struct SDL_Surface;

class Sprite{
	friend class DrawManager;
	friend class SpriteManager;

public:
	Sprite(SDL_Surface *surface, SDL_Texture *texture, int x, int y, int width, int height);
protected:
	SDL_Surface *m_surface;
	SDL_Texture *m_texture;
	int m_x;
	int m_y;
	int m_height;
	int m_width;
};