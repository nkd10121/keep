#include "Player.h"
#include "DxLib.h"

namespace
{
	//�ړ����x
	constexpr float kSpeed = 5.0f;
	constexpr float kDashSpeed = 12.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;

	//��ʃT�C�Y
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;

}

Player::Player():
	m_pos(15,15),
	posX(0),
	posY(0),
	speed(5.0f),
	count(0),
	dashFlag(false),
	dashLog(false)
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

	////W�L�[
	////if ((pad & PAD_INPUT_8) != 0)
	//if ((pad & PAD_INPUT_UP) != 0)
	//{
	//	//�X�y�[�X�L�[���������Ƃ��_�b�V��
	//	if ((pad & PAD_INPUT_10) != 0)
	//	{
	//		move.y -= kDashSpeed;
	//	}
	//	else
	//	{
	//		move.y -= kSpeed;
	//	}
	//	//m_dir = kDirUp;
	//	isMove = true;
	//}

	////S�L�[
	////if ((pad & PAD_INPUT_5) != 0)
	//if ((pad & PAD_INPUT_DOWN) != 0)
	//{

	//	move.y += kSpeed;
	//	//m_dir = kDirDown;
	//	isMove = true;
	//}

	////A�L�[
	////if ((pad & PAD_INPUT_4) != 0)
	//if ((pad & PAD_INPUT_LEFT) != 0)
	//{
	//	//m_pos.x -= kSpeed;
	//	move.x -= kSpeed;
	//	//m_dir = kDirLeft;
	//	isMove = true;
	//}

	////D�L�[
	////if ((pad & PAD_INPUT_6) != 0)
	//if ((pad & PAD_INPUT_RIGHT) != 0)
	//{
	//	//m_pos.x += kSpeed;
	//	move.x += kSpeed;
	//	//m_dir = kDirRight;
	//	isMove = true;
	//}

	//PAD�ł̑���
	GetJoypadAnalogInput(&posX, &posY, DX_INPUT_KEY_PAD1);
	m_pos.x += speed * (static_cast<float>(posX) / 700);
	m_pos.y += speed * (static_cast<float>(posY) / 700);

	//�_�b�V��
	//�����Ă���ԃJ�E���g�𑝂₵������
	//�������u�Ԃ����_�b�V�����A�����Ă�����񉟂��ƃ_�b�V������悤��
	if ((pad & PAD_INPUT_1) != 0)
	{
		count++;
	}
	else
	{
		count = 0;
	}
	//�������u�ԃ_�b�V��
	if (count == 1 && !dashFlag)
	{
		speed = 20.0f;
		dashFlag = true;
	}
	//�X�s�[�h�������Â��̃X�s�[�h��
	if (speed >= kSpeed)
	{
		speed--;
		if (speed == kSpeed)
		{
			dashFlag = false;
		}
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




	//��ʊO�ɏo�Ȃ��悤��
	if (m_pos.x + kWidth >= kScreenWidth)
	{
		m_pos.x = 640 - kWidth;
	}
	if (m_pos.x - kWidth <= 0)
	{
		m_pos.x = 0 + kWidth;
	}
	if (m_pos.y - kHeight <= 0)
	{
		m_pos.y = 0 + kHeight;
	}
	if (m_pos.y + kHeight >= kScreenHeight)
	{
		m_pos.y = 480 - kHeight;
	}

	//�����蔻��̍X�V
	m_colRect.SetCenter(m_pos.x, m_pos.y, kWidth * 2, kHeight * 2);

}

void Player::Draw()
{

	DrawBox(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);
	//DrawCircle(m_pos.x, m_pos.y, 10, GetColor(255, 255, 255), true);

#ifdef _DEBUG
	DrawFormatString(0,0,GetColor(255,255,255),"X�����̓��� : %d",posX);
	DrawFormatString(0,16,GetColor(255,255,255),"Y�����̓��� : %d",posY);
	DrawFormatString(0,32,GetColor(255,255,255),"Xpos : %f",m_pos.x);
	DrawFormatString(0,48,GetColor(255,255,255),"Ypos : %f",m_pos.y);

	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}
