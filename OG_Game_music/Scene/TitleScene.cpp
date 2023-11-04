#include <DxLib.h>
#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "StageSelect.h"
#include "OptionScene.h"

void TitleScene::FadeInUpdate(Input&)
{
	frame_--;
	if (frame_ <= 0)
	{
		//フェードインが終わったら状態を遷移する
		//次の遷移先
		updateFunc_ = &TitleScene::NormalUpdate;
		drawFunc_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("UP") && cursolPosY > 35)
	{
		cursolPosY -= 60;
	}

	if (input.IsTriggered("DOWN") && cursolPosY < 35 * 3)
	{
		cursolPosY += 60;
	}


	if (input.IsTriggered("OK") && cursolPosY == 155)
	{
		DxLib_End();
	}
	else if (input.IsTriggered("OK") && cursolPosY == 35)
	{
		//もしEnterキーが押されたらフェードインを始める
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
		frame_ = 0;
	}
	else if (input.IsTriggered("OK") && cursolPosY == 95)
	{
		//もしEnterキーが押されたらフェードインを始める
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
		frame_ = 0;
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	frame_++;
	if (frame_ >= 60)
	{
		//フェードアウトが終わったらSceneを変える
		if (cursolPosY == 35)
		{
			manager_.ChangeScene(std::make_shared<StageSelect>(manager_));
		}
		if (cursolPosY == 95)
		{
			manager_.ChangeScene(std::make_shared<OptionScene>(manager_));
		}

	}
}

void TitleScene::FadeDraw()
{
	//通常の描画(NormalDrawに書いたものをコピペする)
	DrawBox(50, 40, 160, 80, 0xffffff, false);
	DrawString(88, 52, "Play", 0xffffff);

	DrawBox(50, 100, 160, 140, 0xffffff, false);
	DrawString(80, 112, "Option", 0xffffff);

	DrawBox(50, 160, 160, 200, 0xffffff, false);
	DrawString(88, 172, "Quit", 0xffffff);

	//カーソル
	DrawBox(cursolPosX, cursolPosY, cursolPosX + 120, cursolPosY + 50, 0xff0000, false);

#ifdef _DEBUG
	DrawString(0, 0, "TitleScene", 0xffffff);
#endif

	//フェード暗幕
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	//Playボタン
	DrawBox(50, 40, 160, 80, 0xffffff, false);
	DrawString(88, 52, "Play", 0xffffff);

	//Optionボタン
	DrawBox(50, 100, 160, 140, 0xffffff, false);
	DrawString(80, 112, "Option", 0xffffff);
	
	//Quitボタン
	DrawBox(50, 160, 160, 200, 0xffffff, false);
	DrawString(88, 172, "Quit", 0xffffff);

	//カーソル
	DrawBox(cursolPosX, cursolPosY, cursolPosX + 120, cursolPosY + 50, 0xff0000, false);

#ifdef _DEBUG
	DrawString(0, 0, "TitleScene", 0xffffff);
#endif
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager),
	cursolPosX(45),
	cursolPosY(35)
{
	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	OutputDebugString("タイトルシーンがdeleteされました\n");
}

void TitleScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	(this->*drawFunc_)();
}
