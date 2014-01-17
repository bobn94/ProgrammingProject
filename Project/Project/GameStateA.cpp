#include <iostream>
#include "GameStateA.h"


GameStateA::GameStateA() {
	
};


bool GameStateA::Enter() {
	
	return true;
};

void GameStateA::Exit() {

};

bool GameStateA::Update(float deltatime) {

	return false;	
};

void GameStateA::Draw() {
	
};

std::string GameStateA::Next() {
	
	return "MenuState";
};

bool GameStateA::IsType(const std::string &type) {
	return type.compare("GameStateA") == 0;
};