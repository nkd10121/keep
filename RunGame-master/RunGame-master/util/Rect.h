#pragma once
#include "Vec2.h"
// ��`�N���X
class Rect
{
public:
	// ���W�̎��
	// ���S���W���擾������A������W���w�肵�ċ�`���������肷��
	enum class PosType
	{
		Center,		// ���S
		LT,			// ������W
		Underfoot	// ����(x�͒��S�Ay��bottom)
	};

public:
	Rect();
	virtual ~Rect() {}

	// ��`��񐶐�
	void setup(PosType type, Vec2 pos, float width, float height);	// ��ʒu+�T�C�Y�w��
	void setup(float left, float top, float right, float bottom);	// �㉺���E�̍��W�w��

	// ���W�擾
	Vec2 getPos(PosType type) const;
	Vec2 getCenter() const { return getPos(PosType::Center); }
	
	// �㉺���E
	float getLeft() const	{ return m_left; }
	float getRight() const	{ return m_right; }
	float getTop() const	{ return m_top; }
	float getBottom() const { return m_bottom; }
	// �㉺���E�ʒu���ڑ���
	void setLeft(float left) { m_left = left; }
	void setRight(float right) { m_right = right; }
	void setTop(float top) { m_top = top; }
	void setBottom(float bottom) { m_bottom = bottom; }

	// ���擾
	float getWidth() const;
	// �����擾
	float getHeight() const;

	// �`��
	void draw(unsigned int color, bool isFill) const;

	// ���̋�`�Ƃ̂����蔻��
	bool isCollision( Rect& rect ) const;
	// �_�Ƃ̂����蔻��(�_����`�Ɋ܂܂�Ă��邩�̔���)
	bool isCollision(Vec2 pos) const;

private:
	float m_left;
	float m_right;
	float m_top;
	float m_bottom;
};