#pragma once
#include "Sprite2D.h"
class Card : public Sprite2D
{
public:
	Card(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	void	SetOnClick(void(*pBtClick)());
	void	HandleTouchEvents(GLint x, GLint y, bool bIsPressed);
	bool	IsHandle();
	~Card();
	int posX, posY;
	int id;
private:
	void(*m_pBtClick)();
	bool	m_isHandle;
};