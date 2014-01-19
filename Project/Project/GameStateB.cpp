#include <iostream>
#include "GameStateB.h"


GameStateB::GameStateB() {
	
};


bool GameStateB::Enter() {
	
	return true;
};

void GameStateB::Exit() {
	
};

bool GameStateB::Update(float deltatime, SpriteManager* m_sprite_manager) {
	

	return false;	
};

void GameStateB::Draw(DrawManager* m_draw_manager) {
	
};

std::string GameStateB::Next() {
	
	return "MenuState";
};

bool GameStateB::IsType(const std::string &type) {
	return type.compare("GameStateB") == 0;
};