#include "Bg.h"
#include "DxLib.h"

#include "game.h"
#include "Player.h"
#include "EffectPlayer.h"

namespace
{
	const char* const kBgTileFileName[] =
	{
		"data/image/bg/Blue.png",
		"data/image/bg/Brown.png",
		"data/image/bg/Gray.png",
		"data/image/bg/Green.png",
		"data/image/bg/Pink.png",
		"data/image/bg/Purple.png",
		"data/image/bg/Yellow.png"
	};
	constexpr int kBgTileKindNum = _countof(kBgTileFileName);
	constexpr int kBgTileSize = 64;

}

Bg::Bg():
	m_scroll(0),
	m_bgTileKind(0),
	m_playerCreateFrameCount(0),
	m_playerInterval(-1),
	m_playerCreateNum(0)
{
}

Bg::~Bg()
{
	unload();
}

void Bg::load()
{
	for (int i = 0; i < kBgTileKindNum; i++)
	{
		m_handle.push_back(LoadGraph(kBgTileFileName[i]));
	}
}

void Bg::unload()
{
	for (auto& handle : m_handle)
	{
		DeleteGraph(handle);
	}
}

bool Bg::isLoaded()
{
	for (auto& handle : m_handle)
	{
		if (CheckHandleASyncLoad(handle))	return false;
	}
	return true;
}

void Bg::update()
{
	m_scroll++;
	if (m_scroll >= kBgTileSize)	m_scroll -= kBgTileSize;

	// 背景演出用のプレイヤー生成
	if (m_playerInterval > 0)
	{
		m_playerCreateFrameCount++;
		if (m_playerCreateFrameCount >= m_playerInterval)
		{
			m_playerCreateFrameCount = 0;

			for (int i = 0; i < m_playerCreateNum; i++)
			{
				addPlayer();
			}
		}
	}

	for (auto& player : m_pPlayer)
	{
		player->update();
	}
	// 画面外に出たら削除
	m_pPlayer.remove_if(
		[](auto& player) {
			return !player->isExist();
		});
}

void Bg::drawBg()
{
	for (int x = 0; x < Game::kScreenWidth; x += kBgTileSize)
	{
		for (int y = 0 - m_scroll; y < Game::kScreenWidth; y += kBgTileSize)
		{
			DrawGraph(x, y, m_handle[m_bgTileKind], true);
		}
	}
}

void Bg::drawPlayer()
{
	for (auto& player : m_pPlayer)
	{
		player->draw();
	}
}

void Bg::drawAll()
{
	drawBg();
	drawPlayer();
}

void Bg::setTileKindRandom()
{
	m_bgTileKind = GetRand(kBgTileKindNum-1);
}

void Bg::addPlayer()
{
	std::shared_ptr<EffectPlayer> pPlayer = std::make_shared<EffectPlayer>();
	pPlayer->setupTitle();
	m_pPlayer.push_back(pPlayer);
}
