#pragma once
#include "Vec2.h"
#include "Rect.h"
#include <vector>
#include <deque>
#include <memory>
#include <list>

class PlayerManager;
class Field;
class ParticleManager;
class Player
{
public:
	// �풓���\�[�X�֘A
	// �v���C���[�̃O���t�B�b�N�͏풓������
	static void startLoad();	// �v���C���[�O���t�B�b�N�񓯊��ǂݍ��݂̊J�n
	static void unload();		// �v���C���[�O���t�B�b�N�̃A�����[�h

	static bool isLoaded();		// �v���C���[�̃O���t�B�b�N�ǂݍ��݊����m�F
	static int getKindNum();		// �v���C���[�O���t�B�b�N�̎�ގ擾
	static int getIdleGraph(int kind);	// �w�肵���v���C���[�ҋ@�O���t�B�b�N�̃n���h���擾
	static int getRunGraph(int kind);	// �w�肵���v���C���[����O���t�B�b�N�̃n���h���擾
	static int getColor(int kind);

	// �v���C���[�O���t�B�b�N���̎擾
	static int getIdleAnimeNum();	// �A�j���[�V�����̃R�}���擾
	static int getRunAnimeNum();

	

public:
	Player(bool isDemo);
	virtual ~Player();

	void setManager(std::shared_ptr<PlayerManager> pManager) { m_pManager = pManager; }
	void setField(std::shared_ptr<Field> pField) { m_pField = pField; }
	void setParticle(std::shared_ptr<ParticleManager> pParticle) { m_pParticle = pParticle; }

	void init(int playerNo);
	void update();
	void draw();

	Vec2 getPos() const { return m_pos; }
	Vec2 getScroll() const { return m_scroll; }

	void setKind(int kind) { m_kind = kind; }
	int getKind() const { return m_kind; }
	// 
	unsigned int getParticleColor();
	unsigned int getDigColor();

	// �c�ʒu�ݒ�	�����ʒu��ݒ肷��̂Ɏg�p����
	void setStartY(float y);
	// �v���C���[�ԍ��\�����s�����ݒ�	��l�v���C�Ȃ��\��
	void setDispPlayerNo(bool isDisp) { m_isDispPlayerNo = isDisp; }

//	// �ړ������̎擾
//	float getMoveDistance();
	// �v���C���[�ԍ��̎擾
	int getPlayerNo() const { return m_playerNo; }

	// �X�R�A�̎擾
	int getScore();

	// �v���C����(�t���[����)�̎擾
	int getPlayFrame() const { return m_playFrameCount; }

	// �v���C���[����ԑJ�ڂ�����
//	void startWait();	// �g���\�薳��
	void startIdling();
	void startDig();

	// ����ł��邩
	bool isDead();

	// �Q�[���i�s���x�̎擾
	int getTempo()const { return m_tempo; }
	float getDt();

	// �f���v���C
	bool	isDemo();

private:
	// �\���Ɏg�p������
	struct DispData
	{
		Vec2 pos;
		int grphHandle;
		int animIndex;
		double angle;
	};

	// ���݂̏����ŐVDispData�Ƃ��Ēǉ�����
	void addDispData();
	void addDispDataIdle();

	// �v���C���[�̏�Ԃ��Ƃ�update()
	void updateWait();		// �ŏ��̑ҋ@
	void updateIdling();	// �J�E���g�_�E����	�ړ��͂��Ȃ�������͂ł���
	void updateDig();		// �@��i��

	void updateDeadHit();	// �n�ʂɂԂ����Ď��S

	// ���S�`�F�b�N
	bool isCheckDead();

	// �v���C���[�ʒu�����ăX�N���[���ʂ𒲐�����
	void setScroll();

	// �ړ��O�Ճp�[�e�B�N������
	void createMoveParticle();

private:
	// �풓���\�[�X
	static std::vector<int>	m_idleGraph;
	static std::vector<int>	m_runGraph;

private:
	// 
	std::shared_ptr<PlayerManager>	m_pManager;
	// �n�`�f�[�^
	std::shared_ptr<Field>	m_pField;
	// �p�[�e�B�N��
	std::shared_ptr<ParticleManager>	m_pParticle;

	// �����o�[�֐��|�C���^
//	void (Player::*m_updateFunc)() = &Player::updateIdling;
	void (Player::* m_updateFunc)() = &Player::updateWait;

	// ���삷��v���C���[�̔ԍ�
	int m_playerNo;

	// �v���C���[�̎��
	int m_kind;

	// �v���C���[�ԍ��\��	��l�v���C�Ȃ�\�����Ȃ�
	bool m_isDispPlayerNo;

	// �v���C���[�̐i�s���x�Ǘ�
	int m_tempo;

	// �A�j���[�V�����p�̃J�E���^
	float m_animFrame;
	// 
	Vec2	m_pos;	// ���S�ʒu
	Vec2	m_vec;
	float	m_angle;

	Vec2	m_scroll;

	// �v���C����(�����c��t���[����)
	int		m_playFrameCount;

	// �V�[�P���X�ω����Ă���̃t���[����
	int		m_updateFrameCount;
	// �@����ʉ��t���[���J�E���g
	float	m_digFrameCount;
	// �e���|�A�b�v���Ă���̌o�߃t���[��
	int		m_tempoUpFrame;

	// �\���p�f�[�^
	std::deque<DispData>	m_dispData;

	// �f���v���C
	bool m_isDemo;
};

