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
#include "OptionsState.h"
#include "StateManager.h"
#include "GlobalConfig.h"
#include "MenuState.h"



OptionsState::OptionsState() {
	m_done = false;
	m_changetoGameState = false;

	m_volume = 100;

	auto it = m_objects.begin();
	while(it != m_objects.end()){
		delete (*it)->GetSprite();
		//delete (*it)->GetCollider();
		delete (*it);
		++it;
	}
};


bool OptionsState::Enter() {
	return true;
};

void OptionsState::Exit() {


};

bool OptionsState::Update(float deltatime, SpriteManager* m_sprite_manager) {
	
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_crosshairPos.m_x = x -16;
	m_crosshairPos.m_y = y -16;
	m_objects[0]->SetPosition(m_crosshairPos);
	m_objects[0]->m_collider->m_position = m_crosshairPos;

	UpdateVolume();
	return !m_done;
};

void OptionsState::Initialize(SpriteManager* m_sprite_manager) {
	SpawnMenuCrosshair(m_sprite_manager);
	
	m_BackgroundSprite = m_sprite_manager->Load("Menubackground.png", 0, 0, 1024, 960);

	Sprite *sprite = m_sprite_manager->Load("playbutton.png", 0, 0, 45, 41);
	Collider *collider = new Collider;
	collider->m_position = Vector2(400, 550);
	collider->m_extention = Vector2(45, 41);
	m_playbutton = new GameObject(sprite, collider);
	m_playbutton->SetPosition(Vector2(400, 550));

	sprite = m_sprite_manager->Load("nextbutton.png", 0, 0, 45, 41);
	collider = new Collider;
	collider->m_position = Vector2(445, 550);
	collider->m_extention = Vector2(45, 41);
	m_nextbutton = new GameObject(sprite, collider);
	m_nextbutton->SetPosition(Vector2(445, 550));

	sprite = m_sprite_manager->Load("prevbutton.png", 0, 0, 45, 41);
	collider = new Collider;
	collider->m_position = Vector2(490, 550);
	collider->m_extention = Vector2(45, 41);
	m_prevbutton = new GameObject(sprite, collider);
	m_prevbutton->SetPosition(Vector2(490, 550));

	sprite = m_sprite_manager->Load("stopbutton.png", 0, 0, 45, 41);
	collider = new Collider;
	collider->m_position = Vector2(535, 550);
	collider->m_extention = Vector2(45, 41);
	m_stopbutton = new GameObject(sprite, collider);
	m_stopbutton->SetPosition(Vector2(535, 550));

	sprite = m_sprite_manager->Load("volumeupbutton.png", 0, 0, 45, 41);
	collider = new Collider;
	collider->m_position = Vector2(580, 550);
	collider->m_extention = Vector2(45, 41);
	m_volumeupbutton = new GameObject(sprite, collider);
	m_volumeupbutton->SetPosition(Vector2(580, 550));

	sprite = m_sprite_manager->Load("volumedownbutton.png", 0, 0, 45, 41);
	collider->m_position = Vector2(625, 550);
	collider->m_extention = Vector2(45, 41);
	m_volumedownbutton = new GameObject(sprite, collider);
	m_volumedownbutton->SetPosition(Vector2(625, 550));

	sprite = m_sprite_manager->Load("optionscollider.png", 0, 0, 245, 39);
	collider = new Collider;
	collider->m_position = Vector2(350, 635);
	collider->m_extention = Vector2(245, 41);
	m_gametext = new GameObject(sprite, collider);
	m_gametext->SetPosition(Vector2(620, 635));

}

