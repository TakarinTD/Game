#include "GSPauseMenu.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "SpriteAnimation.h"
#include "Sprite2D.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPauseMenu::GSPauseMenu()
{
}


GSPauseMenu::~GSPauseMenu()
{

}


void GSPauseMenu::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

}
void GSPauseMenu::Exit()
{

}


void GSPauseMenu::Pause()
{

}

void GSPauseMenu::Resume()
{

}


void GSPauseMenu::HandleEvents()
{

}

void GSPauseMenu::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSPauseMenu::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPauseMenu::Update(float deltaTime)
{
}

void GSPauseMenu::Draw()
{
	m_BackGround->Draw();

}
