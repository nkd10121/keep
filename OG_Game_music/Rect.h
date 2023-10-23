#pragma once
#include "Vec2.h"
//��`�̍��W���Ǘ�����N���X
class Rect
{
public:
	Rect();
	virtual ~Rect();

	//�`��
	void Draw(unsigned int color, bool isFill);

	//������W�ƕ��������w��
	void SetLT(float left, float top, float width, float height);

	//���S���W�ƕ��������w��
	void SetCenter(float x, float y, float width, float height);


	//�Q�[���ɂ���Ă͒��S���W�Ŏw�肵���葫���̍��W�Ŏw�肷��
	//set�֐����������ق����֗���������Ȃ�

	//�K�v�ȏ����擾����
	float GetWidth() const;		//��
	float GetHeight() const;	//����
	Vec2 GetCenter() const;		//���S���W

	//��`���m�̓����蔻��
	bool IsCollision(const Rect& rect);

private:
	float m_left;
	float m_top;
	float m_right;
	float m_bottom;

};

