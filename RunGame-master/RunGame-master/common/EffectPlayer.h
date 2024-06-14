#pragma once
#include "Vec2.h"

// ���o�p�v���C���[�\���N���X
// ��{�I�ɂ܂������O�ɐi�ނ��Ƃ�z�肵�Ď���
class EffectPlayer
{
public:
	EffectPlayer();
	virtual ~EffectPlayer();

	void setupIcon(Vec2 pos);	// �ړ����Ȃ��A�C�R���Ƃ��ăZ�b�g�A�b�v
								// �ʒu�ƃx�N�g��(�ړ����Ȃ�)�ʂ����ݒ肵�ĂȂ�
	void setupTitle();		// �^�C�g���̔w�i�ɕ\������p�Z�b�g�A�b�v
	void setupPlayMob(float dt);	// �v���C����ʏ㕔�ɏo�����o�p�Z�b�g�A�b�v	���݂̃Q�[���i�s���x��n��(�f�t�H���g1.0)

	void update();
	void draw();

	bool isExist() const { return m_isExist; }

	// ���ڐݒ�
	void setPos(Vec2 pos) { m_pos = pos; }
	void setVec(Vec2 vec) { m_vec = vec; }
	void setScale(double scale) { m_scale = scale; }
	void setKind(int kind) { m_playerKind = kind; }
	void setAnimSpeed(int speed) { m_animSpeed = speed; }	// �A�j��1�R�}�̃t���[�������w�肷��(1�ȏ�)	�������Ƒ���
	void setRun(bool isRun) { m_isRun = isRun; }
	void setMove(bool isMove) { m_isMove = isMove; }	// false����setVec�Ō��߂����������������ňړ����Ȃ�	�f�t�H���gtrue

	// �v���C���[�̎�ނ������_���ɕύX����
	void setRandomKind();

	Vec2 getPos() const { return m_pos; }
	Vec2 getVec() const { return m_vec; }
	int getPlayerKind() { return m_playerKind; }

private:
	Vec2	m_pos;		// ���S���W
	Vec2	m_vec;
	double m_scale;

	int m_playerKind;
	int m_animFrame;
	int m_animSpeed;	// �A�j��1�R�}�̃t���[����	�������Ƒ���

	bool m_isMove;		// true:m_vec�̕����Ɉړ�����	false:m_vec�͉�]�p�x���w�肷��̂Ɏg��
	bool m_isRun;		// false:�ҋ@�A�j��
	bool m_isExist;
};

