#include "PadUi.h"
#include "PadUiItem.h"
#include "DxLib.h"

#include "Pad.h"
#include "Font.h"
#include "Sound.h"

namespace
{
	// キーリーピートフレーム
	constexpr int kFirstRepeatFrame = 30;
	constexpr int kRepeatFrame = 4;

	// 
	enum InputDir
	{
		DirUp,
		DirDown,
		DirLeft,
		DirRight,

		DirNum
	};
	constexpr int kDirInputKey[DirNum] =
	{
		PAD_INPUT_UP,
		PAD_INPUT_DOWN,
		PAD_INPUT_LEFT,
		PAD_INPUT_RIGHT,
	};
}

PadUi::PadUi() :
	m_buttonGraph(-1),
	m_isLoop(true),
	m_sinRate(0.0f)
{
	// 上下左右方向のリピートフレームを保存する
	m_repeatFrame.resize(DirNum, 0);
}

PadUi::~PadUi()
{
}

int PadUi::update()
{
	m_sinRate += 0.05f;
	if (m_sinRate > DX_TWO_PI_F)	m_sinRate -= DX_TWO_PI_F;

	for (auto& item : m_pItem)
	{
		item->update();
	}

	// 全てのUIが待機状態になったら操作可能に
	if (!isOperable())
	{
		return -1;
	}

	std::vector<bool>	isTrg;
	isTrg.resize(DirNum, false);
	std::vector<bool>	isRep;
	isRep.resize(DirNum, false);
	for (int i = 0; i < DirNum; i++)
	{
		 const int key = kDirInputKey[i];
		 if (Pad::isTrigger(key))
		 {
			 isTrg[i] = true;
			 m_repeatFrame[i] = kFirstRepeatFrame;
		 }
		 else if (Pad::isPress(key))
		 {
			 m_repeatFrame[i]--;
			 if (m_repeatFrame[i] <= 0)
			 {
				 isRep[i] = true;
				 m_repeatFrame[i] = kRepeatFrame;
			 }
		 }
	}
	int next = getSelectIndex();
	if (next >= 0)
	{
		std::shared_ptr<PadUiItem> pItem = getItem(getSelectIndex());
		if (isTrg[DirUp] && pItem->getTriggerUp() >= 0)
		{
			next = pItem->getTriggerUp();
		}
		else if (isTrg[DirDown] && pItem->getTriggerDown() >= 0)
		{
			next = pItem->getTriggerDown();
		}
		else if (isTrg[DirLeft] && pItem->getTriggerLeft() >= 0)
		{
			next = pItem->getTriggerLeft();
		}
		else if (isTrg[DirRight] && pItem->getTriggerRight() >= 0)
		{
			next = pItem->getTriggerRight();
		}
		else if (isRep[DirUp] && pItem->getRepeatUp() >= 0)
		{
			next = pItem->getRepeatUp();
		}
		else if (isRep[DirDown] && pItem->getRepeatDown() >= 0)
		{
			next = pItem->getRepeatDown();
		}
		else if (isRep[DirLeft] && pItem->getRepeatLeft() >= 0)
		{
			next = pItem->getRepeatLeft();
		}
		else if (isRep[DirRight] && pItem->getRepeatRight() >= 0)
		{
			next = pItem->getRepeatRight();
		}
	}
	else
	{
		for (int i = 0; i < DirNum; i++)
		{
			if (isTrg[i])	next = 0;
		}
	}

	if (next != getSelectIndex())
	{
		Sound::getInstance().play("uiMoveCursor");
		Pad::vibrationLow();
		int prev = getSelectIndex();
		for (auto& item : m_pItem)
		{
			if (item->getIndex() == prev)
			{
				item->onUnselect();
			}
			else if (item->getIndex() == next)
			{
				item->onSelect();
			}
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1) && isDecideEnable())
	{
		if (getSelectIndex() >= 0)
		{
			Sound::getInstance().play("uiDecide");
		}

		for (int i = 0; i < m_pItem.size(); i++)
		{
			if (i != getSelectIndex())
			{
				// 選ばれなかった項目
				m_pItem[i]->eraseNoDecide();
			}
			else
			{
				// 選んだ項目
				m_pItem[i]->decide();
			}
		}

		return getSelectIndex();
	}
	return -1;
}

void PadUi::draw()
{
	for (auto& item : m_pItem)
	{
		item->draw();
	}
}

