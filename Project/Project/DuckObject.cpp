#include "DuckObject.h"

#include <ctime>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <SDL_render.h>

float Random(float min, float max) {
	return min + ((max - min) * ((float)rand() / (float)RAND_MAX));
};

DuckObject::DuckObject(Sprite* sprite, Collider* collider)
: GameObject(sprite, collider)
{
	srand((unsigned int) time(0));
	m_current_animation_key = "horizontal";
	m_dir_x = 0.0f;
	m_dir_y = 0.0f;
	m_angle = 0.0f;
	m_duckType = (rand() %6+1);
	m_timer = 0.0f;

	spawnDuck = false;
	isHit = false;
	isMissed = false;
};

void DuckObject::Update(float deltatime) {
	if (m_duckType >= 0 && m_duckType <= 3) {
		speed = 400.0f;
	}
	else if (m_duckType >= 4 && m_duckType <= 5) {
		speed = 500.0f;
	}
	else {
		speed = 700.0f;
	}


	if (!isHit) {
		if(m_position.m_y < 500) {
			if(!spawnDuck){	
			spawnDuck = true;
			}
		}
		if (spawnDuck) {
			CheckCollision();
			ChangeDirections();
		};
	setCurrentAnimation();
	};
	
	if (isHit) {
		Death();
	}
	if(isMissed){
		FlyAway();
	}


	m_position.m_x += m_dir_x * deltatime * speed;
	m_position.m_y += m_dir_y * deltatime * speed;
	
	if(HasCollider()) {
		m_collider->m_position = m_position;
	};

	if(m_current_animation != nullptr) {
		m_current_animation->Update(deltatime);
	}

};

