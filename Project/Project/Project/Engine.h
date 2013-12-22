#pragma once

#include "Log.h"

class DuckObject;

class Engine {
public:
	Engine();
	~Engine();

	bool Initialize();
	void Run();
	void Cleanup();

private:
	void UpdateDeltatime();
	void UpdateEvents();

private:
	struct SDL_Window *m_window;
	struct SDL_Renderer *m_renderer;

	bool m_running;
	int m_width;
	int m_height;
	float m_deltatime;
	unsigned int m_ticks;

	Log m_log;
	DuckObject* m_duck;
};
