#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <cmath>
#include <ctime>
#include <sstream>
#pragma comment (lib, "sdl2.lib")
#pragma comment(lib, "sdl2main.lib")
#pragma comment(lib, "SDL2_ttf.lib")

#include "DrawManager.h"
#include "SpriteManager.h"
#include "Collider.h"
#include "Level.h"
#include "DuckObject.h"
#include "Engine.h"
#include "Input.h"

Engine::Engine() : m_log("log.txt") {
	m_window = nullptr;
	m_level = nullptr;
	m_draw_manager = nullptr;
	m_sprite_manager = nullptr;
	//m_mouse = nullptr;
	//m_keyboard = nullptr;
	m_running = false;
	m_width = 0;
	m_height = 0;
	m_deltatime = 0.01f;
	m_ticks = SDL_GetTicks();

	m_duck = nullptr;
};

Engine::~Engine() {
};

bool Engine::Initialize() {
	m_width = 1024;
	m_height = 960;
	
	SDL_Init(SDL_INIT_EVERYTHING);
	m_window = SDL_CreateWindow("Duck Hunt", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
		m_width, m_height,
		SDL_WINDOW_OPENGL);

	m_draw_manager = new DrawManager;
	if(!m_draw_manager->Initialize(m_window, m_width, m_height)) {
		return false;
	};

	m_sprite_manager = new SpriteManager(m_draw_manager);
	if(!m_sprite_manager->Initialize("../data/sprites/")){
		return false;
	};

	if(m_window == nullptr) { return false; };

	Collider* collider = new Collider(
	Vector2(500.0f, 500.0f), 
	Vector2(132.0f, 122.0f));
	m_duck = new DuckObject(nullptr, collider);
	m_duck->SetPosition(Vector2(500.0f, 400.0f));

	AnimatedSprite* sprite = m_sprite_manager->Load("../data/animations/blue_horizontal.txt");
	m_duck->AddAnimation("blue_horizontal", sprite);
	
	sprite = m_sprite_manager->Load("../data/animations/blue_vertical.txt");
	m_duck->AddingAnimation("blue_vertical", sprite);

	sprite = m_sprite_manager->Load("../data/animations/blue_diagonal.txt");
	m_duck->AddingAnimation("blue_diagonal", sprite);

	sprite = m_sprite_manager->Load("../data/animations/blue_death.txt");
	m_duck->AddingAnimation("blue_death", sprite);


	//660.0f
	
	/*SDL_RendererFlip flipType = SDL_FLIP_NONE;
	flipType = SDL_FLIP_HORIZONTAL;*/


	m_level = new Level;
	m_level->ChangeAmmo(true, 3); //ChangeAmmo(true, 3) - sätter ammo till 3, ChangeAmmo(false, 3) - ökar ammon med 3
	m_level->SetScore(0);
	m_level->SpawnCrosshair(m_sprite_manager);
	m_level->m_currentDuck = 0;
	for(int i = 0; i <= 9; ++i){
		m_level->m_ducksHit[i] = 'W';
	}
	TTF_Init();
	SDL_ShowCursor( SDL_DISABLE );
	m_running = true;
	
	return true;
};

void Engine::Run() {
	m_duck->Randomize();

	while(m_running) {
		UpdateDeltatime();
		UpdateEvents();
		m_duck->CheckCollision(m_width, m_height);
		m_duck->Update(m_deltatime);
		m_level->UppdateCrosshair();	

		m_duck->GetAngle();

		m_draw_manager->Clear();
		
		m_draw_manager->Draw(
			m_duck->GetSprite(),
			m_duck->GetPosition().m_x,
			m_duck->GetPosition().m_y);


		//std::cout << m_duck->m_angle << std::endl;

		Sprite* sprite = m_sprite_manager->Load("background4.png", 0, 0, 1024, 960);
		m_draw_manager->Draw(sprite, 0, 0);

		sprite = m_sprite_manager->Load("DucksHit.png", 0, 0, 450, 68);	
		m_draw_manager->Draw(sprite, 253, 828);



		if(m_level->m_ammo == 3){					//Kollar vilken ammo bild som ska visas
			sprite = m_sprite_manager->Load("AmmoIs3.png", 0, 0, 116, 84);	
			m_draw_manager->Draw(sprite, 83, 818);
		}
		else if(m_level->m_ammo == 2){
			sprite = m_sprite_manager->Load("AmmoIs2.png", 0, 0, 116, 84);
			m_draw_manager->Draw(sprite, 83, 818);
		}
		else if(m_level->m_ammo == 1){
			sprite = m_sprite_manager->Load("AmmoIs1.png", 0, 0, 116, 84);
			m_draw_manager->Draw(sprite, 83, 818);
		}
		else{
			sprite = m_sprite_manager->Load("AmmoIs0.png", 0, 0, 116, 84);
			m_draw_manager->Draw(sprite, 83, 818);

		}


		
		std::stringstream strm;		
		strm << m_level->m_score;		//Gör om m_score till en mer utskriftsvänlig version.
		SDL_Color foregroundColor = { 255, 255, 255 };		//Sätter Textfärg till vit
		SDL_Color backgroundColor = { 0, 0, 0 };			//sätter Bakgrundsfärg till svart
		TTF_Font* font = TTF_OpenFont("../data/fonts/emulogic.ttf", 25);	//Berättar att vi ska använda ariblk som ligger i ../data/fonts/, och använda den med storlek 20.
		SDL_Surface* screen = TTF_RenderText_Shaded(font, strm.str().c_str(), foregroundColor, backgroundColor);
		m_draw_manager->Draw(screen, 765, 830);
		screen = TTF_RenderText_Shaded(font, "Score", foregroundColor, backgroundColor);	//Skriver ut Score
		m_draw_manager->Draw(screen, 765, 860);												//Vid Pixlarna 765, 860
		int duckPos_x = 362;
		for(int i = 0; i <= 9; ++i){
			if(m_level->m_ducksHit[i] == 'R'){
				sprite = m_sprite_manager->Load("RedDuck.png", 0, 0, 34, 31);	
				m_draw_manager->Draw(sprite,duckPos_x + (i * 34), 837);
			}
			else if(m_level->m_ducksHit[i] == 'W'){
				sprite = m_sprite_manager->Load("WhiteDuck.png", 0, 0, 34, 31);	
				m_draw_manager->Draw(sprite,duckPos_x + (i * 34), 837);
			}
		}
		/*if(m_level->m_ammo == 0){
			m_duck->AnnoyingDogAnimation();
		}*/

		m_level->Draw(m_draw_manager);
		m_draw_manager->Present();

		SDL_Delay(10);
		delete sprite;
	};
};

void Engine::Cleanup() {
	if(m_window != nullptr) {
		SDL_DestroyWindow(m_window);
		m_window = nullptr;
	};
	delete m_duck;
	TTF_Quit();
};


void Engine::UpdateDeltatime() {
	unsigned int ticks = SDL_GetTicks();
	unsigned int delta = ticks - m_ticks;
	m_ticks = ticks;
	m_deltatime = (float)delta * 0.001f;
	if(m_deltatime > 0.1f) {
		m_deltatime = 0.1f;
	};
};

void Engine::UpdateEvents() {
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_QUIT) {
			m_running = false;
		}
		if(event.type == SDL_MOUSEBUTTONDOWN){
			Vector2 offset;
			if(m_level->CheckCollision(m_duck, offset)){
				//m_duck->SetPosition(offset + m_duck->GetPosition());
				
			}
		}
	};
};