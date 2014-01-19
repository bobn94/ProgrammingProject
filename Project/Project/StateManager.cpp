#include <iostream>
#include "State.h"
#include "StateManager.h"

StateManager::StateManager() {
	m_current = nullptr;
};

StateManager::~StateManager() {
	auto it = m_states.begin();
	while(it != m_states.end()) {
		delete (*it);
		++it;
	};
};

void StateManager::Attach(State *state) {
	m_states.push_back(state);
};

void StateManager::Update(float deltatime, SpriteManager* m_sprite_manager) {
	if(m_current == nullptr) { return; };
	if(!m_current->Update(deltatime, m_sprite_manager)) {
		ChangeState();
	};
};

void StateManager::Draw(DrawManager* m_draw_manager) {
	if(m_current == nullptr) { return; };
	m_current->Draw(m_draw_manager);
};

void StateManager::SetState(const std::string &type){
	for (unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(type)) {
			m_current = m_states[i];
			m_current->Enter();
			return;
		};
	};
};

void StateManager::ChangeState() {
	std::string next = m_current->Next();
	if (m_current != nullptr) {
		m_current->Exit();
		m_current= nullptr;
	};

	for (unsigned int i = 0; i < m_states.size(); i++) {
		if(m_states[i]->IsType(next)) {
			m_current = m_states[i];
			m_current->Enter();
			return;
		};
	};
};

bool StateManager::IsRunning() {
	return m_current != nullptr;
};