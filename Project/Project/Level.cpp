//#pragma comment(lib, "SDL2_ttf.lib")
#include <fstream>
#include <SDL.h>
#include <sstream>
#include "Level.h"
#include "SpriteManager.h"
#include "DrawManager.h"
#include "GameObject.h"
#include "DuckObject.h"
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
	TTF_Init();
	
	drawmanager->Draw(
		m_duck->GetSprite(),
		m_duck->GetPosition().m_x,
		m_duck->GetPosition().m_y);
	
	drawmanager->Draw(m_BackgroundSprite, 0, 0);

	drawmanager->Draw(m_DucksHitSprite, 253, 828);
	if(m_ammo == 3){					//Kollar vilken ammo bild som ska visas	
			drawmanager->Draw(m_Ammo3Sprite, 83, 818);
		}
		else if(m_ammo == 2){
			drawmanager->Draw(m_Ammo2Sprite, 83, 818);
		}
		else if(m_ammo == 1){
			drawmanager->Draw(m_Ammo1Sprite, 83, 818);
		}
		else{
			drawmanager->Draw(m_Ammo0Sprite, 83, 818);
		}
	std::stringstream strm;
	std::stringstream rnd;


	strm << m_score;		//Gör om m_score till en mer utskriftsvänlig version.
	rnd << m_currentRound;
	SDL_Color m_foregroundColor = { 255, 255, 255 };		//Sätter Textfärg till vit
	SDL_Color m_backgroundColor = { 0, 0, 0 };			//sätter Bakgrundsfärg till svart
	TTF_Font* m_font = TTF_OpenFont("../data/fonts/emulogic.ttf", 25);	//Berättar att vi ska använda ariblk som ligger i ../data/fonts/, och använda den med storlek 20.
	SDL_Surface* screen = TTF_RenderText_Shaded(m_font, strm.str().c_str(), m_foregroundColor, m_backgroundColor);
	drawmanager->Draw(screen, 765, 830);
	SDL_FreeSurface(screen);
	screen = TTF_RenderText_Shaded(m_font, "Score", m_foregroundColor, m_backgroundColor);	//Skriver ut Score
	drawmanager->Draw(screen, 765, 860);
	SDL_FreeSurface(screen);
	m_font = TTF_OpenFont("../data/fonts/emulogic.ttf", 20);
	screen = TTF_RenderText_Shaded(m_font, "R =", m_foregroundColor, m_backgroundColor);	//Skriver ut Score
	drawmanager->Draw(screen, 98, 770);
	SDL_FreeSurface(screen);
	screen = TTF_RenderText_Shaded(m_font, rnd.str().c_str(), m_foregroundColor, m_backgroundColor);	//Skriver ut Score
	drawmanager->Draw(screen, 150, 770);
	SDL_FreeSurface(screen);
	int ducksPos_x = 362;
		for(int i = 0; i <= 9; ++i){
			if(m_ducksHit[i] == 'R'){	
				drawmanager->Draw(m_RedDuckSprite,ducksPos_x + (i * 34), 837);
			}
			else if(m_ducksHit[i] == 'W'){	
				drawmanager->Draw(m_WhiteDuckSprite,ducksPos_x + (i * 34), 837);
			}
		}
	for(auto i = 0UL; i < m_objects.size(); i++){
		drawmanager->Draw(m_objects[i]->GetSprite(), 
			m_objects[i]->GetPosition().m_x, 
			m_objects[i]->GetPosition().m_y);

	}


	
	TTF_Quit();
}
bool Level::CheckCollision(Vector2 &offset, SpriteManager* sprite_manager, float deltatime){
	
	
	if(SDL_BUTTON(1) && m_ammo > 0 && !m_duck->isHit){
		m_ammo -= 1;
		//shoot->Play();
		for (auto i = 0UL; i < m_objects.size(); i++){
			if(m_objects[i]->HasCollider()) {
				Vector2 off;
				if(m_objects[i]->GetCollider()->Overlap(*m_duck->GetCollider(), off)){

					if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
						offset += off;
					}
				}
			}
			if(offset.Length() > 0.0f){
				
				if (m_duck->m_duckType >= 0 && m_duck->m_duckType <= 3){
					m_score += (500 * m_currentRound);
				} else if (m_duck->m_duckType >= 4 && m_duck->m_duckType <= 5) {
					m_score += (1000 * m_currentRound);
				}
				else {
					m_score += (1500 * m_currentRound);
				}
				m_duck->isHit = true;
				m_ducksHit[m_currentDuck] = 'R';
				m_ammo = 3;
				if(m_currentDuck == 9){
					for(int i = 0; i <= 9; ++i){
						for(int j = 0; j <= 9; ++j){
							if(m_ducksHit[j+1] == 'R' && m_ducksHit[j] == 'w'){
								int temp;
								temp = m_ducksHit[j];
								m_ducksHit[j] = m_ducksHit[j+1];
								m_ducksHit[j+1] = temp;
							}
						}
					}
					int ducksHit = 0;
					for(int i = 0; i <= 9; ++i){
						if(m_ducksHit[i] == 'R'){
							ducksHit += 1;
						}
					}
					
					for(int i = 0; i <= 9; ++i){
						m_ducksHit[i] = 'W';
						
					}		
					m_currentDuck = 0;
					if(ducksHit >= 7){
						m_currentRound += 1;
						if(m_currentRound == 11){
						Victory();
						m_currentRound = 1;
					}
					}
					else{
						Defeat();
						m_currentRound = 1;
					}
				}
				else{
					m_currentDuck += 1;
					if(m_currentRound == 11){
						Victory();
						m_currentRound = 1;
					}
				}

				return true;
				}
			}
		}
		if(m_ammo == 0){
			m_duck->isMissed = true;
			m_ammo = 3;
			if(m_currentDuck == 9){
					for(int i = 0; i <= 9; ++i){
						for(int j = 0; j <= 9; ++j){
							if(m_ducksHit[j+1] == 'R' && m_ducksHit[j] == 'w'){
								int temp;
								temp = m_ducksHit[j];
								m_ducksHit[j] = m_ducksHit[j+1];
								m_ducksHit[j+1] = temp;
							}
						}
					}
					int ducksHit = 0;
					for(int i = 0; i <= 9; ++i){
						if(m_ducksHit[i] == 'R'){
							ducksHit += 1;
						}
					}
					for(int i = 0; i <= 9; ++i){
						m_ducksHit[i] = 'W';
						SDL_Delay(100);
					}		
					m_currentDuck = 0;
					if(ducksHit >= 7){
						m_currentRound += 1;
						if(m_currentRound == 11){
						Victory();
						m_currentRound = 1;
					}
					}
					else{
						Defeat();
						m_currentRound = 1;
					}
				}
				else{
					m_currentDuck += 1;
					if(m_currentRound == 11){
						Victory();
						m_currentRound = 1;
					}
				}
		}
		return false;
	
}
void Level::SpawnCrosshair(SpriteManager *sprite_manager){
	Sprite *sprite = sprite_manager->Load("Crosshair.png", 0, 0, 32, 32);
	Collider *collider = new Collider;
	collider->m_position = Vector2(0,0);
	collider->m_extention = Vector2(32, 32);
	GameObject *go = new GameObject(sprite, collider);
	go->SetPosition(m_crosshairPos);
	m_objects.push_back(go);
	
}

