#include "DuckObject.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>

float Random(float min, float max) {
	return min + ((max - min) * ((float)rand() / (float)RAND_MAX));
};


DuckObject::DuckObject(Sprite* sprite, Collider* collider)
: GameObject(sprite, collider)
{	
	srand((unsigned int) time(0));
	m_current_animation_key = "blue_vertical";
	m_dir_x = 0.0f;
	m_dir_y = 0.0f;
	m_angle = 0.0f;
};


void DuckObject::Update(float deltatime) {
	
	const float speed = 350.0f;


	m_position.m_x += m_dir_x * deltatime * speed;
	m_position.m_y += m_dir_y * deltatime * speed;

	setCurrentAnimation();

	if(m_current_animation != nullptr) {
		m_current_animation->Update(deltatime);
		};
};

void DuckObject::setCurrentAnimation()
{
	if ((m_angle >= 80 && m_angle <= 100) || (m_angle <= -80 && m_angle >= -100))
	{
		//std::cout << "Vertical" << std::endl;
		m_current_animation_key = "blue_vertical";
	} else{
		//std::cout << "Horizontal" << std::endl;
		m_current_animation_key = "blue_horizontal";
	}

	m_current_animation = m_animations[m_current_animation_key];
}


void DuckObject::AddingAnimation(const std::string &name, AnimatedSprite *sprite) {
	m_animations.insert(std::pair<std::string,AnimatedSprite*>(name, sprite));
};

void DuckObject::AddAnimation(const std::string &name, AnimatedSprite *sprite) {
	m_animations.insert(std::pair<std::string,AnimatedSprite*>(name, sprite));
	if(m_sprite == nullptr) {
		m_sprite = sprite;
		m_current_animation = sprite;
	};
};


void DuckObject::CheckCollision(int width, int height) {
	if (m_position.m_y - 15.5f <= 0 || m_position.m_y >= 661){
		m_dir_y = -m_dir_y;
	} else if (m_position.m_x - 16.0f <= 0 || m_position.m_x + 128.0f>= width){
		m_dir_x = -m_dir_x;
	};
};

void DuckObject::SwitchDirections() {
	m_dir_x = Random(-1.0f, 1.0f) * 5.0f;
	m_dir_y = Random(-1.0f, 1.0f);
};

void DuckObject::Randomize() {
	m_dir_x = Random(-1.0f, 1.0f) * 5.0f;
	m_dir_y = Random(-1.0f, 1.0f);

	float length = sqrtf(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
	if (length < 0.0f) {
		m_dir_x /= length;
		m_dir_y /= length;
	}
	else {
		m_dir_x = 0.5f;
		m_dir_y = -1.0f;

		length = sqrtf(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
		m_dir_x /= length;
		m_dir_y /= length;
	};
};

void DuckObject::GetAngle() {
	m_angle = atan2f(-m_dir_y, m_dir_x);
	m_angle = m_angle * (180/3.1415);
};


void DuckObject::SpawnDuck(){
	m_duckPos.m_x = (float)(rand()%1000 + 24);
	m_duckPos.m_y = 500;
	if(!m_isDuckSpawned){

		m_isDuckSpawned = true;
	}
	m_spawn_position.m_x = 500;
	m_spawn_position.m_y = m_duckPos.m_y;
}

Vector2 DuckObject::GetSpawnPosition() {
	return m_spawn_position;
};