void OptionsState::Draw(DrawManager* m_draw_manager) {
	TTF_Init();
	
	m_draw_manager->Draw(m_BackgroundSprite, 0, 0);

	
	TTF_Font* m_font = TTF_OpenFont("../data/fonts/duckhunt.ttf", 250);
	SDL_Color m_foregroundColor = { 72, 205, 222 };
	SDL_Color m_backgroundColor = { 0, 0, 0 };
	SDL_Surface* screen = TTF_RenderText_Shaded(m_font, "Duck", m_foregroundColor, m_backgroundColor);
	m_draw_manager->Draw(screen, 170, 100);

	screen = TTF_RenderText_Shaded(m_font, "Hunt", m_foregroundColor, m_backgroundColor);
	m_draw_manager->Draw(screen, 320, 300);



	SDL_Color m_foregroundColor2 = { 255, 255, 255 };
	m_font = TTF_OpenFont("../data/fonts/emulogic.ttf", 35);
	screen = TTF_RenderText_Shaded(m_font, "Start game", m_foregroundColor2, m_backgroundColor);
	m_draw_manager->Draw(screen, 350, 630);
	


	m_draw_manager->Draw(
		m_playbutton->GetSprite(),
		m_playbutton->GetPosition().m_x,
		m_playbutton->GetPosition().m_y);

	m_draw_manager->Draw(
		m_nextbutton->GetSprite(),
		m_nextbutton->GetPosition().m_x,
		m_nextbutton->GetPosition().m_y);

	m_draw_manager->Draw(
		m_prevbutton->GetSprite(),
		m_prevbutton->GetPosition().m_x,
		m_prevbutton->GetPosition().m_y);

	m_draw_manager->Draw(
		m_stopbutton->GetSprite(),
		m_stopbutton->GetPosition().m_x,
		m_stopbutton->GetPosition().m_y);

	m_draw_manager->Draw(
		m_volumeupbutton->GetSprite(),
		m_volumeupbutton->GetPosition().m_x,
		m_volumeupbutton->GetPosition().m_y);

	m_draw_manager->Draw(
		m_volumedownbutton->GetSprite(),
		m_volumedownbutton->GetPosition().m_x,
		m_volumedownbutton->GetPosition().m_y);

	m_draw_manager->Draw(
		m_gametext->GetSprite(),
		m_gametext->GetPosition().m_x,
		m_gametext->GetPosition().m_y);


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

std::string OptionsState::Next() {
	return m_next_state;
	m_done = true;
	isOn = false;
};

bool OptionsState::IsType(const std::string &type) {
	return type.compare("OptionsState") == 0;
};


void OptionsState::SpawnMenuCrosshair(SpriteManager *sprite_manager){
	Sprite *sprite = sprite_manager->Load("MenuCrosshair.png", 0, 0, 32, 32);
	Collider *collider = new Collider;
	collider->m_position = Vector2(0,0);
	collider->m_extention = Vector2(32, 32);
	GameObject *go = new GameObject(sprite, collider);
	go->SetPosition(m_crosshairPos);
	m_objects.push_back(go);
	
}

 bool OptionsState::CheckCrosshairCollision(Vector2 &offset, SpriteManager* sprite_manager) {
	if(isOn = true) {
	StateManager mgr;
	 
	 if(SDL_BUTTON(1)) {
		for (auto i = 0UL; i < m_objects.size(); i++){
			if(m_objects[i]->HasCollider()) {
				Vector2 off;
				if(m_objects[i]->GetCollider()->Overlap(*m_playbutton->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_resetit){
				
				//m_menu->m_sound_manager->PlayPause();
				return true;
			}


				if(m_objects[i]->GetCollider()->Overlap(*m_nextbutton->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_resetit){
				
				//m_menu->m_sound_manager->PlayNext();
				return true;
			}

				if(m_objects[i]->GetCollider()->Overlap(*m_prevbutton->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_resetit){
				
				//m_menu->m_sound_manager->PlayPrev();
				return true;
			}

				if(m_objects[i]->GetCollider()->Overlap(*m_stopbutton->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_resetit){
				
				//m_menu->m_sound_manager->Stop();
				return true;
			}


				if(m_objects[i]->GetCollider()->Overlap(*m_volumeupbutton->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_resetit){
				
				m_volume++;
				std::cout << "up" << std::endl;
				setMusicVolume(m_volume);
				return true;
			}


				if(m_objects[i]->GetCollider()->Overlap(*m_volumedownbutton->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}

				if(offset.Length() > 0.0f && m_resetit){
				
				m_volume--;
				setMusicVolume(m_volume);
				return true;
			}

				if(m_objects[i]->GetCollider()->Overlap(*m_gametext->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					} 
				}

			}


			if(offset.Length() > 0.0f && m_GoGamestate){
				mgr.SetState("GameState");
				m_changetoGameState = true;
				m_done = true;
				isOn = false;
				return true;
			}
		return false;
	}
	 }}
 }


/*void OptionsState::ResetHighscore(){
	if (m_resetHighScore = true) {
		std::ofstream ostream("../data/score/score.txt");
		ostream.clear();
		ostream << "10\n";
		for (int i = 0; i <= 9; ++i){
			ostream << (i+1);
			ostream << " ";
			ostream << 0;
			ostream << "\n";
		}
	};
}*/


 void OptionsState::UpdateVolume()
{
	setMusicVolume(m_volume);
}