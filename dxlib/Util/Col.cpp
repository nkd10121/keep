#include "col.h"
#include "DxLib.h"
#include <cassert>

Col::Col() :
	m_left(0.0f),
	m_top(0.0f),
	m_right(0.0f),
	m_bottom(0.0f),
	m_centerX(0.0f),
	m_centerY(0.0f),
	m_rad(0)
{

}

Col::~Col()
{
}

void Col::DrawColBox(unsigned int color)
{
	//DrawBoxAA(m_left,m_top,m_right,m_bottom,Color,isFill);
	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top),
		static_cast<int>(m_right), static_cast<int>(m_bottom), color,false);
}

void Col::DrawColCircle(unsigned int color)
{
	DrawCircle(static_cast<int>(m_centerX), static_cast<int>(m_centerY), m_rad, color, false);
}

void Col::SetBox(float left, float top, float right, float bottom)
{
	m_left = left;
	m_top = top;
	m_right = right;
	m_bottom = bottom;
}

void Col::SetLT(float left, float top, float width, float height)
{
	m_left = left;			//�����X���W
	m_top = top;			//�����Y���W
	m_right = left + width;	//�E����X���W
	m_bottom = top + height;//�E����Y���W
}

void Col::SetCenter(float x, float y, float width, float height)
{
	m_left = x - width / 2;		//�����X���W
	m_top = y - height / 2;		//�����Y���W
	m_right = x + width / 2;	//�E����X���W
	m_bottom = y + height / 2;	//�E����Y���W
}

void Col::SetCircle(float x, float y, int rad)
{
	m_centerX = x;
	m_centerY = y;
	m_rad = rad;

	m_left = m_centerX - rad;
	m_top = m_centerY - rad;
	m_right = m_centerX + rad;
	m_bottom = m_centerY + rad;
}

float Col::GetWidth() const
{
	assert(m_right >= m_left);	//���E�̍��W�̓���ւ��`�F�b�N

	return m_right - m_left;
}

float Col::GetHeight() const
{
	assert(m_bottom >= m_top);	//�㉺�̍��W�̓���ւ��`�F�b�N

	return m_bottom - m_top;
}

bool Col::IsCollision(const Col& col)
{
	//��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
	if (m_left > col.m_right)	return false;
	if (m_top > col.m_bottom)	return false;
	if (m_right < col.m_left)	return false;
	if (m_bottom < col.m_top)	return false;

	//������Ȃ��p�^�[���ȊO�͓������Ă���
	return true;
}

bool Col::IsCollisionCircle(const Col& col)
{
	if (IsCollision(col))
	{
		//col.�@�����Ă���̂�Circle�̏��
		if (col.m_centerX > m_left && col.m_centerX < m_right &&
			col.m_centerY > m_right - col.m_rad && col.m_centerY < m_left + col.m_rad)
		{
			return true;
		}

		if (col.m_centerX > m_right - col.m_rad && col.m_centerX < m_left + col.m_rad &&
			col.m_centerY > m_top && col.m_centerY < m_bottom)
		{
			return true;
		}

		float X1 = (m_left - col.m_centerX) * (m_left - col.m_centerX);
		float X2 = (m_right - col.m_centerX) * (m_right - col.m_centerX);
		float Y1 = (m_top - col.m_centerY) * (m_top - col.m_centerY);
		float Y2 = (m_bottom - col.m_centerY) * (m_bottom - col.m_centerY);

		//���a�̓��
		float squaredRad = static_cast<float>(col.m_rad) * static_cast<float>(col.m_rad);

		if ((X1 + Y1) < squaredRad)
		{
			return true;
		}

		if ((X2 + Y1) < squaredRad)
		{
			return true;
		}

		if ((X2 + Y2) < squaredRad)
		{
			return true;
		}

		if ((X1 + Y2) < squaredRad)
		{
			return true;
		}
	}

	//�ǂ��̏����ɂ�����������Ȃ������ꍇ�������Ă��Ȃ�
	return false;
}
