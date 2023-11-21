#pragma once
#include "Vec2.h"
#include "Rect.h"

class Input;

class Player
{
public:
	Player();
	~Player();
	
	void Init();
	void Update(Input& input);
	void Draw();

	//�v���C���[�̓����蔻����擾����
	Rect GetColRect() const { return m_colRect; }

	int SetKnockBackSpeed(int speed) { return m_knockBackSpeed = speed; }

	float GetPlayerPosX()const;

	//�v���C���[���G�ɓ����������̏���
	void HitEnemy();

private:
	Vec2 m_pos;
	Vec2 m_colPos;

	int ScreenSizeW;
	int ScreenSizeH;

	//�����蔻��p�̋�`
	Rect m_colRect;

	//Pad�̃X�e�B�b�N���X���������Ƒ傫��������悤
	int m_padStickX;
	int m_padStickY;

	//�v���C���[�̃X�s�[�h
	float m_speed;

	//�_�b�V�����������Ƃ��̃J�E���g
	int m_dashCount;
	//�_�b�V�����Ă��邩
	bool m_isDash;
	//���������ǂ������肷��悤
	bool m_dashLog;

	//�G�ɓ���������
	int hitCount;

	//�m�b�N�o�b�N�������̃X�s�[�h
	int m_knockBackSpeed;

	//�G�Ƀq�b�g�������v���C���[���_�ł���悤��
	int m_damageDrawFrame;

	//�G�Ƀq�b�g�������ɖ��G����
	int m_playerInvincibleTime;
};

