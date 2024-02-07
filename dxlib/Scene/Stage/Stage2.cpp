#include "Stage2.h"
#include "../SceneManager.h"
#include "../../Enemy/Line/EnemyLineDown.h"
#include "../../Enemy/Line/EnemyLineFromUpper.h"
#include "../../Enemy/Line/EnemyLineFromRight.h"
#include "../../Enemy/Line/EnemyLineFromLeft.h"

#include "../../Goal.h"

Stage2::Stage2(SceneManager& mgr) :
	StageBase(mgr)
{
	progressSpeed = 0.0481154f;
}

Stage2::~Stage2()
{

}

void Stage2::Update(Input& input)
{
	//最初にstage2のアドレスを取っておく
	//ゲームオーバーからstage2に戻ってこれるように
	if (isFirst)
	{
		m_manager.GetPtr(2);
		isFirst = false;
	}

	//一定の間をあけて音楽を再生する
	if (frame == 10)
	{
		m_manager.sManager.PlayBGM("stage2", true);
	}

	StageBase::Update(input);

	//敵の生成をする
	//参考
	//width = 1280,height = 720
	//中心 640,360

	if (frame == 360)
	{
		eneCirclePos = { 1000,0 };
		eneCircleBurstVec = { -1,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 32);


	}
	else if (frame == 410 - 2)
	{
		eneCirclePos = { 1000,720 };
		eneCircleBurstVec = { -1,-8 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 32);


	}
	else if (frame == 460 - 4)
	{
		eneCirclePos = { 200,0 };
		eneCircleBurstVec = { 1,6 };
		eneCircleBurstSpeed = 30;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 32);

	}
	else if (frame == 510 - 6)
	{
		eneCirclePos = { 450,720 };
		eneCircleBurstVec = { 8,-2 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 32);

	}
	else if (frame == 560 - 8)
	{
		eneCirclePos = { 700,0 };
		eneCircleBurstVec = { 2,2 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 32);

	}
	else if (frame == 610 - 10)
	{
		eneCirclePos = { 1280,360 };
		eneCircleBurstVec = { -4,0 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 16, 32);

	}

	//750
	if (frame == 660)
	{
		lineWidth = 40;
		eneLinePos = { 560, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 70, 90, new EnemyLineFromUpper);
	}
	else if (frame == 660 + 2)
	{
		lineWidth = 40;
		eneLinePos = { 680, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 68, 88, new EnemyLineDown);
	}
	else if (frame == 660 + 18)
	{
		lineWidth = 40;
		eneLinePos = { 200, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 52, 72, new EnemyLineDown);
	}
	else if (frame == 660 + 20)
	{
		lineWidth = 40;
		eneLinePos = { 1040, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 50, 70, new EnemyLineFromUpper);
	}
	else if (frame == 660 + 36)
	{
		lineWidth = 40;
		eneLinePos = { 0, 280 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 34, 54, new EnemyLineFromLeft);
	}
	else if (frame == 660 + 38)
	{
		lineWidth = 40;
		eneLinePos = { 1280, 400 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 32, 52, new EnemyLineFromRight);
	}
	else if (frame == 660 + 54)
	{
		lineWidth = 40;
		eneLinePos = { 1280, 120 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 16, 36, new EnemyLineFromRight);
	}
	else if (frame == 660 + 56)
	{
		lineWidth = 40;
		eneLinePos = { 0, 560 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 14, 34, new EnemyLineFromLeft);
	}



	if (frame == 750)
	{
		eneCirclePos = { 280,0 };
		eneCircleBurstVec = { 2,1 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 800 - 2)
	{
		eneCirclePos = { 760,0 };
		eneCircleBurstVec = { -1,2 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 850 - 4)
	{
		eneCirclePos = { 1280,100 };
		eneCircleBurstVec = { -4,6 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 900 - 6)
	{
		eneCirclePos = { 1280,600 };
		eneCircleBurstVec = { -1,-2 };
		eneCircleBurstSpeed = 12;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 950 - 8)
	{
		eneCirclePos = { 600,720 };
		eneCircleBurstVec = { -1,-1 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1000 - 10)
	{
		eneCirclePos = { 80,720 };
		eneCircleBurstVec = { 4,-4 };
		eneCircleBurstSpeed = 24;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1050 - 12)
	{
		eneCirclePos = { 1000,0 };
		eneCircleBurstVec = { -2,1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}


	if (frame == 1000)
	{
		eneCirclePos = { 320, 360 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 100, 120);
	}
	else if (frame == 1010)
	{
		eneCirclePos = { 960, 360 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 100, 120);
	}
	else if (frame == 1020)
	{
		eneCirclePos = { 640, 360 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 100, 120);
	}


	if (frame == 1130)
	{
		eneCirclePos = { 100,0 };
		eneCircleBurstVec = { 2,4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1178)
	{
		eneCirclePos = { 1020,0 };
		eneCircleBurstVec = { -4,6 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1226)
	{
		eneCirclePos = { 1280,400 };
		eneCircleBurstVec = { -2,-4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1274)
	{
		eneCirclePos = { 560,720 };
		eneCircleBurstVec = { -2,-8 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1322)
	{
		eneCirclePos = { 160,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 24;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1370)
	{
		eneCirclePos = { 0,180 };
		eneCircleBurstVec = { 4,1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}

	if (frame == 1414)
	{
		lineWidth = 40;
		eneLinePos = { 0, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 70, 90, new EnemyLineFromUpper);
	}
	else if (frame == 1416)
	{
		lineWidth = 40;
		eneLinePos = { 1240, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 68, 88, new EnemyLineDown);
	}
	else if (frame == 1432)
	{
		lineWidth = 40;
		eneLinePos = { 600, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 52, 72, new EnemyLineDown);
	}
	else if (frame == 1434)
	{
		lineWidth = 40;
		eneLinePos = { 640, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 50, 70, new EnemyLineFromUpper);
	}
	else if (frame == 1450)
	{
		lineWidth = 40;
		eneLinePos = { 0, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 34, 54, new EnemyLineFromLeft);
	}
	else if (frame == 1452)
	{
		lineWidth = 40;
		eneLinePos = { 1280, 680 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 32, 52, new EnemyLineFromRight);
	}
	else if (frame == 1468)
	{
		lineWidth = 40;
		eneLinePos = { 1280, 320 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 16, 36, new EnemyLineFromRight);
	}
	else if (frame == 1470)
	{
		lineWidth = 40;
		eneLinePos = { 0, 360 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 14, 34, new EnemyLineFromLeft);
	}


	if (frame == 1510)//1
	{
		eneCirclePos = { 0,0 };
		eneCircleBurstVec = { 1,1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1560 - 4)//2
	{
		eneCirclePos = { 560,0 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1610 - 8)//3
	{
		eneCirclePos = { 1280,660 };
		eneCircleBurstVec = { -2,-1 };
		eneCircleBurstSpeed = 24;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1660 - 12)//4
	{
		eneCirclePos = { 240,0 };
		eneCircleBurstVec = { 2,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1710 - 16)//5
	{
		eneCirclePos = { 0,120 };
		eneCircleBurstVec = { 2,2 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1760 - 20)//6
	{
		eneCirclePos = { 1060,0 };
		eneCircleBurstVec = { -4,2 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1810 - 24)//7
	{
		eneCirclePos = { 340,0 };
		eneCircleBurstVec = { -1,2 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1860 - 28)//8
	{
		eneCirclePos = { 1280,60 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1910 - 32)//9
	{
		eneCirclePos = { 360,0 };
		eneCircleBurstVec = { -2,6 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 1960 - 36)//10
	{
		eneCirclePos = { 1280,400 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2010 - 40)//11
	{
		eneCirclePos = { 0,600 };
		eneCircleBurstVec = { 4,-3 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2060 - 44)//12
	{
		eneCirclePos = { 1100,0 };
		eneCircleBurstVec = { -4,1 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2110 - 48)//13
	{
		eneCirclePos = { 280,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2160 - 52)//14
	{
		eneCirclePos = { 280,0 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}


	//2216
	if (frame == 2160)
	{
		lineWidth = 40;
		eneLinePos = { 0, 180 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 70, 90, new EnemyLineFromLeft);
	}
	else if (frame == 2160 + 2)
	{
		lineWidth = 40;
		eneLinePos = { 920, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 68, 88, new EnemyLineFromUpper);
	}
	else if (frame == 2160 + 18)
	{
		lineWidth = 40;
		eneLinePos = { 0, 500 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 52, 72, new EnemyLineFromRight);
	}
	else if (frame == 2160 + 20)
	{
		lineWidth = 40;
		eneLinePos = { 320, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 50, 70, new EnemyLineDown);
	}
	else if (frame == 2160 + 36)
	{
		lineWidth = 40;
		eneLinePos = { 0, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 34, 54, new EnemyLineFromLeft);
	}
	else if (frame == 2160 + 38)
	{
		lineWidth = 40;
		eneLinePos = { 1240, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 32, 52, new EnemyLineFromUpper);
	}
	else if (frame == 2160 + 54)
	{
		lineWidth = 40;
		eneLinePos = { 0, 680 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 16, 36, new EnemyLineFromRight);
	}
	else if (frame == 2160 + 56)
	{
		lineWidth = 40;
		eneLinePos = { 0, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 14, 34, new EnemyLineDown);
	}


	if (frame == 1530)
	{
		eneCirclePos = { 200, 520 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 90, 110);
	}
	else if (frame == 1900)
	{
		eneCirclePos = { 1080, 200 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 106, 126);
	}



	//2360 ~ 2948 Burst
	if (frame == 2360)//1
	{
		eneCirclePos = { 1280,200 };
		eneCircleBurstVec = { -2,2 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);

		//CreateEnemyBox(Vec2{ 280,160 }, 140, 24, 24, 48);

	}
	else if (frame == 2360 + 46)//2
	{
		eneCirclePos = { 240,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);

		//CreateEnemyBox(Vec2{ 280,720 - 160 }, 140, 24, 24, 48);

	}
	else if (frame == 2360 + 46 * 2)//3
	{
		eneCirclePos = { 100,0 };
		eneCircleBurstVec = { 6,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 3)//4
	{
		eneCirclePos = { 1280,720 };
		eneCircleBurstVec = { -2,-4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 4)//5
	{
		eneCirclePos = { 820,0 };
		eneCircleBurstVec = { -4,2 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 5)//6
	{
		eneCirclePos = { 0,600 };
		eneCircleBurstVec = { 4,-2 };
		eneCircleBurstSpeed = 26;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 6)//7
	{
		eneCirclePos = { 80,0 };
		eneCircleBurstVec = { 2,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 7)//8
	{
		eneCirclePos = { 1280,0 };
		eneCircleBurstVec = { -6,2 };
		eneCircleBurstSpeed = 26;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 8)//9
	{
		eneCirclePos = { 400,720 };
		eneCircleBurstVec = { 2,-2 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 9)//10
	{
		eneCirclePos = { 0,300 };
		eneCircleBurstVec = { 8,-4 };
		eneCircleBurstSpeed = 24;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 10)//11
	{
		eneCirclePos = { 1000,720 };
		eneCircleBurstVec = { -8,-4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 11)//12
	{
		eneCirclePos = { 400,0 };
		eneCircleBurstVec = { 4,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 12)//13
	{
		eneCirclePos = { 800,720 };
		eneCircleBurstVec = { 1,-4 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 2360 + 46 * 13)//14
	{
		eneCirclePos = { 580,0 };
		eneCircleBurstVec = { -1,2 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}


	//2300
	if (frame == 2360)
	{
		eneCirclePos = { 640, 180 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 84, 104);

		eneCirclePos = { 640, 540 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 92, 112);
	}


	//2720 ~ 2728
	if (frame == 2720)
	{
		eneCirclePos = { 280, 360 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 96, 116);
	}
	else if (frame == 2720 + 4)
	{
		eneCirclePos = { 1000, 360 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 92, 112);
	}
	else if (frame == 2720 + 8)
	{
		eneCirclePos = { 640, 360 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 96, 116);
	}

	//3010 Line
	if (frame == 3010)
	{
		lineWidth = 40;
		eneLinePos = { 1180, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 70, 90, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 2)
	{
		lineWidth = 40;
		eneLinePos = { 1020, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 68, 88, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 18)
	{
		lineWidth = 40;
		eneLinePos = { 860, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 52, 72, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 20)
	{
		lineWidth = 40;
		eneLinePos = { 700, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 50, 70, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 36)
	{
		lineWidth = 40;
		eneLinePos = { 540, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 34, 54, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 38)
	{
		lineWidth = 40;
		eneLinePos = { 380, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 32, 52, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 54)
	{
		lineWidth = 40;
		eneLinePos = { 220, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 16, 36, new EnemyLineFromUpper);
	}
	else if (frame == 3010 + 56)
	{
		lineWidth = 40;
		eneLinePos = { 60, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 14, 34, new EnemyLineFromUpper);
	}


	//3110 ~  Burst
	if (frame == 3110)//1
	{
		eneCirclePos = { 200,0 };
		eneCircleBurstVec = { 4,4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);

		//CreateEnemyBox(Vec2{ 280,160 }, 120, 24, 28, 40);
	}
	else if (frame == 3110 + 46)//2
	{
		eneCirclePos = { 40,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);

	}
	else if (frame == 3110 + 46 * 2)//3
	{
		eneCirclePos = { 1000,720 };
		eneCircleBurstVec = { -2,-4 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 3)//4
	{
		eneCirclePos = { 1000,0 };
		eneCircleBurstVec = { -4,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 4)//5
	{
		eneCirclePos = { 600,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 5)//6
	{
		eneCirclePos = { 1280,400 };
		eneCircleBurstVec = { -6,-1 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 6)//7
	{
		eneCirclePos = { 0,0 };
		eneCircleBurstVec = { 4,4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 7)//8
	{
		eneCirclePos = { 280,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 8)//9
	{
		eneCirclePos = { 1280,600 };
		eneCircleBurstVec = { -2,-4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 9)//10
	{
		eneCirclePos = { 700,0 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 10)//11
	{
		eneCirclePos = { 1140,720 };
		eneCircleBurstVec = { -2,-4 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 11)//12
	{
		eneCirclePos = { 280,0 };
		eneCircleBurstVec = { 2,1 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 12)//13
	{
		eneCirclePos = { 200,720 };
		eneCircleBurstVec = { 6,-4 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3110 + 46 * 13)//14
	{
		eneCirclePos = { 700,0 };
		eneCircleBurstVec = { -1,4 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}

	//2300
	if (frame == 3110)
	{
		eneCirclePos = { 640, 180 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 92, 112);

		eneCirclePos = { 640, 540 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 84, 104);
	}


	//3470
	if (frame == 3470)
	{
		eneCirclePos = { 280, 360 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 96, 116);
	}
	else if (frame == 3470 + 4)
	{
		eneCirclePos = { 1000, 360 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 92, 112);
	}
	else if (frame == 3470 + 8)
	{
		eneCirclePos = { 640, 360 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 96, 116);
	}

	//3760 Line
	if (frame == 3760)
	{
		lineWidth = 40;
		eneLinePos = { 60, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 70, 90, new EnemyLineDown);
	}
	else if (frame == 3760 + 2)
	{
		lineWidth = 40;
		eneLinePos = { 220, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 68, 88, new EnemyLineDown);
	}
	else if (frame == 3760 + 18)
	{
		lineWidth = 40;
		eneLinePos = { 380, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 52, 72, new EnemyLineDown);
	}
	else if (frame == 3760 + 20)
	{
		lineWidth = 40;
		eneLinePos = { 540, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 50, 70, new EnemyLineDown);
	}
	else if (frame == 3760 + 36)
	{
		lineWidth = 40;
		eneLinePos = { 700, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 34, 54, new EnemyLineDown);
	}
	else if (frame == 3760 + 38)
	{
		lineWidth = 40;
		eneLinePos = { 860, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 32, 52, new EnemyLineDown);
	}
	else if (frame == 3760 + 54)
	{
		lineWidth = 40;
		eneLinePos = { 1020, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 16, 36, new EnemyLineDown);
	}
	else if (frame == 3760 + 56)
	{
		lineWidth = 40;
		eneLinePos = { 1180, 0 };
		CreateEnemyLineFrom(eneLinePos, lineWidth, 14, 34, new EnemyLineDown);
	}




	if (frame == 3860)//1
	{
		eneCirclePos = { 980,0 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46)//2
	{
		eneCirclePos = { 0,80 };
		eneCircleBurstVec = { 6,1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 2)//3
	{
		eneCirclePos = { 1280,400 };
		eneCircleBurstVec = { -2,1 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 3)//4
	{
		eneCirclePos = { 400,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 4)//5
	{
		eneCirclePos = { 300,0 };
		eneCircleBurstVec = { 6,4 };
		eneCircleBurstSpeed = 20;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 5)//6
	{
		eneCirclePos = { 280,720 };
		eneCircleBurstVec = { 2,-4 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 6)//7
	{
		eneCirclePos = { 600,0 };
		eneCircleBurstVec = { 2,4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 7)//8
	{
		eneCirclePos = { 1280,700 };
		eneCircleBurstVec = { -2,-2 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 8)//9
	{
		eneCirclePos = { 200,720 };
		eneCircleBurstVec = { 1,-8 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 9)//10
	{
		eneCirclePos = { 0,160 };
		eneCircleBurstVec = { 10,2 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 10)//11
	{
		eneCirclePos = { 1000,0 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 11)//12
	{
		eneCirclePos = { 1280,360 };
		eneCircleBurstVec = { -2,-2 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 12)//13
	{
		eneCirclePos = { 640,720 };
		eneCircleBurstVec = { 0,-4 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}
	else if (frame == 3860 + 46 * 13)//14
	{
		eneCirclePos = { 280,0 };
		eneCircleBurstVec = { -2,4 };
		eneCircleBurstSpeed = 14;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 28);
	}

	//3860
	if (frame == 3860)
	{
		eneCirclePos = { 320, 180 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 92, 112);

		eneCirclePos = { 960, 180 };
		eneCircleRadius = 120;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 84, 104);
	}


	//4220
	if (frame == 4220)
	{
		eneCirclePos = { 280, 540 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 96, 116);
	}
	else if (frame == 4220 + 4)
	{
		eneCirclePos = { 1000, 540 };
		eneCircleRadius = 160;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 92, 112);
	}
	else if (frame == 4220 + 8)
	{
		eneCirclePos = { 640, 540 };
		eneCircleRadius = 140;
		CreateEnemyCircleScaling(eneCirclePos, eneCircleRadius, 96, 116);
	}

	//4500 ~ 4590 Last
	if (frame == 4500)
	{
		eneCirclePos = { 640,0 };
		eneCircleBurstVec = { 0,1 };
		eneCircleBurstSpeed = 12;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 90);
	}
	else if (frame == 4500 + 2)
	{
		eneCirclePos = { 1280,0 };
		eneCircleBurstVec = { -2,1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 88);
	}
	else if (frame == 4500 + 18)
	{
		eneCirclePos = { 1280,360 };
		eneCircleBurstVec = { -1,0 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 72);
	}
	else if (frame == 4500 + 20)
	{
		eneCirclePos = { 1280,720 };
		eneCircleBurstVec = { -2,-1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 70);
	}
	else if (frame == 4500 + 36)
	{
		eneCirclePos = { 640,720 };
		eneCircleBurstVec = { 0,-1 };
		eneCircleBurstSpeed = 12;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 54);
	}
	else if (frame == 4500 + 38)
	{
		eneCirclePos = { 0,720 };
		eneCircleBurstVec = { 2,-1 };
		eneCircleBurstSpeed = 18;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 52);
	}
	else if (frame == 4500 + 54)
	{
		eneCirclePos = { 0,360 };
		eneCircleBurstVec = { 1,0 };
		eneCircleBurstSpeed = 16;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 36);
	}
	else if (frame == 4500 + 56)
	{
		eneCirclePos = { 0,0 };
		eneCircleBurstVec = { 2,1 };
		eneCircleBurstSpeed = 22;
		CreateEnemyBurst(eneCirclePos, eneCircleBurstVec, eneCircleBurstSpeed, 14, 34);
	}


	//if (frame == 4988)
	//{
	//	m_manager.sManager.StopBGM("stage2");
	//}
	else if (frame == 5050)
	{
		goalFlag = true;
	}

	if (goalFlag)
	{
		goal->Update();

		Col goalCol = goal->GetColRect();

		//プレイヤーとゴールが当たった時の処理
		if (playerCol.IsCollision(goalCol))
		{
			goal->Hit();
			m_manager.SetStageClearFlag(1);
			onGoal = true;
		}

	}

	if (frame <= 4988)
	{
		progressPos += progressSpeed;
	}
}

void Stage2::Draw()
{
	StageBase::Draw();
}

void Stage2::CreateLineRush(int pattern, int firstFrame)
{
	frame++;
	switch (pattern)
	{
	case 0:
		if (frame == firstFrame)
		{
			lineWidth = 40;
			eneLinePos = { 560, 0 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 70, 90, new EnemyLineFromUpper);
		}
		else if (frame == firstFrame + 2)
		{
			lineWidth = 40;
			eneLinePos = { 680, 0 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 68, 88, new EnemyLineDown);
		}
		else if (frame == firstFrame + 18)
		{
			lineWidth = 40;
			eneLinePos = { 200, 0 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 52, 72, new EnemyLineDown);
		}
		else if (frame == firstFrame + 20)
		{
			lineWidth = 40;
			eneLinePos = { 1040, 0 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 50, 70, new EnemyLineFromUpper);
		}
		else if (frame == firstFrame + 38)
		{
			lineWidth = 40;
			eneLinePos = { 0, 280 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 34, 54, new EnemyLineFromLeft);
		}
		else if (frame == firstFrame + 40)
		{
			lineWidth = 40;
			eneLinePos = { 1280, 400 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 32, 52, new EnemyLineFromRight);
		}
		else if (frame == firstFrame + 58)
		{
			lineWidth = 40;
			eneLinePos = { 1280, 120 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 16, 36, new EnemyLineFromRight);
		}
		else if (frame == firstFrame + 60)
		{
			lineWidth = 40;
			eneLinePos = { 0, 560 };
			CreateEnemyLineFrom(eneLinePos, lineWidth, 14, 34, new EnemyLineFromLeft);
		}
	}
}
