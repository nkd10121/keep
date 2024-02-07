#include "EnemyBurstedCircle.h"
#include "../../Util/Game.h"
#include "../../Scene/GamePlayingScene.h"

namespace
{
	constexpr int kSpeed = 8;
	//”¼Œa@‚È‚º‚©12ˆÈ‰º‚É‚·‚é‚Æ“–‚½‚éŽž‚Æ“–‚½‚ç‚È‚¢‚Æ‚«‚ª‚ ‚é
	constexpr int kRadius = 6;
}


EnemyBurstedCircle::EnemyBurstedCircle() :
	m_vec(0, 0)
{
}

EnemyBurstedCircle::~EnemyBurstedCircle()
{
}

void EnemyBurstedCircle::Start(Vec2 pos, Vec2 vec)
{
	m_isExist = true;
	m_pos = pos;
	m_vec = vec;
	m_colRect.SetCircle(m_pos.x, m_pos.y, kRadius);
}

void EnemyBurstedCircle::Update()
{
	if (!m_isExist)return;
	m_pos += m_vec.getNormalize() * kSpeed;


	if (m_pos.x > 1280 || m_pos.x < 0 || m_pos.y > 720 || m_pos.y < 0)
		m_isExist = false;


	m_colRect.SetCircle(m_pos.x, m_pos.y, kRadius);

}

void EnemyBurstedCircle::Draw()
{
	if (!m_isExist)
	{
		return;
	}

	DrawCircle(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), kRadius, 0xff00ff, true);
#ifdef _DEBUG
	//m_colRect.DrawRectCircle(0xffffff, false);
	m_colRect.DrawColBox(0xffffff);
#endif
}
