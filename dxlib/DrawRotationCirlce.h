#pragma once
#include "Util/Vec2.h"
#include "DxLib.h"

#include <vector>

class DrawRotationCirlce
{
public:
	DrawRotationCirlce();
	~DrawRotationCirlce();

	/// <summary>
	/// 
	/// </summary>
	/// <param name="Rr">中心からの半径</param>
	/// <param name="clockwise">true = 時計回り,false = 反時計回り</param>
	/// <param name="white">true = 色を白に,false = 色をシアンに</param>
	void start(int Rr, bool clockwise = true, bool white = false);
	void Update(Vec2 pos);
	void Draw();
private:
	Vec2 center;

	Vec2 pos1;
	Vec2 pos2;
	int frameCount;
	float angle;
	int circleRadius;
	int rotateRadius;

	bool isWhite;

	//残像を表示するために過去の位置を覚えておく
	std::vector<Vec2> posLog1;
	std::vector<Vec2> posLog2;

	bool isClockwise;
};