#pragma once

#include "Log.h"
#include "Vector2.h"

class DrawManager;
class SpriteManager;
class DuckObject;
class Collider;
class Level;
class Input;
class MenuState;
class OptionsState;

class SoundManager;
class MusicClip;

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

	bool LoadConfigFile(const std::string &filename);
private:
	struct SDL_Window *m_window;
	Level* m_level;
	DrawManager *m_draw_manager;
	SpriteManager *m_sprite_manager;
	MenuState *m_menu_state;
	OptionsState *m_options_state;

	
	Log m_log;
	
	bool m_menustate;
	bool m_gamestate;
	bool m_optionsstate;

	bool m_running;
	bool m_start;

	int m_width;
	int m_height;

	float m_deltatime;
	unsigned int m_ticks;
	Collider *m_collider;
	DuckObject *m_duck;
	Input *m_input;
	Vector2 m_duckPos;
	Vector2 m_duckExt;

	SoundManager *m_sound_manager;
	MusicClip *m_music;
};