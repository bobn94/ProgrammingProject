#include <iostream>


#include "GameStateA.h"
#include "Level.h"


GameStateA::GameStateA() {
	m_level = nullptr;
};


bool GameStateA::Enter() {

	return true;
};

void GameStateA::Exit() {

};

bool GameStateA::Update(float deltatime, SpriteManager* m_sprite_manager) {

	return false;	
};

void GameStateA::Draw(DrawManager* m_draw_manager) {

};

std::string GameStateA::Next() {
	
	return "MenuState";
};

bool GameStateA::IsType(const std::string &type) {
	return type.compare("GameStateA") == 0;
};