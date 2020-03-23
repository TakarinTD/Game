#include "card.h"
Card::Card(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture) :Sprite2D(model, shader, texture)
{
	m_pBtClick = nullptr;
	m_isHandle = false;
	/*posX = x;
	posY = y;*/
}
void Card::SetOnClick(void(*pBtClickFun)())
{
	m_pBtClick = pBtClickFun;
}
void Card::HandleTouchEvents(GLint x, GLint y, bool bIsPressed)
{
	m_isHandle = false;
	if ((x > m_Vec2DPos.x - m_iWidth / 2) && (x < m_Vec2DPos.x + m_iWidth / 2) && (y > m_Vec2DPos.y - m_iHeight / 2) && (y < m_Vec2DPos.y + m_iHeight / 2))
	{
		m_pBtClick();
		m_isHandle =true;
	}
}

bool Card::IsHandle()
{
	return m_isHandle;
}

Card::~Card()
{
}