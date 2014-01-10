#pragma once

#include "Log.h"
#include "Vector2.h"

class DrawManager;
class SpriteManager;
class DuckObject;
class Collider;
class Level;
class Input;

class Engine {
public: 
	Engine();
	~Engine();

	bool Initialize();
	void Run();
	void Cleanup();
	
	bool m_isDuckSpawned;
private:
	void UpdateEvents();
	void UpdateDeltatime();
	void SpawnDuck();
private:
	struct SDL_Window *m_window;
	Level* m_level;
	DrawManager *m_draw_manager;
	SpriteManager *m_sprite_manager;

	Log m_log;
	
	bool m_running;
	int m_width;
	int m_height;
	float m_deltatime;
	unsigned int m_ticks;
	Collider *m_collider;
	DuckObject *m_duck;
	Input *m_input;
	Vector2 m_duckPos;
	Vector2 m_duckExt;
};