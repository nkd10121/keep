#pragma once
#include "SceneBase.h"
#include <memory>
#include <list>
#include <vector>

class Player;
class PlayerManager;
class Field;
class PadUi;
class DispRecord;
class ParticleManager;
class EffectString;
class EffectPlayer;
class MultiPlayScore;

class SceneMain : public SceneBase
{
public:
	SceneMain(int playerNum, bool isDemo);
	virtual ~SceneMain() {}

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

#ifdef _DEBUG
	// デバッグ表示(最前面表示)
	virtual void drawDebug() override;
#endif

	// プレイヤーの種類指定	余分に渡しても良い(止まらないし特に何かに反映されたりしない)
	void setPlayerKind(int playerNo, int kind);

private:
	// シーケンスごとのupdate処理
	void updateWait();		// 開始前の待ち時間
	void updateCountdown();	// 3,2,1表示
	void updatePlay();		// ゲームプレイ

	void updateGameover();	// ゲームオーバー演出

	void updateResult();	// ゲームオーバー後のランキング表示

	//  ゲーム開始前説明メッセージの表示
	void drawTutorial();
	void drawTutorialSingle();
	void drawTutorialMulti();

	// 背景演出
	void drawBg();

	// 現在の移動距離の表示
	void drawScore();

	// 表示座標(数値の単位の間の座標を指定)と表示したいスコア、フォントを指定して表示
	// 一人プレイ用
	void drawScoreSingle( int x, int y, int score );

	// メッセージ表示	スピードアップ
	// 画面上部(邪魔にならないところに表示する)
	void drawMessage();

	// ゲームオーバーUIの生成	ランクインした場合は順位を引数で渡す	ランクインしていない場合は-1
	void startGameOver(int rank);
	// 対戦結果の生成
	void startBattleResult();

	// 演出用キャラクターの更新
	void updateMob();
	// 演出用キャラクターの走行エフェクト生成
	void createMobParticle(std::shared_ptr<EffectPlayer> pMob);

	// 使用するBGMの名前
	const char* getBgmName();

	// 多人数プレイ判定
	bool isMulti();
	// デモプレイ
	bool isDemo();
	// デモ用のランキングUI生成
	void startDemoRanking();

private:
	// シーケンス別update処理
//	void (SceneMain::*m_updateFunc)() = &SceneMain::updatePlay;
	void (SceneMain::* m_updateFunc)() = &SceneMain::updateWait;
	// プレイヤー数
	int m_playerNum;
	// プレイヤーの種類指定	他のシーンからの受け渡しに使用	-1の場合はランダム
	std::vector<int> m_selectPlayerKind;
	// ゲーム画面
	int m_gameScreen;
	// グラフィック
	int m_fieldGraph;
	int m_uiBorder;
	int m_bgTile;

	std::shared_ptr<PlayerManager>	m_pPlayer;
	std::shared_ptr<Field>	m_pField;
	// パーティクル演出
	std::shared_ptr<ParticleManager>	m_pParticle;
	// 地上の演出用キャラクター
	int m_mobInterval;	// キャラクター登場間隔カウント
	std::list<std::shared_ptr<EffectPlayer>>	m_pMob;

	// 対戦プレイ用スコアUI
	std::vector<std::shared_ptr<MultiPlayScore>>	m_pMultiPlayScore;

	// ポーズ表示
	std::shared_ptr<EffectString>	m_pPauseText;

	// ゲームオーバーのUI
	std::shared_ptr<PadUi>	m_pGameOver;

	// ランキング表示
	std::shared_ptr<DispRecord>	m_pRecord;

	// デモ中のメッセージ表示
	std::shared_ptr<EffectString>	m_pDemoText;

	// チュートリアルメッセージ表示
	int m_tutorialMessageNo;
	float m_tutorialMessageSinRate;

	// カウントダウン表示
	int m_countDownNum;
	int m_countDownAlpha;
	double m_countDownScale;

	// ゲームメッセージ表示
	bool m_isDispMessage;
	int	m_messageFrameCount;
	int	m_messageDispFrame;

	// 演出
	int m_updateFrame;

	// ポーズ
	bool m_isPause;
	// デモプレイ
	bool m_isDemo;
};

