#include <SDL.h>
#include <iostream>
#pragma comment (lib, "sdl2.lib")
#pragma comment(lib, "sdl2main.lib")

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Level.h"
#include "DuckObject.h"
#include "Engine.h"

Engine::Engine() : m_log("log.txt") {
	m_window = nullptr;

	m_draw_manager = nullptr;
	m_sprite_manager = nullptr;

	m_running = false;
	m_width = 0;
	m_height = 0;
	m_deltatime = 0.01f;
	m_ticks = SDL_GetTicks();

	m_duck = nullptr;
};

Engine::~Engine() {
};

bool Engine::Initialize() {
	m_width = 1024;
	m_height = 960;

	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("DuckHunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height,
		SDL_WINDOW_OPENGL);

	m_draw_manager = new DrawManager;
	if(!m_draw_manager->Initialize(m_window, m_width, m_height)) {
		return false;
	};

	m_sprite_manager = new SpriteManager(m_draw_manager);
	if(!m_sprite_manager->Initialize("../data/sprites/")){
		return false;
	};

	if(m_window == nullptr) { return false; };

	/*Sprite* sprite = m_sprite_manager->Load("p2_spritesheet.png", 0, 0, 70, 70);
	m_duck = new DuckObject(sprite);*/
	
	
	m_running = true;

	return true;
};

void Engine::Run() {
	while(m_running) {
		UpdateDeltatime();
		UpdateEvents();

		//m_duck->Update(m_deltatime);
	
		Vector2 offset;

		m_draw_manager->Clear();
		Sprite* sprite = m_sprite_manager->Load("background3.png", 0, 0, 1024, 960);
		m_draw_manager->Draw(sprite, 0, 0);
		/*sprite = m_sprite_manager->Load("duck_hunt_sprites2.png", 40, 200, 1024, 472);
		m_draw_manager->Draw(sprite, 75, 777);*/
		/*m_draw_manager->Draw(
			m_duck->GetSprite(),
			m_duck->GetPosition().m_x,
			m_duck->GetPosition().m_y);
			*/
		m_draw_manager->Present();

		SDL_Delay(10);
	};
};

void Engine::Cleanup() {
	if(m_window != nullptr) {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	};
};


void Engine::UpdateDeltatime() {
	unsigned int ticks = SDL_GetTicks();
	unsigned int delta = ticks - m_ticks;
	m_ticks = ticks;
	m_deltatime = (float)delta * 0.001f;
	if(m_deltatime > 0.1f) {
		m_deltatime = 0.1f;
	};
};

void Engine::UpdateEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			m_running = false;
		}
		/*if(event.type == SDL_MOUSEBUTTONDOWN){
			if(m_level->CheckCollision(m_player, offset)){
				m_player->SetPosition(offset + m_player->GetPosition());
				
			}
		}*/
	};
};