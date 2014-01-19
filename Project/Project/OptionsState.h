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
class GameObject;

class OptionsState : public State {
public:
	OptionsState();
	
	bool Enter();
	void Exit();
	bool Update(float deltatime, SpriteManager* m_sprite_manager);
	void Initialize(SpriteManager* m_sprite_manager);
	void Draw(DrawManager* m_draw_manager);
	std::string Next();
	bool IsType(const std::string &type);

	bool m_resetHighScore;
	bool m_changetoGameState;

	void SpawnMenuCrosshair(SpriteManager *sprite_manager);
	bool CheckCrosshairCollision(Vector2 &offset, SpriteManager* sprite_manager);

	void ResetHighscore();

	bool isOn;

private:

	Vector2 m_crosshairPos;
	Sprite* m_BackgroundSprite;
	std::vector<GameObject*> m_objects;

	GameObject *m_resethighscoretext;
	GameObject *m_gametext;

	bool m_GoGamestate;
	bool m_resetit;

	bool m_done;
	std::string m_next_state;
};

