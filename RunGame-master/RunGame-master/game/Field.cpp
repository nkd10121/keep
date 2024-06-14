#include "Field.h"
#include "DxLib.h"
#include "game.h"
#include "Font.h"
#include "Message.h"
#include "Player.h"
#include "PlayerManager.h"

#include <string>
#include <cassert>

namespace
{
	// マップチップ情報
	constexpr int kChipWidth = 16;
	constexpr int kChipHeight = 16;
	// チップ番号
	constexpr int kWallChipNo = 122;	// プレイヤーがぶつかる壁のチップ番号
	constexpr int kSoilChipNo = 29;	// 土のチップ番号
	constexpr int kLandChipNo = 7;	// 地面のチップ番号

	// 地面を表示する高さ
	constexpr int kFieldY = kChipHeight * 6;

	// 上下壁の位置
	constexpr int kPipeTopY = -Game::kScreenHeight / 2 + kFieldY + kChipHeight;	// 地面のすぐ下
	constexpr int kPipeBottomY = Game::kScreenHeight / 2 - kChipHeight;

	// 掘った場所の色
	constexpr unsigned int kDigColor = 0x4C2E30;

	// 掘る穴のサイズ
	constexpr int kDigRadiusMin = 10;
	constexpr int kDigRadiusMax = 16;

	// 穴の位置データ最大保存数
	constexpr int kDigDataMax = 1024;

	// 一定間隔で線を引く
	constexpr int kDispDistanceY = 48+44;
	constexpr int kDispDistanceInterval = 100;

	constexpr int kDispDistanceArrowY = 96 + 44;

	// 一定間隔ごとに難易度上昇(メートル)
	constexpr int kLevelUpDistanceY = 1000;
}

Field::Field(bool isDemo):
	m_handle(-1),
	m_graphW(0),
	m_graphH(0),
	m_chipNumX(0),
	m_chipNumY(0),
	m_lineNo(1),	// 0メートルは表示しない
	m_lineSin(0.0f),
	m_isDemo(isDemo)
{
	m_digData.resize(Game::kMaxPlayer);
}

Field::~Field()
{
}

void Field::init()
{
	// グラフィックデータから情報を生成する
	GetGraphSize(m_handle, &m_graphW, &m_graphH);

	// グラフィックに含まれるチップの数
	m_chipNumX = m_graphW / kChipWidth;
	m_chipNumY = m_graphH / kChipHeight;

	initFieldLine();
}

void Field::update()
{
	Vec2 scroll = m_pPlayer->getScroll();
	// ラインの点滅
	m_lineSin += 0.05f;
	if (m_lineSin > DX_TWO_PI_F)	m_lineSin -= DX_TWO_PI_F;

	int lineX = static_cast<int>(Game::kScreenWidth / 2 + m_pPlayer->getScroll().x + (m_lineNo * kDispDistanceInterval) * 16.0f);
	if (lineX < 0 - 64)
	{
		m_lineNo++;
	}

	// プレイヤーの現在位置から使用済みのマップ情報を削除し、
	// これから必要になりそうなデータを追加する

	updateFieldLine();
}

