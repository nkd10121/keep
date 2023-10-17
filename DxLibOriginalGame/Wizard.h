#pragma once
#include "Vec2.h"
//#include "Rect.h"

class Wizard
{
public:
	Wizard();
	~Wizard();

	void Init();
	void Update();
	void Draw();

private:
	//�ړ����x
	float m_speed;

	//�t���[����
	int m_frameNum;

	//����������悤
	int m_randNum;

	//�X���C���̃n���h��
	int m_handle;
	int m_handle0;
	int m_handle1;

	//�����A�j���[�V����
	int m_walkAnimFrame;

	//�ҋ@�A�j���[�V����
	int m_walkIdleFrame;

	//�ړ����Ă��邩�ǂ���
	bool m_isMove;

	//�A�j���[�V�����̐؂�ւ��p
	int m_srcX;
	int m_srcY;

	bool m_isRight;

	//�\���ʒu
	Vec2 m_pos;
};
