#include "EnemyLine.h"
#include "DxLib.h"

namespace
{
	constexpr int kLineWidth = 50;
}

EnemyLine::EnemyLine():
	startPosX(GetRand(1230)),
	startPosY(0),
	endPosX(startPosX + kLineWidth),
	endPosY(0),
	frame(0)
{
}

EnemyLine::~EnemyLine()
{
}

void EnemyLine::Draw()
{
	DrawBox(startPosX, startPosY,
		endPosX, endPosY,
		0xff2222, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フェード暗幕
	int alpha = 255 * (float)frame / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(startPosX, startPosY,
		endPosX, endPosY,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawFormatString(0, 720 - 16, 0xffffff, "endPosY : %d", endPosY);
}

void EnemyLine::Update()
{

	if (endPosY >= 720)
	{
		frame++;
	}
	else
	{
		endPosY++;
	}
}
