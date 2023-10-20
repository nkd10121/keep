#include <DxLib.h>

#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"

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
		manager_.ChangeScene(new GamePlayingScene(manager_));
	}
}

void TitleScene::FadeDraw()
{
	//通常の描画
	DrawString(100, 100, L"TitleScene", 0xffffff);
	DrawGraph(100, 100, handle_, true);

	//フェード暗幕
	int alpha = 255 * (float)frame_ / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0,0,640,480,0x000000,true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	DrawString(100, 100, L"TitleScene", 0xffffff);
	DrawGraph(100, 100, handle_, true);
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager)
{
	handle_ = LoadGraph(L"./img/title.png");
	frame_ = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{
	DeleteGraph(handle_);
}

void TitleScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void TitleScene::Draw()
{
	(this->*drawFunc_)();
}
