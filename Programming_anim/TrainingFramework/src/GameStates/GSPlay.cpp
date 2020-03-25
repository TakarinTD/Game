#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include "SpriteAnimation.h"
#include<string>



extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine
extern int clickstat;
int Step;
int flip = 0;
int matchCheck = 0;
int stackk[2], stackIndex[2];
const int CardNo = 12;           //số lượng các quân bài là 12 => có 24 lá bài
const int GameWidth = 6;
const int GameHeight = 4;        //Các lá bài được sắp thành ma trận 4x6 
const int CardSizeW = 160;
const int CardSizeH = 160;         //kích thước của các lá bài là 86x64 pixel
const int CardSpacing = 16;
int CardCount[CardNo];
int CardMatrix[GameHeight][GameWidth];			// ma trận các lá bài         
int FirstCardX, FirstCardY;   //Vị trí của lá bài thứ nhất đã mở trong ma trận
std::string ImagePaths[] = { "card1", "card2", "card3",
"card4", "card5", "card6",
"card7", "card8", "card9",
"card10", "card11", "card12" };
GSPlay::GSPlay()
{
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	Step = 0;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//button pause
	texture = ResourceManagers::GetInstance()->GetTexture("button_pause");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth / 2, 20);
	button->SetSize(40, 40);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Pause);
	});
	m_listButton.push_back(button);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_step = std::make_shared< Text>(shader, font, "Step: " + std::to_string(Step), TEXT_COLOR::RED, 1.0);
	m_step->Set2DPosition(Vector2(5, 30));

	
	int tmp = 0;
	Newgame();
	for (int i = 0; i < GameHeight; i++) {
		for (int j = 0; j < GameWidth; j++) {
			int index = CardMatrix[i][j];
			card[tmp] = std::make_shared <Card>(ResourceManagers::GetInstance()->GetModel("Sprite2D"),
				ResourceManagers::GetInstance()->GetShader("TextureShader"),
				ResourceManagers::GetInstance()->GetTexture(ImagePaths[index]), (CardSizeW + CardSpacing)* (j + 1), (CardSizeH + CardSpacing)* (i + 1));
			card[tmp]->id = index;
			card[tmp]->SetSize(160, 160);
			card[tmp]->Set2DPosition(card[tmp]->posX, card[tmp]->posY);

			cardDown[tmp] = std::make_shared <Card>(ResourceManagers::GetInstance()->GetModel("Sprite2D"),
				ResourceManagers::GetInstance()->GetShader("TextureShader"),
				ResourceManagers::GetInstance()->GetTexture("Dirt"), (CardSizeW + CardSpacing)* (j + 1), (CardSizeH + CardSpacing)* (i + 1));
			cardDown[tmp]->id = index;
			cardDown[tmp]->SetSize(160, 160);
			cardDown[tmp]->Set2DPosition(cardDown[tmp]->posX, cardDown[tmp]->posY);
			tmp++;
		}
	}

}
void GSPlay::Newgame()
{
	int i, j, k;
	flip = 0;
	//Mảng này cho biết mỗi quân bài xuất hiện mấy lần (lá bài)

	for (k = 0; k < CardNo; k++)
		CardCount[k] = 2;               //Thiết lập có 2 lá bài cho mỗi quân bài

	srand(time(NULL));

	//duyệt qua từng ô trong ma trận, chọn ngẫu nhiên lá bài cho ô đó
	for (i = 0; i < GameHeight; i++)
		for (j = 0; j < GameWidth; j++)
		{
			do
			{
				k = rand() % (CardNo);      //tạo đối tượng sinh số ngẫu nhiên
			} while (CardCount[k] == 0);    // Nếu CardCount[k] == 0 nghĩa là 
											//quân bài thứ k đã sử dụng hết 
											//các lá bài, cần tìm k khác.
			CardMatrix[i][j] = k;       //lá bài tại ô i, j là quân bài thứ k
			CardCount[k]--;            //quân bài thứ k đã dùng 1 lá bài
		}
}

void GSPlay::Exit()
{

}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{

}

bool GSPlay::isOnRange(int idx, int x, int y, int sz) {
	return(x >= card[idx]->posX - sz / 2 && x <= card[idx]->posX + sz / 2 &&
		y >= card[idx]->posY - sz / 2 && y <= card[idx]->posY + sz / 2);
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!clickstat) {
		for (auto it : m_listButton)
		{
			(it)->HandleTouchEvents(x, y, bIsPressed);
			if ((it)->IsHandle()) break;
		}
		for (int i = 0; i < 24; i++) {
			if (isOnRange(i, x, y, 160) && card[i]->Solving == false && card[i]->isSolve == false) {
				stackIndex[flip] = i;
				stackk[flip] = card[i]->id;
				if (flip == 0) {
					card[i]->Solving = true;
				}
				else if (flip == 1) {
					card[i]->Solving = true;
					matchCheck = 1;
				}
				flip++;
				Step++;
				break;
			}
		}
		clickstat = 1;
	}
	else {
		clickstat = 0;
	}
}

void GSPlay::Update(float deltaTime)
{
	m_step->UpdateText(deltaTime, "Step: " + std::to_string(Step));
	m_BackGround->Update(deltaTime);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}

	
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_step->Draw();
	for (auto it : m_listButton) (it)->Draw();
	for (int i = 0; i < 24; i++) (cardDown[i])->Draw();
	if (matchCheck == 1) {
		card[stackIndex[0]]->Solving = true;
		card[stackIndex[1]]->Solving = true;
		matchCheck = 2;
	}
	else if (matchCheck == 2) {
		Sleep(1000);
		if (stackk[0] == stackk[1]) {
			card[stackIndex[0]]->isSolve = true;
			card[stackIndex[1]]->isSolve = true;
		}
		else {
			card[stackIndex[0]]->Solving = false;
			card[stackIndex[1]]->Solving = false;
		}
		flip = 0;
		matchCheck = 0;
	}
	for (int i = 0; i < 24; i++) {
		if (card[i]->isSolve == true || card[i]->Solving == true) {
			(card[i])->Draw();
		}
	}
	
}
