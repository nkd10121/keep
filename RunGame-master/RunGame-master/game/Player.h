#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>
#include <deque>
#include <memory>
#include <list>

class PlayerManager;
class Field;
class ParticleManager;
class Player
{
public:
	// 常駐リソース関連
	// プレイヤーのグラフィックは常駐させる
	static void startLoad();	// プレイヤーグラフィック非同期読み込みの開始
	static void unload();		// プレイヤーグラフィックのアンロード

	static bool isLoaded();		// プレイヤーのグラフィック読み込み完了確認
	static int getKindNum();		// プレイヤーグラフィックの種類取得
	static int getIdleGraph(int kind);	// 指定したプレイヤー待機グラフィックのハンドル取得
	static int getRunGraph(int kind);	// 指定したプレイヤー走りグラフィックのハンドル取得
	static int getColor(int kind);

	// プレイヤーグラフィック情報の取得
	static int getIdleAnimeNum();	// アニメーションのコマ数取得
	static int getRunAnimeNum();

	

public:
	Player(bool isDemo);
	virtual ~Player();

	void setManager(std::shared_ptr<PlayerManager> pManager) { m_pManager = pManager; }
	void setField(std::shared_ptr<Field> pField) { m_pField = pField; }
	void setParticle(std::shared_ptr<ParticleManager> pParticle) { m_pParticle = pParticle; }

	void init(int playerNo);
	void update();
	void draw();

	Vec2 getPos() const { return m_pos; }
	Vec2 getScroll() const { return m_scroll; }

	void setKind(int kind) { m_kind = kind; }
	int getKind() const { return m_kind; }
	// 
	unsigned int getParticleColor();
	unsigned int getDigColor();

	// 縦位置設定	初期位置を設定するのに使用する
	void setStartY(float y);
	// プレイヤー番号表示を行うか設定	一人プレイなら非表示
	void setDispPlayerNo(bool isDisp) { m_isDispPlayerNo = isDisp; }

//	// 移動距離の取得
//	float getMoveDistance();
	// プレイヤー番号の取得
	int getPlayerNo() const { return m_playerNo; }

	// スコアの取得
	int getScore();

	// プレイ時間(フレーム数)の取得
	int getPlayFrame() const { return m_playFrameCount; }

	// プレイヤーを状態遷移させる
//	void startWait();	// 使う予定無し
	void startIdling();
	void startDig();

	// 死んでいるか
	bool isDead();

	// ゲーム進行速度の取得
	int getTempo()const { return m_tempo; }
	float getDt();

	// デモプレイ
	bool	isDemo();

private:
	// 表示に使用する情報
	struct DispData
	{
		Vec2 pos;
		int grphHandle;
		int animIndex;
		double angle;
	};

	// 現在の情報を最新DispDataとして追加する
	void addDispData();
	void addDispDataIdle();

	// プレイヤーの状態ごとのupdate()
	void updateWait();		// 最初の待機
	void updateIdling();	// カウントダウン中	移動はしないが旋回はできる
	void updateDig();		// 掘り進む

	void updateDeadHit();	// 地面にぶつかって死亡

	// 死亡チェック
	bool isCheckDead();

	// プレイヤー位置を見てスクロール量を調整する
	void setScroll();

	// 移動軌跡パーティクル生成
	void createMoveParticle();

private:
	// 常駐リソース
	static std::vector<int>	m_idleGraph;
	static std::vector<int>	m_runGraph;

private:
	// 
	std::shared_ptr<PlayerManager>	m_pManager;
	// 地形データ
	std::shared_ptr<Field>	m_pField;
	// パーティクル
	std::shared_ptr<ParticleManager>	m_pParticle;

	// メンバー関数ポインタ
//	void (Player::*m_updateFunc)() = &Player::updateIdling;
	void (Player::* m_updateFunc)() = &Player::updateWait;

	// 操作するプレイヤーの番号
	int m_playerNo;

	// プレイヤーの種類
	int m_kind;

	// プレイヤー番号表示	一人プレイなら表示しない
	bool m_isDispPlayerNo;

	// プレイヤーの進行速度管理
	int m_tempo;

	// アニメーション用のカウンタ
	float m_animFrame;
	// 
	Vec2	m_pos;	// 中心位置
	Vec2	m_vec;
	float	m_angle;

	Vec2	m_scroll;

	// プレイ時間(生き残りフレーム数)
	int		m_playFrameCount;

	// シーケンス変化してからのフレーム数
	int		m_updateFrameCount;
	// 掘る効果音フレームカウント
	float	m_digFrameCount;
	// テンポアップしてからの経過フレーム
	int		m_tempoUpFrame;

	// 表示用データ
	std::deque<DispData>	m_dispData;

	// デモプレイ
	bool m_isDemo;
};

