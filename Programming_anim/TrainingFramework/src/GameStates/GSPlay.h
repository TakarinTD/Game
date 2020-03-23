#pragma once
#include <cstdlib>
#include <iostream>
#include "gamestatebase.h"
#include "GameButton.h"
#include"card.h"
#include <vector>
#include <ctime>
#include <windows.h>

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSPlay :
	public GameStateBase
{
public:
	GSPlay();
	~GSPlay();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void Newgame();
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
	void DrawGame();
	void CardClick(int x, int y);
private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_step;
	std::shared_ptr<Text>  m_time;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::list<std::shared_ptr<Card>>	m_listCard;
	Card *card_back=NULL;
	std::shared_ptr<Card> card1;
	std::shared_ptr<Card> card[24];

//	std::vector < std::shared_ptr<Card>> card;
};

