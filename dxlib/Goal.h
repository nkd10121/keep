#pragma once
#include "Util/Vec2.h"
#include "Util/Col.h"
#include "DrawRotationCirlce.h"

class Goal
{
public:
	Goal();
	~Goal();

	void Start();
	void Update();
	void Draw();

	void DrawQuilateralTriangle(Vec2 centerPos, int sideLength, unsigned int color);

	void Hit();

	Col GetColRect() const { return m_colRect; }

	/// <summary>
	/// 画面内に存在するかのフラグを返す
	/// </summary>
	/// <returns>存在しているかフラグ</returns>
	bool isExist() const { return m_isExist; }
private:
	int frame;

	int handle = 0;

	Vec2 center;
	Col m_colRect;
	bool m_isExist;

	DrawRotationCirlce inSide;
	DrawRotationCirlce outSide;
};