#include "Stage1.h"
#include "../SceneManager.h"
#include "../../Goal.h"
#include "../../Util/Col.h"

#include "../../Enemy/Line/EnemyLineFromRight.h"
#include "../../Enemy/Line/EnemyLineFromLeft.h"
#include "../../Enemy/Line/EnemyLineDown.h"

namespace
{
	//1回目の花火のフレーム
	constexpr int kFirstBurstFrame = 960;
	//2回目の花火のフレーム
	constexpr int kSecondBurstFrame = 1840;
	//3回目の花火のフレーム
	constexpr int kThirdBurstFrame = 2720;
	//花火のインターバル
	constexpr int kInterval = 55;
}

Stage1::Stage1(SceneManager& mgr) :
	StageBase(mgr)
{
	progressSpeed = 0.0538116f;
}

Stage1::~Stage1()
{
	m_manager.sManager.StopBGM("stage1");

}

void Stage1::Update(Input& input)
{
	if (isFirst)
	{
		m_manager.GetPtr(1);
		isFirst = false;
	}

	if (frame == 60)
	{
		m_manager.sManager.PlayBGM("stage1", true);
	}

	if (frame == 250)
	{
		eneCirclePos = { 320, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 250 + 20)
	{
		eneCirclePos = { 960, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 410)
	{
		eneCirclePos = { 320, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 410 + 20)
	{
		eneCirclePos = { 960, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 410 + 60)
	{
		eneCirclePos = { 640,0 };
		eneCircleBurstVec = { 0,1 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 8, 30);
	}

	if (frame == 680)
	{
		eneCirclePos = { 320, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 680 + 20)
	{
		eneCirclePos = { 960, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 840)
	{
		eneCirclePos = { 320, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 840 + 20)
	{
		eneCirclePos = { 960, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 840 + 60)
	{
		eneCirclePos = { 640,0 };
		eneCircleBurstVec = { 0,1 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 8, 30);
	}

	if (frame == kFirstBurstFrame)
	{
		CreateFireFlower(true, 28);
	}
	if (frame == kFirstBurstFrame + kInterval)
	{
		CreateFireFlower(false, 30);
	}
	if (frame == kFirstBurstFrame + kInterval * 2)
	{
		CreateFireFlower(true, 24);
	}
	if (frame == kFirstBurstFrame + kInterval * 3)
	{
		CreateFireFlower(false, 26);
	}
	if (frame == kFirstBurstFrame + kInterval * 4)
	{
		CreateFireFlower(true, 28);
	}
	if (frame == kFirstBurstFrame + kInterval * 5)
	{
		CreateFireFlower(false, 22);
	}
	if (frame == kFirstBurstFrame + kInterval * 6)
	{
		CreateFireFlower(true, 26);
	}
	if (frame == kFirstBurstFrame + kInterval * 7)
	{
		CreateFireFlower(false, 28);
	}
	if (frame == kFirstBurstFrame + kInterval * 8)
	{
		CreateFireFlower(true, 30);
	}
	if (frame == kFirstBurstFrame + kInterval * 9)
	{
		CreateFireFlower(false, 28);
	}
	if (frame == kFirstBurstFrame + kInterval * 10)
	{
		CreateFireFlower(true, 26);
	}
	if (frame == kFirstBurstFrame + kInterval * 11)
	{
		CreateFireFlower(false, 22);
	}
	if (frame == kFirstBurstFrame + kInterval * 12)
	{
		CreateFireFlower(true, 24);
	}
	if (frame == kFirstBurstFrame + kInterval * 13)
	{
		CreateFireFlower(false, 26);
	}

	if (frame == 1748)
	{
		eneCirclePos = { 640, 160 };
		eneCircleRadius = 40;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 80, 80);
	}
	if (frame == 1748 + 14 * 1)
	{
		eneCirclePos = { 640, 160 };
		eneCircleRadius = 80;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 80 - 14 * 1, 80 - 14 * 1);
	}
	if (frame == 1748 + 14 * 2)
	{
		eneCirclePos = { 640, 160 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 80 - 14 * 2, 80 - 14 * 2);
	}
	if (frame == 1748 + 14 * 3)
	{
		eneCirclePos = { 640, 160 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius,60,80);
	}


	if (frame == kSecondBurstFrame + kInterval * 0)
	{
		CreateFireFlower(true, 30);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 1)
	{
		CreateFireFlower(false, 22);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 2)
	{
		CreateFireFlower(true, 24);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 3)
	{
		CreateFireFlower(false, 28);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 4)
	{
		CreateFireFlower(true, 32);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 5)
	{
		CreateFireFlower(false, 26);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 6)
	{
		CreateFireFlower(true, 30);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 7)
	{
		CreateFireFlower(false, 22);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 8)
	{
		CreateFireFlower(true, 24);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 9)
	{
		CreateFireFlower(false, 26);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 10)
	{
		CreateFireFlower(true, 28);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 11)
	{
		CreateFireFlower(false, 26);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 12)
	{
		CreateFireFlower(true, 30);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 13)
	{
		CreateFireFlower(false, 24);
		CreateUnderLine(true);
	}
	if (frame == kSecondBurstFrame + kInterval * 14)
	{
		CreateFireFlower(true, 26);
		CreateUnderLine(false);
	}
	if (frame == kSecondBurstFrame + kInterval * 15)
	{
		CreateFireFlower(false, 28);
		CreateUnderLine(true);
	}

	if (frame == 2680)
	{
		eneCirclePos = { 640, 160 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 40, 60);
	}

	if (frame == kThirdBurstFrame + kInterval * 0)
	{
		CreateFireFlower(false, 34);
		CreateFireFlower(true, 34);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 1)
	{
		CreateFireFlower(true, 28);
		CreateFireFlower(false, 28);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 2)
	{
		CreateFireFlower(false, 22);
		CreateFireFlower(true, 22);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 3)
	{
		CreateFireFlower(true, 32);
		CreateFireFlower(false, 32);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 4)
	{
		CreateFireFlower(false, 28);
		CreateFireFlower(true, 28);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 5)
	{
		CreateFireFlower(true, 26);
		CreateFireFlower(false, 26);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 6)
	{
		CreateFireFlower(false, 24);
		CreateFireFlower(true, 24);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 7)
	{
		CreateFireFlower(true, 30);
		CreateFireFlower(false, 30);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 8)
	{
		CreateFireFlower(false, 28);
		CreateFireFlower(true, 28);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 9)
	{
		CreateFireFlower(true, 32);
		CreateFireFlower(false, 32);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 10)
	{
		CreateFireFlower(false, 24);
		CreateFireFlower(true, 24);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 11)
	{
		CreateFireFlower(true, 22);
		CreateFireFlower(false, 22);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 12)
	{
		CreateFireFlower(false, 28);
		CreateFireFlower(true, 28);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 13)
	{
		CreateFireFlower(true, 24);
		CreateFireFlower(false, 24);
		CreateUnderLine(true);
	}
	if (frame == kThirdBurstFrame + kInterval * 14)
	{
		CreateFireFlower(false, 28);
		CreateFireFlower(true, 28);
		CreateUnderLine(false);
	}
	if (frame == kThirdBurstFrame + kInterval * 15)
	{
		CreateFireFlower(true, 26);
		CreateFireFlower(false, 26);
		CreateUnderLine(true);
	}

	if (frame == 3280)
	{
		lineWidth = 100;
		eneLinePos = { 590, static_cast<float>(Game::kScreenHeight - lineWidth) - 180 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 100, 100, new EnemyLineDown);
	}

	if (frame == 3380)
	{
		eneCirclePos = { 640,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = 28;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 12, 197);
	}
	if (frame == 3380 + 30)
	{
		eneCirclePos = { 640,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = 28;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 12, 168);
	}
	if (frame == 3380 + 30 * 2)
	{
		eneCirclePos = { 640,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = 28;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 12, 139);
	}
	if (frame == 3380 + 30 * 3)
	{
		eneCirclePos = { 640,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = 28;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 12, 110);
	}

	if (frame == 3770)
	{
		eneCirclePos = { 320, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 3770 + 20)
	{
		eneCirclePos = { 960, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}

	if (frame == 3930)
	{
		eneCirclePos = { 320, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 3930 + 20)
	{
		eneCirclePos = { 960, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 3930 + 60)
	{
		eneCirclePos = { 640,0 };
		eneCircleBurstVec = { 0,1 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 8, 30);
	}

	if (frame == 4200)
	{
		eneCirclePos = { 320, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 4200 + 20)
	{
		eneCirclePos = { 960, 720 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}

	if (frame == 4360)
	{
		eneCirclePos = { 320, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 4360 + 20)
	{
		eneCirclePos = { 960, 0 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 10, 40);
	}
	if (frame == 4360 + 60)
	{
		eneCirclePos = { 640,0 };
		eneCircleBurstVec = { 0,1 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 8, 30);
	}

	if (frame == 4460)
	{
		goalFlag = true;
		isSoundFadeOut = true;
	}

	if (frame <= 4460)
	{
		progressPos += progressSpeed;
	}

	if (isSoundFadeOut)
	{
		m_manager.sManager.FadeOutBGM("stage1", soundFadeFrame);
	}

	StageBase::Update(input);

	if (goalFlag)
	{
		if (!goal->isExist())
		{
			delete goal;
			goal = nullptr;
		}
		else
		{
			goal->Update();

			Col goalCol = goal->GetColRect();

			//プレイヤーとゴールが当たった時の処理
			if (playerCol.IsCollision(goalCol))
			{
				m_manager.sManager.StopBGM("stage1");

				goal->Hit();
				m_manager.SetStageClearFlag(1);
				onGoal = true;
			}
		}
	}
}

void Stage1::Draw()
{
	StageBase::Draw();
}

void Stage1::CreateFireFlower(bool isRight, int speed)
{

	if (isRight)
	{
		eneCirclePos = { 1040,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = speed;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 8, 28);
	}
	else
	{
		eneCirclePos = { 280,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = speed;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 8, 28);
	}

}

void Stage1::CreateUnderLine(bool isRight)
{
	if (isRight)
	{
		lineWidth = 80;
		eneLinePos = { 1280, static_cast<float>(Game::kScreenHeight - lineWidth) };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 28, 60, new EnemyLineFromRight);
	}
	else
	{
		lineWidth = 80;
		eneLinePos = { 0, static_cast<float>(Game::kScreenHeight - lineWidth) };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 28, 60, new EnemyLineFromLeft);
	}
}
