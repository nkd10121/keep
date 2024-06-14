#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <memory>

class Bg;
class EffectString;
class PadUi;
class EffectPlayer;
class CursorPlayer;
class Telop;
class ParticleManager;
class SceneMainMenu : public SceneBase
{
public:
	SceneMainMenu();
	virtual ~SceneMainMenu();

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
	// UI�Ƀ{�^������ǉ�
	void addUiItem(int index);

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

	// �O���t�B�b�N
	int m_uiBorder;

	// �J�[�\���̏�ԊǗ�
	Vec2	m_cursorPos;		// ���݈ʒu
};

