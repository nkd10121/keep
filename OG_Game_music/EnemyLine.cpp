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
	endPosY(0)
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

	endPosY++;
}

void EnemyLine::Update()
{
}
