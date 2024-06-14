#include "SceneRecord.h"
#include "DxLib.h"
#include "Font.h"
#include "Pad.h"
#include "game.h"

#include "Sound.h"
#include "SaveData.h"
#include "EffectString.h"
#include "DispRecord.h"
#include "SceneMainMenu.h"
#include "EffectString.h"
#include "Bg.h"
#include "Telop.h"

namespace
{
	// �O���t�B�b�N�t�@�C����
	const char* const kBgTileFilename = "data/image/bg/Gray.png";
	// �e���b�v�̃e�L�X�g
//	const char* const kTelopText = "�z���t�H�[�G���@�[���v���C���ă����N�C�����߂������I";
	const char* const kTelopTextId = "MSG_RECORD_T_DEFAULT";

	// �\���J�n�܂ő҂����Ԑݒ�
	constexpr int kDispWaitInterval = 10;	// ���ʂ���kDispWaitInterval�t���[���Ԋu�ŕ\������
}

SceneRecord::SceneRecord()
{
	// �V�[���ݒ�
	setDispLoading(false);	// ���[�h���\�����s��Ȃ�

	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
}

void SceneRecord::startLoad()
{
	// �񓯊��ǂݍ��݂��J�n����
	SetUseASyncLoadFlag(true);

	m_pBg->load();

	// �f�t�H���g�ɖ߂�
	SetUseASyncLoadFlag(false);
}

bool SceneRecord::isLoaded() const
{
//	if (!Player::isLoaded())	return false;
	if (!m_pBg->isLoaded())	return false;

	return true;
}

void SceneRecord::init()
{
	m_pRecord = std::make_shared<DispRecord>();
	m_pRecord->setupTitle(DispRecord::TitleType::Ranking);
	// �Z�[�u�f�[�^�̋L�^��\���f�[�^�Ƃ��ēo�^
	for (int i = 0; i < SaveData::kSaveRankDataNum; i++)
	{
		m_pRecord->addData(i, i, SaveData::getInstance().getRankPlayerScore(i), SaveData::getInstance().getRankPlayerKind(i));
	}
	int waitFrame = 0;
	for (int i = SaveData::kSaveRankDataNum - 1; i >= 0; i--)
	{
		// ���Ԋu�Ńe���|�悭�\������
		m_pRecord->setDispWait(i, waitFrame);
		waitFrame += kDispWaitInterval;
	}

	m_pTelop = std::make_shared<Telop>();
	m_pTelop->setupId(kTelopTextId, false);
	m_pTelop->setDispBack(true);

	Sound::getInstance().playBgm("bgmMenuCommon");
	Sound::getInstance().setVolume("bgmMenuCommon", 0);
}

void SceneRecord::end()
{
	Sound::getInstance().stop("bgmMenuCommon");
	m_pBg->unload();
}

void SceneRecord::update()
{
	if (getFadeProgress() > 0.0f)
	{
		Sound::getInstance().setVolume("bgmMenuCommon", static_cast <int>(255 * (1.0f - getFadeProgress())));
		return;
	}

	m_pBg->update();
	m_pRecord->update();
	m_pTelop->update();

//	if (m_pRecord->isDispEnd())	// ���S�ɕ\������܂Ŗ߂�Ȃ�
	{
		if (Pad::isTrigger(PAD_INPUT_2))
		{
			Sound::getInstance().play("uiCancel");
			setNextScene(new SceneMainMenu);
		}
	}
}

void SceneRecord::draw()
{
	if (!isLoaded())	return;

	m_pBg->drawAll();

	if (m_pRecord)	m_pRecord->draw();
	m_pTelop->draw();

//	DrawString(8, 8, "SceneRecord", 0xffffff);
}
