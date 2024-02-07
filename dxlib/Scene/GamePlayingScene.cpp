//#include "GamePlayingScene.h"
//#include <DxLib.h>
//#include "SceneManager.h"
//#include "StageSelect.h"
//#include "GameoverScene.h"
//#include "PauseScene.h"
//#include "../Util/Game.h"
//#include "../Player.h"
//#include "../Util/Input.h"
//#include "../Enemy/Line/EnemyLineBase.h"
//#include "../Enemy/Line/EnemyLineFromUpper.h"
//#include "../Enemy/Line/EnemyLineDown.h"
//#include "../Enemy/Line/EnemyLineFromLeft.h"
//#include "../Enemy/Line/EnemyLineFromRight.h"
//#include "../Enemy/Circle/EnemyCircleBase.h"
//#include "../Enemy/Circle/EnemyCircle.h"
//#include "../Enemy/Circle/EnemyBurst.h"
//#include "../Enemy/Circle/EnemyCircleScaling.h"
//#include "../Goal.h"
//
//namespace
//{
//	//�t�F�[�h�C���A�t�F�[�h�A�E�g�ɂ����鎞��
//	constexpr int kFadeFrame = 30;
//	//��ʓ��ɕ\������G�̍ő吔
//	constexpr int kEnemyLineMax = 60;
//
//	constexpr int kEnemyCircleMax = 32;
//	//enemy���o�Ă���N�[���^�C��
//	constexpr int kEnemyInterval = 10;
//	//checkpointLine���o�Ă���N�[���^�C��
//	constexpr int kCheckPointLineInterval = 1200;
//}
//
//void GamePlayingScene::FadeInUpdate(Input& input)
//{
//	fadeFrame--;
//	if (fadeFrame <= 0)
//	{
//		updateFunc_ = &GamePlayingScene::NormalUpdate;
//		drawFunc_ = &GamePlayingScene::NormalDraw;
//	}
//}
//
//void GamePlayingScene::NormalUpdate(Input& input)
//{
//	//TODO:�X�e�[�W�N���A�������ɃX�e�[�W�Z���N�g�ɖ߂�
//	if (input.IsTriggered("OK"))
//	{
//		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
//		drawFunc_ = &GamePlayingScene::FadeDraw;
//	}
//	//TODO:Escape or ���j���[�{�^����Pause��ʂɈړ�
//	if (input.IsTriggered("pause"))
//	{
//		m_manager.PushScene(std::make_shared<PauseScene>(m_manager));
//	}
//
//	if (player->ReturnHitEnemyNum() >= 4)
//	{
//		updateFunc_ = &GamePlayingScene::FadeOutUpdate;
//		drawFunc_ = &GamePlayingScene::FadeDraw;
//	}
//}
//
//void GamePlayingScene::FadeOutUpdate(Input& input)
//{
//	fadeFrame++;
//	if (fadeFrame >= kFadeFrame)
//	{
//		if(onGoal)
//		{
//			m_manager.ChangeScene(std::make_shared<StageSelect>(m_manager));
//		}
//		else if (player->ReturnHitEnemyNum() == 4)
//		{
//			m_manager.ChangeScene(std::make_shared<GameoverScene>(m_manager));
//		}
//	}
//}
//
//void GamePlayingScene::FadeDraw()
//{
//	//�ʏ�̕`��
//	//DrawString(100, 100, "GamePlayingScene", 0xffffff);
//
//	int alpha = 255 * static_cast<float>(fadeFrame) / (float)kFadeFrame;
//	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
//	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
//}
//
//void GamePlayingScene::NormalDraw()
//{
//	//DrawString(100, 100, "GamePlayingScene", 0xffffff);
//	//DrawFormatString(10, 10, 0xffffff, "fps=%2.2f", fps);
//}
//
//
////-----------------------------------------------------------------//
//GamePlayingScene::GamePlayingScene(SceneManager& mgr) :
//	Scene(mgr),
//	enemyIntervalFrame(kEnemyInterval),
//	startTime(0),
//	nowTime(0),
//	eneLinePos(0.0f,0.0f),
//	lineWidth(0),
//	eneCirclePos(0,0),
//	eneCircleBurstVec(0,0),
//	eneCircleRadius(0),
//	eneCircleBurstSpeed(0),
//	fadeFrame(0),
//	enemyGenerateFrame(0),
//	frame(0),
//	checkPointCount(0),
//	checkPointX(1280),
//	isDrawCheckPointLine(false),
//	onGoal(false)
//{
//	startTime = (float)GetNowHiPerformanceCount();
//
//	//�������m��
//	player = new Player;
//
//	eneLine.resize(kEnemyLineMax);
//
//	for (int i = 0; i < eneLine.size(); i++)
//	{
//		eneLine[i] = nullptr;
//	}
//
//	eneCircle.resize(kEnemyCircleMax);
//
//	for (int i = 0; i < eneCircle.size(); i++)
//	{
//		eneCircle[i] = nullptr;
//	}
//
//	player->Init();
//
//	updateFunc_ = &GamePlayingScene::FadeInUpdate;
//	drawFunc_ = &GamePlayingScene::FadeDraw;
//	fadeFrame = 60;
//
//	goal = new Goal;
//	goal->Start();
//}
//
//GamePlayingScene::~GamePlayingScene()
//{
//	delete player;
//	player = nullptr;
//
//	for (int i = 0; i < eneLine.size(); i++)
//	{
//		if (eneLine[i] != nullptr)
//		{
//			delete eneLine[i];
//			eneLine[i] = nullptr;
//		}
//	}
//	
//	for (int i = 0; i < eneCircle.size(); i++)
//	{
//		if (eneCircle[i] != nullptr)
//		{
//			delete eneCircle[i];
//			eneCircle[i] = nullptr;
//		}
//	}
//
//	delete goal;
//	goal = nullptr;
//}
//
//void GamePlayingScene::Update(Input& input)
//{
//	nowTime = (float)GetNowHiPerformanceCount() - startTime;
//
//	//�t���[�������J�E���g
//	frame++;
//
//	//�X�V
//	player->Update(input);
//	//enemy->Update();
//
//	//�����蔻��̐ݒ�
//	Col playerCol = player->GetColRect();
//
//
//	//enemyLine�̍X�V
//	for (int i = 0; i < eneLine.size(); i++)
//	{
//		if(eneLine[i])
//		{
//			eneLine[i]->Update();
//
//			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
//			if (!eneLine[i]->isExist())
//			{
//				//���������������
//				delete eneLine[i];
//				eneLine[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
//
//				/*�\���������������悤�Ƃ�����*/
//				//eneLine.erase(eneLine.begin() + i);
//				//eneLine[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
//				//eneLine.resize(eneLine.size() + 1);
//			}
//			else
//			{
//				Col enemyLineCol = eneLine[i]->GetColRect();
//				if (playerCol.IsCollision(enemyLineCol))
//				{
//					player->HitEnemy();
//				}
//			}
//		}
//	}
//
//	for (int i = 0; i < eneCircle.size(); i++)
//	{
//		if (eneCircle[i])
//		{
//			eneCircle[i]->Update();
//
//			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
//			if (!eneCircle[i]->isExist())
//			{
//				//���������������
//				delete eneCircle[i];
//				eneCircle[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
//			}
//			else
//			{
//				Col enemyCircleCol = eneCircle[i]->GetColRect();
//				if (playerCol.IsCollisionCircle(enemyCircleCol))
//				{
//					player->HitEnemy();
//				}
//			}
//		}
//	}
//	//enemyLine���o�Ă���J�E���g�𑝂₵��
//	//�K�萔�𒴂�����G���o�Ă���悤��
//
//	enemyGenerateFrame++;
//
//	///////////////////////// ��������G�������_������ ////////////////////////////////
//	if (enemyGenerateFrame >= enemyIntervalFrame)
//	{
//		enemyGenerateFrame = 0;
//		switch (GetRand(6))
//		{
//		case 0:
//			eneCircleRadius = GetRand(60) + 20;
//			eneCirclePos.y = (float)GetRand(Game::kScreenHeight - eneCircleRadius * 2) + eneCircleRadius;
//			CreateEnemyCircle(eneCirclePos.y, eneCircleRadius, false);
//			break;
//		case 1:
//			lineWidth = GetRand(64) + 64;
//			eneLinePos = { (float)GetRand(Game::kScreenWidth - lineWidth),0 };
//			CreateEnemyLineFrom(eneLinePos,lineWidth,new EnemyLineFromUpper);
//			break;
//		case 2:
//			lineWidth = GetRand(64) + 64;
//			eneLinePos = { (float)GetRand(Game::kScreenWidth - lineWidth),0 };
//			CreateEnemyLineFrom(eneLinePos, lineWidth, new EnemyLineDown);
//			break;
//		case 3:
//			lineWidth = GetRand(64) + 64;
//			eneLinePos = { 0, (float)GetRand(Game::kScreenHeight - lineWidth) };
//			CreateEnemyLineFrom(eneLinePos, lineWidth,new EnemyLineFromLeft);
//			break;
//		case 4:
//			lineWidth = GetRand(64) + 64;
//			eneLinePos = { 0, (float)GetRand(Game::kScreenHeight - lineWidth) };
//			CreateEnemyLineFrom(eneLinePos, lineWidth, new EnemyLineFromRight);
//			break;
//		case 5:
//			eneCirclePos = {(float)GetRand(Game::kScreenWidth),(float)GetRand(Game::kScreenHeight)};
//			eneCircleBurstVec = {GetRandF(20) - 10,GetRandF(20) - 10 };
//			eneCircleBurstSpeed = GetRand(4) + 1;
//			CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed);
//			break;
//		case 6:
//			eneCirclePos = { (float)GetRand(Game::kScreenWidth),(float)GetRand(Game::kScreenHeight) };
//			eneCircleRadius = GetRand(100);
//			CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius);
//			break;
//		}
//	}
//	////////////////////////////////////////////////////////////////////////////
//
//	//�`�F�b�N�|�C���g�֌W
//	if (frame == kCheckPointLineInterval)
//	{
//		isDrawCheckPointLine = true;
//	}
//	
//	if (checkPointX <= player->GetPlayerPosX())
//	{
//		isDrawCheckPointLine = false;
//		checkPointX = 1280;
//	}
//
//	if (frame >= 300)
//	{
//		if (!goal->isExist())
//		{
//			delete goal;
//			goal = nullptr;
//		}
//		else
//		{
//			goal->Update();
//
//			Col goalCol = goal->GetColRect();
//
//			//�v���C���[�ƃS�[���������������̏���
//			if (playerCol.IsCollision(goalCol))
//			{
//				goal->Hit();
//				onGoal = true;
//			}
//		}
//	}
//	(this->*updateFunc_)(input);
//}
//
//void GamePlayingScene::Draw()
//{
//	//�w�i
//	DrawBox(0, 0, 1280, 720, 0x000000, true);
//
//	//enemy->Draw();
//	for (int i = 0; i < eneLine.size(); i++)
//	{
//		if (eneLine[i])
//		{
//			eneLine[i]->Draw();
//		}
//	}
//
//  	for (int i = 0; i < eneCircle.size(); i++)
//	{
//		if (eneCircle[i])
//		{
//			eneCircle[i]->Draw();
//		}
//	}
//
//	player->Draw();
//
//	(this->*drawFunc_)();
//
//	//�t���[������1500�ȏ�ɂȂ������A�`�F�b�N�|�C���g�̃��C����\������
//	if (isDrawCheckPointLine)
//	{
//		checkPointX -= 2;
//		DrawLine(checkPointX,0,checkPointX,720,0x00bfff,5);
//	}
//
//	if (frame >= 300)
//	{
//		if (!goal->isExist())
//		{
//			delete goal;
//			goal = nullptr;
//		}
//		else
//		{
//			goal->Draw();
//		}
//	}
//
//#ifdef _DEBUG
//	//�f�o�b�O�p
//	DrawFormatString(640, 0, 0xffffff, "%.2f", nowTime * 0.000001f);
//	//DrawFormatString(640, 0, 0xff0000, "%d", frame);
//#endif
//}
//
//void GamePlayingScene::CreateEnemyLineFrom(Vec2 pos, int width, int first, int second, EnemyLineBase* enemy)
//{
//	for (int i = 0; i < kEnemyLineMax; i++)
//	{
//		if (!eneLine[i])
//		{
//			eneLine[i] = enemy;
//			eneLine[i]->Start(pos, width,first,second);
//			return;
//		}
//	}
//	delete enemy;
//}
//
//void GamePlayingScene::CreateEnemyCircle(float pos, int radius, bool isSmooth)
//{
//	for (int i = 0; i < kEnemyCircleMax; i++)
//	{
//		if (!eneCircle[i])
//		{
//			eneCircle[i] = new EnemyCircle;
//			eneCircle[i]->Start(pos, radius, isSmooth);
//			return;
//		}
//	}
//}
//
//void GamePlayingScene::CreateEnemyBurst(Vec2 pos, Vec2 vec, int speed)
//{
//	//for (int i = 0; i < kEnemyCircleMax; i++)
//	//{
//	//	if (!eneCircle[i])
//	//	{
//	//		eneCircle[i] = new EnemyBurst(this);
//	//		eneCircle[i]->Start(pos,vec,speed);
//	//		return;
//	//	}
//	//}
//}
//
//void GamePlayingScene::CreateEnemyCircleScaling(Vec2 pos, int rad)
//{
//	for (int i = 0; i < kEnemyCircleMax; i++)
//	{
//		if (!eneCircle[i])
//		{
//			eneCircle[i] = new EnemyCircleScaling;
//			eneCircle[i]->Start(pos, rad, 60,120);
//			return;
//		}
//	}
//}
//
//void GamePlayingScene::AddEnemy(EnemyLineBase* test)
//{
//	for (int i = 0; i < kEnemyLineMax; i++)
//	{
//		if (!eneLine[i])
//		{
//			eneLine[i] = test;
//			eneLine[i]->Start();
//			return;
//		}
//	}
//}
//
////void GamePlayingScene::AddEnemy(EnemyCircleBase* test)
////{
////	for (int i = 0; i < kEnemyCircleMax; i++)
////	{
////		if (!eneCircle[i])
////		{
////			eneCircle[i] = test;
////			eneCircle[i]->Start();
////			return;
////		}
////	}
////}
