
#pragma once
#include <string>
#include <vector>
#include <map>
#include <SDL_ttf.h>
#include "Vector2.h"
#include "DuckObject.h"


class SpriteManager;
class Sprite;
class GameObject;
class DrawManager;
class Mouse;

class Level{
	friend class Engine;
	struct Cords{
		int x, y, w, h, f;
		
	};
public:
	Level();
	~Level();
	void SpawnCrosshair(SpriteManager *sprite_manager);
	
	void InitLevel(SpriteManager *sprite_manager);
	
	void UpdateLevel(float deltatime, SpriteManager* spritemanager);
	
	void Draw(DrawManager *drawmanager);
	
	bool CheckCollision(Vector2 &offset, SpriteManager* sprite_manager, float deltatime);
	
	void ChangeAmmo(bool set, int value);
	
	void DrawText(SDL_Surface* screen, const char* string, int size, int x, int y, int fgR, int fgG, int fgB, int bgR, int bgG, int bgB);
	
	void SetScore(int score);
	
	void DrawLevel();
	
	void DeleteDuck();
	
	void SpawnDuck(SpriteManager *spritemanager);

	void Defeat();

	void Victory();

	void CheckHighscore();

private:
	
	Vector2 m_crosshairPos;
	Sprite* m_FlyAway;
	Sprite* m_FlyAwayBG;
	Sprite* m_BackgroundSprite;
	Sprite* m_DucksHitSprite;

	Sprite* m_Ammo3Sprite;
	Sprite* m_Ammo2Sprite;
	Sprite* m_Ammo1Sprite;
	Sprite* m_Ammo0Sprite;

	Sprite* m_RedDuckSprite;
	Sprite* m_WhiteDuckSprite;

	DuckObject *m_duck;

	Mouse* m_mouse;

	std::string m_spritemap_filename;
	std::map<char, Sprite*> m_sprite;
	std::vector<GameObject*> m_objects;

	int m_flag;
	int m_ammo;
	int m_score;
	int m_currentRound;
	char m_ducksHit[10];
	int m_currentDuck;
	bool m_isDuckSpawned;
	bool shouldEnd;
};