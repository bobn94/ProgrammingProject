#include <iostream>
#include "MenuState.h"


MenuState::MenuState() {
	m_done = false;
};


bool MenuState::Enter() {
	return true;
};

void MenuState::Exit() {


};

bool MenuState::Update(float deltatime) {
	

	return !m_done;
};

void MenuState::Draw() {
};

std::string MenuState::Next() {
	return m_next_state;
};

bool MenuState::IsType(const std::string &type) {
	return type.compare("MenuState") == 0;
};