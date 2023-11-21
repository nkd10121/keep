#include "GamePlayingScene.h"
#include <DxLib.h>
#include "SceneManager.h"
#include "StageSelect.h"
#include "PauseScene.h"
#include "../Game.h"
#include "../Player.h"
#include "../Input.h"
#include "../Enemy.h"
#include "../EnemyLine.h"

namespace
{
	//��ʓ��ɕ\������G�̍ő吔
	constexpr int kEnemyLineMax = 32;
	//enemyLine���o�Ă���N�[���^�C��
	constexpr int kEnemyLineInterval = 16;
	//checkpointLine���o�Ă���N�[���^�C��
	constexpr int kCheckPointLineInterval = 1200;
}

void GamePlayingScene::FadeInUpdate(Input& input)
{
	fadeFrame--;
	if (fadeFrame <= 0)
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
	fadeFrame++;
	if (fadeFrame >= 60)
	{
		//TODO:�X�e�[�W�Z���N�g��ʂɑJ��
		manager_.ChangeScene(std::make_shared<StageSelect>(manager_));
	}
}

void GamePlayingScene::FadeDraw()
{
	//�ʏ�̕`��
	//DrawString(100, 100, "GamePlayingScene", 0xffffff);

	int alpha = 255 * static_cast<float>(fadeFrame) / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void GamePlayingScene::NormalDraw()
{
	//DrawString(100, 100, "GamePlayingScene", 0xffffff);
	//DrawFormatString(10, 10, 0xffffff, "fps=%2.2f", fps);
}


//-----------------------------------------------------------------//
GamePlayingScene::GamePlayingScene(SceneManager& mgr) :
	Scene(mgr),
	color(0),
	fps(0.0f),
	fadeFrame(0),
	enemyLineInterval(0),
	frame(0),
	checkPointCount(0),
	checkPointX(1280),
	isDrawCheckPointLine(false)
{
	//�������m��
	player = new Player;
	enemy = new Enemy;

	eneLin.resize(kEnemyLineMax);

	for (int i = 0; i < kEnemyLineMax; i++)
	{
		eneLin[i] = nullptr;
	}

	player->Init();
	enemy->Init();

	color = (0xffffff);

	updateFunc_ = &GamePlayingScene::FadeInUpdate;
	drawFunc_ = &GamePlayingScene::FadeDraw;
	fadeFrame = 60;
}

GamePlayingScene::~GamePlayingScene()
{
	delete player;
	player = nullptr;

	delete enemy;
	enemy = nullptr;

	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i] != nullptr)
		{
			eneLin[i] = nullptr;
		}
	}
}

void GamePlayingScene::Update(Input& input)
{
	//�t���[�������J�E���g
	frame++;

	//�X�V
	player->Update(input);
	enemy->Update();

	//enemyLine�̍X�V
	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i])
		{
			eneLin[i]->Update();

			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!eneLin[i]->isExist())
			{
				//���������������
				delete eneLin[i];
				eneLin[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
			}

		}
	}

	//�����蔻��̐ݒ�
	Rect playerRect = player->GetColRect();
	Rect enemyRect = enemy->GetColRect();

	//�v���C���[�ƓG�������������̏���
	if (playerRect.IsCollision(enemyRect))
	{
		//Debag�p
#ifdef _DEBUG
		//printfDx("hit\n");
		color = (0xff0000);
#endif
		//player���m�b�N�o�b�N�����ď����̖��G���Ԃ�^����
		//�m�b�N�o�b�N->player�Ƀm�b�N�o�b�N�X�s�[�h��n���֐���p�ӂ���
		//	player���Ńm�b�N�o�b�N�X�s�[�h��0�ɂ��鏈��������
		player->HitEnemy();

		//���G���� -> bool��Ԃ��֐���p�ӂ���
		//	player����true�̎��_�łƓ����蔻��̍폜���s������������
	}
	else
	{
#ifdef _DEBUG
		color = (0xffffff);
#endif
	}

	//enemyLine����ʓ��ɕ\�����ꂽ�Ƃ��̓����蔻�菈��
	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i])
		{
			Rect enemyLineRect = eneLin[i]->GetColRect();
			if (playerRect.IsCollision(enemyLineRect))
			{
#ifdef _DEBUG
		//Debag�p
		//printfDx("hit\n");
				color = (0xff0000);
#endif
				//player���m�b�N�o�b�N�����ď����̖��G���Ԃ�^����
				//�m�b�N�o�b�N->player�Ƀm�b�N�o�b�N�X�s�[�h��n���֐���p�ӂ���
				//	player���Ńm�b�N�o�b�N�X�s�[�h��0�ɂ��鏈��������
				player->HitEnemy();

				//���G���� -> bool��Ԃ��֐���p�ӂ���
				//	player����true�̎��_�łƓ����蔻��̍폜���s������������
			}
			else
			{
#ifdef _DEBUG
				color = (0xffffff);
#endif
			}
		}
	}


	//enemyLine���o�Ă���J�E���g�𑝂₵��
	//�K�萔�𒴂�����G���o�Ă���悤��
	enemyLineInterval++;
	if (enemyLineInterval >= kEnemyLineInterval)
	{
		enemyLineInterval = 0;
		CreateEnemyLine();
	}

	enemy->SetColor(color);

	if (frame == kCheckPointLineInterval)
	{
		isDrawCheckPointLine = true;
	}
	
	if (checkPointX <= player->GetPlayerPosX())
	{
		isDrawCheckPointLine = false;
		checkPointX = 1280;
	}
	fps = GetFPS();
	(this->*updateFunc_)(input);
}

void GamePlayingScene::Draw()
{
	//�w�i
	DrawBox(0, 0, 1280, 720, 0x000000, true);

	enemy->Draw();
	for (int i = 0; i < eneLin.size(); i++)
	{
		if (eneLin[i])
		{
			eneLin[i]->Draw();

		}
	}

	player->Draw();

	(this->*drawFunc_)();

	//�t���[������1500�ȏ�ɂȂ������A�`�F�b�N�|�C���g�̃��C����\������
	if (isDrawCheckPointLine)
	{
		checkPointX -= 4;
		DrawLine(checkPointX,0,checkPointX,720,0xffffff,5);
	}
#ifdef _DEBUG
	//�f�o�b�O�p
	DrawFormatString(640, 0, 0xff0000, "%d", frame);
#endif
}

void GamePlayingScene::CreateEnemyLine()
{
	for (int i = 0; i < kEnemyLineMax; i++)
	{
		if (!eneLin[i])
		{
			eneLin[i] = new EnemyLine;
			eneLin[i]->Start();
			return;
		}
	}
}
