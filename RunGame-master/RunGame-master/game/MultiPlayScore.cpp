#include "MultiPlayScore.h"
#include "DxLib.h"
#include "game.h"
#include "Font.h"
#include "Player.h"
#include "EffectPlayer.h"
#include "Particle.h"
#include "ParticleManager.h"

#include <cassert>

namespace
{
	// 人数別配置情報
	// 使用するのは2人以上の情報

	constexpr int kStartX[Game::kMaxPlayer] =
	{
		0,		396,	276,	156,
		36,		36,		6,		1
	};
	constexpr int kIntervalX[Game::kMaxPlayer] =
	{
		0,		240,	240,	240,
		240,	200,	180,	160

	};
	constexpr int kWindowWidth[Game::kMaxPlayer] =
	{
		0,		188,	188,	188,
		188,	188,	178,	158
	};

	constexpr int kDispY = 12;
	constexpr int kWindowHeight = 72;
	// プレイヤーアイコン表示位置(ウインドウ左上からのオフセット)
	constexpr int kIconOffsetX = 16;
	constexpr int kIconOffsetY = 20;
}

MultiPlayScore::MultiPlayScore(std::shared_ptr<Player> pPlayer, int playerNum) :
	m_pPlayer(pPlayer),
	m_totalPlayerNum(playerNum)
{
	assert(m_pPlayer);
	assert(m_totalPlayerNum > 1);

	m_pParticle = std::make_shared<ParticleManager>();

	int playerNo = m_pPlayer->getPlayerNo();
	int playerKind = m_pPlayer->getKind();
	int posIndex = m_totalPlayerNum - 1;

	Vec2 iconPos;
	iconPos.x = static_cast<float>(getX() + kIconOffsetX);
	iconPos.y = static_cast<float>(getY() + kIconOffsetY);

	m_pIcon = std::make_shared<EffectPlayer>();
	m_pIcon->setupIcon(iconPos);
	m_pIcon->setVec(Vec2{ 1,0 });
	m_pIcon->setRun(true);
	m_pIcon->setMove(false);
	m_pIcon->setKind(playerKind);
}

MultiPlayScore::~MultiPlayScore()
{
}

void MultiPlayScore::update()
{
	m_pParticle->update();
	if (!m_pPlayer->isDead())
	{
		m_pIcon->update();
	}
	createParticle();
}

void MultiPlayScore::draw()
{
	const int font = Font::getHandle(Font::Id::GameScore);
	int playerNo = m_pPlayer->getPlayerNo();
	int playerKind = m_pPlayer->getKind();

	unsigned int color = 0xffffff;
	if (m_pPlayer->isDead())	color = 0xf00000;

	// 背景の矩形
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 96);
	DrawRoundRect(getX(), getY(), getX() + getWidth(), getY() + getHeight(), 8, 8, Player::getColor(playerKind), true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawRoundRect(getX(), getY(), getX() + getWidth(), getY() + getHeight(), 8, 8, Player::getColor(playerKind), false);

	// 時間表示
	{
		int width = Font::getDrawTimeWidth(Font::Id::GameScoreMulti);
		int x = getX() + getWidth() - width - 8;
		int y = getY() + getHeight() - 24;
		Font::drawTimeFromFrame(x, y, m_pPlayer->getPlayFrame(), color, Font::Id::GameScoreMulti);
	}
	
	// アイコン
	if (m_pPlayer->isDead())
	{
		SetDrawBright(0, 0, 0);
	}
	m_pIcon->draw();
	SetDrawBright(255, 255, 255);
	// ?P表示
	{
		int width = GetDrawFormatStringWidthToHandle(Font::getHandle(Font::Id::PlayerNo), "%dP", playerNo + 1);
		int x = static_cast<int>(m_pIcon->getPos().x + 8);
		int y = static_cast<int>(m_pIcon->getPos().y);
		DrawFormatStringToHandle(x, y, Player::getColor(playerKind), Font::getHandle(Font::Id::PlayerNo), "%dP", playerNo + 1);
	}
	m_pParticle->draw();
}

int MultiPlayScore::getX()
{
	const int posIndex = m_totalPlayerNum - 1;
	const int playerNo = m_pPlayer->getPlayerNo();
	const int startX = kStartX[posIndex];
	const int interval = kIntervalX[posIndex];

	return startX + interval * playerNo;
}

int MultiPlayScore::getY()
{
	return kDispY;
}

int MultiPlayScore::getWidth()
{
	int posIndex = m_totalPlayerNum - 1;
	return kWindowWidth[posIndex];
}

int MultiPlayScore::getHeight()
{
	return kWindowHeight;
}

void MultiPlayScore::createParticle()
{
	if (!m_pPlayer->isDead())	return;

	for (int i = 0; i < 2; i++)
	{
		Vec2 pos = m_pIcon->getPos();

		pos.x += GetRand(20) - 10;
		pos.y += GetRand(20) - 10;

		float vecY = static_cast<float>(-GetRand(300));
		vecY /= 1000;

		std::shared_ptr<Particle> pPart = std::make_shared<Particle>(m_pParticle);
		pPart->init();
		pPart->setPos(pos);
		pPart->setVec(Vec2{ 0.0f, vecY });
		pPart->setRadius(1.0f);
		pPart->setColor(0x000000);
		pPart->setExistFrame(120);
		pPart->setAlphaAcc(-2);

		pPart->setUseScroll(false);

		m_pParticle->add(pPart);
	}
}
