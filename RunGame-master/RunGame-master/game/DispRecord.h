#pragma once

#include <memory>
#include <vector>

// ランキング表示
class EffectString;
class EffectPlayer;
class SingleRecord;
class DispRecord
{
public:
	// 表示するタイトル
	enum TitleType
	{
		None,
		Gameover,
		Ranking,
		MultiResult,

		Num
	};

public:
	DispRecord();
	virtual ~DispRecord();

	// 表示するタイトルの設定	表示しない場合はNoneをする必要なし(setupTitleを呼ばなくてOK)
	void setupTitle(TitleType type);
	// 背景フェードアルファ設定	デフォルトは0(背景フェード無し)
	void setBgAlpha(int alpha) { m_bgAlpha = alpha; }
	
	// 表示するデータの登録
	// rankは0からの通し番号	0を指定したら1位として表示される
	// playerNoは対戦でプレイヤー番号を表示したいとき指定する	0を指定したら1Pとして表示される
	// デフォルトの-1だと非表示
	// 一人プレイの場合はtotalPlayerNumに-1を指定	対戦の場合は人数を指定する
	void addData(int index, int rank, int score, int playerKind, int playerNo = -1, int totalPlayerNum = -1);

	// 表示するまでの待ち時間を設定する
	void setDispWait(int index, int frame);

	void update();
	void draw();

	// 強調表示を行いたい順位を指定する	0~の番号で指定
	void setHighlightRank(int rank);

	// 完全に表示が終わったかどうかを取得
	bool isDispEnd();
	// 強制的に完全に表示演出を終わらせて表示状態に
	void forceDisp();

private:
	// 
	int m_frameCount;

	// タイトル文字列
	std::shared_ptr<EffectString>	m_pTitle;
	// 各順位の表示データ
	std::vector<std::shared_ptr<SingleRecord>>	m_pRecord;

	// 背景フェードアルファ	0ならフェード無し、255なら真っ暗
	int		m_bgAlpha;
};

