#include "EnemyCircleScaling.h"

namespace
{
	constexpr int kRotFrame = 60;
}

EnemyCircleScaling::EnemyCircleScaling():
	m_frame(0),
	m_angle(0),
	m_offset(0,0),
	m_center(0,0),
	m_radius(0),
	m_mainCircleRadius(0),
	m_defaultColor(0xff00ff),
	m_addColor(0x001100),
	m_waitFrame(0),
	m_drawFrame(0)
{
}

EnemyCircleScaling::~EnemyCircleScaling()
{
}

void EnemyCircleScaling::Start(Vec2 pos, int rad, int wait,int draw, int speed)
{
	m_center = pos;
	m_pos = m_center;
	m_radius = rad;

	m_waitFrame = wait;
	m_drawFrame = draw;

	m_radiusSmallSpeed = speed;
	m_isExist = true;
}

void EnemyCircleScaling::Update()
{
	if (!m_isExist)return;

	m_frame++;


	m_angle += DX_TWO_PI_F / kRotFrame;

	//最初の点線の処理
	if (m_frame <= m_waitFrame)
	{
		for (int i = 0; i < m_radius; i++)
		{
			//m_pos += m_offset;

		}
	}
	//本体の登場処理
	else if (m_frame <= m_drawFrame)
	{
		if (m_mainCircleRadius <= m_radius)
		{
			m_mainCircleRadius += 12;
		}
		else if (m_mainCircleRadius <= m_radius + m_drawFrame * 0.2)
		{
			m_mainCircleRadius += 1;
		}
	}
	//本体が消える処理
	else
	{
		m_mainCircleRadius -= m_radiusSmallSpeed;

	}

	if (m_mainCircleRadius < 0)
	{
		m_isExist = false;
	}


	m_col.SetCircle(m_center.x, m_center.y, m_mainCircleRadius);
}

void EnemyCircleScaling::Draw()
{
	if (!m_isExist)return;

	//最初の点線の描画
	if (m_frame <= m_waitFrame)
	{
		for (int i = 0; i < m_radius; i++)
		{
			m_offset = { -cosf(m_angle + i) * m_radius , sinf(m_angle + i) * m_radius };

			DrawCircle(static_cast<int>(m_pos.x + m_offset.x), static_cast<int>(m_pos.y + m_offset.y), 1, 0x880088, true);
		}
	}
	//else if (m_waitFrame <= m_frame)
	//{
	//	if (m_frame <= m_drawFrame)
	//	{
	//		DrawCircle(static_cast<int>(m_center.x), static_cast<int>(m_center.y), m_mainCircleRadius, m_defaultColor + m_addColor * (m_frame % 16), true);
	//	}
	//}
	else
	{
		DrawCircle(static_cast<int>(m_center.x), static_cast<int>(m_center.y), m_mainCircleRadius, m_defaultColor + m_addColor * (m_frame % 16), true);
	}

#ifdef _DEBUG
	//m_col.DrawColCircle(0xffffff);
#endif
}
