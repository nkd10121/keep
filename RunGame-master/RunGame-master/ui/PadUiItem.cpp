#include "PadUiItem.h"
#include "DxLib.h"

#include "Font.h"
#include "EffectString.h"

namespace
{
	// 色
	constexpr int kSelectColorR = 0xff;
	constexpr int kSelectColorG = 0xff;
	constexpr int kSelectColorB = 0xff;

	constexpr int kUnselectColorR = 0xa0;
	constexpr int kUnselectColorG = 0xa0;
	constexpr int kUnselectColorB = 0xa0;

	// 選択、非選択状態変化時に色が変化するのにかかるフレーム数
	constexpr int kColorChangeFrame = 8;

	const int kColorRChangeValue = abs(kSelectColorR - kUnselectColorR) / kColorChangeFrame;
	const int kColorGChangeValue = abs(kSelectColorG - kUnselectColorG) / kColorChangeFrame;
	const int kColorBChangeValue = abs(kSelectColorB - kUnselectColorB) / kColorChangeFrame;

	// 演出
	constexpr int kAppearFrame = 8;
	constexpr int kEraseFrame = 8;

	constexpr double kSelectScale = 1.0;
	constexpr double kUnselectScale = 0.5;
	constexpr int kScaleChangeFrame = 8;
}

PadUiItem::PadUiItem(int index, const char* str):
	m_graphHandle(-1),
	m_borderHandle(-1),
	m_font(-1),
	m_karning(0),
	m_isDecideEnable(true),
	m_colorR(kUnselectColorR),
	m_colorG(kUnselectColorG),
	m_colorB(kUnselectColorB),
	m_alpha(0),
	m_selectScale(kSelectScale),
	m_unselectScale(kUnselectScale),
	m_index(index),
	m_str(str),
	m_isSelect(false),
	m_frameCount(0),
	m_startWait(-1),
	m_scale(m_unselectScale),
	m_trgUp(-1),
	m_repUp(-1),
	m_trgDown(-1),
	m_repDown(-1),
	m_trgLeft(-1),
	m_repLeft(-1),
	m_trgRight(-1),
	m_repRight(-1)
{
}

PadUiItem::~PadUiItem()
{
	DeleteGraph(m_graphHandle);
}

void PadUiItem::setSelectScale(double scale)
{
	m_selectScale = scale;
	if (m_isSelect)	m_scale = m_selectScale;
}

void PadUiItem::setUnselectScale(double scale)
{
	m_unselectScale = scale;
	if (!m_isSelect)	m_scale = m_selectScale;
}

void PadUiItem::setup()
{
	m_graphHandle = MakeScreen(static_cast<int>(m_rect.getWidth()), static_cast<int>(m_rect.getHeight()), true);

	Vec2 strCenter;
	strCenter.x = m_rect.getWidth() / 2;
	strCenter.y = m_rect.getHeight() / 2;
	m_pString = std::make_shared<EffectString>();
	m_pString->setupCenter(strCenter, m_str, m_font, m_karning);
}

void PadUiItem::update()
{
	(this->*m_updateFunc)();
}

