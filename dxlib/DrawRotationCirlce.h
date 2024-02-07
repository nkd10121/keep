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
	/// <param name="Rr">���S����̔��a</param>
	/// <param name="clockwise">true = ���v���,false = �����v���</param>
	/// <param name="white">true = �F�𔒂�,false = �F���V�A����</param>
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

	//�c����\�����邽�߂ɉߋ��̈ʒu���o���Ă���
	std::vector<Vec2> posLog1;
	std::vector<Vec2> posLog2;

	bool isClockwise;
};