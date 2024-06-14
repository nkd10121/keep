#pragma once
#include "Vec2.h"
#include <memory>

class EffectPlayer;
class ParticleManager;
// �J�[�\���Ƃ��Ďg�p����v���C���[
class CursorPlayer
{
public:
	CursorPlayer();
	virtual ~CursorPlayer();

	// �p�[�e�B�N���\��	�ݒ肵�Ȃ��Ă�����(�p�[�e�B�N���͕\������Ȃ�)
	void setParticle(std::shared_ptr<ParticleManager> pParticle) { m_pParticle = pParticle; }

	void update();
	void draw();

	// �ʒu�𒼐ڐݒ�	��ɏ������Ɏg�p
	void setPos(Vec2 pos);
	// �Ώۈʒu��ݒ�
	void setTarget(Vec2 target);
	// ��ނ�ݒ�
	void setPlayerKind(int kind);

private:
	// �ړ��O�Ճp�[�e�B�N������
	void createMoveParticle();

private:

	// �\���p
	std::shared_ptr<EffectPlayer>	m_pCursor;
	// �p�[�e�B�N��
	std::shared_ptr<ParticleManager>	m_pParticle;

//	Vec2 m_pos;	// ���݈ʒu
	Vec2 m_startPos;	// �ړ��J�n�ʒu
	Vec2 m_targetPos;	// �ړ��I���ʒu

	int m_moveFrame;
};

