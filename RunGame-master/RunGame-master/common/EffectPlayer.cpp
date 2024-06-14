#include "EffectPlayer.h"
#include "DxLib.h"

#include "game.h"
#include "Player.h"

namespace
{
	constexpr int kDefaultAnimSpeed = 4;
}

EffectPlayer::EffectPlayer():
	m_scale(1.0),
	m_playerKind(0),
	m_animFrame(0),
	m_animSpeed(kDefaultAnimSpeed),
	m_isMove(true),
	m_isRun(false),
	m_isExist(false)
{
}

EffectPlayer::~EffectPlayer()
{
}

void EffectPlayer::setupIcon(Vec2 pos)
{
	m_pos = pos;
	m_vec = Vec2{ 0,0 };
	m_scale = 1.0;
	m_playerKind = 0;
	m_animFrame = 0;
	m_animSpeed = kDefaultAnimSpeed;
	m_isRun = false;
	m_isExist = true;
}

void EffectPlayer::setupTitle()
{
	// まれに逆走
	bool isRare = (GetRand(256) == 0);

	// タイトル画面での使用を想定した初期化を行う
	int randPos = GetRand(Game::kScreenHeight + Game::kScreenWidth);
	if (randPos < Game::kScreenHeight)
	{
		
		if (isRare)
		{
			// 右から
			Game::kScreenWidth + 32.0f;
		}
		else
		{
			// 画面左から出てくる
			m_pos.x = -32.0f;
		}
		m_pos.y = static_cast<float>(randPos);
	}
	else
	{
		
		m_pos.x = static_cast<float>(randPos - Game::kScreenHeight);
		if (isRare)
		{
			// 上から
			m_pos.y = -32.0f;
		}
		else
		{
			// 画面下から出てくる
			m_pos.y = Game::kScreenHeight + 32.0f;
		}
	}
	m_vec.x = static_cast<float>(Game::kScreenWidth) / 128.0f;
	m_vec.y = - static_cast<float>(Game::kScreenHeight) / 128.0f;
	float speed = static_cast<float>(6 + GetRand(4));
	m_vec = m_vec.normalize();
	m_vec *= speed;

	if (isRare)	m_vec *= -1.0f;

	m_scale = 2.0;
	m_playerKind = GetRand(Player::getKindNum() -1);
	m_animFrame = 0;
	m_animSpeed = 4;

	m_isRun = true;
	m_isExist = true;
}

void EffectPlayer::setupPlayMob(float dt)
{
	// 1/2の確率で逆走
	bool isBack = (GetRand(1) == 0);

	// プレイ中の演出で使用することを想定下初期化を行う
	if (isBack)
	{
		// 右から左
		m_pos.x = static_cast<float>(Game::kScreenWidth + 16);
		m_pos.y = 84.0f;
	//	m_vec.x = -static_cast<float>(GetRand(8)+2);
		m_vec.x = -3.0f - GetRand(3);
		m_vec.y = 0.0f;
	}
	else
	{
		// 左から右
		m_pos.x = -16.0f;
		m_pos.y = 84.0f;
	//	m_vec.x = static_cast<float>(GetRand(8) + 2);
		m_vec.x = 3.0f + GetRand(3);
		m_vec.y = 0.0f;
	}

	m_scale = 1.0;
	m_playerKind = GetRand(Player::getKindNum() - 1); 
	m_animFrame = 0;
	m_animSpeed = 4;

	m_isRun = true;
	m_isExist = true;

	// ゲームテンポに合わせた最終調整
	m_vec.x *= dt;
	m_vec.x -= 2.0f * dt;
}

void EffectPlayer::update()
{
	if (!m_isExist)	return;

	int maxFrame = Player::getRunAnimeNum() * m_animSpeed;
	if (!m_isRun)
	{
		maxFrame = Player::getIdleAnimeNum() * m_animSpeed;
	}

	m_animFrame++;
	if (m_animFrame >= maxFrame)
	{
		m_animFrame = 0;
	}

	// まっすぐ進んで画面外に出たら終了
	if (m_isMove)
	{
		m_pos += m_vec;
	}
	if (m_vec.x > 0 && m_pos.x > Game::kScreenWidth + 32)
	{
		m_isExist = false;
	}
	if (m_vec.x < 0 && m_pos.x <-32)
	{
		m_isExist = false;
	}
	if (m_vec.y > 0 && m_pos.y > Game::kScreenHeight + 32)
	{
		m_isExist = false;
	}
	if (m_vec.y < 0 && m_pos.y < -32)
	{
		m_isExist = false;
	}
}

void EffectPlayer::draw()
{
	if (!m_isExist)	return;

	double angle = atan2(m_vec.y, m_vec.x);

	int animNo = m_animFrame / m_animSpeed;

	int handle = Player::getRunGraph(m_playerKind);
	if(!m_isRun)	handle = Player::getIdleGraph(m_playerKind);

	if (m_vec.x >= 0.0f)
	{
		// 右に移動
		DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), animNo * 32, 0, 32, 32, m_scale, angle, handle, true);
	}
	else
	{
		// 左に移動
		DrawRectRotaGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y), animNo * 32, 0, 32, 32, m_scale, angle - DX_PI, handle, true, true);
	}
}

void EffectPlayer::setRandomKind()
{
	m_playerKind = GetRand(Player::getKindNum() - 1);
}