void DuckObject::setCurrentAnimation(){

	if (m_angle > -0 && m_angle <= 63)
	{
		m_current_animation_key = "diagonal";
	} 
	else if (m_angle >= 116 && m_angle <= 180) {

		m_current_animation_key = "diagonal_flip";
	}
	else if (m_angle < 116 && m_angle > 63) {

		m_current_animation_key = "vertical";
	}
	else if (m_angle <= -90 && m_angle >= -180){

		m_current_animation_key = "horizontal_flip";
	}
	
	else{
		m_current_animation_key = "horizontal";
	}

	m_current_animation = m_animations[m_current_animation_key];
	m_sprite = m_animations[m_current_animation_key];

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

void DuckObject::CheckCollision() {
	if (m_position.m_y - 15.5f <= 0 || m_position.m_y >= 500){
		m_dir_y = -m_dir_y;
	} else if (m_position.m_x - 16.0f <= 0 || m_position.m_x + 128.0f>= 1024){
		m_dir_x = -m_dir_x;
	}
};

void DuckObject::ChangeDirections () {
		if (m_timer > 1.0f) {
			m_dir_x = Random(1.0f, 1.0f) * 5.0f;
			m_dir_y = Random(-0.5f, 1.0f);

			float length = sqrtf(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
			m_dir_x /= length;
			m_dir_y /= length;

			m_timer = 0;
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
		m_dir_x = 0.0f;
		m_dir_y = -1.0f;

		length = sqrtf(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
		m_dir_x /= length;
		m_dir_y /= length;

	};

};

void DuckObject::Death() {
	if (m_timer < 1.0f) {
		m_timer = 3;
	}
	if (m_timer >= 3.0f && m_timer <= 3.5f) {
		m_current_animation_key = "hit";
		m_current_animation = m_animations[m_current_animation_key];
		m_sprite = m_animations[m_current_animation_key];
		m_dir_x = 0.0f;
		m_dir_y = 0.0f;
		
	} else if (m_timer > 3.5f) {
		m_current_animation_key = "death";
		m_current_animation = m_animations[m_current_animation_key];
		m_sprite = m_animations[m_current_animation_key];
		m_dir_x = 0.0f;
		m_dir_y = 1.0f;

		float length = sqrtf(m_dir_x * m_dir_x + m_dir_y * m_dir_y);
		m_dir_y /= length;
	};
}

void DuckObject::GetAngle() {
	m_angle = atan2f(-m_dir_y, m_dir_x);
	m_angle = m_angle * (180/3.1415);
};

Vector2 DuckObject::GetSpawnPosition() {
	m_spawn_position.m_x = (float)(rand()%800+1);
	m_spawn_position.m_y = 650.0f;
	return m_spawn_position;
};

void DuckObject::Timer(float deltatime) {
		m_timer += deltatime;
};

void DuckObject::LoadAnimations(SpriteManager *m_sprite_manager) {	
	if(m_duckType >= 0 && m_duckType <= 3) {
		AnimatedSprite* sprite = m_sprite_manager->Load("../data/animations/black_horizontal.txt");
		AddAnimation("horizontal", sprite);
		
		sprite = m_sprite_manager->Load("../data/animations/black_vertical.txt");
		AddAnimation("vertical", sprite);
			
		sprite = m_sprite_manager->Load("../data/animations/black_diagonal.txt");
		AddAnimation("diagonal", sprite);
			
		sprite = m_sprite_manager->Load("../data/animations/black_death.txt");
		AddAnimation("death", sprite);

		//flipped
		sprite = m_sprite_manager->Load("../data/animations/black_horizontal_flip.txt");
		AddAnimation("horizontal_flip", sprite);
			
		sprite = m_sprite_manager->Load("../data/animations/black_diagonal_flip.txt");
		AddAnimation("diagonal_flip", sprite);
			
		sprite = m_sprite_manager->Load("../data/animations/black_hit.txt");
		AddAnimation("hit", sprite);
	}

	else if (m_duckType >= 4 && m_duckType <= 5) {
		AnimatedSprite* sprite = m_sprite_manager->Load("../data/animations/blue_horizontal.txt");
		AddAnimation("horizontal", sprite);
		
		sprite = m_sprite_manager->Load("../data/animations/blue_vertical.txt");
		AddAnimation("vertical", sprite);
			
		sprite = m_sprite_manager->Load("../data/animations/blue_diagonal.txt");
		AddAnimation("diagonal", sprite);

		sprite = m_sprite_manager->Load("../data/animations/blue_death.txt");
		AddAnimation("death", sprite);
		
		//flipped
		sprite = m_sprite_manager->Load("../data/animations/blue_horizontal_flip.txt");
		AddAnimation("horizontal_flip", sprite);
	
			
		sprite = m_sprite_manager->Load("../data/animations/blue_diagonal_flip.txt");
		AddAnimation("diagonal_flip", sprite);

		sprite = m_sprite_manager->Load("../data/animations/blue_hit.txt");
		AddAnimation("hit", sprite);
	}

	else {
		AnimatedSprite* sprite = m_sprite_manager->Load("../data/animations/red_horizontal.txt");
		AddAnimation("horizontal", sprite);
		
		sprite = m_sprite_manager->Load("../data/animations/red_vertical.txt");
		AddAnimation("vertical", sprite);

		sprite = m_sprite_manager->Load("../data/animations/red_diagonal.txt");
		AddAnimation("diagonal", sprite);

		sprite = m_sprite_manager->Load("../data/animations/red_death.txt");
		AddAnimation("death", sprite);

		//flipped
		sprite = m_sprite_manager->Load("../data/animations/red_horizontal_flip.txt");
		AddAnimation("horizontal_flip", sprite);

		sprite = m_sprite_manager->Load("../data/animations/red_diagonal_flip.txt");
		AddAnimation("diagonal_flip", sprite);

		sprite = m_sprite_manager->Load("../data/animations/red_hit.txt");
		AddAnimation("hit", sprite);
	}
	
}
void DuckObject::FlyAway(){
	m_current_animation_key = "vertical";
	m_current_animation = m_animations[m_current_animation_key];
		m_sprite = m_animations[m_current_animation_key];
		m_dir_x = 0.0f;
		m_dir_y = -1.0f;
		if(m_position.m_y <= -400){
			isMissed = false;
		}
}