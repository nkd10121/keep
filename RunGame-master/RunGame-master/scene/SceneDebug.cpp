#include "DxLib.h"
#include "game.h"

#include "Player.h"
#include "Font.h"
#include "Sound.h"
#include "SceneDebug.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneMainMenu.h"
#include "SceneRecord.h"
#include "SceneConfig.h"
#include "SceneSelectPlayerNum.h"

#include "Pad.h"

#include "DebugUi.h"

#include <string>
#include <cassert>

namespace
{
}

SceneDebug::SceneDebug():
	m_frameCount(0)
{
	// �V�[���ݒ�
	setDispLoading(false);	// ���[�h���\���ݒ�
//	setFadeFrame(8);		// �t�F�[�h�t���[����ݒ�	�ݒ肹���Ƀf�t�H���g�t���[���ɂ��Ă��ǂ�
}

void SceneDebug::startLoad()
{
	// �񓯊��ǂݍ��݂��J�n����
	SetUseASyncLoadFlag(true);


	// �f�t�H���g�ɖ߂�
	SetUseASyncLoadFlag(false);
}

bool SceneDebug::isLoaded() const
{
	return true;
}

void SceneDebug::init()
{
	m_pUi = std::make_shared<DebugUi>(8, 8);
	m_pUi->addItem(0, "�^�C�g������");
	m_pUi->addItem(1, "�Q�[������");
	m_pUi->addItem(2, "���C�����j���[");
	m_pUi->addItem(3, "�l���I��");
	m_pUi->addItem(4, "�����L���O");
	m_pUi->addItem(5, "�R���t�B�O");
	m_pUi->addItem(6, "test");
	m_pUi->addItem(7, "�f���v���C");
	m_pUi->setSelect(0);
}

void SceneDebug::end()
{
}

void SceneDebug::update()
{
	// �t�F�[�h�C���A�E�g���̓Q�[�������s��Ȃ�
//	if (isFading())
	if(getFadeProgress() > 0.0f)
	{
		// �t�F�[�h�����w�i����������ҋ@�A�j������ꍇ�͂�����

		return;
	}

	// �ʏ�̓^�C�g����ʂŃ��[�h�҂����s����
	// �f�o�b�O���j���[����͌o�R���Ȃ��\��������̂ł����Ń��[�h�҂�
	bool isLoading = false;
	if (!Sound::getInstance().isLoaded())
	{
	//	printfDx("sound loading...\n");
		isLoading = true;
	}
	if (!Font::isLoaded())
	{
	//	printfDx("font loading...\n");
		isLoading = true;
	}

	// ���[�h���̃��[�\�[�X������ꍇ�i�߂Ȃ�
	if (isLoading)
	{
		return;
	}

	int result = m_pUi->update();

	m_frameCount++;

//	if(Pad::isTrigger(PAD_INPUT_1))
	if(result >= 0)	// �������獀�ڂ��I�����ꂽ
	{
		// �^�C�g���o�R���Ȃ��Ə������g���擾���Ă��Ȃ��̂Ŏ��W���Ă���
		Sound::getInstance().collectData();
		// �t�H���g�̏����W
		Font::collectData();

		switch (result)
		{
		case 0:	setNextScene(new SceneTitle);		break;
		case 1:	setNextScene(new SceneMain{ 1, false });	break;
		case 2:	setNextScene(new SceneMainMenu);	break;
		case 3:	setNextScene(new SceneSelectPlayerNum);	break;
		case 4:	setNextScene(new SceneRecord);		break;
		case 5:	setNextScene(new SceneConfig);		break;
		case 6:	setNextScene(new SceneTest);	break;
		case 7: setNextScene(new SceneMain{ Player::getKindNum(), true });	break;
		default:	setNextScene(new SceneTest);	break;
		}
	}
}

void SceneDebug::draw()
{
	if (!isInitialized())	return;
	// �t�F�[�h�C���A�E�g�����`��͍s��
//	if (isFading()) {}

	// ���\�[�X�̃��[�h���I���܂ł͕`�悵�Ȃ��̂��悳����
	// (�ǂ���ɂ���t�F�[�h�d�؂��Ă���̂ŉ��������Ȃ��͂�)
	if (!isLoaded())	return;

	m_pUi->draw();
}

