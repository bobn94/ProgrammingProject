
#include <iostream>
#include "OptionsState.h"

OptionsState::OptionsState() {
};


bool OptionsState::Enter() {

	return true;
};

void OptionsState::Exit() {

};

bool OptionsState::Update(float deltatime, SpriteManager* m_sprite_manager) {

	return false;	
};

void OptionsState::Draw(DrawManager* m_draw_manager) {
	
};

std::string OptionsState::Next() {
	
	return "MenuState";
};

bool OptionsState::IsType(const std::string &type) {
	return type.compare("OptionsState") == 0;
};