#include "Player.h"
#include "DxLib.h"
#include "Input.h"
#include "Application.h"

namespace
{
	//�ړ����x
	constexpr float kBaseSpeed = 3.0f;
	constexpr float kDashSpeed = 16.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 8;
	constexpr int kHeight = 8;
}

Player::Player() :
	m_pos(15, 15),
	m_colPos(0,0),
	m_padStickX(0),
	m_padStickY(0),
	m_speed(kBaseSpeed),
	m_dashCount(0),
	m_isDash(false),
	m_dashLog(false),
	m_knockBackSpeed(0),
	m_damageDrawFrame(0),
	m_playerInvincibleTime(0)
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	ScreenSizeW = size.w;
	ScreenSizeH = size.h;
}

Player::~Player()
{

}

void Player::Init()
{

}

void Player::Update(Input& input)
{
	if (m_damageDrawFrame >= 0)
	{
		m_damageDrawFrame--;
	}
	else
	{
		m_damageDrawFrame = 0;
	}

	if (m_playerInvincibleTime >= 0)
	{
		m_playerInvincibleTime--;
	}
	else
	{
		m_playerInvincibleTime = 0;
	}


	//pad�̏\���L�[���g�p���ăv���C���[���ړ�������
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	//�ړ��ʂ����悤�ɂ���
	Vec2 move{ 0.0f,0.0f };

	//pad�̃X�e�B�b�N�����擾
	GetJoypadAnalogInput(&m_padStickX, &m_padStickY, DX_INPUT_KEY_PAD1);

#ifdef false
	//W�L�[
	//if ((pad & PAD_INPUT_8) != 0)
	if (input.IsPushed("UP"))
	{
		move.y = m_padStickY;
		//move.y += m_speed * (m_padStickY * 0.00002);
	}

	//S�L�[
	//if ((pad & PAD_INPUT_5) != 0)
	if (input.IsPushed("DOWN"))
	{
		move.y = m_padStickY;
		//move.y += m_speed * (m_padStickY * 0.00002);
	}

	//A�L�[
	//if ((pad & PAD_INPUT_4) != 0)
	if (input.IsPushed("LEFT"))
	{
		move.x -= m_speed;
		//move.x += m_speed * (m_padStickX * 0.00002);
	}

	//D�L�[
	//if ((pad & PAD_INPUT_6) != 0)
	if (input.IsPushed("RIGHT"))
	{
		move.x += m_speed;
		//move.x += m_speed * (m_padStickX * 0.00002);
	}
#endif

	////PAD�ł̑���
	m_pos.x += m_speed * (static_cast<float>(m_padStickX) / 700) - m_knockBackSpeed;
	m_pos.y += m_speed * (static_cast<float>(m_padStickY) / 700);

	//�m�b�N�o�b�N�����Ƃ�
	//�m�b�N�o�b�N�̃X�s�[�h�����񂾂񌸂炷
	if (m_knockBackSpeed != 0)
	{
		m_knockBackSpeed--;
	}

	//�΂߈ړ��̏ꍇ�����������ňړ�����悤�ɂ���
	//�x�N�g���̐��K��
	move.normalize();

	//�x�N�g���̒�����kspeed�ɂ���
	move *= kBaseSpeed;

	//���W�ƃx�N�g���̑����Z
	m_pos += move;

	//��ʊO�ɏo�Ȃ��悤��
	if (m_pos.x + kWidth >= ScreenSizeW)
	{
		m_pos.x = ScreenSizeW - kWidth;
	}
	if (m_pos.x - kWidth <= 0)
	{
		m_pos.x = 0 + kWidth;
	}
	if (m_pos.y - kHeight <= 0)
	{
		m_pos.y = 0 + kHeight;
	}
	if (m_pos.y + kHeight >= ScreenSizeH)
	{
		m_pos.y = ScreenSizeH - kHeight;
	}


	//�_�b�V��
	//�����Ă���ԃJ�E���g�𑝂₵������
	//�������u�Ԃ����_�b�V�����A�����Ă�����񉟂��ƃ_�b�V������悤��
	if(input.IsPushed("dash"))
	{
		m_dashCount++;
	}
	else
	{
		m_dashCount = 0;
	}
	//�������u�ԃ_�b�V��
	if (m_dashCount == 1 && !m_isDash)
	{
		m_speed = kDashSpeed;
		m_isDash = true;
	}
	//�X�s�[�h�����������̃X�s�[�h��
	if (m_speed >= kBaseSpeed)
	{
		m_speed--;
		if (m_speed <= kBaseSpeed)
		{
			m_isDash = false;
		}
	}


	//�����蔻��̍X�V
	//�_�b�V�����Ă���Ƃ����_���[�W���󂯂���̖��G���Ԃ̊Ԃ͓����蔻����Ȃ���
	if (m_isDash  || m_playerInvincibleTime != 0)
	{
		m_colPos = {-30,-30};
	}
	//����ȊO�̎��͓����蔻�������
	else
	{
		m_colPos = m_pos;
	}

	//�����蔻��̐ݒ�
	m_colRect.SetCenter(m_colPos.x, m_colPos.y, kWidth * 2, kHeight * 2);
}

void Player::Draw()
{
#ifdef _DEBUG
	DrawFormatString(0, 0, GetColor(255, 255, 255), "X�����̓��� : %d", m_padStickX);
	DrawFormatString(0, 16, GetColor(255, 255, 255), "Y�����̓��� : %d", m_padStickY);

	//DrawFormatString(0, 0, GetColor(255, 255, 255), "m_speed : %f", m_speed);
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Xpos : %f", m_pos.x);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Ypos : %f", m_pos.y);

	m_colRect.Draw(GetColor(255, 0, 0), false);
#endif

	//�v���C���[�̘g
	DrawBox(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), false);

	//�_���[�W���󂯂��Ƃ��_�ł���悤��
	if (m_damageDrawFrame % 6 >= 4)
	{
		DrawBox(m_pos.x - kWidth, (m_pos.y - kHeight) + (m_playerInvincibleTime / 11.25), m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 128, 0), true);
		return;
	}

	//�v���C���[�̕\��
	DrawBox(m_pos.x - kWidth, (m_pos.y - kHeight) + (m_playerInvincibleTime / 11.25), m_pos.x + kWidth, m_pos.y + kHeight, GetColor(255, 255, 0), true);

}

void Player::HitEnemy()
{
	int count = 180;
	count--;

	//�m�b�N�o�b�N�X�s�[�h��^����
	m_knockBackSpeed = 20;

	m_damageDrawFrame = 180;
	m_playerInvincibleTime = 180;
}
