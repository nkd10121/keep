#include "StageBase.h"
#include "../SceneManager.h"
#include "../StageSelect.h"
#include "../GameoverScene.h"
#include "../PauseScene.h"
#include "../../Player.h"
#include "../../Efect/GoalEfect.h"
#include "../../Util/Input.h"
#include "../../Enemy/Line/EnemyLineBase.h"
#include "../../Enemy/Line/EnemyBox.h"
#include "../../Enemy/Line/EnemyLineFromUpper.h"
#include "../../Enemy/Line/EnemyLineDown.h"
#include "../../Enemy/Line/EnemyLineFromLeft.h"
#include "../../Enemy/Line/EnemyLineFromRight.h"
#include "../../Enemy/Circle/EnemyCircleBase.h"
#include "../../Enemy/Circle/EnemyCircle.h"
#include "../../Enemy/Circle/EnemyBurst.h"
#include "../../Enemy/Circle/EnemyCircleScaling.h"
#include "../../Goal.h"

#include "StageTutorial.h"
namespace
{
	//フェードイン、フェードアウトにかかる時間
	constexpr int kFadeFrame = 30;
	//画面内に表示する敵の最大数
	constexpr int kEnemyLineMax = 80;

	constexpr int kEnemyCircleMax = 64;
	//enemyが出てくるクールタイム
	constexpr int kEnemyInterval = 30;
	//checkpointLineが出てくるクールタイム
	constexpr int kCheckPointLineInterval = 1200;
}

StageBase::StageBase(SceneManager& mgr)	:
	Scene(mgr),
	eneLinePos(0.0f, 0.0f),
	lineWidth(0),
	eneCirclePos(0, 0),
	eneCircleBurstVec(0, 0),
	eneCircleRadius(0),
	eneCircleBurstSpeed(0),
	fadeFrame(0),
	frame(0),
	onGoal(false)
{

	//ゲーム画面描画先の生成
	//画面サイズと同じ大きさのグラフィックデータを生成する
	m_gameScreenHandle = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	//メモリ確保
	player = new Player;
	player->Init(true);
	

	//eneLine.resize(kEnemyLineMax);

	//for (int i = 0; i < eneLine.size(); i++)
	//{
	//	eneLine[i] = nullptr;
	//}

	//eneCircle.resize(kEnemyCircleMax);

	//for (int i = 0; i < eneCircle.size(); i++)
	//{
	//	eneCircle[i] = nullptr;
	//}

	goal = new Goal;
	goal->Start();

	goalEfect = new GoalEfect;

	updateFunc_ = &StageBase::FadeInUpdate;
	drawFunc_ = &StageBase::FadeDraw;
	fadeFrame = 60;
}

StageBase::~StageBase()
{
	delete player;
	player = nullptr;

	for (int i = 0; i < eneLine.size(); i++)
	{
		if (eneLine[i] != nullptr)
		{
			delete eneLine[i];
			eneLine[i] = nullptr;
		}
	}

	for (int i = 0; i < eneCircle.size(); i++)
	{
		if (eneCircle[i] != nullptr)
		{
			delete eneCircle[i];
			eneCircle[i] = nullptr;
		}
	}

	delete goal;
	goal = nullptr;
}

