
#include <fstream>
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
bool Level::Load(const std::string &filename, SpriteManager *sprite_manager){
	std::ifstream stream(filename);
	if(!stream.is_open()){
		return false;
	}


	std::string row;
	unsigned int cords_count = 0;
	stream >> m_spritemap_filename;
	stream >> cords_count;
	std::getline(stream, row);
	for(unsigned int i = 0; i < cords_count; i++){
		
		std::getline(stream, row);
		std::stringstream ss(row);
		std::string ch;
		Cords cord;

		ss >> ch;		// laddar in en del av en bild som fins på pixlarna x,y - x+w, y+h
		ss >> cord.x;
		ss >> cord.y;
		ss >> cord.w;
		ss >> cord.h;
		ss >> cord.f;
		m_tile_cords.insert( std::pair<char,Cords>(ch[0], cord));
	}
	unsigned int x = 0;
	unsigned int y = 0;
	while(!stream.eof()){
		std::getline(stream, row, '\n');
		if(row.length() == 0){
			continue;
		}
		x= 0;
		for(unsigned int i = 0; i < row.length(); i++){
			if(row[i] == '0'){
				x += 32;
				continue;
			}
			

			std::map<char,Cords>::iterator it = m_tile_cords.find(row[i]);
			if(it == m_tile_cords.end()){
				continue;
			}
			Cords &c = it->second;
			Sprite *sprite = sprite_manager->Load(m_spritemap_filename, c.x, c.y, c.w, c.h);
			Collider *collider = new Collider;
			if(c.f){ // om flaggan är 1, ge objectet en collider
			
			collider->m_position = Vector2(x,y);
			collider->m_extention = Vector2(c.w, c.h);
			}
			else{// är flaggan inte 1, ge den inte en collider
				delete collider;
				collider = nullptr;
			}
			GameObject *go = new GameObject(sprite, collider, m_flag);
			go->SetPosition(Vector2(x, y));
			m_objects.push_back(go);

			x += 32;
		}
		y += 32;
	}

	stream.close();

	return true;
}
void Level::Draw(DrawManager *drawmanager){
	for(auto i = 0UL; i < m_objects.size(); i++){
		drawmanager->Draw(m_objects[i]->GetSprite(), 
			m_objects[i]->GetPosition().m_x, 
			m_objects[i]->GetPosition().m_y);
	}
}
bool Level::CheckCollision(GameObject *object, Vector2 &offset){
	
	for (auto i = 0UL; i < m_objects.size(); i++){
		if(m_objects[i]->HasCollider()) {
			Vector2 off;
			if(m_objects[i]->GetCollider()->Overlap(*object->GetCollider(), off)){
				if((off.m_x != 0 && off.m_x != offset.m_x) || (off.m_y != 0 && off.m_y != offset.m_y)){
					offset += off;
				}
			}
		}
		if(offset.Lenght() > 0.0f){
			return true;
		}
	}
	return false;
}