#pragma once
#include <vector>
#include <list>
#include <memory>

class EffectPlayer;
class Bg
{
public:
	Bg();
	virtual ~Bg();

	void load();
	void unload();
	bool isLoaded();

	void update();

	void drawBg();		// スクロール背景
	void drawPlayer();	// プレイヤー演出

	void drawAll();		// drawBgとdrawPlayerを両方行う

	// 使用する背景データの決定
	void setTileKind(int kind) { m_bgTileKind = kind; }
	void setTileKindRandom();	// ランダムに決定

	// プレイヤー生成間隔の設定
	void setPlayerInterval(int interval) { m_playerInterval = interval; }	// 何フレーム間隔でプレイヤーを生成するか
	void setPlayerCreateNum(int num) { m_playerCreateNum = num; }			// 生成時同時に何体生成するか

	// プレイヤーを1体生成
	void addPlayer();

private:
	std::vector<int>	m_handle;
	int	m_scroll;
	int m_bgTileKind;


	// 演出用プレイヤー
	std::list<std::shared_ptr<EffectPlayer>>	m_pPlayer;
	int m_playerCreateFrameCount;

	// 演出プレイヤー生成ルール
	int m_playerInterval;
	int m_playerCreateNum;
};

