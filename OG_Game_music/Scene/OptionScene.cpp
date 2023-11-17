#include "OptionScene.h""
#include "TitleScene.h""
#include "../Input.h"
#include "../Game.h"
#include "GamePlayingScene.h"
#include "SceneManager.h"
#include <DxLib.h>

void OptionScene::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0)
	{
		updateFunc_ = &OptionScene::NormalUpdate;
		drawFunc_ = &OptionScene::NormalDraw;
	}
}

void OptionScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("UP") && cursolPosY > 35)
	{
		cursolPosY -= 60;
	}

	if (input.IsTriggered("DOWN") && cursolPosY < 35 * 2)
	{
		cursolPosY += 60;
	}
	
	if (input.IsTriggered("OK") && cursolPosY == 95)
	{
		updateFunc_ = &OptionScene::FadeOutUpdate;
		drawFunc_ = &OptionScene::FadeDraw;
	}
}

void OptionScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		if (cursolPosY == 95)
		{
			manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
		}
	}
}

void OptionScene::FadeDraw()
{
	//通常の描画
	//playボタン
	DrawBox(50, 40, 160, 80, 0xffffff, false);
	DrawString(84, 52, "test", 0xffffff);

	//Quitボタン
	DrawBox(50, 100, 160, 140, 0xffffff, false);
	DrawString(80, 112, "return", 0xffffff);

	//カーソル
	DrawBox(cursolPosX, cursolPosY, cursolPosX + 120, cursolPosY + 50, 0xff0000, false);

	DrawString(0, 0, "OptionScene", 0xffffff);


	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void OptionScene::NormalDraw()
{
	//playボタン
	DrawBox(50, 40, 160, 80, 0xffffff, false);
	DrawString(84, 52, "test", 0xffffff);

	//Quitボタン
	DrawBox(50, 100, 160, 140, 0xffffff, false);
	DrawString(80, 112, "return", 0xffffff);

	//カーソル
	DrawBox(cursolPosX, cursolPosY, cursolPosX + 120, cursolPosY + 50, 0xff0000, false);


	DrawString(0, 0, "OptionScene", 0xffffff);
}

OptionScene::OptionScene(SceneManager& mgr) :
	Scene(mgr),
	cursolPosX(45),
	cursolPosY(35)
{
	updateFunc_ = &OptionScene::FadeInUpdate;
	drawFunc_ = &OptionScene::FadeDraw;
	frame_ = 60;
}

OptionScene::~OptionScene()
{

}

void OptionScene::Update(Input& input)
{
	(this->*updateFunc_)(input);

}

void OptionScene::Draw()
{
	(this->*drawFunc_)();
}
