#include "SelectSeveral.h"
#include "DxLib.h"
#include "Pad.h"
#include "Font.h"
#include "EffectPlayer.h"

#include <cassert>

namespace
{
	constexpr Font::Id kFont = Font::Id::Size32_4;

	// 表示情報
	constexpr unsigned int kSelectTextColor = 0xffffff;
	constexpr unsigned int kUnselectTextColor = 0xa0a0a0;

	// カーソル表示
	constexpr int kCursorMarginX = 32;	// 文字の端からカーソル表示位置までの隙間
	constexpr int kCursorOffsetY = -2;	// カーソルをいい感じの位置に表示するためのY位置ずらし
}

SelectSeveral::SelectSeveral():
	m_selectNo(0),
	m_isActive(false),
	m_cursorMoveX(0.0f)
{
	m_pCursorL = std::make_shared<EffectPlayer>();
	m_pCursorL->setupIcon(Vec2{ 0,0 });
	m_pCursorL->setVec(Vec2{ -1,0 });
	m_pCursorL->setRun(true);
	m_pCursorL->setMove(false);
	m_pCursorL->setRandomKind();

	m_pCursorR = std::make_shared<EffectPlayer>();
	m_pCursorR->setupIcon(Vec2{ 0,0 });
	m_pCursorR->setVec(Vec2{ 1,0 });
	m_pCursorR->setRun(true);
	m_pCursorR->setMove(false);
	m_pCursorR->setKind(m_pCursorL->getPlayerKind());
}

SelectSeveral::~SelectSeveral()
{
}

void SelectSeveral::init(Vec2 center)
{
	m_center = center;
}

void SelectSeveral::update()
{
	// 文字サイズに合わせてカーソルの表示位置設定
	updateCurorPos();

	// 選択されていない場合の処理はここまで
	if (!m_isActive)	return;

	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		m_selectNo--;
		if (m_selectNo < 0)	m_selectNo = 0;
	}
	else if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_selectNo++;
		if (m_selectNo >= m_item.size())	m_selectNo = static_cast<int>(m_item.size()) - 1;
	}

	m_cursorMoveX += 0.2f;
	if (m_cursorMoveX >= 12.0f)	m_cursorMoveX = 0;
	m_pCursorL->update();
	m_pCursorR->update();
}

void SelectSeveral::draw()
{
	unsigned int color = kSelectTextColor;
	if(!m_isActive) color = kUnselectTextColor;

	int width = Font::getStringWidth(m_item[m_selectNo].str, kFont);
	int height = Font::getSize(kFont);
	int x = static_cast<int>(m_center.x - width / 2);
	int y = static_cast<int>(m_center.y - height / 2);
	Font::drawString(x, y, m_item[m_selectNo].str, color, kFont);

	if (m_selectNo < getItemNum() - 1)
	{
		m_pCursorR->draw();
	}
	if (m_selectNo > 0)
	{
		m_pCursorL->draw();
	}
}

void SelectSeveral::addItem(const char* str, int value)
{
	Item item;
	item.str = str;
	item.value = value;

	m_item.push_back(item);
}

void SelectSeveral::setup()
{
	// 文字サイズに合わせてカーソルの表示位置設定
	updateCurorPos();
}

void SelectSeveral::setSelectIndex(int index)
{
	m_selectNo = index;
}

void SelectSeveral::setSelectValue(int value)
{
	for (int i = 0; i < m_item.size(); i++)
	{
		if (m_item[i].value == value)
		{
			m_selectNo = i;
			return;
		}
	}
	assert(false);
}

void SelectSeveral::setActive(bool isActive)
{
	m_isActive = isActive;
}

int SelectSeveral::getItemNum()
{
	return static_cast<int>(m_item.size());
}

int SelectSeveral::getSelectNo()
{
	return m_selectNo;
}

int SelectSeveral::getSelectValue()
{
	return m_item[m_selectNo].value;
}

int SelectSeveral::getValue(int index)
{
	return m_item[index].value;
}

void SelectSeveral::updateCurorPos()
{
	// 文字サイズに合わせてカーソルの表示位置設定
	int width = Font::getStringWidth(m_item[m_selectNo].str, kFont);
	Vec2 pos = m_center;
	// 左カーソル
	pos.x = m_center.x - width / 2 - kCursorMarginX - m_cursorMoveX;
	pos.y += kCursorOffsetY;
	m_pCursorL->setPos(pos);
	// 右カーソル
	pos.x = m_center.x + width / 2 + kCursorMarginX + m_cursorMoveX;
	pos.y += kCursorOffsetY;
	m_pCursorR->setPos(pos);
}
