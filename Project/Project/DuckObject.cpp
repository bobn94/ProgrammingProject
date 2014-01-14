#include "DuckObject.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
 

float Random(float min, float max) {
	return min + ((max - min) * ((float)rand() / (float)RAND_MAX));
};


DuckObject::DuckObject(Sprite* sprite, Collider* collider)
: GameObject(sprite, collider)
{
	//srand((unsigned int)time(0));	 seedar i Engine::Initzialize, koden överflödig
	m_dir_x = 0.0f;
	m_dir_y = 0.0f;
};


void DuckObject::Update(float deltatime) {
	Randomize();
	
	const float speed = 350.0f;

	//m_position.m_x += m_dir_x * deltatime * speed;
	//m_position.m_y += m_dir_y * deltatime * speed;

	if(m_current_animation != nullptr) {
		m_current_animation->Update(deltatime);
	};
};


void DuckObject::AddAnimation(const std::string &name, AnimatedSprite *sprite) {
	m_animations.insert(std::pair<std::string,AnimatedSprite*>(name, sprite));
	if(m_sprite == nullptr) {
		m_sprite = sprite;
		m_current_animation = sprite;
	};
};


void DuckObject::CheckCollision(int width, int height) {
	if (m_position.m_y - 132.0f <= 500 || m_position.m_y + 132.0f >= height){
		m_dir_y = -m_dir_y;
		}
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
		m_dir_x = 1.0f;
		m_dir_y = -1.0f;

		length = sqrtf(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
		m_dir_x /= length;
		m_dir_y /= length;
	};
};


void DuckObject::SpawnDuck(){
	//m_duckPos.m_x = (float)(rand()%1000 + 24);
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