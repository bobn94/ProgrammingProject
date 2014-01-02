#pragma once

#include <map>
#include <string>
#include "Animation.h"
#include "GameObject.h"

class Sprite;

class DuckObject : public GameObject {
public:
	DuckObject(Sprite* sprite = nullptr);

	void Update(float deltatime);

	void AddAnimation(const std::string &name, Animation *sprite);

protected:

	Animation *m_current_animation;
	std::map<std::string, Animation*> m_animations;
};