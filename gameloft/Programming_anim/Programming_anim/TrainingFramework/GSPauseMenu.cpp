#include "GSPauseMenu.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"



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
	//button resume
	texture = ResourceManagers::GetInstance()->GetTexture("button_resume1");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 250);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Resume);
	});
	m_listButton.push_back(button);
	//button restart
	texture = ResourceManagers::GetInstance()->GetTexture("button_restart");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 350);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Restart);
	});
	m_listButton.push_back(button);
	//button exit
	texture = ResourceManagers::GetInstance()->GetTexture("button_exit");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 450);
	button->SetSize(50, 50);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Exit);
	});
	m_listButton.push_back(button);

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
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSPauseMenu::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSPauseMenu::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
