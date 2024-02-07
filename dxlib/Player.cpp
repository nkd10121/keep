#include "Player.h"
#include "DxLib.h"
#include <cassert>
#include "Util/Input.h"
#include "Util/Application.h"
#include "Efect/AfterImagePlayer.h"
#include "Efect/Efects.h"
#include "Efect/DashEfect.h"
#include "Efect/HitEfect.h"

namespace
{
	//�ړ����x
	constexpr float kBaseSpeed = 6.0f;
	constexpr float kDashSpeed = kBaseSpeed * 4;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 14;
	constexpr int kHeight = 14;

	//�c���̍ő吔
	constexpr int kAfterImageNumMax = 64;

	//�G�t�F�N�g�̐�
	constexpr int kEfectMax = 32;
}

Player::Player() :
	m_isInStage(true),
	m_pos(15, 15),
	m_colPos(0,0),
	m_padStickX(0),
	m_padStickY(0),
	powerX(0),
	powerY(0),
	angle(0),
	m_speed(kBaseSpeed),
	m_dashCount(0),
	m_isDash(false),
	m_hitCount(0),
	m_knockBackSpeed(0),
	m_damageDrawFrame(0),
	m_playerInvincibleTime(0)
{
	Application& app = Application::GetInstance();
	const auto& size = app.GetWindowSize();

	ScreenSizeW = size.w;
	ScreenSizeH = size.h;

	playerHandle[0] = LoadGraph("data/player/player0.png");
	playerHandle[1] = LoadGraph("data/player/player1.png");
	playerHandle[2] = LoadGraph("data/player/player2.png");
	playerHandle[3] = LoadGraph("data/player/player3.png");

	for (int i = 0; i < 4; i++)
	{
		assert(playerHandle[i] != -1);
	}

	afterImage.resize(kAfterImageNumMax);
	efects.resize(kEfectMax);
}

Player::~Player()
{
	for (int i = 0; i < 4; i++)
	{
		DeleteGraph(playerHandle[i]);
	}
}

void Player::Init(bool isInStage)
{
	m_isInStage = isInStage;
	if (m_isInStage)
	{
		m_pos.x = 100;
		m_pos.y = 360;
	}
	else
	{
		m_pos.x = Game::kScreenWidth / 4 * 3;
		m_pos.y = Game::kScreenHeight / 2;
	}
}

void Player::Update(Input& input)
{
	frame++;
	m_posLog = m_pos;

	//m_damageDrawFrame��0���傫���Ƃ��ɂ��񂾂񏬂�������
	//�ꉞ����ȊO�̎���0��������悤�ɂ���
	if (m_damageDrawFrame >= 0)
	{
		m_damageDrawFrame--;
	}
	else
	{
		m_damageDrawFrame = 0;
	}

	if (m_playerInvincibleTime > 0)
	{
		m_playerInvincibleTime--;
	}
	else
	{
		m_playerInvincibleTime = 0;
	}

	//pad�̃X�e�B�b�N���(�e���L�[�̖��L�[)���擾
	GetJoypadAnalogInput(&m_padStickX, &m_padStickY, DX_INPUT_KEY_PAD1);


	if (m_padStickX == 0 && m_padStickY == 0)
	{
		if (input.IsPushed("UP"))
		{
			m_padStickY = -1000;
		}
		if (input.IsPushed("DOWN"))
		{
			m_padStickY = 1000;
		}
		if (input.IsPushed("LEFT"))
		{
			m_padStickX = -1000;
		}
		if (input.IsPushed("RIGHT"))
		{
			m_padStickX = 1000;
		}
	}

	powerX = static_cast<float>(m_padStickX) / 1000;
	powerY = static_cast<float>(m_padStickY) / 1000;


	//�v���C���[�̊p�x�𒲐�
	if (m_padStickX != 0 || m_padStickY != 0)
	{
		angle = atan2(powerX, -powerY);
	}
	else
	{
		//����������Ă��Ȃ��Ƃ�������߂�
		angle = 0.0;
	}

	//PAD�ł̑���
	m_pos.x += m_speed * powerX - m_knockBackSpeed;
	m_pos.y += m_speed * powerY;

	//�m�b�N�o�b�N�����Ƃ�
	//�m�b�N�o�b�N�̃X�s�[�h�����񂾂񌸂炷
	if (m_knockBackSpeed != 0)
	{
		m_knockBackSpeed--;
	}

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
		for (int i = 0; i < GetRand(4) + 20; i++)
		{
			CreateAfterImage(m_pos, (m_pos - m_posLog), GetRand(1) + 3, true);
		}

		CreateDashEfect(m_pos);
		
		m_speed = kDashSpeed;
		m_isDash = true;
	}


	//�X�s�[�h�����������̃X�s�[�h��
	if (m_speed >= kBaseSpeed)
	{
		m_speed--;
		if (m_speed < kBaseSpeed)
		{
			m_isDash = false;
		}
	}

	if (m_pos - m_posLog != Vec2{} && !m_isDash)
	{
		if (frame % 2 == 0)
		{
			CreateAfterImage(m_pos, (m_pos - m_posLog), 4, false);
		}
	}

	m_colPos = m_pos;
	//�����蔻��̍X�V
	//�_�b�V�����Ă���Ƃ����_���[�W���󂯂���̖��G���Ԃ̊Ԃ͓����蔻����Ȃ���
	if (m_isDash  || m_playerInvincibleTime != 0)
	{
		if (m_isInStage)
		{
			m_colPos = { -150,-150 };
		}
	}

	//�����蔻��̐ݒ�
	m_colRect.SetCenter(m_colPos.x, m_colPos.y, kWidth * 2, kHeight * 2);

	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			afterImage[i]->Update();

			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!afterImage[i]->isExist())
			{
				//���������������
				delete afterImage[i];
				afterImage[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
			}
		}
	}

	for (int i = 0; i < efects.size(); i++)
	{
		if (efects[i])
		{
			efects[i]->Update();

			//�g�p�ς݂̓G�L�����N�^���폜����K�v������
			if (!efects[i]->isExist())
			{
				//���������������
				delete efects[i];
				efects[i] = nullptr;	//�g���Ă��Ȃ��Ƃ킩��悤��
			}
		}
	}
}

