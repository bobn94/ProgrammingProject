#include <iostream>
#include "GameStateB.h"


GameStateB::GameStateB() {
	
};


bool GameStateB::Enter() {
	
	return true;
};

void GameStateB::Exit() {
	
};

bool GameStateB::Update(float deltatime) {
	

	return false;	
};

void GameStateB::Draw() {
	
};

std::string GameStateB::Next() {
	
	return "MenuState";
};

bool GameStateB::IsType(const std::string &type) {
	return type.compare("GameStateB") == 0;
};