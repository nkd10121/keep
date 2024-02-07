#include "Stage3.h"
#include "../../Enemy/Line/EnemyLineFromUpper.h"
#include "../../Enemy/Line/EnemyLineDown.h"
#include "../../Enemy/Line/EnemyLineFromLeft.h"
#include "../../Enemy/Line/EnemyLineFromRight.h"

Stage3::Stage3(SceneManager& mgr):
	StageBase(mgr)
{
}

Stage3::~Stage3()
{
}

void Stage3::Update(Input& input)
{
	//�G�̐���������

	if (frame % 10 == 0)
	{
		float x = static_cast<float>(frame / 10);

		if (1280 - x * 36 > 0)
		{
			CreateEnemyBox(Vec2{ 1280 - x * 36 ,360 }, 20, 4, 40, 200, false);
		}
	}

	
	//if (enemyGenerateFrame % 10 == 0)
	//{
	//	switch (GetRand(7))
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
	//	case 7:
	//		int size = GetRand(100) + 40;
	//		Vec2 pos = { static_cast<float>(GetRand(Game::kScreenWidth - size) + size / 2),static_cast<float>(GetRand(Game::kScreenHeight - size) + size / 2) };
	//		int first = GetRand(60) + 60;
	//		int second = GetRand(60) + first;
	//		CreateEnemyBox(pos, size, GetRand(20) + 10, first, second);
	//	}
	//}

	StageBase::Update(input);
}

void Stage3::Draw()
{
	StageBase::Draw();
}