void Player::Draw()
{
	//�c���̕`��
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			afterImage[i]->Draw();
		}
	}

	for (int i = 0; i < efects.size(); i++)
	{
		if (efects[i])
		{
			efects[i]->Draw();
		}
	}

	//�_���[�W���󂯂��Ƃ��_�ł���悤��
	if (m_damageDrawFrame % 6 != 4)
	{
		//�v���C���[�̕`��
		DrawRotaGraph(m_pos.x, m_pos.y, 1.0, angle, playerHandle[m_hitCount], true);
	}
	//�v���C���[�̘g
	//DrawBox(m_pos.x - kWidth, m_pos.y - kHeight, m_pos.x + kWidth, m_pos.y + kHeight, GetColor(24, 24, 24), false);

#ifdef _DEBUG
	//DrawFormatString(0, 0, GetColor(255, 255, 255), "X�����̓��� : %d", m_padStickX);
	//DrawFormatString(0, 16, GetColor(255, 255, 255), "Y�����̓��� : %d", m_padStickY);

	////DrawFormatString(0, 0, GetColor(255, 255, 255), "m_speed : %f", m_speed);
	//DrawFormatString(0, 32, GetColor(255, 255, 255), "Xpos : %f", m_pos.x);
	//DrawFormatString(0, 48, GetColor(255, 255, 255), "Ypos : %f", m_pos.y);

	//DrawFormatString(0, 64, GetColor(255, 255, 255), "hitCount : %d", m_hitCount);

	m_colRect.DrawColBox(0x000000);
#endif
}

void Player::HitEnemy()
{
	//�m�b�N�o�b�N�X�s�[�h��^����
	m_knockBackSpeed = 20;

	m_damageDrawFrame = 180;
	m_playerInvincibleTime = 180;

	if (m_hitCount < 3)
	{
		CreateHitEfect(m_pos);
	}
	else
	{
		CreateHitEfect(m_pos,true);
	}
	StartJoypadVibration(DX_INPUT_PAD1, 1000, 200,1);

	if (m_isInStage)
	{
		m_hitCount++;
	}
}

void Player::CreateAfterImage(Vec2 pos, Vec2 vec, int size, bool isDash)
{
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (!afterImage[i])
		{
			afterImage[i] = new AfterImagePlayer;
			afterImage[i]->Init(pos, vec,size,isDash);
			return;
		}
	}
}

void Player::CreateDashEfect(Vec2 pos, bool isLastHit)
{
	for (int i = 0; i < efects.size(); i++)
	{
		if (!efects[i])
		{
			efects[i] = new DashEfect;
			efects[i]->Init(pos, isLastHit);
			return;
		}
	}
}

void Player::CreateHitEfect(Vec2 pos, bool isLastHit)
{
	for (int i = 0; i < efects.size(); i++)
	{
		if (!efects[i])
		{
			efects[i] = new HitEfect;
			efects[i]->Init(pos, isLastHit);
			return;
		}
	}
}