void Level::UpdateLevel(float deltatime, SpriteManager* spritemanager){
	if(!m_isDuckSpawned){
		SpawnDuck(spritemanager);
		m_isDuckSpawned = true;
	}
	int x, y;
	SDL_GetMouseState(&x, &y);
	m_crosshairPos.m_x = x -16;
	m_crosshairPos.m_y = y -16;
	m_objects[0]->SetPosition(m_crosshairPos);
	m_objects[0]->m_collider->m_position.m_x = x -16;
	m_objects[0]->m_collider->m_position.m_y = y -16;
	m_duck->Timer(deltatime);
	m_duck->Update(deltatime);
	m_duck->m_collider->m_position = m_duck->m_position;
	m_duck->GetAngle();

	if(m_duck->m_position.m_y >= 700.0f || m_duck->m_position.m_y <= -100.0f) {
		delete m_duck->GetSprite();
		delete m_duck->GetCollider();
		delete m_duck;
		m_duck = nullptr;
		SpawnDuck(spritemanager);
	}
	
}
void Level::ChangeAmmo(bool set, int value){
	if(set){
		m_ammo = value;
	}
	else{
		m_ammo += value;
	}
}
/*void Level::DrawText(SDL_Surface* screen,const  char* string, int size, int x, int y, int fR, int fG, int fB, int bR, int bG, int bB){
	
	TTF_Font* font = TTF_OpenFont("../data/fonts/arial.ttf", size);
	SDL_Color foregroundColor = { fR, fG, fB }; 
	SDL_Color backgroundColor = { bR, bG, bB };
	SDL_Surface* textSurface = TTF_RenderText_Shaded(font, string, 
	foregroundColor, backgroundColor);
	SDL_Rect textLocation = { x, y, 0, 0 };
	SDL_BlitSurface(textSurface, NULL, screen, &textLocation);
	SDL_FreeSurface(textSurface);
	TTF_CloseFont(font);
}*/
void Level::SetScore(int score){
	m_score = score;	
}
void Level::InitLevel(SpriteManager *sprite_manager){
	m_currentRound = 1;
	m_isDuckSpawned = false;
	ChangeAmmo(true, 3); //ChangeAmmo(true, 3) - sätter ammo till 3, ChangeAmmo(false, 3) - ökar ammon med 3
	SetScore(0);
	shouldEnd = false;
	SpawnCrosshair(sprite_manager);
	m_currentDuck = 0;
	
	for(int i = 0; i <= 9; ++i){
		m_ducksHit[i] = 'W';
	}
	m_BackgroundSprite = sprite_manager->Load("background4.png", 0, 0, 1024, 960);
	m_DucksHitSprite = sprite_manager->Load("DucksHit.png", 0, 0, 450, 68);
	m_Ammo3Sprite = sprite_manager->Load("AmmoIs3_2.png", 0, 0, 116, 84);
	m_Ammo2Sprite = sprite_manager->Load("AmmoIs2_2.png", 0, 0, 116, 84);
	m_Ammo1Sprite = sprite_manager->Load("AmmoIs1_2.png", 0, 0, 116, 84);
	m_Ammo0Sprite = sprite_manager->Load("AmmoIs0_2.png", 0, 0, 116, 84);
	m_RedDuckSprite = sprite_manager->Load("RedDuck.png", 0, 0, 28, 28);
	m_WhiteDuckSprite = sprite_manager->Load("WhiteDuck.png", 0, 0, 28, 28);

}
void Level::SpawnDuck(SpriteManager *spritemanager){
	Collider* collider = new Collider(
	Vector2(500.0f, 500.0f), 
	Vector2(132.0f, 122.0f));
	m_duck = new DuckObject(nullptr, collider);
	m_duck->SetPosition(m_duck->GetSpawnPosition());
	m_duck->LoadAnimations(spritemanager);
	m_duck->Randomize();
}
void Level::Defeat(){
	CheckHighscore();
	
	
}

void Level::Victory(){
	CheckHighscore();


}

void Level::CheckHighscore(){
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
	stream.close();
	std::ofstream ostream("../data/score/score.txt");
	ostream.clear();
	std::string scoreOut;
	if(m_score > highscore[9]){
		highscore[9] = m_score;
	}

	for(int i = 9; i >= 1; --i){
		
			if(highscore[i-1] < highscore[i]){

				int temp;

				temp = highscore[i];

				highscore[i] = highscore[i-1];

				highscore[i-1] = temp;

			}
		
	}
	ostream << "10\n";
	for (int i = 0; i <= 9; ++i){
		ostream << (i+1);
		ostream << " ";
		ostream << highscore[i];
		ostream << "\n";
	}
}