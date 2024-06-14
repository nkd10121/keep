#pragma once
#include <memory>

class Player;
class EffectPlayer;
class ParticleManager;

// �ΐ�v���C�p�̃X�R�A�\��
class MultiPlayScore
{
public:
	MultiPlayScore(std::shared_ptr<Player> pPlayer, int playerNum);
	virtual ~MultiPlayScore();

	void update();
	void draw();

private:
	// �E�C���h�E�\�����
	int getX();
	int getY();
	int getWidth();
	int getHeight();

	// ���o�p�[�e�B�N������
	void createParticle();

private:
	// �X�R�A��\������v���C���[�̏��
	std::shared_ptr<Player>	m_pPlayer;
	// ���o�p�p�[�e�B�N��	�v���C�I���e�B�̊֌W��SceneMain�͎̂g�킸�Ɏ��O�Ŋm��
	std::shared_ptr<ParticleManager>	m_pParticle;
	// �v���C�l��	�l���ɂ���Ĕz�u���ς��
	int	m_totalPlayerNum;

	// �v���C���[�A�C�R��
	std::shared_ptr<EffectPlayer>	m_pIcon;
};

