#pragma once
 
#include <map>
#include <string>
#include "AnimatedSprite.h"
#include "GameObject.h"
 
class Sprite;
 
class DuckObject : public GameObject {
public:
	DuckObject(Sprite* sprite = nullptr, Collider* collider = nullptr, int flag = 0);

	void Update(float deltatime);

	void AddAnimation(const std::string &name, AnimatedSprite *sprite);
 
	void CheckCollision(int width);

	void Randomize();

	float m_dir_x;
	float m_dir_y;

	void SpawnDuck();
	bool m_isDuckSpawned;
	Vector2 m_duckPos;
	Vector2 m_duckExt;

	Vector2 GetSpawnPosition();
 
protected:
	AnimatedSprite *m_current_animation;
	std::map<std::string, AnimatedSprite*> m_animations;

private:
	Vector2 m_spawn_position;
};