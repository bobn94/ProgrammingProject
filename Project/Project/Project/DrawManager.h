
#pragma once
class Sprite;

class DrawManager {
	friend class SpriteManager;

public:
	DrawManager();
	~DrawManager();

	bool Initialize(struct SDL_Window *window, int width, int height);
	void Cleanup();
	void Clear();
	void Present();
	void Draw(Sprite *sprite, int x, int y);

private:
	struct SDL_Renderer *m_renderer;
};