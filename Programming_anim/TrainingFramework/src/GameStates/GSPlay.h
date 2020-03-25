#pragma once
#include <cstdlib>
#include <iostream>
#include "gamestatebase.h"
#include "GameButton.h"
#include"card.h"
#include <vector>
#include <ctime>

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
	bool isOnRange(int idx, int x, int y, int sz);
	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);
	void Newgame();
	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();
private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::shared_ptr<Text>  m_step;
	std::shared_ptr<Text>  m_time;
	std::vector < std::shared_ptr<Sprite2D>> m_listSprite2D;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
	std::shared_ptr<Card> card[24];
	std::shared_ptr<Card> cardDown[24];
	std::vector < std::shared_ptr<Card>> cardback,cardface;

};

