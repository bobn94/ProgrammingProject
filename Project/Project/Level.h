
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
	struct Cords{
		int x, y, w, h, f;
		
	};
public:
	Level();
	~Level();
	bool Load(const std::string &filename, SpriteManager *sprite_manager);
	
	void Draw(DrawManager *drawmanager);
	bool CheckCollision(GameObject *object, Vector2 &offset);
	void SpawnDuck(SpriteManager *sprite_manager);
	bool m_isDuckSpawned;
	Vector2 m_duckPos;
	Vector2 m_duckExt;
private:
	std::string m_spritemap_filename;
	std::map<char, Cords> m_tile_cords;
	std::map<char, Sprite*> m_sprite;
	std::vector<GameObject*> m_objects;
	int m_flag;

};