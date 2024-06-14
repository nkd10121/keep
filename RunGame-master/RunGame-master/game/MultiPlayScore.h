#pragma once
#include <memory>

class Player;
class EffectPlayer;
class ParticleManager;

// 対戦プレイ用のスコア表示
class MultiPlayScore
{
public:
	MultiPlayScore(std::shared_ptr<Player> pPlayer, int playerNum);
	virtual ~MultiPlayScore();

	void update();
	void draw();

private:
	// ウインドウ表示情報
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// 演出パーティクル生成
	void createParticle();

private:
	// スコアを表示するプレイヤーの情報
	std::shared_ptr<Player>	m_pPlayer;
	// 演出用パーティクル	プライオリティの関係でSceneMainのは使わずに自前で確保
	std::shared_ptr<ParticleManager>	m_pParticle;
	// プレイ人数	人数によって配置が変わる
	int	m_totalPlayerNum;

	// プレイヤーアイコン
	std::shared_ptr<EffectPlayer>	m_pIcon;
};

