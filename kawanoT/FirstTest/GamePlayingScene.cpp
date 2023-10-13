#include "GamePlayingScene.h"
#include "Input.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include <DxLib.h>

void GamePlayingScene::FadeInUpdate(Input& input)
{
	frame_--;
	if (frame_ <= 0)
	{
		updateFunc_ = &GamePlayingScene::NormalUpdate;
		drawFunc_ = &GamePlayingScene::NormalDraw;
	}
}

void GamePlayingScene::NormalUpdate(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
		drawFunc_ = &GamePlayingScene::FadeDraw;
	}
}

void GamePlayingScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		manager_.ChangeScene(new GameOverScene(manager_));
	}
}

void GamePlayingScene::FadeDraw()
{
	//í èÌÇÃï`âÊ
	DrawString(100, 100, L"GamePlayingScene", 0xffffff);
	DrawGraph(100, 100, handle_, true);

	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	DrawString(100, 100, L"GamePlayingScene", 0xffffff);
	DrawGraph(100, 100, handle_, true);
}

GamePlayingScene::GamePlayingScene(SceneManager& mgr) :
	Scene(mgr)
{
	handle_ = LoadGraph(L"./img/playing.png");
	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
	frame_ = 60;
}

GamePlayingScene::~GamePlayingScene()
{
	DeleteGraph(handle_);
}

void GamePlayingScene::Update(Input& input)
{
	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	(this->*drawFunc_)();
}
