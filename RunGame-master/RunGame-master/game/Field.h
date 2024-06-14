#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <memory>
#include <vector>
#include <deque>
class PlayerManager;
class Field
{
public:
	Field(bool isDemo);
	virtual ~Field();

	void init();
	void update();
	void draw();

	void setHandle(int handle) { m_handle = handle; }
	// initより前に呼び出す！
	void setPlayerManager(std::shared_ptr<PlayerManager> pPlayer) { m_pPlayer = pPlayer; }

	// プレイヤーの当たり矩形情報から移動可能な矩形情報を取得する
	Rect getMoveEnableRect(const Rect rect);

	// 掘った部分の位置情報を追加
	void addDigData(Vec2 pos, unsigned int color, int playerNo);
	// 初期位置用の穴データ追加
	void addStartDigData(Vec2 pos, unsigned int color, int playerNo);

	// プレイヤーとの当たり判定
	bool isCol(Vec2 pos);

private:
	// 地面のデータ
	struct FieldChip
	{
		int y;
	};
	// 地面データ縦1列分
	struct FieldLine
	{
		int x;
		std::vector<FieldChip>	chip;
	};

	// 掘った部分のデータ
	struct DigData
	{
		Vec2 pos;
		int radius;
		unsigned int color;
	};

	// 地形データ生成関連関数

	// 初期地形データ生成
	void initFieldLine();
	// 画面データ更新	画面外に出た部分を削除して新たに入ってくる部分を生成する
	void updateFieldLine();

	// 縦１ライン分のデータ生成
	FieldLine createLine(int posX);

	// 1ブロック分の地形データ生成して追加
	void addFieldBlock(int startX);

	int addUpperWall(int startX, int lineNum);	// 上半分くらいを覆う壁
	int addUnderWall(int startX, int lineNum);	// 下半分くらいを覆う壁

	int addPipe(int startX, int lineNum);		// 上下の壁追加
	int addHole(int startX, int lineNum);		// ランダムに穴が空いた壁

	// 
	void drawBg();

	// 一定距離ごとの現在距離表示
	void drawDistance();

	// デモプレイ	上下以外障害物出ない
	bool isDemoPlay();

private:
	int m_handle;
	// チップ用グラフィック情報
	int m_graphW;
	int m_graphH;
	int m_chipNumX;
	int m_chipNumY;

	std::shared_ptr<PlayerManager> m_pPlayer;

	// 地面データ
	std::deque<FieldLine>	m_fieldData;

	// 掘った部分データ
	std::vector<std::deque<DigData>>	m_digData;

	// 数メートルおきにラインを引く
	int	m_lineNo;
	float m_lineSin;

	// デモプレイ	障害物出ない
	bool m_isDemo;
};

