#include "GSSetting.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "SpriteAnimation.h"
#include "Sprite2D.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSSetting::GSSetting()
{
}


GSSetting::~GSSetting()
{

}


void GSSetting::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_setting");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

}
void GSSetting::Exit()
{

}


void GSSetting::Pause()
{

}

void GSSetting::Resume()
{

}


void GSSetting::HandleEvents()
{

}

void GSSetting::HandleKeyEvents(int key, bool bIsPressed)
{

}

void GSSetting::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSSetting::Update(float deltaTime)
{
}

void GSSetting::Draw()
{
	m_BackGround->Draw();

}
