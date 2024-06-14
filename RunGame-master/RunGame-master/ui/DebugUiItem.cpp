#include "DebugUiItem.h"
#include "DxLib.h"

DebugUiItem::DebugUiItem(int index, Vec2 pos, const char* str):
	m_index(index),
	m_pos(pos),
	m_str(str),
	m_isSelect(false)
{
}

DebugUiItem::~DebugUiItem()
{
}

void DebugUiItem::update()
{
}

void DebugUiItem::draw()
{
	int x = static_cast<int>(m_pos.x);
	int y = static_cast<int>(m_pos.y);
	unsigned int color = 0xffffff;
	if(m_isSelect)	color = 0xffff00;

	DrawString(x, y, m_str, color);
}

void DebugUiItem::OnSelect()
{
	m_isSelect = true;
}

void DebugUiItem::OnUnselect()
{
	m_isSelect = false;
}
