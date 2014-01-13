#pragma once
#include "SpriteManager.h"
#include "Sprite.h"
#include <SDL_image.h>
#include <string>
#pragma comment(lib, "sdl2_image.lib")
#include "DrawManager.h"
#include <fstream>
#include <sstream>
#include "AnimatedSprite.h"

SpriteManager::SpriteManager(DrawManager *draw_manager)
{
	m_draw_manager = draw_manager;
}
	SpriteManager::~SpriteManager(){

	}

	bool SpriteManager::Initialize(const std::string &directory){
		IMG_Init(IMG_INIT_PNG);
		
		m_directory = directory;

		
		return true;
	}
	void SpriteManager::cleanup(){
		std::map<std::string, Pair>::iterator it = m_sprites.begin();
		while(it != m_sprites.end()){
			SDL_FreeSurface(it->second.surface);
			SDL_DestroyTexture(it->second.texture);
			++it;
		}
		m_sprites.clear();

		IMG_Quit();
	}
	Sprite* SpriteManager::Load(const std::string &filename, int x, int y, int width, int height){
		std::map<std::string,Pair>::iterator it = m_sprites.find(filename);
		if(it == m_sprites.end()){
			std::string path = m_directory + filename;
			SDL_Surface* surface = IMG_Load(path.c_str());
			if (surface == nullptr){
				return nullptr;
			}
			SDL_Texture* texture = SDL_CreateTextureFromSurface(m_draw_manager->m_renderer, surface);
			Pair pair = { surface, texture };
			m_sprites.insert( std::pair<std::string,Pair>( filename, pair ) );
			it = m_sprites.find(filename);
		}
		return new Sprite(it->second.surface, it->second.texture, x, y, width, height);
	}
AnimatedSprite* SpriteManager::Load(const std::string &filename){					//code for if/when animation is added
		std::ifstream stream;
		stream.open(filename.c_str());
		if(!stream.is_open()){
			return nullptr;
		}
		std::string row;
		stream >> row;
		std::map<std::string, Pair>::iterator it = m_sprites.find(row);
		if(it == m_sprites.end()){
			if(!LoadImage(row)){
				stream.close();
				return nullptr;
			}
			it = m_sprites.find(row);
		}

		SDL_Surface *surface = it->second.surface;
		SDL_Texture *texture = it->second.texture;

		AnimatedSprite *sprite = new AnimatedSprite(surface, texture, 0, 0, 0, 0);

		while(!stream.eof()){
			std::getline(stream, row);
			if(row.length() == 0){
				continue;
			}
			std::stringstream ss(row);

			AnimatedSprite::Frame frame;

			ss >> frame.duration;
			ss >> frame.x;
			ss >> frame.y;
			ss >> frame.width;
			ss >> frame.height;
			sprite->AddFrame(frame);

		}
	
		
		stream.close();
		return sprite;
	}
	bool SpriteManager::LoadImage(std::string &filename){
		std::string path = m_directory + filename;
		SDL_Surface *surface = IMG_Load(path.c_str());
		const char *error = IMG_GetError();
		if(surface == nullptr){
			return false;
		}
		SDL_Texture* texture = SDL_CreateTextureFromSurface(m_draw_manager->m_renderer, surface);
		Pair pair = { surface, texture };
		m_sprites.insert( std::pair<std::string,Pair>(filename, pair ) );

		return true;
	}