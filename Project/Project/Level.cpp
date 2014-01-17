
#include <fstream>
#include <SDL_ttf.h>
#include <SDL.h>
#include <sstream>
#include "Level.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "GameObject.h"
#include "Collider.h"

Level::Level(){
	
}
Level::~Level(){
	auto it = m_objects.begin();
	while(it != m_objects.end()){
		delete (*it)->GetSprite();
		//delete (*it)->GetCollider();
		delete (*it);
		++it;
	}

}
void Level::Draw(DrawManager *drawmanager){
	for(auto i = 0UL; i < m_objects.size(); i++){
		drawmanager->Draw(m_objects[i]->GetSprite(), 
			m_objects[i]->GetPosition().m_x, 
			m_objects[i]->GetPosition().m_y);

	}
	

}
bool Level::CheckCollision(GameObject *object, Vector2 &offset){
	if(SDL_BUTTON(1) && m_ammo > 0){
		m_ammo -= 1;
		//<Gun sound here>
		for (auto i = 0UL; i < m_objects.size(); i++){
			if(m_objects[i]->HasCollider()) {
				Vector2 off;
				if(m_objects[i]->GetCollider()->Overlap(*object->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}
			}
			if(offset.Length() > 0.0f){
				m_score += 100;
			return true;
			}
		}
			if(m_ammo == 0){
				m_ducksHit[m_currentDuck] = 'R';

			if(m_currentDuck == 9){
				m_currentDuck = 0;
			}
			else{
				m_currentDuck += 1;
			}

		}
		return false;
	}
}
void Level::SpawnCrosshair(SpriteManager *sprite_manager){
	Sprite *sprite = sprite_manager->Load("crosshair.png", 0, 0, 32, 32);
	Collider *collider = new Collider;
	collider->m_position = Vector2(0,0);
	collider->m_extention = Vector2(32, 32);
	GameObject *go = new GameObject(sprite, collider);
	go->SetPosition(m_crosshairPos);
	m_objects.push_back(go);
	
}

void Level::UpdateCrosshair(){
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_crosshairPos.m_x = x -16;
	m_crosshairPos.m_y = y -16;
	m_objects[0]->SetPosition(m_crosshairPos);
	m_objects[0]->m_collider->m_position.m_x = x -16;
	m_objects[0]->m_collider->m_position.m_y = y -16;
	
}
void Level::ChangeAmmo(bool set, int value){
	if(set){
		m_ammo = value;
	}
	else{
		m_ammo += value;
	}
}
void Level::DrawText(SDL_Surface* screen,const  char* string, int size, int x, int y, int fR, int fG, int fB, int bR, int bG, int bB){
	
	TTF_Font* font = TTF_OpenFont("../data/fonts/arial.ttf", size);
	SDL_Color foregroundColor = { fR, fG, fB }; 
	SDL_Color backgroundColor = { bR, bG, bB };
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string, 
	foregroundColor, backgroundColor);
	SDL_Rect textLocation = { x, y, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}
void Level::SetScore(int score){
	m_score = score;	
}