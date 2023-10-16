#include "Slime.h"
#include "DxLib.h"

#include <cmath>

namespace
{
	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//�L�����N�^�[�̃A�j���[�V����
	//�摜�̍����̃~�X��0��2��1�̗���œ������Ȃ��Ƃ����Ȃ�(�ҋ@)
	constexpr int kUseAttackFrame[] = { 0,1,2,3,4,1 };
	constexpr int kUseIdleFrame[] = { 0,2,1,2 };
	constexpr int kUseMoveFrame[] = { 0,0,1,2,3 };

	//�A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;

	//�A�j���[�V����1�T�C�N���̃t���[����
	constexpr int kAttackAnimFrameCycle = _countof(kUseAttackFrame) * kAnimFrameNum;
	constexpr int kIdleAnimFrameCycle = _countof(kUseIdleFrame) * kAnimFrameNum;
	constexpr int kMoveAnimFrameCycle = _countof(kUseMoveFrame) * kAnimFrameNum;
}

Slime::Slime() :
	m_speed(2.0f),
	m_frameNum(0),
	m_randNum(0),
	m_handle(-1),
	m_handle0(-1),
	m_handle1(-1),
	m_walkAnimFrame(0),
	m_walkIdleFrame(0),
	m_isMove(false),
	m_srcX(0),
	m_srcY(0),
	m_isRight(false),
	m_pos(320, 240)
{

}

Slime::~Slime()
{
	DeleteGraph(m_handle0);
	DeleteGraph(m_handle1);
}

void Slime::Init()
{
	m_handle0 = LoadGraph("img/�X���C��.png");
	m_handle1 = LoadGraph("img/�X���C��2.png");
	int ran = GetRand(1);
	if (ran == 0)
	{
		m_handle = m_handle0;
	}
	else
	{
		m_handle = m_handle1;
	}
}

void Slime::Update()
{
	m_frameNum++;
	if (m_frameNum >= 60)
	{
		m_randNum = GetRand(7);
		m_frameNum = 0;
	}

	//pad�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�A�j���[�V�������ړ����x�𓯊�
	if (m_walkAnimFrame <= 24)
	{
		m_speed = 0.0f;
	}
	else
	{
		m_speed = 2.0f;
	}

	m_isMove = false;	//�ړ����Ă��邩�ǂ���

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	
	if(m_randNum == 4 || m_randNum == 5)
	//if ((pad & PAD_INPUT_LEFT) != 0)
	{
		move.x -= m_speed;

		m_isRight = false;
		m_isMove = true;
	}

	if (m_randNum == 6 || m_randNum == 7)
	//if ((pad & PAD_INPUT_RIGHT) != 0)
	{
		move.x += m_speed;

		m_isRight = true;
		m_isMove = true;
	}

	//���������̎��͈ړ����Ȃ��悤��
	if ((pad & PAD_INPUT_LEFT) != 0 && (pad & PAD_INPUT_RIGHT) != 0)
	{
		m_isMove = false;
	}

	////�x�N�g���̐��K��
	//move.normalize();

	////�x�N�g���̒�����kspeed�ɂ���
	//move *= m_speed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

	if (m_isMove)
	{
		//�ҋ@�̃A�j���[�V�������͂��߂���ɂ���
		m_walkIdleFrame = 0;

		//�����A�j���[�V����
		m_walkAnimFrame++;
		if (m_walkAnimFrame >= kMoveAnimFrameCycle)
		{
			m_walkAnimFrame = 0;
		}
	}
	else
	{
		//�ړ��̃A�j���[�V�������͂��߂���ɂ���
		m_walkAnimFrame = 0;

		//�ҋ@�A�j���[�V����
		m_walkIdleFrame++;
		if (m_walkIdleFrame >= kIdleAnimFrameCycle)
		{
			m_walkIdleFrame = 0;
		}
	}
}

void Slime::Draw()
{
	int animFrame;

	//�����Ă�����ړ��A�j���[�V�������A
	//�~�܂��Ă�����ҋ@�A�j���[�V�����𓮂���
	if (m_isMove)
	{
		animFrame = m_walkAnimFrame / kAnimFrameNum;

		m_srcX = kWidth * kUseMoveFrame[animFrame];
		m_srcY = 64;
	}
	else
	{
		animFrame = m_walkIdleFrame / kAnimFrameNum;

		m_srcX = kWidth * kUseIdleFrame[animFrame];
		m_srcY = 128;
	}

	//�E�����ƍ�����
	if (m_isRight)
	{
		DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
			m_srcX, m_srcY, kWidth, kHeight,
			m_handle, true, true);
	}
	else
	{
		DrawRectGraph(static_cast<int>(m_pos.x), static_cast<int>(m_pos.y),
			m_srcX, m_srcY, kWidth, kHeight,
			m_handle, true, false);
	}


	DrawFormatString(8, 24, GetColor(255, 255, 255),
		"�v���C���[�̑��x(%f)", m_speed);	
	DrawFormatString(8, 40, GetColor(255, 255, 255),
		"�t���[����(%d)", m_frameNum);
	DrawFormatString(8, 56, GetColor(255, 255, 255),
		"����(%d)", m_randNum);
}
