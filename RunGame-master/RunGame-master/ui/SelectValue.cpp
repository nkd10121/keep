#include "SelectValue.h"
#include "DxLib.h"

#include "EffectPlayer.h"
#include "Pad.h"
#include "Font.h"
#include "Player.h"

#include <cassert>

namespace
{
	// 表示情報
	constexpr unsigned int kSelectTextColor = 0xffffff;
	constexpr unsigned int kUnselectTextColor = 0xa0a0a0;

	// BGM,SE音量
	constexpr int kBarLen = 420;
	constexpr int kBarHeight = 16;
}

SelectValue::SelectValue():
	m_isActive(false),
	m_value(0),
	m_min(0),
	m_max(0)
{
	m_pCurrectValue = std::make_shared<EffectPlayer>();
	m_pCurrectValue->setupIcon(Vec2{ 0,0 });
	m_pCurrectValue->setVec(Vec2{ 1,0 });
	m_pCurrectValue->setRun(true);
	m_pCurrectValue->setMove(false);
	m_pCurrectValue->setRandomKind();
	m_pCurrectValue->setScale(1.2);

	m_pCursorL = std::make_shared<EffectPlayer>();
	m_pCursorL->setupIcon(Vec2{ 0,0 });
	m_pCursorL->setVec(Vec2{ -1,0 });
	m_pCursorL->setRun(true);
	m_pCursorL->setMove(false);
	m_pCursorL->setKind(m_pCurrectValue->getPlayerKind());

	m_pCursorR = std::make_shared<EffectPlayer>();
	m_pCursorR->setupIcon(Vec2{ 0,0 });
	m_pCursorR->setVec(Vec2{ 1,0 });
	m_pCursorR->setRun(true);
	m_pCursorR->setMove(false);
	m_pCursorR->setKind(m_pCurrectValue->getPlayerKind());
}

SelectValue::~SelectValue()
{
}

void SelectValue::init(Vec2 center, int min, int max, int nowValue)
{
	assert(min < max);

	m_center = center;
	m_min = min;
	m_max = max;
	m_value = nowValue;

	updateValueIconPos();
	updateValueIconAnim(0);
}

void SelectValue::update()
{

	// 選択されていない場合の処理はここまで
	if (!m_isActive)	return;

	m_pCurrectValue->update();

	if (Pad::isTrigger(PAD_INPUT_LEFT))
	{
		m_value--;
		if (m_value < m_min)
		{
			m_value = m_min;
		}
		else
		{
			updateValueIconAnim(-1);
		}
		updateValueIconPos();
	}
	else if (Pad::isTrigger(PAD_INPUT_RIGHT))
	{
		m_value++;
		if (m_value > m_max)
		{
			m_value = m_max;
		}
		else
		{
			updateValueIconAnim(1);
		}
		updateValueIconPos();
	}
}

void SelectValue::draw()
{
	int x = static_cast<int>(m_center.x - kBarLen);
	int y = static_cast<int>(m_center.y - kBarHeight);
	unsigned int color = kSelectTextColor;
	if (!m_isActive)	color = kUnselectTextColor;

	// 数値表示
	DrawFormatStringToHandle(x-64, y, color, Font::getHandle(Font::Id::Size32_4), "%d", m_value);

	float rate = getValueRate();

	// バー表示
	DrawBox(x - 2, y - 2, x + kBarLen + 2, y + kBarHeight + 2, 0xffffff, false);
	DrawBox(x, y, getBarEndX(), y + kBarHeight, Player::getColor(m_pCurrectValue->getPlayerKind()), true);

	// 演出アイコン表示
	m_pCurrectValue->draw();
}

void SelectValue::setActive(bool isActive)
{
	m_isActive = isActive;
}

float SelectValue::getValueRate()
{
	int range = m_max - m_min;
	int val = m_value - m_min;
	return static_cast<float>(val) / static_cast<float>(range);
}

int SelectValue::getBarEndX()
{
	int x = static_cast<int>(m_center.x - kBarLen);
	return x + static_cast<int>(kBarLen * getValueRate());
}

void SelectValue::updateValueIconPos()
{
	Vec2 iconPos;
	iconPos.x = static_cast<float>(getBarEndX());
	iconPos.y = m_center.y - kBarHeight + 8;
	m_pCurrectValue->setPos(iconPos);
}

void SelectValue::updateValueIconAnim(int change)
{
	if (m_value == 0)
	{
		m_pCurrectValue->setVec(Vec2{ 0,-1 });
		m_pCurrectValue->setRun(false);
		m_pCurrectValue->setAnimSpeed(16);
		return;
	}
	if (change >= 0)
	{
		// デフォルト、音量アップ時は右向きに
		m_pCurrectValue->setVec(Vec2{ 1,0 });
		m_pCurrectValue->setRun(true);
	}
	else
	{
		// 音量下げたときは左向きに
		m_pCurrectValue->setVec(Vec2{ -1,0 });
		m_pCurrectValue->setRun(true);
	}
	m_pCurrectValue->setAnimSpeed(10 - static_cast<int>(8 * getValueRate()));
}
