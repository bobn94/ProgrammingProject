#pragma once
#include <string>
#include <vector>
#include <map>
#include <SDL_ttf.h>
#include "Vector2.h"
#include "State.h"
#include "SpriteManager.h"
#include "DrawManager.h"

class SpriteManager;
class Sprite;
class DrawManager;

class MenuState : public State {
public:
	MenuState();
	
	bool Enter();
	void Exit();
	bool Update(float deltatime, SpriteManager* m_sprite_manager);
	void Draw(DrawManager* m_draw_manager);
	std::string Next();
	bool IsType(const std::string &type);

private:
	bool m_done;
	std::string m_next_state;
};

