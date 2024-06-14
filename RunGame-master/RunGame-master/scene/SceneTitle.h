#pragma once
#include "SceneBase.h"
#include "Vec2.h"
#include <list>
#include <memory>

class EffectPlayer;
class EffectString;
class SceneTitle : public SceneBase
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	virtual void startLoad() override;
	virtual bool isLoaded() const override;

	virtual void init() override;
	virtual void end() override;

	virtual void update() override;
	virtual void draw() override;


private:
	// �w�i���o�p�̃v���C���[
	struct TitlePlayer
	{
		Vec2 pos;
		bool isExist = false;
	};

private:
	// �V�[�P���X���Ƃ�update����

	void updateLoadWait();
	void updateTitleAppear();	// �^�C�g���o�ꉉ�o
	void updateWait();			// �v���C���[�̓��͑҂�

	// �^�C�g�����S�O���t�B�b�N�̐���
	void createLogoGraph();

	// �^�C�g�����S�̕\��
	void drawTitleLogo();

	// �w�i���o
	void drawBg();

	// �^�C�g�����o�I��
	bool isTitleAppearEnd();

private:
	// �V�[�P���X��update����
//	void (SceneTitle::*m_updateFunc)() = &SceneTitle::updateTitleAppear;
	void (SceneTitle::* m_updateFunc)() = &SceneTitle::updateLoadWait;

	// �w�i�X�N���[��
	int m_bgScreen;
	// �O���t�B�b�N���\�[�X
	int m_bgTile;

	// �^�C�g�����S���
	int m_titleFontHandle;
	int m_titleGraph;
	int m_titleWidth;

	int m_loadFrameCount;
	// �^�C�g�����S�o�ꉉ�o
	int m_titleFrameCount;
	// �w�i�X�N���[�����o
	int m_bgScroll;
	// �f���v���C�J�n�҂�����
	int m_demoWaitFrame;

	// �{�^���������ĂˁI�e�L�X�g
	std::shared_ptr<EffectString>	m_pText;

	// ���o�p�v���C���[
	std::list<std::shared_ptr<EffectPlayer>>	m_pPlayer;
};

