#include "EnemyCircle.h"
#include "DxLib.h"
#include "../../Util/Game.h"

EnemyCircle::EnemyCircle() :
	m_rad(0),
	m_isSmooth(false),
	m_angle(0.0f),
	m_diagonal(0),
	effectCircleRad(0)
{

}

EnemyCircle::~EnemyCircle()
{

}

void EnemyCircle::Start(float pos, int radius, bool isSmooth)
{
	m_isExist = true;

	m_isSmooth = isSmooth;
	if (m_isSmooth)
	{
		m_rad = radius;
	}
	else
	{
		m_rad = radius;
		m_diagonal = m_rad + (m_rad / 5);
	}
	//登場時のエフェクトの半径
	effectCircleRad = radius;

	//始点座標と終点座標を入れる
	m_startPos = { Game::kScreenWidth , pos};
	m_endPos = { -80 ,m_startPos.y };

	m_pos.x = m_startPos.x + m_rad ;
	m_pos.y = m_startPos.y;

	//ベクトルを求める
	m_dir = m_endPos - m_startPos;

	//正規化
	m_dir = m_dir.getNormalize();

	efectCirclePos = static_cast<int>(m_pos.x) - m_rad;

}

void EnemyCircle::Update()
{
	if (!m_isExist)
		return;

	effectCircleRad -= 4;

	m_pos += m_dir * 8;

	//m_colRect.SetCircle(m_pos,m_rad);
	

	if (m_endPos.x == m_pos.x + m_rad * 2)
	{
		m_isExist = false;
	}

	if (m_isSmooth)
	{
		m_col.SetCircle(m_pos.x, m_pos.y, m_rad);
	}
	else
	{
		m_col.SetCircle(m_pos.x, m_pos.y, m_rad + (m_rad / 8));
		m_angle += 0.1f;
	}
}

void EnemyCircle::Draw()
{
	if (!m_isExist)
		return;

	if (m_isSmooth)
	{

		DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rad, 0xff00ff, true);

	}
	else
	{

		float offsetX1 = cosf(m_angle) * m_diagonal;
		float offsetY1 = sinf(m_angle) * m_diagonal;

		float offsetX2 = cosf(m_angle + 0.75f) * m_diagonal;
		float offsetY2 = sinf(m_angle + 0.75f) * m_diagonal;

		DrawQuadrangle(
			static_cast<int>(m_pos.x + 1 - offsetX2), static_cast<int>(m_pos.y + 1 - offsetY2),
			static_cast<int>(m_pos.x + 1 + offsetY2), static_cast<int>(m_pos.y + 1 - offsetX2),
			static_cast<int>(m_pos.x + 1 + offsetX2), static_cast<int>(m_pos.y + 1 + offsetY2),
			static_cast<int>(m_pos.x + 1 - offsetY2), static_cast<int>(m_pos.y + 1 + offsetX2),
			0xff00ff,
			true
		);

		DrawQuadrangle(
			static_cast<int>(m_pos.x + 1 + offsetX1), static_cast<int>(m_pos.y + 1 + offsetY1),
			static_cast<int>(m_pos.x + 1 + offsetY1), static_cast<int>(m_pos.y + 1 - offsetX1),
			static_cast<int>(m_pos.x + 1 - offsetX1), static_cast<int>(m_pos.y + 1 - offsetY1),
			static_cast<int>(m_pos.x + 1 - offsetY1), static_cast<int>(m_pos.y + 1 + offsetX1),
			0xff00ff,
			true);

		DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), m_rad, 0xff00ff, true);
	}

	if (effectCircleRad >= 0)
	{
		DrawCircle(efectCirclePos, static_cast<int>(m_pos.y), effectCircleRad, 0xffffff, true);
	}

#ifdef _DEBUG
	m_col.DrawColCircle(0xffffff);
#endif
}
