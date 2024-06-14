#include "DebugUi.h"
#include "DebugUiItem.h"
#include "DxLib.h"

#include "Pad.h"
#include <cassert>

namespace
{
	// �I�����ڂ��������
	const char* const kCursorString = "��";

	// �L�[���[�s�[�g�t���[��
	constexpr int kFirstRepeatFrame = 30;
	constexpr int kRepeatFrame = 4;
}

DebugUi::DebugUi(int x, int y):
	m_isLoop(true),
	m_offsetX(x),
	m_offsetY(y),
	m_repeatUp(-1),
	m_repeatDown(-1)
{
}

DebugUi::~DebugUi()
{
}

int DebugUi::update()
{
	for (auto& item : m_pItem)
	{
		item->update();
	}

	bool isUp = false;
	bool isDown = false;
	if (Pad::isTrigger(PAD_INPUT_UP))
	{	
		isUp = true;
		m_repeatUp = kFirstRepeatFrame;
	}
	else if (Pad::isPress(PAD_INPUT_UP))
	{
		m_repeatUp--;
		if (m_repeatUp <= 0 )
		{
			isUp = true;
			m_repeatUp = kRepeatFrame;
		}
	}
	if (Pad::isTrigger(PAD_INPUT_DOWN))
	{
		isDown = true;
		m_repeatDown = kFirstRepeatFrame;
	}
	else if (Pad::isPress(PAD_INPUT_DOWN))
	{
		m_repeatDown--;
		if (m_repeatDown <= 0)
		{
			isDown = true;
			m_repeatDown = kRepeatFrame;
		}
	}

	// �I�����ڂ�ς���
	// index��0����n�܂�ʂ��ԍ���z�肵�Ď���
	int next = getSelectIndex();
	if (isDown)
	{
		next++;
		if (next >= m_pItem.size())
		{
			// ���[�v���~�܂邩
			if (m_isLoop)	next = 0;
			else			next = getSelectIndex();
		}
	}
	else if (isUp)
	{
		next--;
		if (next < 0)
		{
			// ���[�v���~�܂邩
			if (m_isLoop)	next = static_cast<int>(m_pItem.size())-1;
			else			next = 0;
		}
	}

	if (next != getSelectIndex())
	{
		int prev = getSelectIndex();
		for (auto& item : m_pItem)
		{
			if (item->getIndex() == prev)
			{
				item->OnUnselect();
			}
			else if (item->getIndex() == next)
			{
				item->OnSelect();
			}
		}
	}

	if (Pad::isTrigger(PAD_INPUT_1))
	{
		return getSelectIndex();
	}
	return -1;
}

void DebugUi::draw()
{
	for (auto& item : m_pItem)
	{
		item->draw();
		if (item->isSelecting())
		{
			Vec2 pos = item->getPos();
			pos.x -= 18;
			// �킩��₷�����邽�߂ɓ�����
			int x = static_cast<int>(pos.x) + GetRand(4) - 2;
			int y = static_cast<int>(pos.y) + GetRand(4) - 2;
			DrawString(x,y,	kCursorString, 0xffff00);
		}
	}
}

void DebugUi::addItem(int index, const char* str)
{
	assert(index >= 0);
	Vec2 pos;
	pos.x = 18.0f + m_offsetX;	// �J�[�\���ƌ��Ԃ̕��E�ɕ\������
	pos.y = 0.0f + index * 16 + m_offsetY;

	std::shared_ptr<DebugUiItem>	pItem = std::make_shared<DebugUiItem>(index, pos, str);
	m_pItem.push_back(pItem);
}

void DebugUi::setSelect(int index)
{
	for (auto& item : m_pItem)
	{
		if (item->getIndex() == index)
		{
			item->OnSelect();
		}
		else
		{
			item->OnUnselect();
		}
	}
}

int DebugUi::getSelectIndex()
{
	for (auto& item : m_pItem)
	{
		if (item->isSelecting())	return item->getIndex();
	}
	return -1;
}
