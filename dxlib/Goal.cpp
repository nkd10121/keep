#include "Goal.h"
#include "DxLib.h"

namespace
{
	//プレイヤーの周りを一回転するのにかかるフレーム数
	constexpr int kRotFrame = 90;

	//覚えておく過去の位置情報の数
	constexpr int kPosLogNum = 34;
}

Goal::Goal():
	frame(0),
	center(1380,360),
	m_isExist(false)
{
	handle = LoadGraph("data/goal.png");
}

Goal::~Goal()
{
}

void Goal::Start()
{
	m_isExist = true;
	inSide.start(32, false, false);
	outSide.start(40, true, true);
}

void Goal::Update()
{
	if (!m_isExist)
	{
		return;
	}

	if (center.x >= 1180)
	{
		center.x -= 4;
	}


	inSide.Update(center);
	outSide.Update(center);

	m_colRect.SetCircle(center.x, center.y, 24);
}

void Goal::Draw()
{
	if (!m_isExist)
	{
		return;
	}

	inSide.Draw();
	outSide.Draw();

	DrawRotaGraph(center.x - 20,center.y,0.4f,0.0f,handle,true);

	//DrawQuilateralTriangle(center, 36, 0xdcffff);
	//DrawQuilateralTriangle(center, 10, 0x000000);
}

void Goal::DrawQuilateralTriangle(Vec2 centerPos, int sideLength, unsigned int color)
{
	Vec2 top = { centerPos.x,centerPos.y - (float)(sideLength * 0.6) };
	Vec2 right = { centerPos.x - (float)(sideLength / 2),centerPos.y + (float)(sideLength * 0.34) };
	Vec2 left = { centerPos.x + (float)(sideLength / 2),centerPos.y + (float)(sideLength * 0.34) };

	DrawTriangle(static_cast<int>(top.x), static_cast<int>(top.y), static_cast<int>(right.x), static_cast<int>(right.y), static_cast<int>(left.x), static_cast<int>(left.y), color, true);
#ifdef _DEBUG
	m_colRect.DrawColCircle(0xffffff);
#endif
}


void Goal::Hit()
{
	frame++;
	if (frame >= 1)
	{
		m_isExist = false;
	}

}
