//#include "Rect.h"
//#include "DxLib.h"
//#include <cassert>
//
//Rect::Rect():
//	m_left(0.0f),
//	m_top(0.0f),
//	m_right(0.0f),
//	m_bottom(0.0f),
//	m_center(0.0f,0.0f),
//	m_rad(0)
//{
//
//}
//
//Rect::~Rect()
//{
//}
//
//void Rect::Draw(unsigned int color, bool isFill)
//{
//	//DrawBoxAA(m_left,m_top,m_right,m_bottom,color,isFill);
//	DrawBox(static_cast<int>(m_left), static_cast<int>(m_top),
//		static_cast<int>(m_right), static_cast<int>(m_bottom),color,isFill);
//}
//
//void Rect::DrawRectCircle(unsigned int color, bool isFill)
//{
//	DrawCircle(m_center.x, m_center.y, m_rad, color, isFill);
//}
//
//void Rect::SetBox(float left, float top, float right, float bottom)
//{
//	m_left = left;
//	m_top = top;
//	m_right = right;
//	m_bottom = bottom;
//}
//
//void Rect::SetLT(float left, float top, float width, float height)
//{
//	m_left = left;			//�����X���W
//	m_top = top;			//�����Y���W
//	m_right = left + width;	//�E����X���W
//	m_bottom = top + height;//�E����Y���W
//}
//
//void Rect::SetCenter(float x, float y, float width, float height)
//{
//	m_left = x - width / 2;		//�����X���W
//	m_top = y - height / 2;		//�����Y���W
//	m_right = x + width / 2;	//�E����X���W
//	m_bottom = y + height / 2;	//�E����Y���W
//}
//
//void Rect::SetCircle(Vec2 center, int rad)
//{
//	m_center = center;
//	m_rad = rad;
//
//	m_left = center.x - rad;
//	m_top = center.y - rad;
//	m_right = center.x + rad;
//	m_bottom = center.y + rad;
//}
//
//float Rect::GetWidth() const
//{
//	assert(m_right >= m_left);	//���E�̍��W�̓���ւ��`�F�b�N
//
//	return m_right - m_left;
//}
//
//float Rect::GetHeight() const
//{
//	assert(m_bottom >= m_top);	//�㉺�̍��W�̓���ւ��`�F�b�N
//
//	return m_bottom - m_top;
//}
//
//Vec2 Rect::GetCenter() const
//{
//	//���S���W
//	float x = 0.0f;
//	float y = 0.0f;
//
//	x = (m_right + m_left) / 2;
//	y = (m_top + m_bottom) / 2;
//
//	return Vec2{ x,y };
//}
//
//bool Rect::IsCollision(const Rect& rect)
//{
//	//��΂ɓ�����Ȃ��p�^�[�����͂����Ă���
//	if (m_left > rect.m_right)	return false;
//	if (m_top > rect.m_bottom)	return false;
//	if (m_right < rect.m_left)	return false;
//	if (m_bottom < rect.m_top)	return false;
//
//	//������Ȃ��p�^�[���ȊO�͓������Ă���
//	return true;
//}
//
//bool Rect::IsCollisionCircle(const Rect& rect)
//{
//	//if (IsCollision(rect))
//	{
//		//rect.�@�����Ă���̂�Circle�̏��
//		if (rect.m_center.x > m_left && rect.m_center.x < m_right &&
//			rect.m_center.y > m_right - rect.m_rad && rect.m_center.y < m_left + rect.m_rad)
//		{
//			printfDx("e");
//			return true;
//		}
//
//		if (rect.m_center.x > m_right - rect.m_rad && rect.m_center.x < m_left + rect.m_rad &&
//			rect.m_center.y > m_top && rect.m_center.y < m_bottom)
//		{
//			printfDx("f");
//			return true;
//		}
//
//		float X1 = (m_left - rect.m_center.x) * (m_left - rect.m_center.x);
//		float X2 = (m_right - rect.m_center.x) * (m_right - rect.m_center.x);
//		float Y1 = (m_top - rect.m_center.y) * (m_top - rect.m_center.y);
//		float Y2 = (m_bottom - rect.m_center.y) * (m_bottom - rect.m_center.y);
//
//		//���a�̓��
//		float squaredRad = rect.m_rad * rect.m_rad;
//
//		if ((X1 + Y1) < squaredRad)
//		{
//			printfDx("a");
//			return true;
//		}
//
//		if ((X2 + Y1) < squaredRad)
//		{
//			printfDx("b");
//			return true;
//		}
//
//		if ((X2 + Y2) < squaredRad)
//		{
//			printfDx("c");
//			return true;
//		}
//
//		if ((X1 + Y2) < squaredRad)
//		{
//			printfDx("d");
//			return true;
//		}
//	}
//
//	//�ǂ��̏����ɂ�����������Ȃ������ꍇ�������Ă��Ȃ�
//	return false;
//}
