#include "Player.h"
#include "DxLib.h"
#include "../Input.h"

namespace
{
	//�ړ����x
	constexpr float kBaseSpeed = 4.0f;
	constexpr float kDashSpeed = 16.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;

	//��ʃT�C�Y
	constexpr int kScreenWidth = 640;
	constexpr int kScreenHeight = 480;

}

Player::Player() :
	m_pos(15, 15),
	m_colPos(0,0),
	m_padStickX(0),
	m_padStickY(0),
	m_speed(4.0f),
	m_count(0),
	m_isDash(false),
	m_dashLog(false)
{

}

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Update(Input& input)
{
	//pad�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	bool isMove = false;	//�ړ����Ă��邩�ǂ���
	bool isLogMove = false;

	//pad�̃X�e�B�b�N�����擾
	GetJoypadAnalogInput(&m_padStickX, &m_padStickY, DX_INPUT_KEY_PAD1);

	//W�L�[
	//if ((pad & PAD_INPUT_8) != 0)
	if (input.IsPushed("UP"))
	{
		move.y -= m_speed;
		//move.y += m_speed * (m_padStickY * 0.00002);
		isMove = true;
	}

	//S�L�[
	//if ((pad & PAD_INPUT_5) != 0)
	if (input.IsPushed("DOWN"))
	{
		move.y += m_speed;
		//move.y += m_speed * (m_padStickY * 0.00002);
		isMove = true;
	}

	//A�L�[
	//if ((pad & PAD_INPUT_4) != 0)
	if (input.IsPushed("LEFT"))
	{
		move.x -= m_speed;
		//move.x += m_speed * (m_padStickX * 0.00002);
		isMove = true;
	}

	//D�L�[
	//if ((pad & PAD_INPUT_6) != 0)
	if (input.IsPushed("RIGHT"))
	{
		move.x += m_speed;
		//move.x += m_speed * (m_padStickX * 0.00002);
		isMove = true;
	}

	////PAD�ł̑���
	//m_pos.x += m_speed * (static_cast<float>(m_posX) / 700);
	//m_pos.y += m_speed * (static_cast<float>(m_posY) / 700);


	//�~�܂������A�{�Ƃ݂����ɓ���������
	if (!(isMove) && isLogMove)
	{

	}

	isLogMove = isMove;

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���

	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= m_speed;

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


	//�_�b�V��
	//�����Ă���ԃJ�E���g�𑝂₵������
	//�������u�Ԃ����_�b�V�����A�����Ă�����񉟂��ƃ_�b�V������悤��
	if(input.IsPushed("dash"))
	{
		m_count++;
	}
	else
	{
		m_count = 0;
	}
	//�������u�ԃ_�b�V��
	if (m_count == 1 && !m_isDash)
	{
		m_speed = kDashSpeed;
		m_isDash = true;
	}
	//�X�s�[�h�������Â��̃X�s�[�h��
	if (m_speed >= kBaseSpeed)
	{
		m_speed--;
		if (m_speed <= kBaseSpeed)
		{
			m_isDash = false;
		}
	}
	//�����蔻��̍X�V
	if (m_isDash)
	{
		m_colPos = {-30,-30};
	}
	else
	{
		m_colPos = m_pos;
	}

	m_colRect.SetCenter(m_colPos.x, m_colPos.y, kWidth * 2, kHeight * 2);

}

void Player::Draw()
{

	DrawBox(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);
	//DrawCircle(m_pos.x, m_pos.y, 10, GetColor(255, 255, 255), true);

#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), "X�����̓��� : %d", m_padStickX);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Y�����̓��� : %d", m_padStickY);
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "m_speed : %f", m_speed);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Xpos : %f", m_pos.x);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Ypos : %f", m_pos.y);

	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif
}
