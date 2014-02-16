

#pragma once
enum EmouseButton{
	MB_LEFT,
	MB_RIGHT,
	MB_COUNT,
};
class KeyBoard{
	friend class Engine;
public:
	KeyBoard();

	bool IsDown(int key);
	bool IsDownOnce(int key);

	void PostUpdate();

private:
	bool m_current[256];
	bool m_previous[256];
};
class Mouse{
	friend class Engine;
public:
	Mouse();

	int GetX() const;
	int GetY() const;
	bool IsDown(EmouseButton button) const;
	bool IsDownOnce(EmouseButton button) const;
	void PostUpdate();
	
private:
	bool m_current[MB_COUNT];
	bool m_previous[MB_COUNT];
	int m_x;
	int m_y;
};