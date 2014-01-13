#include "DuckObject.h"
#include <ctime>
#include <cmath>
#include <cstdlib>
 

DuckObject::DuckObject(Sprite* sprite, Collider* collider, int flag)
: GameObject(sprite, collider, flag)
{
	srand((unsigned int)time(0));	
	m_dir_x = 0.0f;
	m_dir_y = 0.0f;
};


void DuckObject::Update(float deltatime) {
	const float speed = 200.0f;
	m_position.m_y = deltatime * speed;
/*	if(m_current_animation != nullptr) {
		m_current_animation->Update(deltatime);
	};*/
};


void DuckObject::AddAnimation(const std::string &name, AnimatedSprite *sprite) {
	m_animations.insert(std::pair<std::string,AnimatedSprite*>(name, sprite));
	if(m_sprite == nullptr) {
		m_sprite = sprite;
		m_current_animation = sprite;
	};
};


void DuckObject::CheckCollision(int width) {
	if (m_position.m_y /*- m_size*/ <= 0 || m_position.m_y /*+ m_size*/ >= 0){ //Grassheight!
		m_dir_y = -m_dir_y;
		}
};