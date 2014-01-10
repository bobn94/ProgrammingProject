
#include "Sprite.h"
#include "DrawManager.h"
#include <SDL.h>
#pragma comment(lib, "sdl2.lib")
#pragma comment(lib, "sdl2main.lib")
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
		SDL_SetRenderDrawColor(m_renderer, 63, 191, 255, 0xff);//Background color
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