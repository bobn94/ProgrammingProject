#pragma once
#include <map>
#include "Animation.h"
#include <string>

class Sprite;
class DrawManager;

class SpriteManager{
	struct Pair{
		struct SDL_Surface *surface;
		struct SDL_Texture *texture;
	};

public:
	SpriteManager(DrawManager *draw_manager);
	~SpriteManager();

	bool Initialize(const std::string &directory);
	void cleanup();
	bool LoadImage(std::string &filename);
	virtual Sprite* Load(const std::string &filename, int x, int y, int width, int height);
	Animation* Load(const std::string &filename);
private:
	std::string m_directory;
	std::string m_filename;
	Animation::Frame m_frame;
	std::map<std::string,Pair> m_sprites;
	DrawManager *m_draw_manager;
};