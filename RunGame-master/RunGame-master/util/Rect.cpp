#include "Rect.h"
#include "DxLib.h"
#include <cassert>

Rect::Rect():
	m_left(0.0f),
	m_right(0.0f),
	m_top(0.0f),
	m_bottom(0.0f)
{
}

void Rect::setup(PosType type, Vec2 pos, float width, float height)
{
	float left = 0.0f;
	float top = 0.0f;
	float right = 0.0f;
	float bottom = 0.0f;

	switch (type)
	{
	case Rect::PosType::Center:
		left = pos.x - width / 2;
		top = pos.y - height / 2;
		right = pos.x + width / 2;
		bottom = pos.y + height / 2;
		break;
	case Rect::PosType::LT:
		left = pos.x;
		top = pos.y;
		right = left + width;
		bottom = top + height;
		break;
	case Rect::PosType::Underfoot:
		left = pos.x - width / 2;
		top = pos.y - height;
		right = pos.x + width / 2;
		bottom = pos.y;
		break;
	default:
		assert(false);
		break;
	}

	setup(left, top, right, bottom);
}

void Rect::setup(float left, float top, float right, float bottom)
{
	m_left = left;
	m_top = top;
	m_right = right;
	m_bottom = bottom;
}

Vec2 Rect::getPos(PosType type) const
{
	Vec2 result{0,0};
	switch (type)
	{
	case Rect::PosType::Center:
		result.x = (m_left + m_right) / 2;
		result.y = (m_top + m_bottom) / 2;
		break;
	case Rect::PosType::LT:
		result.x = m_left;
		result.y = m_top;
		break;
	case Rect::PosType::Underfoot:
		result.x = (m_left + m_right) / 2;
		result.y = m_bottom;
		break;
	default:
		assert(false);
		break;
	}
	return result;
}

float Rect::getWidth() const
{
	return (m_right - m_left);
}

float Rect::getHeight() const
{
	return (m_bottom - m_top);
}

void Rect::draw(unsigned int color, bool isFill) const
{
	DrawBox(static_cast<int>(m_left),
		static_cast<int>(m_top),
		static_cast<int>(m_right),
		static_cast<int>(m_bottom),
		color, isFill
	);
}

bool Rect::isCollision(Rect& rect) const
{
	float t0 = m_top;
	float l0 = m_left;
	float b0 = m_bottom;
	float r0 = m_right;

	float t1 = rect.getPos(Rect::PosType::LT).y;
	float l1 = rect.getPos(Rect::PosType::LT).x;
	float b1 = t1 + rect.getHeight();
	float r1 = l1 + rect.getWidth();

	// 当たらないパターン除外
	if (t0 > b1)	return false;
	if (l0 > r1)	return false;
	if (b0 < t1)	return false;
	if (r0 < l1)	return false;

	// 当たってる
	return true;
}

bool Rect::isCollision(Vec2 pos) const
{
	if (pos.y < m_top)		return false;
	if (pos.x < m_left)		return false;
	if (pos.y > m_bottom)	return false;
	if (pos.x > m_right)	return false;

	return true;
}
