#include "GamePlayingScene.h"
#include "../Input.h"
#include "StageSelect.h"
#include "SceneManager.h"
#include <DxLib.h>
#include "PauseScene.h"
#include "Player.h"
#include "../Enemy.h"

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
	//TODO:�X�e�[�W�N���A�������ɃX�e�[�W�Z���N�g�ɖ߂�
	if (input.IsTriggered("OK"))
	{
		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
		drawFunc_ = &GamePlayingScene::FadeDraw;
	}
	//TODO:Escape or ���j���[�{�^����Pause��ʂɈړ�
	else if (input.IsTriggered("pause"))
	{
		manager_.PushScene(std::make_shared<PauseScene>(manager_));
	}
}

void GamePlayingScene::FadeOutUpdate(Input& input)
{
	frame_++;
	if (frame_ >= 60)
	{
		//TODO:�X�e�[�W�Z���N�g��ʂɑJ��
		manager_.ChangeScene(std::make_shared<StageSelect>(manager_));
	}
}

void GamePlayingScene::FadeDraw()
{
	//�ʏ�̕`��
	DrawString(100, 100, "GamePlayingScene", 0xffffff);

	int alpha = 255 * static_cast<float>(frame_) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, 640, 480, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	DrawString(100, 100, "GamePlayingScene", 0xffffff);
	DrawFormatString(10, 10, 0xffffff, "fps=%2.2f", fps);
}

GamePlayingScene::GamePlayingScene(SceneManager& mgr) :
	Scene(mgr)
{
	//�������m��
	player = new Player;
	enemy = new Enemy;

	player->Init();
	enemy->Init();

	color = (0xffffff);

	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
	frame_ = 60;
}

GamePlayingScene::~GamePlayingScene()
{

}

void GamePlayingScene::Update(Input& input)
{
	player->Update(input);
	enemy->Update();

	Rect playerRect = player->GetColRect();
	Rect enemyRect = enemy->GetColRect();

	if (playerRect.IsCollision(enemyRect))
	{
#ifdef _DEBUG
		//printfDx("hit\n");
		color = (0xff0000);
#endif
	}
	else
	{
#ifdef _DEBUG
		color = (0xffffff);
#endif
	}

	enemy->SetColor(color);


	fps = GetFPS();
	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	//�w�i
	DrawBox(0, 0, 640, 640, GetColor(16, 4, 16), true);

	player->Draw();
	enemy->Draw();

	(this->*drawFunc_)();
}