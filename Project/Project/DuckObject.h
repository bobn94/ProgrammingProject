#pragma once
 
#include <map>
#include <string>
#include "Vector2.h"
#include <vector>
#include "AnimatedSprite.h"
#include "GameObject.h"
 
class Sprite;
 
class DuckObject : public GameObject {
public:
	DuckObject(Sprite* sprite = nullptr, Collider* collider = nullptr, int flag = 0);

	void Update(float deltatime);

	void AddAnimation(const std::string &name, AnimatedSprite *sprite);
 
	void CheckCollision(int width);


	float m_dir_x;
	float m_dir_y;

protected:
	AnimatedSprite *m_current_animation;
	std::map<std::string, AnimatedSprite*> m_animations;
};