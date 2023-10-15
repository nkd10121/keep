#pragma once
#include "Vec2.h"

class Slime
{
public:
	//�����Ă������
	enum Dir
	{
		kDirLeft,	//��	= 0
		kDirRight,	//�E	= 1
	};

public:
	Slime();
	~Slime();

	void Init();
	void Update();
	void Draw();

	//�����o�[�ϐ��ɃA�N�Z�X����
	void SetHandle(int handle) { m_handle = handle; }

private:
	int m_handle;	//�O���t�B�b�N�̃n���h��

	//�\���ʒu
	Vec2 m_pos;

	//�����Ă������
	Dir m_dir;

	//�����A�j���[�V����
	int m_walkAnimFrame;
};

