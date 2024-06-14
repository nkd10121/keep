#pragma once
#include <memory>
#include <vector>
#include "Vec2.h"

class Player;
class Field;
class ParticleManager;
class PlayerManager : public std::enable_shared_from_this<PlayerManager>
{
public:
	PlayerManager(bool isDemo);
	virtual ~PlayerManager();

	// 初期設定
	void setField(std::shared_ptr<Field> pField) { m_pField = pField; }
	void setParticleManager(std::shared_ptr<ParticleManager> pParticle) { m_pParticle = pParticle; }

	// 毎フレームの処理
	void update();
	void draw();
	
	// 人数に応じた初期設定を行う
	// 必要な分addPlayerをしてから実行する
	void playSetting();

	// プレイヤーを追加
	void addPlayer(int kind = -1);
	// プレイヤー数の取得
	int getPlayerNum();
	// プレイヤーの取得
	std::shared_ptr<Player> getPlayer(int no);
	// プレイヤーの情報からスクロール量を取得
	Vec2 getScroll();
	// 生きている人数の取得
	int getActiveNum();

	// 一番スコアの高いプレイヤーのスコア(=移動距離)
	int getMaxScore();
	// 一番高速で移動しているプレイヤーのテンポ取得
	int getMaxTempo();
	// 最大deltaTimeで動いているプレイヤーのdeltaTime取得
	float getMaxDt();

	// 全てのプレイヤーを状態遷移させる
	void startIdling();
	void startDig();

private:
	std::vector<std::shared_ptr<Player>>	m_pPlayer;

	std::shared_ptr<Field>	m_pField;
	std::shared_ptr<ParticleManager>	m_pParticle;

	Vec2 m_scroll;
	bool m_isDemo;
};

