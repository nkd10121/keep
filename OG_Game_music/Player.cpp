#include "Player.h"
#include "DxLib.h"

namespace
{
	//�ړ����x
	constexpr float kSpeed = 4.0f;
	constexpr float kDashSpeed = 12.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;

}

Player::Player():
	m_pos(15,15)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{

	//pad�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	bool isMove = false;	//�ړ����Ă��邩�ǂ���
	bool isLogMove = false;

	//W�L�[
	if ((pad & PAD_INPUT_8) != 0)
	{
		//�X�y�[�X�L�[���������Ƃ��_�b�V��
		if ((pad & PAD_INPUT_10) != 0)
		{
			move.y -= kDashSpeed;
		}
		else
		{
			move.y -= kSpeed;
		}
		//m_dir = kDirUp;
		isMove = true;
	}

	//S�L�[
	if ((pad & PAD_INPUT_5) != 0)
	{

		move.y += kSpeed;
		//m_dir = kDirDown;
		isMove = true;
	}

	//A�L�[
	if ((pad & PAD_INPUT_4) != 0)
	{
		//m_pos.x -= kSpeed;
		move.x -= kSpeed;
		//m_dir = kDirLeft;
		isMove = true;
	}

	//D�L�[
	if ((pad & PAD_INPUT_6) != 0)
	{
		//m_pos.x += kSpeed;
		move.x += kSpeed;
		//m_dir = kDirRight;
		isMove = true;
	}

	//�~�܂������A�{�Ƃ݂����ɓ���������
	if (!(isMove) && isLogMove)
	{

	}

	isLogMove = isMove;

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���

	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= kSpeed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

}

void Player::Draw()
{
	DrawBox(0, 0, 640, 640, GetColor(8, 4, 8), true);
	DrawBoxAA(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);
}
