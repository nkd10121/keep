#include "HitEfect.h"
#include "DxLib.h"

HitEfect::HitEfect()
{
}

HitEfect::~HitEfect()
{
}

void HitEfect::Init(Vec2 pos, bool isLastHit)
{
	m_isExist = true;
	alpha = 240;
	handle = LoadGraph("data/player/player0.png");
	for (int i = 0; i < 10; i++)
	{
		parts[i].pos = pos;
		parts[i].vec = { static_cast<float>(GetRand(20) - 10),static_cast<float>(GetRand(20) - 10) };
		parts[i].speed = GetRand(2) + 2;
	}

	if (!isLastHit)
	{
		size = 0.32f;
	}
	else
	{
		size = 1.2f;
	}
}

void HitEfect::Update()
{
	if (!m_isExist)
		return;
	alpha -= 4;

	angle += DX_TWO_PI_F / 60;

	for (int i = 0; i < 10; i++)
	{
		parts[i].pos += parts[i].vec.getNormalize() * parts[i].speed;
	}

	if (alpha < 0)
	{
		m_isExist = false;
	}
}

void HitEfect::Draw()
{
	if (!m_isExist)
		return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	for (int i = 0; i < 10; i++)
	{
		DrawRotaGraph(parts[i].pos.x, parts[i].pos.y, size, angle, handle, true);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}
