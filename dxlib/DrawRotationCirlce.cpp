#include "DrawRotationCirlce.h"

namespace
{
	//プレイヤーの周りを一回転するのにかかるフレーム数
	constexpr int kRotFrame = 44;

	//覚えておく過去の位置情報の数
	constexpr int kPosLogNum = 8;
}

DrawRotationCirlce::DrawRotationCirlce() :
	center(0, 0),
	pos1(0, 0),
	pos2(0, 0),
	frameCount(0),
	angle(0),
	circleRadius(2),
	rotateRadius(0),
	isWhite(false),
	isClockwise(true)
{
	posLog1.resize(kPosLogNum);
	posLog2.resize(kPosLogNum);
}

DrawRotationCirlce::~DrawRotationCirlce()
{
}

void DrawRotationCirlce::start(int Rr, bool clockwise, bool white)
{
	rotateRadius = Rr;
	isClockwise = clockwise;
	isWhite = white;
}

void DrawRotationCirlce::Update(Vec2 pos)
{
	center = pos;

	//残像のログをずらす
	for (int i = static_cast<int>(posLog1.size()) - 1; i >= 1; i--)
	{
		posLog1[i] = posLog1[i - 1];
	}
	posLog1[0] = pos1;

	for (int i = static_cast<int>(posLog2.size()) - 1; i >= 1; i--)
	{
		posLog2[i] = posLog2[i - 1];
	}
	posLog2[0] = pos2;

	//角度の更新
	//kRotFrameかけて一回転する
	angle += DX_TWO_PI_F / kRotFrame;

	Vec2 offset1;	//プレイヤーから見た位置
	Vec2 offset2;	//プレイヤーから見た位置

	if (isClockwise)
	{
		offset1.x = cosf(angle) * rotateRadius;
		offset1.y = sinf(angle) * rotateRadius;

		offset2.x = -cosf(angle) * rotateRadius;
		offset2.y = -sinf(angle) * rotateRadius;
	}
	else
	{
		offset1.x = cosf(angle) * rotateRadius;
		offset1.y = -sinf(angle) * rotateRadius;

		offset2.x = -cosf(angle) * rotateRadius;
		offset2.y = sinf(angle) * rotateRadius;
	}

	pos1 = center + offset1;
	pos2 = center + offset2;
}

void DrawRotationCirlce::Draw()
{

	//残像の処理1
	for (int i = 0; i < posLog1.size(); i++)
	{
		int alpha = 255 - (20 * (i + 1));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		if (isWhite)
		{
			DrawCircle(static_cast<int>(posLog1[i].x), static_cast<int>(posLog1[i].y), circleRadius, 0xffffff, true);
		}
		else
		{
			DrawCircle(static_cast<int>(posLog1[i].x), static_cast<int>(posLog1[i].y), circleRadius, 0x00ffff, true);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	//残像の処理2
	for (int i = 0; i < posLog2.size(); i++)
	{
		int alpha = 255 - (20 * (i + 1));
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		if (isWhite)
		{
			DrawCircle(static_cast<int>(posLog2[i].x), static_cast<int>(posLog2[i].y), circleRadius, 0xffffff, true);
		}
		else
		{
			DrawCircle(static_cast<int>(posLog2[i].x), static_cast<int>(posLog2[i].y), circleRadius, 0x00ffff, true);
		}

		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}

	if (isWhite)
	{
		DrawCircle(static_cast<int>(pos1.x), static_cast<int>(pos1.y), circleRadius, 0xffffff, true);
		DrawCircle(static_cast<int>(pos2.x), static_cast<int>(pos2.y), circleRadius, 0xffffff, true);
	}
	else
	{
		DrawCircle(static_cast<int>(pos1.x), static_cast<int>(pos1.y), circleRadius, 0x00ffff, true);
		DrawCircle(static_cast<int>(pos2.x), static_cast<int>(pos2.y), circleRadius, 0x00ffff, true);
	}
}
