#pragma once
#include <memory>
#include <vector>
#include "Vec2.h"

class Player;
class Field;
class ParticleManager;
class PlayerManager : public std::enable_shared_from_this<PlayerManager>
{
public:
	PlayerManager(bool isDemo);
	virtual ~PlayerManager();

	// �����ݒ�
	void setField(std::shared_ptr<Field> pField) { m_pField = pField; }
	void setParticleManager(std::shared_ptr<ParticleManager> pParticle) { m_pParticle = pParticle; }

	// ���t���[���̏���
	void update();
	void draw();
	
	// �l���ɉ����������ݒ���s��
	// �K�v�ȕ�addPlayer�����Ă�����s����
	void playSetting();

	// �v���C���[��ǉ�
	void addPlayer(int kind = -1);
	// �v���C���[���̎擾
	int getPlayerNum();
	// �v���C���[�̎擾
	std::shared_ptr<Player> getPlayer(int no);
	// �v���C���[�̏�񂩂�X�N���[���ʂ��擾
	Vec2 getScroll();
	// �����Ă���l���̎擾
	int getActiveNum();

	// ��ԃX�R�A�̍����v���C���[�̃X�R�A(=�ړ�����)
	int getMaxScore();
	// ��ԍ����ňړ����Ă���v���C���[�̃e���|�擾
	int getMaxTempo();
	// �ő�deltaTime�œ����Ă���v���C���[��deltaTime�擾
	float getMaxDt();

	// �S�Ẵv���C���[����ԑJ�ڂ�����
	void startIdling();
	void startDig();

private:
	std::vector<std::shared_ptr<Player>>	m_pPlayer;

	std::shared_ptr<Field>	m_pField;
	std::shared_ptr<ParticleManager>	m_pParticle;

	Vec2 m_scroll;
	bool m_isDemo;
};