void PadUiItem::draw()
{
	SetDrawScreen(m_graphHandle);
	ClearDrawScreen();
	drawBase();
	m_pString->draw();

	SetDrawScreen(DX_SCREEN_BACK);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_alpha);
	DrawRotaGraph(static_cast<int>(m_rect.getCenter().x), static_cast<int>(m_rect.getCenter().y),
			m_scale, 0.0,
			m_graphHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void PadUiItem::start(int wait)
{
	m_startWait = wait;
}

void PadUiItem::decide()
{
	m_updateFunc = &PadUiItem::updateDecide;
	m_frameCount = 0;
}

void PadUiItem::eraseNoDecide()
{
	m_updateFunc = &PadUiItem::updateErase;
	m_frameCount = 0;
}

void PadUiItem::onSelect()
{
	m_isSelect = true;
	m_pString->setEffect(EffectString::Effect::Vibration);
}

void PadUiItem::onUnselect()
{
	m_isSelect = false;
	m_pString->setEffect(EffectString::Effect::None);
}

bool PadUiItem::isOperable() const
{
	return (m_updateFunc == &PadUiItem::updateIdle);
}

void PadUiItem::drawBase()
{
	// グラフィックが指定されていない場合は文字のみUI
	if (m_borderHandle == -1)	return;

	SetDrawBright(m_colorR, m_colorG, m_colorB);
	

	int graphW = 0;
	int graphH = 0;
	GetGraphSize(m_borderHandle, &graphW, &graphH);

	int chipW = graphW / 3;
	int chipH = graphH / 3;
#if false
	int left = m_rect.getLeft();
	int top = m_rect.getTop();
	int right = m_rect.getRight();
	int bottom = m_rect.getBottom();
#else
	int left = 0;
	int top = 0;
	int right = static_cast<int>(m_rect.getWidth());
	int bottom = static_cast<int>(m_rect.getHeight());
#endif

	// 左上チップ
	DrawRectGraph(left, top, 0, 0, chipW, chipH,
		m_borderHandle, true, false);
	// 左下チップ
	DrawRectGraph(left, bottom - chipH, 0, chipH * 2, chipW, chipH,
		m_borderHandle, true, false);
	// 右上チップ
	DrawRectGraph(right - chipW, top, chipW * 2, 0, chipW, chipH,
		m_borderHandle, true, false);
	// 右下チップ
	DrawRectGraph(right - chipW, bottom - chipH, chipW * 2, chipH * 2, chipW, chipH,
		m_borderHandle, true, false);
	// 左ボーダー
	DrawRectExtendGraph(left, top + chipH,
		left + chipW, bottom - chipH,
		0, chipW * 1, chipW, chipH,
		m_borderHandle, true);
	// 上ボーダー
	DrawRectExtendGraph(left + chipW, top,
		right - chipW, top + chipH,
		chipH * 1, chipW * 0, chipW, chipH,
		m_borderHandle, true);
	// 下ボーダー
	DrawRectExtendGraph(left + chipW, bottom - chipH,
		right - chipW, bottom,
		chipH * 1, chipW * 2, chipW, chipH,
		m_borderHandle, true);
	// 右ボーダー
	DrawRectExtendGraph(right - chipW, top + chipH,
		right, bottom - chipH,
		chipH * 2, chipW * 1, chipW, chipH,
		m_borderHandle, true);
	// 塗りつぶし
	DrawRectExtendGraph(left + chipW, top + chipH,
		right - chipW, bottom - chipH,
		chipH * 1, chipW * 1, chipW, chipH,
		m_borderHandle, true);

	// 戻しておく
	SetDrawBright(255, 255, 255);
}

void PadUiItem::updateDispColor()
{
	int targetR = kUnselectColorR;
	int targetG = kUnselectColorG;
	int targetB = kUnselectColorB;
	if (m_isSelect)
	{
		targetR = kSelectColorR;
		targetG = kSelectColorG;
		targetB = kSelectColorB;
	}
	if (m_colorR < targetR)
	{
		m_colorR += kColorRChangeValue;
		m_colorR = min(m_colorR, targetR);
	}
	else if (m_colorR > targetR)
	{
		m_colorR -= kColorRChangeValue;
		m_colorR = max(m_colorR, targetR);
	}

	if (m_colorG < targetG)
	{
		m_colorG += kColorGChangeValue;
		m_colorG = min(m_colorG, targetG);
	}
	else if (m_colorG > targetG)
	{
		m_colorG -= kColorGChangeValue;
		m_colorG = max(m_colorG, targetG);
	}

	if (m_colorB < targetB)
	{
		m_colorB += kColorBChangeValue;
		m_colorB = min(m_colorB, targetB);
	}
	else if (m_colorB > targetB)
	{
		m_colorB -= kColorBChangeValue;
		m_colorB = max(m_colorB, targetB);
	}
}

unsigned int PadUiItem::getDispColor()
{
	return GetColor(m_colorR,m_colorG,m_colorB);
}

void PadUiItem::updateWait()
{
	m_frameCount++;

	m_alpha = 0;
	if (m_startWait >= 0)
	{
		m_startWait--;
		if (m_startWait <= 0)
		{
			m_updateFunc = &PadUiItem::updateAppear;
			m_frameCount = 0;
		}
	}
}

void PadUiItem::updateAppear()
{
	m_frameCount++;
	float rate = static_cast<float>(m_frameCount) / static_cast<float>(kAppearFrame);
	rate = min(rate, 1.0f);

	m_alpha = static_cast<int>(255 * rate);
	if (rate >= 1.0f)
	{
		m_alpha = 255;
		m_updateFunc = &PadUiItem::updateIdle;
		m_frameCount = 0;
	}

	updateDispColor();
	m_pString->setColor(getDispColor());
	m_pString->update();
}

void PadUiItem::updateIdle()
{
	m_frameCount++;

	m_alpha = 255;

	double scaleChangeValue = abs(m_selectScale - m_unselectScale) / kScaleChangeFrame;
	if (m_isSelect)
	{
		m_scale += scaleChangeValue;
		m_scale = min(m_scale, m_selectScale);
	}
	else
	{
		m_scale -= scaleChangeValue;
		m_scale = max(m_scale, m_unselectScale);
	}

	updateDispColor();
	m_pString->setColor(getDispColor());
	m_pString->update();
}

void PadUiItem::updateDecide()
{
	m_frameCount++;

	m_scale = m_selectScale + sin(m_frameCount * 0.05) * 0.2;

	updateDispColor();
	m_pString->setColor(getDispColor());
	m_pString->update();
}

void PadUiItem::updateErase()
{
	m_frameCount++;

	float rate = static_cast<float>(m_frameCount) / static_cast<float>(kEraseFrame);
	rate = min(rate, 1.0f);

	m_alpha = static_cast<int>(255 * (1.0f - rate));
	if (rate >= 1.0f)
	{
		m_alpha = 0;
	//	m_updateFunc = &PadUiItem::updateIdle;
	//	m_frameCount = 0;
	}

	updateDispColor();
	m_pString->setColor(getDispColor());
	m_pString->update();
}
