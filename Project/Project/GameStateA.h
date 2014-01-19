#pragma once

#include "State.h"

class DrawManager;
class SpriteManager;
class Level;


class GameStateA : public State {
public:
	GameStateA();

	bool Enter();
	void Exit();
	bool Update(float deltatime, SpriteManager* m_sprite_manager);
	void Draw(DrawManager* m_draw_manager);
	std::string Next();
	bool IsType(const std::string &type);

private:
	Level* m_level;
};

