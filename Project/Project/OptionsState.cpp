
#include <iostream>
#include "OptionsState.h"

OptionsState::OptionsState() {
};


bool OptionsState::Enter() {

	return true;
};

void OptionsState::Exit() {

};

bool OptionsState::Update(float deltatime) {

	return false;	
};

void OptionsState::Draw() {
	
};

std::string OptionsState::Next() {
	
	return "MenuState";
};

bool OptionsState::IsType(const std::string &type) {
	return type.compare("OptionsState") == 0;
};