#pragma once
#include "SceneBase.h"
#include <memory>
#include <list>
#include <vector>

class Player;
class PlayerManager;
class Field;
class PadUi;
class DispRecord;
class ParticleManager;
class EffectString;
class EffectPlayer;
class MultiPlayScore;

class SceneMain : public SceneBase
{
public:
	SceneMain(int playerNum, bool isDemo);
	virtual ~SceneMain() {}

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

#ifdef _DEBUG
	// �f�o�b�O�\��(�őO�ʕ\��)
	virtual void drawDebug() override;
#endif

	// �v���C���[�̎�ގw��	�]���ɓn���Ă��ǂ�(�~�܂�Ȃ������ɉ����ɔ��f���ꂽ�肵�Ȃ�)
	void setPlayerKind(int playerNo, int kind);

private:
	// �V�[�P���X���Ƃ�update����
	void updateWait();		// �J�n�O�̑҂�����
	void updateCountdown();	// 3,2,1�\��
	void updatePlay();		// �Q�[���v���C

	void updateGameover();	// �Q�[���I�[�o�[���o

	void updateResult();	// �Q�[���I�[�o�[��̃����L���O�\��

	//  �Q�[���J�n�O�������b�Z�[�W�̕\��
	void drawTutorial();
	void drawTutorialSingle();
	void drawTutorialMulti();

	// �w�i���o
	void drawBg();

	// ���݂̈ړ������̕\��
	void drawScore();

	// �\�����W(���l�̒P�ʂ̊Ԃ̍��W���w��)�ƕ\���������X�R�A�A�t�H���g���w�肵�ĕ\��
	// ��l�v���C�p
	void drawScoreSingle( int x, int y, int score );

	// ���b�Z�[�W�\��	�X�s�[�h�A�b�v
	// ��ʏ㕔(�ז��ɂȂ�Ȃ��Ƃ���ɕ\������)
	void drawMessage();

	// �Q�[���I�[�o�[UI�̐���	�����N�C�������ꍇ�͏��ʂ������œn��	�����N�C�����Ă��Ȃ��ꍇ��-1
	void startGameOver(int rank);
	// �ΐ팋�ʂ̐���
	void startBattleResult();

	// ���o�p�L�����N�^�[�̍X�V
	void updateMob();
	// ���o�p�L�����N�^�[�̑��s�G�t�F�N�g����
	void createMobParticle(std::shared_ptr<EffectPlayer> pMob);

	// �g�p����BGM�̖��O
	const char* getBgmName();

	// ���l���v���C����
	bool isMulti();
	// �f���v���C
	bool isDemo();
	// �f���p�̃����L���OUI����
	void startDemoRanking();

private:
	// �V�[�P���X��update����
//	void (SceneMain::*m_updateFunc)() = &SceneMain::updatePlay;
	void (SceneMain::* m_updateFunc)() = &SceneMain::updateWait;
	// �v���C���[��
	int m_playerNum;
	// �v���C���[�̎�ގw��	���̃V�[������̎󂯓n���Ɏg�p	-1�̏ꍇ�̓����_��
	std::vector<int> m_selectPlayerKind;
	// �Q�[�����
	int m_gameScreen;
	// �O���t�B�b�N
	int m_fieldGraph;
	int m_uiBorder;
	int m_bgTile;

	std::shared_ptr<PlayerManager>	m_pPlayer;
	std::shared_ptr<Field>	m_pField;
	// �p�[�e�B�N�����o
	std::shared_ptr<ParticleManager>	m_pParticle;
	// �n��̉��o�p�L�����N�^�[
	int m_mobInterval;	// �L�����N�^�[�o��Ԋu�J�E���g
	std::list<std::shared_ptr<EffectPlayer>>	m_pMob;

	// �ΐ�v���C�p�X�R�AUI
	std::vector<std::shared_ptr<MultiPlayScore>>	m_pMultiPlayScore;

	// �|�[�Y�\��
	std::shared_ptr<EffectString>	m_pPauseText;

	// �Q�[���I�[�o�[��UI
	std::shared_ptr<PadUi>	m_pGameOver;

	// �����L���O�\��
	std::shared_ptr<DispRecord>	m_pRecord;

	// �f�����̃��b�Z�[�W�\��
	std::shared_ptr<EffectString>	m_pDemoText;

	// �`���[�g���A�����b�Z�[�W�\��
	int m_tutorialMessageNo;
	float m_tutorialMessageSinRate;

	// �J�E���g�_�E���\��
	int m_countDownNum;
	int m_countDownAlpha;
	double m_countDownScale;

	// �Q�[�����b�Z�[�W�\��
	bool m_isDispMessage;
	int	m_messageFrameCount;
	int	m_messageDispFrame;

	// ���o
	int m_updateFrame;

	// �|�[�Y
	bool m_isPause;
	// �f���v���C
	bool m_isDemo;
};

