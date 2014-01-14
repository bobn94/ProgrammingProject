#pragma once
 
#include <map>
#include <string>
#include "AnimatedSprite.h"
#include "SpriteManager.h"
#include "GameObject.h"
 
class Sprite;
class SpriteManager;
 
class DuckObject : public GameObject {
public:
	DuckObject(Sprite* sprite = nullptr, Collider* collider = nullptr);

	void Update(float deltatime);

	void AddAnimation(const std::string &name, AnimatedSprite *sprite);

	void AddingAnimation(const std::string &name, AnimatedSprite *sprite);

	void CheckCollision(int width, int height);

	void SwitchDirections();

	void GetAngle();

	void setCurrentAnimation();

	void Randomize();

	float m_dir_x;
	float m_dir_y;
	float m_angle;
	SpriteManager *_sprite_manager;

	void SpawnDuck();
	bool m_isDuckSpawned;
	Vector2 m_duckPos;
	Vector2 m_duckExt;

	Vector2 GetSpawnPosition();
 
protected:
	AnimatedSprite *m_current_animation;
	std::map<std::string, AnimatedSprite*> m_animations;

	std::string m_current_animation_key;

private:
	Vector2 m_spawn_position;
};