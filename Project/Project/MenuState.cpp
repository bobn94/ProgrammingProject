#include <iostream>

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
#include "StateManager.h"


MenuState::MenuState() {
	m_done = false;
	m_changetoGameState = false;
	m_changetoOptionsState = false;

	auto it = m_objects.begin();
	while(it != m_objects.end()){
		delete (*it)->GetSprite();
		//delete (*it)->GetCollider();
		delete (*it);
		++it;
	}
};


bool MenuState::Enter() {
	return true;
};

void MenuState::Exit() {


};

bool MenuState::Update(float deltatime, SpriteManager* m_sprite_manager) {
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_crosshairPos.m_x = x -16;
	m_crosshairPos.m_y = y -16;
	m_objects[0]->SetPosition(m_crosshairPos);
	m_objects[0]->m_collider->m_position = m_crosshairPos;
	return !m_done;
};

void MenuState::Initialize(SpriteManager* m_sprite_manager) {
	SpawnMenuCrosshair(m_sprite_manager);
	
	m_BackgroundSprite = m_sprite_manager->Load("Menubackground.png", 0, 0, 1024, 960);


	Sprite *sprite = m_sprite_manager->Load("startgamecollider.png", 0, 0, 354, 41);
	Collider *collider = new Collider;
	collider->m_position = Vector2(350, 550);
	collider->m_extention = Vector2(245, 41);
	m_startgametext = new GameObject(sprite, collider);
	m_startgametext->SetPosition(Vector2(350, 550));

	sprite = m_sprite_manager->Load("optionscollider.png", 0, 0, 245, 39);
	collider = new Collider;
	collider->m_position = Vector2(400, 635);
	collider->m_extention = Vector2(245, 39);
	m_optionstext = new GameObject(sprite, collider);
	m_optionstext->SetPosition(Vector2(400, 635));

}

void MenuState::Draw(DrawManager* m_draw_manager) {
	TTF_Init();
	
	m_draw_manager->Draw(m_BackgroundSprite, 0, 0);

	
	TTF_Font* m_font = TTF_OpenFont("../data/fonts/duckhunt.ttf", 250);
	SDL_Color m_foregroundColor = { 72, 205, 222 };
	SDL_Color m_backgroundColor = { 0, 0, 0 };
	SDL_Surface* screen = TTF_RenderText_Shaded(m_font, "Duck", m_foregroundColor, m_backgroundColor);
	m_draw_manager->Draw(screen, 170, 100);
	SDL_FreeSurface(screen);
	screen = TTF_RenderText_Shaded(m_font, "Hunt", m_foregroundColor, m_backgroundColor);
	m_draw_manager->Draw(screen, 320, 300);
	SDL_FreeSurface(screen);


	SDL_Color m_foregroundColor2 = { 255, 255, 255 };
	m_font = TTF_OpenFont("../data/fonts/emulogic.ttf", 35);
	screen = TTF_RenderText_Shaded(m_font, "Start Game", m_foregroundColor2, m_backgroundColor);
	m_draw_manager->Draw(screen, 350, 550);
	SDL_FreeSurface(screen);


	screen = TTF_RenderText_Shaded(m_font, "Options", m_foregroundColor2, m_backgroundColor);
	m_draw_manager->Draw(screen, 400, 630);
	SDL_FreeSurface(screen);


	m_draw_manager->Draw(
		m_startgametext->GetSprite(),
		m_startgametext->GetPosition().m_x,
		m_startgametext->GetPosition().m_y);

	m_draw_manager->Draw(
		m_optionstext->GetSprite(),
		m_optionstext->GetPosition().m_x,
		m_optionstext->GetPosition().m_y);


	int highscore[10];
	std::ifstream stream("../data/score/score.txt");
	if(!stream.is_open()){
		return;
	}


	std::string row;
	unsigned int cords_count = 0;
	stream >> cords_count;
	std::getline(stream, row);
	for(unsigned int i = 0; i < cords_count; i++){
		std::getline(stream, row);
		std::stringstream ss(row);
		std::string ch;
		int score;
		ss >> ch;
		ss >> highscore[i];
	}
	


	std::stringstream hisc;

	hisc <<  highscore[0];

	SDL_Color m_foregroundColor3 = { 64, 228, 48 };
	screen = TTF_RenderText_Shaded(m_font, "Highscore: ", m_foregroundColor3, m_backgroundColor);
	m_draw_manager->Draw(screen, 230, 750);
	SDL_FreeSurface(screen);
	screen = TTF_RenderText_Shaded(m_font, hisc.str().c_str(), m_foregroundColor3, m_backgroundColor);
	m_draw_manager->Draw(screen, 630, 750);
	SDL_FreeSurface(screen);


	for(auto i = 0UL; i < m_objects.size(); i++){
		m_draw_manager->Draw(m_objects[i]->GetSprite(), 
			m_objects[i]->GetPosition().m_x, 
			m_objects[i]->GetPosition().m_y);

	}

	
	TTF_Quit();
};

std::string MenuState::Next() {
	return m_next_state;
};

bool MenuState::IsType(const std::string &type) {
	return type.compare("MenuState") == 0;
};


void MenuState::SpawnMenuCrosshair(SpriteManager *sprite_manager){
	Sprite *sprite = sprite_manager->Load("MenuCrosshair.png", 0, 0, 32, 32);
	Collider *collider = new Collider;
	collider->m_position = Vector2(0,0);
	collider->m_extention = Vector2(32, 32);
	GameObject *go = new GameObject(sprite, collider);
	go->SetPosition(m_crosshairPos);
	m_objects.push_back(go);
	
}

 bool MenuState::CheckCrosshairCollision(Vector2 &offset, SpriteManager* sprite_manager) {
	StateManager mgr;
	 
	 if(SDL_BUTTON(1)) {
		for (auto i = 0UL; i < m_objects.size(); i++){
			if(m_objects[i]->HasCollider()) {
				Vector2 off;
				if(m_objects[i]->GetCollider()->Overlap(*m_startgametext->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_GoGamestate){
				m_changetoGameState = true;
				return true;
			}

				if(m_objects[i]->GetCollider()->Overlap(*m_optionstext->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					} 
				}

			}


			if(offset.Length() > 0.0f && m_GoOptionsstate){
				mgr.SetState("OptionsState");
				m_changetoOptionsState = true;
				return true;
			}
		return false;
	}
	}
 }