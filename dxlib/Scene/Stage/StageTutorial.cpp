#include "StageTutorial.h"
#include "../SceneManager.h"
#include "../../Enemy/Line/EnemyLineDown.h"
#include "../../Enemy/Line/EnemyLineFromUpper.h"
#include "../../Enemy/Line/EnemyLineFromRight.h"
#include "../../Enemy/Line/EnemyLineFromLeft.h"

#include "../../Goal.h"

StageTutorial::StageTutorial(SceneManager& mgr) :
	StageBase(mgr)
{
	progressSpeed = 0.0863309f;
}

StageTutorial::~StageTutorial()
{
}

void StageTutorial::Update(Input& input)
{
	if (isFirst)
	{
		m_manager.GetPtr(0);
		isFirst = false;
	}


	//一定の間をあけて音楽を再生する
	if (frame == 60)
	{
		m_manager.sManager.PlayBGM("Tutorial", true);
	}

	StageBase::Update(input);

	if (frame == 60)
	{
		eneCirclePos = { 1000, 0 };
		eneCircleRadius = 200;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 110, 200,40);

		eneCirclePos = { 1000, 720 };
		eneCircleRadius = 200;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 110, 200, 40);
	}

	if (frame == 280)
	{
		CreateEnemyBox(Vec2{ 280,160}, 120, 24, 110, 200);
		CreateEnemyBox(Vec2{ 280,720 - 160 }, 120, 24, 110, 200);
	}

	if (frame == 500)
	{
		lineWidth = 160;
		eneLinePos = { 560, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 90, 140, new EnemyLineFromUpper);
	}

	if (frame == 700)
	{
		lineWidth = 160;
		eneLinePos = { 0, 280 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 120, 180, new EnemyLineFromRight);
	}

	if (frame == 940)
	{
		lineWidth = 160;
		eneLinePos = { 560, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 90, 140, new EnemyLineDown);
	}

	if (frame == 1140)
	{
		lineWidth = 160;
		eneLinePos = { 0, 280 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 120, 180, new EnemyLineFromLeft);
	}

	if (frame == 1380)
	{
		eneCirclePos = { 1000,0 };
		eneCircleBurstVec = { 0,1 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 90);
	}

	if (frame == 1610)
	{
		eneCirclePos = { 1000,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 90);
	}

	if (frame == 1800)
	{
		eneCircleRadius = 160;
		eneCirclePos = { 1280,200 };
		CreateEnemyCircle(eneCirclePos.y, eneCircleRadius, false);
	}

	if (frame == 2020)
	{
		eneCircleRadius = 160;
		eneCirclePos = { 1280,520 };
		CreateEnemyCircle(eneCirclePos.y, eneCircleRadius, false);
	}

	if (frame == 2240)
	{
		lineWidth = 80;
		eneLinePos = { 0, 320 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 120, 400, new EnemyLineFromRight);

		eneCircleRadius = 120;
		eneCirclePos = { 1280,160 };
		CreateEnemyCircle(eneCirclePos.y, eneCircleRadius, false);
	}
	
	if (frame == 2440)
	{
		eneCircleRadius = 120;
		eneCirclePos = { 1280,560 };
		CreateEnemyCircle(eneCirclePos.y, eneCircleRadius, false);
	}

	if (frame == 2780)
	{
		goalFlag = true;
	}

	if (frame <= 2780)
	{
		progressPos += progressSpeed;
	}


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
				goal->Hit();
				onGoal = true;
			}
		}
	}
}

void StageTutorial::Draw()
{
	if (frame <= 1900)
	{
		m_manager.gManager.Draw(640, 360, 1.0f, 0.0f, "Tutorial1");
	}
	else if(frame <= 2780)
	{
		m_manager.gManager.Draw(640, 360, 1.0f, 0.0f, "Tutorial2");
	}
	else
	{
		m_manager.gManager.Draw(640, 360, 1.0f, 0.0f, "Tutorial3");
	}
	StageBase::Draw();
}
