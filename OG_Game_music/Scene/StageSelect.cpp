#include "StageSelect.h"
#include "../Input.h"
#include "../Game.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
#include "SceneManager.h"
#include <DxLib.h>

void StageSelect::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0)
	{
		updateFunc_ = &StageSelect::NormalUpdate;
		drawFunc_ = &StageSelect::NormalDraw;
	}
}

void StageSelect::NormalUpdate(Input& input)
{
	if (input.IsTriggered("UP") && cursolPosY > 35)
	{
		cursolPosY -= 60;
	}

	if (input.IsTriggered("DOWN") && cursolPosY < 35 * 2)
	{
		cursolPosY += 60;
	}

	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &StageSelect::FadeOutUpdate;
		drawFunc_ = &StageSelect::FadeDraw;
	}
}

void StageSelect::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		if (cursolPosY == 35)
		{
			manager_.ChangeScene(std::make_shared<GamePlayingScene>(manager_));
		}
		else if (cursolPosY == 95)
		{
			manager_.ChangeScene(std::make_shared<TitleScene>(manager_));
		}
	}
}

void StageSelect::FadeDraw()
{
	//通常の描画
	//playボタン
	DrawBox(50, 40, 160, 80, 0xffffff, false);
	DrawString(84, 52, "stage1", 0xffffff);

	//Quitボタン
	DrawBox(50, 100, 160, 140, 0xffffff, false);
	DrawString(80, 112, "return", 0xffffff);

	//カーソル
	DrawBox(cursolPosX, cursolPosY, cursolPosX + 120, cursolPosY + 50, 0xff0000, false);

	DrawString(0, 0, "StageSelectScene", 0xffffff);


	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void StageSelect::NormalDraw()
{
	//playボタン
	DrawBox(50, 40, 160, 80, 0xffffff, false);
	DrawString(84, 52, "stage1", 0xffffff);

	//Quitボタン
	DrawBox(50, 100, 160, 140, 0xffffff, false);
	DrawString(80, 112, "return", 0xffffff);

	//カーソル
	DrawBox(cursolPosX, cursolPosY, cursolPosX + 120, cursolPosY + 50, 0xff0000, false);


	DrawString(0, 0, "StageSelectScene", 0xffffff);
}

StageSelect::StageSelect(SceneManager& mgr) : 
	Scene(mgr),
	cursolPosX(45),
	cursolPosY(35)
{
	updateFunc_ = &StageSelect::FadeInUpdate;
	drawFunc_ = &StageSelect::FadeDraw;
	frame_ = 60;
}

StageSelect::~StageSelect()
{

}

void StageSelect::Update(Input& input)
{
	(this->*updateFunc_)(input);

}

void StageSelect::Draw()
{
	(this->*drawFunc_)();
}
