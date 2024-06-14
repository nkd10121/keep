#include "CursorPlayer.h"
#include "DxLib.h"

#include "EffectPlayer.h"
#include "ParticleManager.h"
#include "Particle.h"
#include "Player.h"

namespace
{
	constexpr int kCursourMoveFrame = 8;
}

CursorPlayer::CursorPlayer():
	m_moveFrame(-1)
{
	m_pCursor = std::make_shared<EffectPlayer>();
	m_pCursor->setupIcon(Vec2{ 0.0f,0.0f });
	m_pCursor->setVec(Vec2{ 1.0f,0.0f });
	m_pCursor->setScale(2.0);
	m_pCursor->setRandomKind();
	m_pCursor->setAnimSpeed(4);
	m_pCursor->setRun(true);
	m_pCursor->setMove(false);
}

CursorPlayer::~CursorPlayer()
{
}

void CursorPlayer::update()
{
	if (m_moveFrame >= 0)
	{
		m_moveFrame++;

		float rate = static_cast<float>(m_moveFrame) / static_cast<float>(kCursourMoveFrame);
		rate *= rate;
		Vec2 pos = m_targetPos * rate + m_startPos * (1.0f - rate);
		m_pCursor->setPos(pos);

		if (m_moveFrame >= kCursourMoveFrame)
		{
			m_moveFrame = -1;
			m_pCursor->setPos(m_targetPos);
		}
	}

	m_pCursor->update();
	createMoveParticle();
}

void CursorPlayer::draw()
{
	m_pCursor->draw();
}

void CursorPlayer::setPos(Vec2 pos)
{
	m_pCursor->setPos(pos);
}

void CursorPlayer::setTarget(Vec2 target)
{
	m_startPos = m_pCursor->getPos();
	m_targetPos = target;
	m_moveFrame = 0;

	Vec2 dir = m_targetPos - m_startPos;
	if (dir.x < 0.0f)
	{
		m_pCursor->setVec(Vec2{ -1.0f,0.0f });
	}
	else if (dir.x > 0.0f)
	{
		m_pCursor->setVec(Vec2{ 1.0f,0.0f });
	}
}

void CursorPlayer::setPlayerKind(int kind)
{
	m_pCursor->setKind(kind);
}

void CursorPlayer::createMoveParticle()
{
	if (!m_pParticle)	return;
	// 移動中にのみパーティクル生成
	if (m_moveFrame < 0)	return;

	constexpr int createNum = 4;

	for (int i = 0; i < createNum; i++)
	{
		Vec2 pos = m_pCursor->getPos();

		pos.x += GetRand(40) - 20;
		pos.y += GetRand(40) - 20;

		float vecY = static_cast<float>(-GetRand(600));
		vecY /= 1000;

		std::shared_ptr<Particle> pPart = std::make_shared<Particle>(m_pParticle);
		pPart->init();
		pPart->setPos(pos);
		pPart->setVec(Vec2{ 0.0f, vecY });
		pPart->setRadius(1.0f);
		pPart->setColor(Player::getColor(m_pCursor->getPlayerKind()));
		pPart->setExistFrame(120);
		pPart->setAlphaAcc(-2);

		m_pParticle->add(pPart);
	}
}
