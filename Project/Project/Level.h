
#pragma once
#include <string>
#include <vector>
#include <map>
#include "Vector2.h"
class SpriteManager;
class Sprite;
class GameObject;
class DrawManager;
class Level{
	friend class Engine;
	struct Cords{
		int x, y, w, h, f;
		
	};
public:
	Level();
	~Level();
	void SpawnCrosshair(SpriteManager *sprite_manager);
	void UppdateCrosshair();
	void Draw(DrawManager *drawmanager);
	bool CheckCollision(GameObject *object, Vector2 &offset);
	void ChangeAmmo(bool set, int value);
	void DrawText(SDL_Surface* screen, const char* string, int size, int x, int y, int fgR, int fgG, int fgB, int bgR, int bgG, int bgB);	void SetScore(int score);
private:
	Vector2 m_crosshairPos;
	
	std::string m_spritemap_filename;
	std::map<char, Cords> m_tile_cords;
	std::map<char, Sprite*> m_sprite;
	std::vector<GameObject*> m_objects;
	int m_flag;
	int m_ammo;
	int m_score;
};
//765, 830 - Score Draw, 