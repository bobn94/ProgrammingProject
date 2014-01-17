
#include "Sprite.h"
#include "DrawManager.h"
#include <SDL.h>
#include <SDL_ttf.h>
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "sdl2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")
DrawManager::DrawManager(){
	m_renderer = nullptr;
}
	DrawManager::~DrawManager(){

	}

	bool DrawManager::Initialize(struct SDL_Window *window, int width, int height){
		m_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if(m_renderer == nullptr){
			return false;
		}
		return true;
	}
	void DrawManager::Cleanup(){
		if(m_renderer != nullptr){
			SDL_DestroyRenderer(m_renderer);
			m_renderer = nullptr;
		}
	}
	void DrawManager::Clear(){
		SDL_SetRenderDrawColor(m_renderer, 63, 191, 255, 255);//Background color
		SDL_RenderClear(m_renderer);
	}

	void DrawManager::Present(){
		SDL_RenderPresent(m_renderer);
	}
	void DrawManager::Draw(Sprite *sprite, int x, int y){
		SDL_Rect src = { sprite->m_x, sprite->m_y, sprite->m_width, sprite->m_height};
		SDL_Rect dst = { x, y, sprite->m_width, sprite->m_height};
		SDL_RenderCopy(m_renderer, sprite->m_texture, &src, &dst);
	}
	void DrawManager::Draw(SDL_Surface* surface, int x, int y)
{
    SDL_Rect src = surface->clip_rect;
    SDL_Rect dst = { x, y, surface->w, surface->h};
    SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);
    SDL_RenderCopy(m_renderer, texture, &src, &dst);
    SDL_DestroyTexture(texture);
}