#include "PlayerManager.h"
#include "Player.h"
#include "DxLib.h"

#include "ParticleManager.h"
#include "Field.h"
#include "game.h"

#include <algorithm>
#include <random>

namespace
{
	// �v���C���[�����z�u���	y=-192~288	���ƈ�ԏ�Ɖ����s�������Ȃ̂ŁE�E�E
	// �v���C���[�����z�u���	y=-128~256
	constexpr int kPlayerStartYMin = -128;
	constexpr int kPlayerStartYMax = 256;

	constexpr int kPlayerInterval = (kPlayerStartYMax - kPlayerStartYMin) / Game::kMaxPlayer;	// �z�u�Ԋu
}

PlayerManager::PlayerManager(bool isDemo):
	m_isDemo(isDemo)
{
}

PlayerManager::~PlayerManager()
{
}

void PlayerManager::update()
{
	for (auto& player : m_pPlayer)
	{
		player->update();
	}

	// �擪�v���C���[�̃X�N���[���ʂ��g�p����
	Vec2 result;
	int maxScore = -1;
	for (auto& player : m_pPlayer)
	{
		if (player->getScore() > maxScore)
		{
			result = player->getScroll();
			maxScore = player->getScore();
		}
	}
	m_scroll = m_scroll * 0.9f + result * 0.1f;
}

void PlayerManager::draw()
{
	for (auto& player : m_pPlayer)
	{
		player->draw();
	}
}

void PlayerManager::playSetting()
{
	bool isDispPlayerNo = false;
	if(getPlayerNum() > 1)	isDispPlayerNo = true;
	// �v���C���[�ԍ��\��
	for (auto& player : m_pPlayer)
	{
		player->setDispPlayerNo( isDispPlayerNo );
	}
	// �v���C���[�����ʒu�ݒ�
	std::vector<int> posIndex;
	for (int i = 0; i < Game::kMaxPlayer; i++)
	{
		posIndex.push_back(i);
	}

	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(posIndex.begin(), posIndex.end(), engine);

	int index = 0;
	for (auto& player : m_pPlayer)
	{
		int y = kPlayerStartYMin + kPlayerInterval * posIndex[index];
		player->setStartY(static_cast<float>(y));

		index++;
	}

	// �v���C���[�����ʒu�Ɍ���������
	for (int i = 0; i < m_pPlayer.size(); i++)
	{
		m_pField->addStartDigData(m_pPlayer[i]->getPos(), m_pPlayer[i]->getDigColor(), i);
	}

	// �ŏ��͒N�ł������̂�(�����Ȃ̂�)0�ԃv���C���[�̃X�N���[�����̗p
	m_scroll = m_pPlayer[0]->getScroll();
}

void PlayerManager::addPlayer(int kind)
{
	std::shared_ptr<Player> pPlayer = std::make_shared<Player>(m_isDemo);
	pPlayer->init(getPlayerNum());
	// �v���C���[�̎�ނɎw�肪����Ȃ炻�̃v���C���[��
	if (kind >= 0)
	{
		pPlayer->setKind(kind);
	}
	pPlayer->setManager(shared_from_this());
	pPlayer->setField(m_pField);
	pPlayer->setParticle(m_pParticle);
	m_pPlayer.push_back(pPlayer);
}

int PlayerManager::getPlayerNum()
{
	return static_cast<int>(m_pPlayer.size());
}

std::shared_ptr<Player> PlayerManager::getPlayer(int no)
{
	return m_pPlayer[no];
}

Vec2 PlayerManager::getScroll()
{
	return m_scroll;
}

int PlayerManager::getActiveNum()
{
	int result = 0;
	for (auto& player : m_pPlayer)
	{
		if (!player->isDead())	result++;
	}
	return result;
}

int PlayerManager::getMaxScore()
{
	int result = -1;
	for (auto& player : m_pPlayer)
	{
		if (player->getScore() > result)	result = player->getScore();
	}
	return result;
}

int PlayerManager::getMaxTempo()
{
	int result = -1;
	for (auto& player : m_pPlayer)
	{
		if (player->getTempo() > result)	result = player->getTempo();
	}
	return result;
}

float PlayerManager::getMaxDt()
{
	float result = -1.0f;
	for (auto& player : m_pPlayer)
	{
		if (player->getDt() > result)	result = player->getDt();
	}
	return result;
}

void PlayerManager::startIdling()
{
	for (auto& player : m_pPlayer)
	{
		player->startIdling();
	}
}

void PlayerManager::startDig()
{
	for (auto& player : m_pPlayer)
	{
		player->startDig();
	}
}
