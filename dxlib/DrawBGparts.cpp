#include "GraphManager.h"
#include "DrawBGparts.h"
#include "DxLib.h"

DrawBGparts::DrawBGparts()
{
	gManager.Load("BG", "data/titleParts.png");
	handle = gManager.GetHandle("BG");


	x = GetRand(1280);
	y = GetRand(720);
	exrate = (GetRand(200) + 60) * 0.05;
	angle = DX_TWO_PI_F / GetRand(10) * 0.04f;
	rotateAngle = GetRand(20);
	rotateFrame = GetRand(4000) + 2000;
	rad = GetRand(400) + 100;
}

DrawBGparts::~DrawBGparts()
{
}

void DrawBGparts::Init(bool isMove)
{
	m_isMove = isMove;
}

void DrawBGparts::Update()
{
	rotateSpeed += 0.08f;
	
	if (m_isMove)
	{
		frame++;

		if (frame % 30 == 0)
		{
			mag = 1.1f;
		}
		else
		{
			mag = 1.0f;
		}
	}

	rotateAngle += DX_TWO_PI_F / rotateFrame;
	offsetX = cosf(rotateAngle) * rad;
	offsetY = sinf(rotateAngle) * rad;

	x = 640 + offsetX;
	y = 360 + offsetY;
}

void DrawBGparts::Draw()
{

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 100);
	DrawRotaGraph(static_cast<int>(x), static_cast<int>(y), exrate * mag, angle * rotateSpeed, handle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
