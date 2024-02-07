#include "DashEfect.h"
#include "DxLib.h"

DashEfect::DashEfect()
{
}

DashEfect::~DashEfect()
{
}

void DashEfect::Init(Vec2 pos, bool isLastHi)
{
	m_isExist = true;
	rad = 20;
	m_pos = pos;
}

void DashEfect::Update()
{
	if (!m_isExist)
		return;
	rad += 3;
	alpha -= 4;
	lineThick -= 2;

	if (alpha < 0)
	{
		m_isExist = false;
	}
}

void DashEfect::Draw()
{
	if (!m_isExist)
		return;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	DrawCircle(m_pos.x, m_pos.y, rad, 0x008888, false, lineThick);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, alpha);
}
