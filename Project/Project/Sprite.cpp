#include "Sprite.h"
#include "SpriteManager.h"

Sprite::Sprite(SDL_Surface *surface, SDL_Texture *texture, int x, int y, int width, int height){
	m_surface = surface;
	m_texture = texture;
	m_x = x;
	m_y = y;
	m_width = width;
	m_height = height;
}
