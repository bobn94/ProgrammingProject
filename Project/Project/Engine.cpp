#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#pragma comment (lib, "sdl2.lib")
#pragma comment(lib, "sdl2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Collider.h"
#include "Level.h"
#include "DuckObject.h"
#include "Engine.h"
#include "Input.h"

#include "StateManager.h"

#include "MenuState.h"
#include "GameStateA.h"
#include "GameStateB.h"
#include "OptionsState.h"


Engine::Engine() : m_log("log.txt") {
	m_window = nullptr;
	m_level = nullptr;
	m_draw_manager = nullptr;
	m_sprite_manager = nullptr;
	//m_mouse = nullptr;
	//m_keyboard = nullptr;
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
	m_window = SDL_CreateWindow("Duck Hunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height,
		SDL_WINDOW_OPENGL);

	if(m_window == nullptr) { return false; };

	m_draw_manager = new DrawManager;
	if(!m_draw_manager->Initialize(m_window, m_width, m_height)) {
		return false;
	};

	m_sprite_manager = new SpriteManager(m_draw_manager);
	if(!m_sprite_manager->Initialize("../data/sprites/")){
		return false;
	};


	m_level = new Level;
	m_level->InitLevel(m_sprite_manager);
	
	
	SDL_ShowCursor( SDL_DISABLE );
	m_running = true;
	
	return true;
};

void Engine::Run() {
	StateManager mgr;
		mgr.Attach(new MenuState());
		mgr.Attach(new GameStateA());
		mgr.Attach(new GameStateB());
		mgr.Attach(new OptionsState());
		mgr.SetState("GameStateA");	

	while(m_running) {
	while (mgr.IsRunning()) {
		UpdateDeltatime();
		UpdateEvents();

		m_draw_manager->Clear();		

	if(!mgr.m_current->IsType("GameStateA")) {
		mgr.Update(0.01f, m_sprite_manager);
		mgr.Draw(m_draw_manager);
		}

		if(mgr.m_current->IsType("GameStateA")) {
		m_level->UpdateLevel(m_deltatime, m_sprite_manager);
		m_level->Draw(m_draw_manager);
			}
		
		m_draw_manager->Present();

		SDL_Delay(10);
		};	
	};
};

void Engine::Cleanup() {
	if(m_duck != nullptr) {
		delete m_duck->GetSprite();
		delete m_duck->GetCollider();
		delete m_duck;
		m_duck = nullptr;
	};

	if(m_level != nullptr) {
		delete m_level;
		m_level = nullptr;
	};

	if(m_sprite_manager != nullptr) {
		m_sprite_manager->Cleanup();
		delete m_sprite_manager;
		m_sprite_manager = nullptr;
	};

	if(m_draw_manager != nullptr) {
		m_draw_manager->Cleanup();
		delete m_draw_manager;
		m_draw_manager = nullptr;
	};

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
		if(event.type == SDL_MOUSEBUTTONDOWN){
			Vector2 offset;
			if(m_level->CheckCollision(offset, m_sprite_manager)){
				//m_duck->SetPosition(offset + m_duck->GetPosition());
				
			}
		}
	};
};