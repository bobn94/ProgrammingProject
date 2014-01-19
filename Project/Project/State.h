#pragma once
#include <string>

class SpriteManager;
class DrawManager;

class State {
public:
	virtual ~State() {};
	virtual bool Enter() = 0;
	virtual void Exit() = 0;
	virtual bool Update(float deltatime, SpriteManager* m_sprite_manager) = 0;
	virtual void Draw(DrawManager* m_draw_manager) = 0;
	virtual std::string Next() = 0;
	virtual bool IsType(const std::string &type) = 0;
};
