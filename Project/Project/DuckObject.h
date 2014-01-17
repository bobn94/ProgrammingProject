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

	void setCurrentAnimation();

	void AddAnimation(const std::string &name, AnimatedSprite *sprite);

	void AddingAnimation(const std::string &name, AnimatedSprite *sprite);

	void CheckCollision();

	void ChangeDirections();

	void Randomize();

	float m_dir_x;
	float m_dir_y;
	float m_angle;

	float speed;

	int m_duckType;

	void SpawnDuck();
	bool m_isDuckSpawned;
	Vector2 m_duckPos;

	void GetAngle();

	void Timer(float deltatime);
	float m_timer; 

	Vector2 GetSpawnPosition();

	void LoadAnimations(SpriteManager *m_sprite_manager);
	
 
protected:
	AnimatedSprite *m_current_animation;
	std::map<std::string, AnimatedSprite*> m_animations;

	std::string m_current_animation_key;

private:
	Vector2 m_spawn_position;
};