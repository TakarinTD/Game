#pragma once
#include"GameStates/gamestatebase.h"
#include "GameButton.h"

class Sprite2D;
class Sprite3D;
class Text;
class SpriteAnimation;

class GSLose :
	public GameStateBase
{
public:
	GSLose();
	~GSLose();

	void Init();
	void Exit();

	void Pause();
	void Resume();

	void HandleEvents();
	void HandleKeyEvents(int key, bool bIsPressed);

	void HandleTouchEvents(int x, int y, bool bIsPressed);
	void Update(float deltaTime);
	void Draw();

private:

	std::shared_ptr<Sprite2D> m_BackGround;
	std::list<std::shared_ptr<GameButton>>	m_listButton;
};
