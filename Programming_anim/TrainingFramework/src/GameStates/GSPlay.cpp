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
int value[5][5];
int step;
int Time;
const int CardNo = 12;           //số lượng các quân bài là 12 => có 24 lá bài
const int GameWidth = 6;
const int GameHeight = 4;        //Các lá bài được sắp thành ma trận 4x6 
const int CardSizeW = 160;
const int CardSizeH = 160;         //kích thước của các lá bài là 86x64 pixel
const int CardSpacing = 16;
int OpenedCount;	//Số lá bài đã được mở 
int CardCount[CardNo];
int CardMatrix[GameHeight][GameWidth];			// ma trận các lá bài
bool CardOpened[GameHeight][GameWidth];       //tạo ma trận sấp ngửa
bool FirstCardOpened;        //Mỗi lần mở 2 lá bài, nếu biến này bằng true,
							 // nghĩa là lá bài thứ nhất đã mở
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
	m_step = std::make_shared< Text>(shader, font, "Step: " + std::to_string(step), TEXT_COLOR::RED, 1.0);
	m_step->Set2DPosition(Vector2(5, 30));

	m_time = std::make_shared< Text>(shader, font, "Time: " + std::to_string(Time), TEXT_COLOR::RED, 1.0);
	m_time->Set2DPosition(Vector2(1000, 25));

	int tmp = 0;
	for (int i = 0; i < GameHeight; i++) {
		for (int j = 0; j < GameWidth; j++) {
			card[tmp] = std::make_shared <Card>(ResourceManagers::GetInstance()->GetModel("Sprite2D"),
				ResourceManagers::GetInstance()->GetShader("TextureShader"),
				ResourceManagers::GetInstance()->GetTexture(ImagePaths[tmp % 12]));
			card[tmp]->SetSize(160, 160);

			tmp++;
		}
	}
}
void GSPlay::Newgame()
{
	int i, j, k;

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
				k = rand() % (24);      //tạo đối tượng sinh số ngẫu nhiên
			} while (CardCount[k] == 0);    // Nếu CardCount[k] == 0 nghĩa là 
											//quân bài thứ k đã sử dụng hết 
											//các lá bài, cần tìm k khác.
			CardMatrix[i][j] = k;       //lá bài tại ô i, j là quân bài thứ k
			CardCount[k]--;            //quân bài thứ k đã dùng 1 lá bài
			CardOpened[i][j] = false;     //đầu tiên, lá bài là sấp
		}
	OpenedCount = 0;              //chưa có lá bài nào mở
	FirstCardOpened = false;      //Mỗi lần mở 2 lá bài, đánh dấu lá bài thứ nhất chưa mở
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

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		it->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
	/*for (auto it : card) {
		it->HandleTouchEvents(x, y, WM_LBUTTONDOWN);
		CardClick(x, y);
		if ((it)->IsHandle()) break;
	}*/

}

void GSPlay::Update(float deltaTime)
{
	m_step->UpdateText(deltaTime, "Step: " + std::to_string(step));
	m_time->UpdateText(deltaTime, "Time: " + std::to_string(Time));
	m_BackGround->Update(deltaTime);

	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	Newgame();

}

void GSPlay::Draw()
{
	m_BackGround->Draw();

	m_step->Draw();
	m_time->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
	Newgame();
	for (int i = 0; i < GameHeight; i++)
		for (int j = 0; j < GameWidth; j++) {
			if (CardOpened[i, j]) {
				card[CardMatrix[i][j]]->Set2DPosition((CardSizeW + CardSpacing)* (j + 1), (CardSizeH + CardSpacing)* (i + 1));
				card[CardMatrix[i][j]]->Draw();
			}
		}
}

void GSPlay::DrawGame()
{
}
void GSPlay::CardClick(int x, int y)
{
	if (!CardOpened[y][x])                  //Nếu lá bài chưa mở
	{
		CardOpened[y][x] = true;            //Mở lá bài 
		DrawGame();                         //Vẽ là tình trạng các lá bài
		if (!FirstCardOpened)               //Trong một lần mở 2 lá bài
		{                                   //nếu lá bài đầu tiên chưa mở
			FirstCardOpened = true;         //Đánh dấu là đã mở  
			FirstCardX = x;                 //Lưu lại vị trí mở
			FirstCardY = y;
		}
		else                                //nếu lá bài đầu tiên đã mở  
		{
			//nếu lá bài thứ 2 giống lá bài đầu tiên 
			if (CardMatrix[y, x] == CardMatrix[FirstCardY, FirstCardX])
			{
				OpenedCount += 2;           //đánh dấu đã mở 2 lá bài
											//Nếu đã mở hết tất cả các lá bài, chúc mừng và khởi tạo game mới
				if (OpenedCount == GameWidth * GameHeight)
				{
					Newgame();
					DrawGame();
				}
			}
			else    //nếu lá bài thứ 2 khác lá bài đầu tiên 
			{
				Sleep(1000);         // tạm dừng 1 giây

									 // sấp cả hai lá bài lại
				CardOpened[y][x] = CardOpened[FirstCardY][FirstCardX] = false;
				DrawGame();                   //Vẽ là tình trạng các lá bài
			}
			FirstCardOpened = false;          //Bắt đầu lần mở 2 lá bài khác
		}
	}
}
