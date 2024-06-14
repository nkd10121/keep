#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <memory>

class EffectPlayer;
class EffectString;
class Bg;
class PadUi;
class Telop;
class CursorPlayer;
class ParticleManager;
class SelectSeveral;
class SelectValue;
class SceneConfig : public SceneBase
{
public:
	SceneConfig();
	virtual ~SceneConfig();

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;

#ifdef _DEBUG
	virtual void drawDebug() override;
#endif

private:
	void addUiItem(int index);

	// �I������Ă��鍀�ڕʂ̏���
	void procLanguage();
	void procBgmVol();
	void procSeVol();
	void procVibration();
	void procFullScreen();

	// �e�ݒ荀�ڂ̓��e�\��
	void drawEraseData();

	// ����ύXA�{�^���҂�
	bool isChangeLanguageWait();
	// �E�C���h�E���[�h�ύXA�{�^���҂�
	bool isChangeWindowModeWait();

private:
	// �w�i���o
	std::shared_ptr<Bg>	m_pBg;
	// �^�C�g��������
	std::shared_ptr<EffectString>	m_pTitle;
	// �{�^��UI
	std::shared_ptr<PadUi>	m_pUi;
	// �����e���b�v
	std::shared_ptr<Telop>	m_pTelop;

	// �J�[�\��(�v���C���[�̃O���t�B�b�N�g�p)
	std::shared_ptr<CursorPlayer>	m_pCursor;
	// �p�[�e�B�N�����o
	std::shared_ptr<ParticleManager>	m_pParticle;
	// �J�[�\���̏�ԊǗ�
	Vec2	m_cursorPos;		// ���݈ʒu

	// �R���t�B�O��ʂŎg�p����v���C���[�̎��
	int m_playerKind;

	// ����ݒ�UI
	std::shared_ptr<SelectSeveral>	m_pItemLanguage;
	// ���ʐݒ�\��UI
	std::shared_ptr<SelectValue>	m_pItemBgmVol;
	std::shared_ptr<SelectValue>	m_pItemSeVol;
	// �U���ݒ�\��UI
	std::shared_ptr<SelectSeveral>	m_pItemVibration;
	// �t���X�N���[���ݒ�\��UI
	std::shared_ptr<SelectSeveral>	m_pItemFullScreen;

	// �ݒ�ύX�m�F�\��
	std::shared_ptr<EffectString>	m_pChangeLanguage;
	std::shared_ptr<EffectString>	m_pChangeFullScreen;
};

