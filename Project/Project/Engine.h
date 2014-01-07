#pragma once

#include "Log.h"

class DrawManager;
class SpriteManager;
class DuckObject;
//class Level;
class Input;

class Engine {
public: 
	Engine();
	~Engine();

	bool Initialize();
	void Run();
	void Cleanup();

private:
	void UpdateEvents();
	void UpdateDeltatime();

private:
	struct SDL_Window *m_window;

	DrawManager *m_draw_manager;
	SpriteManager *m_sprite_manager;

	Log m_log;

	bool m_running;
	int m_width;
	int m_height;
	float m_deltatime;
	unsigned int m_ticks;

	DuckObject *m_duck;
	Input *m_input;
};