void PadUi::addItem(std::shared_ptr<PadUiItem> pItem)
{
	m_pItem.push_back(pItem);
}

void PadUi::addItem(int index, const char* str, Rect rect)
{
	std::shared_ptr<PadUiItem>	pItem = std::make_shared<PadUiItem>(index, str);
	pItem->setBorderHandle(m_buttonGraph);
	pItem->setRect(rect);
	pItem->setFont(Font::getHandle(Font::Id::TitleMenu));
	pItem->setup();
	pItem->onUnselect();	// いったん非選択状態に
	m_pItem.push_back(pItem);
}

void PadUi::addItem(int index, const char* str, Vec2 center, int width, int height)
{
	Rect rect;
	rect.setup(Rect::PosType::Center, center, static_cast<float>(width), static_cast<float>(height));
	addItem(index, str, rect);
}

void PadUi::addItem(int index, const char* str, int centerX, int centerY, int width, int height)
{
	Rect rect;
	rect.setup(Rect::PosType::Center, Vec2(static_cast<float>(centerX), static_cast<float>(centerY)), static_cast<float>(width), static_cast<float>(height));
	addItem(index, str, rect);
}

void PadUi::setupVArrange(bool isLoop)
{
	// 項目が1つしか無い場合は移動しない
	if (m_pItem.size() <= 1)	return;

	int buttonNum = static_cast<int>(m_pItem.size());
	
	for(int i = 0; i < buttonNum; i++)
	{
		if (i == 0)
		{
			// 一番上のボタン
			if(isLoop)
			{
				m_pItem[i]->setTriggerUp(buttonNum-1);
			}
			m_pItem[i]->setTriggerDown(i + 1);
			m_pItem[i]->setRepeatDown(i + 1);
		}
		else if (i == (buttonNum - 1))
		{
			// 一番下のボタン
			m_pItem[i]->setTriggerUp(i - 1);
			m_pItem[i]->setRepeatUp(i - 1);
			if (isLoop)
			{
				m_pItem[i]->setTriggerDown(0);
			}
		}
		else
		{
			m_pItem[i]->setTriggerUp(i - 1);
			m_pItem[i]->setRepeatUp(i - 1);
			m_pItem[i]->setTriggerDown(i + 1);
			m_pItem[i]->setRepeatDown(i + 1);
		}
	}
}

void PadUi::setupHArrange(bool isLoop)
{
	// 項目が1つしか無い場合は移動しない
	if (m_pItem.size() <= 1)	return;

	int buttonNum = static_cast<int>(m_pItem.size());

	for (int i = 0; i < buttonNum; i++)
	{
		if (i == 0)
		{
			// 一番左のボタン
			if (isLoop)
			{
				m_pItem[i]->setTriggerLeft(buttonNum-1);
			}
			m_pItem[i]->setTriggerRight(i + 1);
			m_pItem[i]->setRepeatRight(i + 1);
		}
		else if (i == (buttonNum - 1))
		{
			// 一番右のボタン
			m_pItem[i]->setTriggerLeft(i - 1);
			m_pItem[i]->setRepeatLeft(i - 1);
			if (isLoop)
			{
				m_pItem[i]->setTriggerRight(0);
			}
		}
		else
		{
			m_pItem[i]->setTriggerLeft(i - 1);
			m_pItem[i]->setRepeatLeft(i - 1);
			m_pItem[i]->setTriggerRight(i + 1);
			m_pItem[i]->setRepeatRight(i + 1);
		}
	}
}

void PadUi::setSelect(int index)
{
	for (auto& item : m_pItem)
	{
		if (item->getIndex() == index)
		{
			item->onSelect();
		}
		else
		{
			item->onUnselect();
		}
	}
}

int PadUi::getSelectIndex()
{
	for (auto& item : m_pItem)
	{
		if (item->isSelecting())	return item->getIndex();
	}
	return -1;
}

std::shared_ptr<PadUiItem> PadUi::getItem(int index)
{
	return m_pItem[index];
}

bool PadUi::isOperable() const
{
	for (auto& item : m_pItem)
	{
		if (!item->isOperable())	return false;
	}
	return true;
}

bool PadUi::isDecideEnable()
{
	// 何も選択されていない
	if (getSelectIndex() < 0)	return false;
	// 決定出来ないUiItem
	if (!getItem(getSelectIndex())->isDecideEnable())	return false;

	return true;
}