void Field::draw()
{
	drawBg();

	// 掘った部分の情報
	for (auto& hole : m_digData)
	{
		for (auto& dig : hole)
		{
			Vec2 center = dig.pos;
			center += m_pPlayer->getScroll();
			DrawCircle(static_cast<int>(center.x), static_cast<int>(center.y), dig.radius, dig.color, true);
		}
	}

	// 1ラインずつ地面を描画する
	int indexX = kWallChipNo % m_chipNumX;
	int indexY = kWallChipNo / m_chipNumX;
	for (auto& line : m_fieldData)
	{
		int posX = static_cast<int>(line.x + m_pPlayer->getScroll().x);
		for (auto& chip : line.chip)
		{
			int posY = static_cast<int>(chip.y + m_pPlayer->getScroll().y);

			DrawRectGraph(posX, posY,
				indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
		}
	}

	drawDistance();
	
#if false
	// 200メートルラインを引くテスト
	for (int i = 200; i < 5000; i += 200)
	{
		int lineX = Game::kScreenWidth / 2 + m_pPlayer->getScroll().x + i * 16.0f;
		DrawLine(lineX, 0, lineX, Game::kScreenHeight, 0xff0000, 8);
	}
#endif
#if false
	// 無駄に地面データが生成されていないかチェック
	DrawFormatString(8, 640, 0xffffff, "Field line Num : %d", m_fieldData.size());
#endif
#if false
	Vec2 pos = Vec2{0,0};
	pos += m_pPlayer->getScroll();

	DrawRectGraph(static_cast<int>(pos.x), static_cast<int>(pos.y),
		indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
#endif
}

Rect Field::getMoveEnableRect(const Rect rect)
{
	Rect result;

	// マップ全体を移動可能な状態で初期化
	result.setTop(rect.getCenter().y - Game::kScreenHeight / 2);
	result.setBottom(rect.getCenter().y + Game::kScreenHeight / 2);
	result.setLeft(rect.getCenter().x - Game::kScreenWidth / 2);
	result.setRight(rect.getCenter().x + Game::kScreenWidth / 2);

	// 上下方向チェック
	for (auto& field : m_fieldData)
	{
		// 左右方向をチェックして絶対に当たらないものは除外する
		if (field.x > rect.getRight())	continue;
		if (field.x + kChipWidth < rect.getLeft())	continue;

		for (auto& chip : field.chip)
		{
			// プレイヤーより下にあるブロック
			if (chip.y > rect.getBottom()-1)
			{
				if (result.getBottom()-1 > chip.y)
				{
					result.setBottom(static_cast<float>(chip.y));
				}
			}
			// プレイヤーより上にあるブロック
			if (chip.y + kChipHeight < rect.getTop())
			{
				if (result.getTop() < chip.y + kChipHeight)
				{
					result.setTop(static_cast<float>(chip.y + kChipHeight));
				}
			}
		}
	}
	// 右方向チェック	右に進むので左はチェック不要
	bool isEnd = false;
	for (auto& field : m_fieldData)
	{
		// 左にいる奴は除外
		if (field.x < rect.getLeft())	continue;

		for (auto& chip : field.chip)
		{
			// 左右移動で当たらないものを除外
			if (chip.y > rect.getBottom() - 1)	continue;
			if (chip.y + kChipHeight < rect.getTop())	continue;

			// 左から順番にチェックするので最初のが見つかったらそこで終了してOK
			result.setRight(static_cast<float>(field.x));
			isEnd = true;
			break;
		}
		if (isEnd)	break;
	}
	return result;
}

void Field::addDigData(Vec2 pos, unsigned int color, int playerNo)
{
	DigData data;
	data.pos = pos;
	data.radius = kDigRadiusMin + GetRand(kDigRadiusMax - kDigRadiusMin);
	data.color = color;
	m_digData[playerNo].push_back(data);
	if (m_digData[playerNo].size() > kDigDataMax)
	{
		m_digData[playerNo].pop_front();
	}
}

void Field::addStartDigData(Vec2 pos, unsigned int color, int playerNo)
{
	DigData data;
	data.pos = pos;
	data.radius = kDigRadiusMax;
	data.color = color;
	m_digData[playerNo].push_back(data);
	if (m_digData[playerNo].size() > kDigDataMax)
	{
		m_digData[playerNo].pop_front();
	}
}

bool Field::isCol(Vec2 pos)
{
	for (auto& line : m_fieldData)
	{
		if (line.x > pos.x)	continue;
		if (line.x + kChipWidth < pos.x)	continue;

		for (auto& chip : line.chip)
		{
			if (chip.y > pos.y)	continue;
			if (chip.y + kChipHeight < pos.y)	continue;

			return true;
		}
	}

	return false;
}

void Field::initFieldLine()
{
	Vec2 playerPos = m_pPlayer->getPlayer(0)->getPos();
	// 画面左から上下の壁を配置する
	int posX = static_cast<int>(playerPos.x);
	posX -= Game::kScreenWidth / 2;
	int num = Game::kScreenWidth / kChipWidth;
	posX = addPipe(posX, num);

	if (isDemoPlay())
	{
		// 障害物出ない
		posX = addPipe(posX, 100);
		return;
	}

	// 最初は1/2でどっちかのパターン
	if (GetRand(1))
	{
		// 下→上→下→上ルート
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
	}
	else
	{
		// 上→下→上→下ルート
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUnderWall(posX, 4);
		posX = addPipe(posX, 16);
		posX = addUpperWall(posX, 4);
	}
}

void Field::updateFieldLine()
{
	Vec2 scroll = m_pPlayer->getScroll();

	// 画面外に出たラインを削除していく
	int deleteLineNum = 0;
	while (1)
	{
		int screenX = static_cast<int>(m_fieldData.front().x + scroll.x);
		if (screenX > 0 - kChipWidth)	break;

		m_fieldData.pop_front();
		deleteLineNum++;
	}

	// 後ろのラインがなくなりそうなら追加する
	int posX = m_fieldData.back().x;
	if (posX + scroll.x < Game::kScreenWidth + 64)
	{
		addFieldBlock(posX + kChipWidth);
	}
}

Field::FieldLine Field::createLine(int posX)
{
	FieldLine lineData;
	lineData.x = posX;
	// 現在設定中のラインのブロックデータを生成(とりあえず地面のみ)
	FieldChip chip;
	chip.y = 0;
	lineData.chip.push_back(chip);

	return lineData;
}

void Field::addFieldBlock(int startX)
{
	Vec2 scroll = m_pPlayer->getScroll();

	int x = startX;

	if (isDemoPlay())
	{
		// 障害物出ない
		x = addPipe(x, 40);
		return;
	}

	int randNum = GetRand(10);
	if (randNum == 0)	// 0
	{
		// ラッキー	上下以外何もなし
		x = addPipe(x, 40);
	}
	else if (randNum <= 2)	// 1 2
	{
		// 長めのトンネル
		x = addPipe(x, 16);
		x = addHole(x, 24);
	}
	else if (randNum <= 4)	// 34
	{
		// 下→上ルート
		x = addPipe(x, 16);
		x = addUpperWall(x, 4);
		x = addPipe(x, 16);
		x = addUnderWall(x, 4);
	}
	else if (randNum <= 6)	// 5 6
	{
		// 上→下ルート
		x = addPipe(x, 16);
		x = addUnderWall(x, 4);
		x = addPipe(x, 16);
		x = addUpperWall(x, 4);
	}
	else	// 7 8 9 10
	{
		// 穴あき壁
		x = addPipe(x, 16);
		x = addHole(x, 4);
	}
}

int Field::addUpperWall(int startX, int lineNum)
{
	Vec2 scroll = m_pPlayer->getScroll();
	// 上下の壁生成
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		int lineX = (x - Game::kScreenWidth / 2) / 16;
		int num = (lineX / kLevelUpDistanceY) + 1;
		FieldLine lineData;
		lineData.x = x;

		for(int j = 0; j < 20; j++)
		{
			FieldChip chip;
			chip.y = kPipeTopY + kChipHeight * j;
			lineData.chip.push_back(chip);
		}
		for (int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeBottomY - kChipHeight * j;
			lineData.chip.push_back(chip);
		}

		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

int Field::addUnderWall(int startX, int lineNum)
{
	Vec2 scroll = m_pPlayer->getScroll();
	// 上下の壁生成
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		int lineX = (x - Game::kScreenWidth / 2) / 16;
		int num = (lineX / kLevelUpDistanceY) + 1;
		FieldLine lineData;
		lineData.x = x;

		for (int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeTopY + j * kChipHeight;
			lineData.chip.push_back(chip);
		}
		for (int j = 0; j < 20; j++)
		{
			FieldChip chip;
			chip.y = kPipeBottomY - kChipHeight * j;
			lineData.chip.push_back(chip);
		}
		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

int Field::addPipe(int startX, int lineNum)
{
	Vec2 scroll = m_pPlayer->getScroll();
	// 上下の壁生成
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		int lineX = (x - Game::kScreenWidth / 2) / 16;
		int num = (lineX / kLevelUpDistanceY) + 1;

		FieldLine lineData;
		lineData.x = x;

		for(int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeTopY + j * kChipHeight;
			lineData.chip.push_back(chip);
		}
		for (int j = 0; j < num; j++)
		{
			FieldChip chip;
			chip.y = kPipeBottomY - j * kChipHeight;
			lineData.chip.push_back(chip);
		}
		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

int Field::addHole(int startX, int lineNum)
{
	int holeY = GetRand(320) - 160 + (kPipeTopY + kPipeBottomY) / 2;

	// 上下の壁生成
	int x = startX;
	for (int i = 0; i < lineNum; i++)
	{
		FieldLine lineData;
		lineData.x = x;

		for (int y = kPipeTopY; y <= kPipeBottomY; y += kChipHeight)
		{
			// 穴をあける
			if (y > (holeY - 64) && y < (holeY + 64))	continue;

			FieldChip chip;
			chip.y = y;
			lineData.chip.push_back(chip);
		}
		m_fieldData.push_back(lineData);
		x += kChipWidth;
	}
	return x;
}

void Field::drawBg()
{
	assert(m_pPlayer);
	int chipScrollX = static_cast<int>(m_pPlayer->getScroll().x) % kChipWidth;
	
	// 一番上のラインには地面を表示
	int indexX = kLandChipNo % m_chipNumX;
	int indexY = kLandChipNo / m_chipNumX;
	for (int x = 0; x < Game::kScreenWidth + kChipWidth; x += kChipWidth)	// スクロールするので1ライン分広く描画
	{
		DrawRectGraph(x + chipScrollX, kFieldY,
			indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
	}
	// 背景を土で埋める
	indexX = kSoilChipNo % m_chipNumX;
	indexY = kSoilChipNo / m_chipNumX;
	for (int x = 0; x < Game::kScreenWidth + kChipWidth; x += kChipWidth)	// スクロールするので1ライン分広く描画
	{
		for (int y = kFieldY + kChipHeight; y < Game::kScreenHeight; y += kChipHeight)	// 一番上のラインには地面を描画しているのでその下のラインから
		{
			DrawRectGraph(x + chipScrollX, y,
				indexX * kChipWidth, indexY * kChipHeight, kChipWidth, kChipHeight, m_handle, true);
		}
	}
}

void Field::drawDistance()
{
	//	int alpha = static_cast<int>(255 * (sinf(m_lineSin) * 0.5f + 0.5f));
	int distance = m_lineNo * kDispDistanceInterval;
	int lineX = static_cast<int>(Game::kScreenWidth / 2 + m_pPlayer->getScroll().x + distance * 16.0f);

	// 距離の表示
	std::string dispDist = std::to_string(distance);
	if (distance == 1)
	{
		dispDist += Message::getInstance().get_c("MSG_COMMON_UNIT");
	}
	else
	{
		dispDist += Message::getInstance().get_c("MSG_COMMON_UNITS");
	}
	
	int width = Font::getStringWidth(dispDist.c_str(), Font::Id::DispDistance);
	int y = kDispDistanceY + static_cast<int>(16 * sinf(m_lineSin));
	Font::drawString(lineX - width / 2, y, dispDist.c_str(), 0xffffff, Font::Id::DispDistance);

	// 矢印
	y = kDispDistanceArrowY + static_cast<int>(16 * sinf(m_lineSin));
	DrawTriangle(lineX, y, 
				lineX + static_cast<int>(16 * sinf(m_lineSin)), y - 24,
				lineX - static_cast<int>(16 * sinf(m_lineSin)), y - 24, 0xff0000, true);
	DrawTriangle(lineX, y, 
				lineX + static_cast<int>(16 * sinf(m_lineSin)), y - 24,
				lineX - static_cast<int>(16 * sinf(m_lineSin)), y - 24, 0xffffff, false);

	y = 720-32 - static_cast<int>(16 * sinf(m_lineSin));
	DrawTriangle(lineX, y,
		lineX + static_cast<int>(16 * sinf(m_lineSin)), y + 24,
		lineX - static_cast<int>(16 * sinf(m_lineSin)), y + 24, 0xff0000, true);
	DrawTriangle(lineX, y,
		lineX + static_cast<int>(16 * sinf(m_lineSin)), y + 24,
		lineX - static_cast<int>(16 * sinf(m_lineSin)), y + 24, 0xffffff, false);
}

bool Field::isDemoPlay()
{
	return m_isDemo;
}