void StageBase::Update(Input& input)
{
	//フレーム数をカウント
	frame++;

	//更新
	player->Update(input);
	//enemy->Update();

	//当たり判定の設定
	playerCol = player->GetColRect();

	//enemyLineの更新
	for (int i = 0; i < eneLine.size(); i++)
	{
		if (eneLine[i])
		{
			eneLine[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!eneLine[i]->isExist())
			{
				//メモリを解放する
				delete eneLine[i];
				eneLine[i] = nullptr;	//使っていないとわかるように

				eneLine.erase(eneLine.begin() + i);

				/*予測線問題を解決しようとした後*/
				//eneLine.erase(eneLine.begin() + i);
				//eneLine[i] = nullptr;	//使っていないとわかるように
				//eneLine.resize(eneLine.size() + 1);
			}
			else
			{
				if (m_shakeFrame == 0)
				{
					m_shakeFrame = eneLine[i]->GetShakeFrame();
					m_amp = 20;
				}

				Col enemyLineCol = eneLine[i]->GetColRect();
				if (playerCol.IsCollision(enemyLineCol))
				{
					PlayerHit();
				}
			}
		}
	}

	for (int i = 0; i < eneCircle.size(); i++)
	{
		if (eneCircle[i])
		{
			eneCircle[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!eneCircle[i]->isExist())
			{
				//メモリを解放する
				delete eneCircle[i];
				eneCircle[i] = nullptr;	//使っていないとわかるように

				eneCircle.erase(eneCircle.begin() + i);
			}
			else
			{
				Col enemyCircleCol = eneCircle[i]->GetColRect();
				if (playerCol.IsCollisionCircle(enemyCircleCol))
				{
					PlayerHit();
				}
			}
		}
	}
	//enemyLineが出てくるカウントを増やして
	//規定数を超えたら敵が出てくるように

	///////////////////////// いったん敵をランダム実装 ////////////////////////////////
	////敵の生成をする
	//if (enemyGenerateFrame % 10 == 0)
	//{
	//	switch (GetRand(6))
	//	{
	//	case 0:
	//		eneCirclePos = { (float)GetRand(Game::kScreenWidth),(float)GetRand(Game::kScreenHeight) };
	//		eneCircleBurstVec = { GetRandF(20) - 10,GetRandF(20) - 10 };
	//		eneCircleBurstSpeed = GetRand(20) + 10;
	//		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, GetRand(20) + 10, GetRand(30) + 30);
	//		break;
	//	case 1:
	//		lineWidth = GetRand(40) + 20;
	//		eneLinePos = { static_cast<float>(GetRand(Game::kScreenWidth - lineWidth * 2)), 0 };
	//		CreateEnemyLineFrom(eneLinePos, lineWidth, GetRand(30) + 20, GetRand(30) + 50, new EnemyLineFromUpper);
	//		break;
	//	case 2:
	//		lineWidth = GetRand(40) + 20;
	//		eneLinePos = { static_cast<float>(GetRand(Game::kScreenWidth - lineWidth * 2)),0 };
	//		CreateEnemyLineFrom(eneLinePos, lineWidth, GetRand(30) + 20, GetRand(30) + 50, new EnemyLineDown);
	//		break;
	//	case 3:
	//		lineWidth = GetRand(40) + 20;
	//		eneLinePos = { 0,  static_cast<float>(GetRand(Game::kScreenHeight - lineWidth * 2)) };
	//		CreateEnemyLineFrom(eneLinePos, lineWidth, GetRand(30) + 20, GetRand(30) + 50, new EnemyLineFromRight);
	//		break;
	//	case 4:
	//		lineWidth = GetRand(40) + 20;
	//		eneLinePos = { 0,  static_cast<float>(GetRand(Game::kScreenHeight - lineWidth * 2)) };
	//		CreateEnemyLineFrom(eneLinePos, lineWidth, GetRand(30) + 20, GetRand(30) + 50, new EnemyLineFromLeft);
	//		break;
	//	case 5:
	//		CreateEnemyCircle(static_cast<float>(GetRand(Game::kScreenHeight - eneCircleRadius * 2) + eneCircleRadius), GetRand(60) + 20, false);
	//		break;
	//	case 6:
	//		eneCirclePos = { static_cast<float>(GetRand(Game::kScreenWidth)), static_cast<float>(GetRand(Game::kScreenHeight)) };
	//		eneCircleRadius = GetRand(100);
	//		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, GetRand(30) + 30, GetRand(60) + 60);
	//		break;
	//	}
	//}
	////////////////////////////////////////////////////////////////////////////

	//画面揺れフレームのカウントダウン
	if (m_shakeFrame > 0)
	{
		m_shakeFrame--;
		m_amp *= 0.88f;
		if (m_amp < 0.01f)
		{
			m_amp = 0;
		}
	}

	if (input.IsTriggered("Goal"))
	{
		goalFlag = true;
	}

	if (onGoal)
	{
		isStartGoalEfect = true;
		goalEfect->Init(player->GetPlayerPos());
		onGoal = false;
		m_manager.sManager.PlaySE("GoalSE");

	}

	if (isStartGoalEfect)
	{
		goalEfectFrame++;
		goalEfect->Update();
	}

	if (isSoundFadeOut)
	{
		soundFadeFrame++;
	}

	if (m_isHitFlash)
	{
		alpha += 101;
		if (alpha >= 200)
		{
			m_isHitFlash = false;
		}
	}
	else
	{
		if (alpha > 0)
		{
			alpha -= 40;
		}
	}

	(this->*updateFunc_)(input);
}

void StageBase::Draw()
{
	//進捗関係
	DrawBox(520, 20, 760, 30, 0x222222, true);
	DrawBox(520, 20, progressPos, 30, 0x00ffff, true);

	SetDrawScreen(m_gameScreenHandle);
	//描画先スクリーンをクリアする
	ClearDrawScreen();

	if (isStartGoalEfect)
	{
		goalEfect->Draw();
	}

	//enemy->Draw();
	for (int i = 0; i < eneLine.size(); i++)
	{
		if (eneLine[i])
		{
			eneLine[i]->Draw();
		}
	}


	player->Draw();

	for (int i = 0; i < eneCircle.size(); i++)
	{
		if (eneCircle[i])
		{
			eneCircle[i]->Draw();
		}
	}


	if (goalFlag)
	{
		if (!goal->isExist())
		{
			goalFlag = false;
			delete goal;
			goal = nullptr;
		}
		else
		{
			goal->Draw();
		}
	}


	//バックバッファに書き込む設定に戻しておく
	SetDrawScreen(DX_SCREEN_BACK);

	//ゲーム画面をバックバッファに描画する
	int screenX = 0;
	int screenY = 0;

	if (m_shakeFrame > 0)
	{
		//画面揺れ
		//screenX = GetRand(16) - 8;
		//screenY = GetRand(16) - 8;

		screenX = m_amp * GetRand(2) - 1;
		screenY = m_amp * GetRand(2) - 1;
	}

	DrawRectGraph(screenX, screenY,
		0, 0, Game::kScreenWidth, Game::kScreenHeight,
		m_gameScreenHandle, true, false);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x660066, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);


