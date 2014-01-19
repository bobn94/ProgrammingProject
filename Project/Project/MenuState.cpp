#include <fstream>
#include <SDL.h>
#include <sstream>
#include "Level.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "GameObject.h"
#include "DuckObject.h"
#include "Collider.h"
#include "MenuState.h"


MenuState::MenuState() {
	m_done = false;
};


bool MenuState::Enter() {
	return true;
};

void MenuState::Exit() {


};

bool MenuState::Update(float deltatime, SpriteManager* m_sprite_manager) {
	

	return !m_done;
};

void MenuState::Draw(DrawManager* m_draw_manager) {
	SDL_Color m_foregroundColor = { 255, 255, 255 };		//Sätter Textfärg till vit
	SDL_Color m_backgroundColor = { 0, 0, 0 };			//sätter Bakgrundsfärg till svart
	TTF_Font* m_font = TTF_OpenFont("../data/fonts/emulogic.ttf", 25);
	SDL_Surface* screen = TTF_RenderText_Shaded(m_font, "Menu", m_foregroundColor, m_backgroundColor);
	//m_draw_manager->Draw(screen, 765, 830);
};

std::string MenuState::Next() {
	return m_next_state;
};

bool MenuState::IsType(const std::string &type) {
	return type.compare("MenuState") == 0;
};