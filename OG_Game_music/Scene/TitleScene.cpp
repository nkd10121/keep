#include <DxLib.h>

#include "../Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "StageSelect.h"

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
	if (input.IsTriggered("OK"))
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
		manager_.ChangeScene(std::make_shared<StageSelect>(manager_));
	}
}

void TitleScene::FadeDraw()
{
	//通常の描画
	DrawBox(30, 20, 130, 60, 0xffffff, false);
	DrawString(45, 30, "Play", 0xffffff);
	DrawString(100, 100, "TitleScene", 0xffffff);

	//フェード暗幕
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawBox(30, 20, 130, 60, 0xffffff, false);
	DrawString(45, 30, "Play", 0xffffff);
	DrawString(100, 100, "TitleScene", 0xffffff);
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager)
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
