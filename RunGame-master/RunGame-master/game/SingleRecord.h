#pragma once
#include "Vec2.h"
#include <memory>
#include <vector>

// ランキング画面	一人分のデータ表示
class EffectPlayer;
class SingleRecord
{
public:
	struct DispData
	{
		// データ表示位置
		int y;
		int rankX;
		int scoreX;
		// アイコン情報
		int iconX;
		double iconScale;
		int iconAnimSpeed;
		bool isIconRun;
	};

public:
	SingleRecord();
	virtual ~SingleRecord();

	// プレイヤー番号を表示 -1を指定で非表示
	void setPlayerNo(int no) { m_playerNo = no; }
	// 対戦モードの順位表示設定
	// スコアをフレーム数としてそれを時間に変換して表示する	デフォルトはfalse
//	void setMulti(bool isMulti) { m_isMulti = isMulti; }
	// 対戦モードの順位表示設定
	// プレイヤーの人数を指定	一人プレイでランキングを表示したい場合は-1(デフォルト)
	void setMultiPlayerNum(int num) { m_multiPlayerNum = num; }
	void setHightlight(bool isHighlight) { m_isHighlight = isHighlight; }

	// rankは0~9で渡す
	void setup(int index, int rank, int score, int playerKind, int fontHandle);

	void update();
	void draw();
	// 表示開始までのフレーム数を指定
	void setDispWait(int wait) { m_dispWait = wait; }

	// 完全に表示されているかを取得する
	bool isDisp();
	// 強制的に完全に表示された状態にする
	void forceDisp();
	// 対戦モードの結果表示かどうか
	bool isMulti();

private:
	// アイコンの位置情報
	Vec2 getIconPos();

	// ?位	の表示	右端のX座標, 上端のY座標を指定する
	void drawRank(int x, int y);
	// ????メートル	の表示"メートル"の左端X座標を指定する
	void drawScore(int x, int y);
	// 対戦モード用スコア表示	フレーム数を時間に変換して表示
	void drawScoreMulti(int x, int y);
	// 対戦モード用	プレイヤー番号表示
	void drawPlayerNo();

	// アイコン強調表示演出	プレイヤーアイコンの向こうに表示する
	void drawIconHighlight();

private:
	// 表示するのに必要なデータ
	int m_index;	// 表示位置
	int m_rank;		// 表示する順位	+1が順位として表示される(0なら1位と表示)
	int m_score;
	int m_playerKind;
	int m_fontHandle;
	int m_playerNo;	// 対戦モード時に表示するプレイヤー番号	-1の場合は表示しない

	DispData m_dispData;	// 使用する表示位置データ

//	bool m_isMulti;	// scoreを時間として表示する(対戦プレイ用)	デフォルトはfalse
	int m_multiPlayerNum;	// 対戦モードでのプレイ人数	1人プレイでランキングを表示する場合は-1
	bool m_isHighlight;	// 強調表示したい

	// プレイヤーアイコン
	std::shared_ptr<EffectPlayer>	m_pIcon;

	// 表示に必要な情報
	std::vector<int>	m_numWidth;
	int		m_maxWidth;	// 一番横幅の広いフォントの幅

	// 表示までの待ち時間
	int m_dispWait;
	// 表示開始からアルファで完全に表示するまでのフレーム数
	int m_dispAlphaFrame;
	// 表示開始時の効果音を鳴らした
	bool m_isPlaySe;

	// 演出関連
	float m_sinRate;
};

