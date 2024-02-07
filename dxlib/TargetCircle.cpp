#include "TargetCircle.h"
#include "DxLib.h"

namespace
{
	constexpr int kSize = 32;
}

TargetCircle::TargetCircle():
	m_frame(0),
	m_x(0),
	m_y(0),
	m_size(0),
	m_exRate(0.48f)
{
}

TargetCircle::~TargetCircle()
{
}

void TargetCircle::Init(int x, int y,int handleNum)
{
	m_x = x;
	m_y = y;
	m_size = 0.32f;
	tempSize = m_size;

	if (handleNum == 1)
	{
		handle = LoadGraph("data/UI_stageSelect.png");
	}
	if (handleNum == 2)
	{
		handle = LoadGraph("data/UI_stageSelect2.png");
	}
	if (handleNum == 3)
	{
		handle = LoadGraph("data/UI_stageSelect3.png");
	}
}

void TargetCircle::Update()
{
	m_col.SetCircle(static_cast<float>(m_x), static_cast<float>(m_y), 40);
	m_frame++;

	m_size = tempSize;
}

void TargetCircle::Draw()
{
	DrawRotaGraph(m_x, m_y, m_size, angle, handle, true);
#ifdef _DEBUG
	m_col.DrawColCircle(0xff0000);
#endif
}

void TargetCircle::Rotation()
{
	if (!isChangeRotationSpeed)
	{
		angle += DX_TWO_PI_F / 60;
	}
	else
	{
		angle += DX_TWO_PI_F / 20;
	}
}

void TargetCircle::Big()
{
	m_size = m_exRate;
}