#ifdef _DEBUG
	//デバッグ用
	//DrawFormatString(640, 0, 0xffffff, "%.2f", nowTime * 0.000001f);
	DrawFormatString(640, 16, 0xff0000, "%d", frame);
#endif
	(this->*drawFunc_)();

}

void StageBase::CreateEnemyLineFrom(Vec2 pos, int width, int first, int second, EnemyLineBase* enemy)
{
	eneLine.resize(eneLine.size() + 1);
	for (int i = 0; i < kEnemyLineMax; i++)
	{
		if (!eneLine[i])
		{
			eneLine[i] = enemy;
			eneLine[i]->Start(pos, width,first,second);
			return;
		}
	}
	delete enemy;
}

void StageBase::CreateEnemyBox(Vec2 pos, int size, int speed, int firstFrame, int secondFrame,bool isPre)
{
	eneLine.resize(eneLine.size() + 1);
	for (int i = 0; i < kEnemyLineMax; i++)
	{
		if (!eneLine[i])
		{
			eneLine[i] = new EnemyBox;
			eneLine[i]->Start(pos, size, speed, firstFrame, secondFrame,isPre);
			return;
		}
	}
}

void StageBase::CreateEnemyCircle(float pos, int radius, bool isSmooth)
{
	eneCircle.resize(eneCircle.size() + 1);

	for (int i = 0; i < kEnemyCircleMax; i++)
	{
		if (!eneCircle[i])
		{
			eneCircle[i] = new EnemyCircle;
			eneCircle[i]->Start(pos, radius, isSmooth);
			return;
		}
	}
}

void StageBase::CreateEnemyBurst(Vec2 pos, Vec2 vec, int speed, int first, int second)
{
	eneCircle.resize(eneCircle.size() + 1);

	for (int i = 0; i < kEnemyCircleMax; i++)
	{
		if (!eneCircle[i])
		{
			eneCircle[i] = new EnemyBurst(this);
			eneCircle[i]->Start(pos, vec, speed,first,second);
			return;
		}
	}
}

void StageBase::CreateEnemyCircleScaling(Vec2 pos, int rad, int first, int second, int speed)
{
	eneCircle.resize(eneCircle.size() + 1);

	for (int i = 0; i < kEnemyCircleMax; i++)
	{
		if (!eneCircle[i])
		{
			eneCircle[i] = new EnemyCircleScaling;
			eneCircle[i]->Start(pos, rad, first, second,speed);
			return;
		}
	}
}

void StageBase::AddEnemy(EnemyLineBase* test)
{
	eneLine.resize(eneLine.size() + 1);
	for (int i = 0; i < kEnemyLineMax; i++)
	{
		if (!eneLine[i])
		{
			eneLine[i] = test;
			eneLine[i]->Start();
			return;
		}
	}
}

void StageBase::PlayerHit()
{
	player->HitEnemy();
	m_shakeFrame = 16;
	m_amp = 20;
	m_manager.sManager.PlaySE("hitSE");
	m_isHitFlash = true;
}

void StageBase::FadeInUpdate(Input& input)
{

	fadeFrame--;
	if (fadeFrame <= 0)
	{
		updateFunc_ = &StageBase::NormalUpdate;
		drawFunc_ = &StageBase::NormalDraw;
	}
}

void StageBase::NormalUpdate(Input& input)
{
	//TODO:ステージクリアした時にステージセレクトに戻る
	if (input.IsTriggered("end"))
	{
		updateFunc_ = &StageBase::FadeOutUpdate;
		drawFunc_ = &StageBase::FadeDraw;
	}
	//TODO:Escape or メニューボタンでPause画面に移動
	if (input.IsTriggered("pause"))
	{
		m_manager.sManager.StopBGM("stage1");
		m_manager.sManager.StopBGM("stage2");
		m_manager.sManager.StopBGM("Tutorial");
		//m_manager.sManager.Stop("stage2");
		m_manager.PushScene(std::make_shared<PauseScene>(m_manager));
	}

	if (player->ReturnHitEnemyNum() >= 4 || goalEfectFrame >= 120)
	{
		updateFunc_ = &StageBase::FadeOutUpdate;
		drawFunc_ = &StageBase::FadeDraw;
	}
}

void StageBase::FadeOutUpdate(Input& input)
{
	fadeFrame++;
	if (fadeFrame >= kFadeFrame)
	{
		m_manager.sManager.StopBGM("stage1");
		m_manager.sManager.StopBGM("stage2");
		m_manager.sManager.StopBGM("Tutorial");

		if (player->ReturnHitEnemyNum() >= 4)
		{
			m_manager.ChangeScene(std::make_shared<GameoverScene>(m_manager));
		}
		else
		{
			m_manager.ChangeScene(std::make_shared<StageSelect>(m_manager));
		}
	}
}

void StageBase::FadeDraw()
{
	int alpha = 255 * fadeFrame / kFadeFrame;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void StageBase::NormalDraw()
{

}
