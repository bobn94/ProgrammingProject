#include <SDL.h>
#pragma comment(lib,"sdl2.lib")
#pragma comment(lib,"sdl2main.lib")

#include "Engine.h"

Engine::Engine() : m_log("log.txt") {
	m_window = nullptr;

	m_running = false;
	m_width = 0;
	m_height = 0;
	m_deltatime = 0.01f;
	m_ticks = SDL_GetTicks();
};

Engine::~Engine() {
};

bool Engine::Initialize() {
	m_width = 256;
	m_height = 240;

	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("DuckHunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height,
		SDL_WINDOW_OPENGL);

	m_renderer = SDL_CreateRenderer(m_window, -1,
		SDL_RENDERER_ACCELERATED);

	if(m_window == nullptr) { return false; };

	m_running = true;

	return true;
};

void Engine::Run() {
	while(m_running) {
		UpdateDeltatime();
		UpdateEvents();


		SDL_SetRenderDrawColor(m_renderer, 60, 190, 255, 255);
		SDL_RenderClear(m_renderer);
		SDL_RenderPresent(m_renderer);
		};
		SDL_Delay(10);
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
	};
};