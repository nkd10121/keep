#include "SceneStaff.h"
#include "DxLib.h"
#include "game.h"

#include "Message.h"
#include "Font.h"
#include "EffectString.h"
#include "Sound.h"
#include "Pad.h"
#include "Bg.h"
#include "Telop.h"
#include "SceneMainMenu.h"

namespace
{
	// �^�C�g���e�L�X�g
	const char* const kTitleTextId = "MSG_STAFF_TITLE";
	// �e���b�v�ɕ\�������e�L�X�g
	const char* const kTelopTextId = "MSG_STAFF_T_DEFAULT";

	constexpr unsigned int kTextColor = 0xffffff;

	constexpr int kTextStartX = 160;
}

SceneStaff::SceneStaff()
{
	// �V�[���ݒ�
	setDispLoading(false);	// ���[�h���\�����s��Ȃ�

	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
}

SceneStaff::~SceneStaff()
{
}

void SceneStaff::startLoad()
{
	// �񓯊��ǂݍ��݂��J�n����
	SetUseASyncLoadFlag(true);

	m_pBg->load();

	// �f�t�H���g�ɖ߂�
	SetUseASyncLoadFlag(false);
}

bool SceneStaff::isLoaded() const
{
	if (!m_pBg->isLoaded())	return false;
	return true;
}

void SceneStaff::init()
{
	m_pTitle = std::make_shared<EffectString>();
	m_pTitle->setupSceneTitle(Message::getInstance().get_c(kTitleTextId));
	
	// �w�i���o
	m_pBg->setPlayerInterval(4);
	m_pBg->setPlayerCreateNum(1);

	m_pTelop = std::make_shared<Telop>();
	m_pTelop->setupId(kTelopTextId, false);
	m_pTelop->setDispBack(true);

	Sound::getInstance().playBgm("bgmMenuCommon");
	Sound::getInstance().setVolume("bgmMenuCommon", 0);
}

void SceneStaff::end()
{
	Sound::getInstance().stop("bgmMenuCommon");
	m_pBg->unload();
}

void SceneStaff::update()
{
	m_pBg->update();
	m_pTitle->update();
	m_pTelop->update();
	if (getFadeProgress() > 0.0f)
	{
		Sound::getInstance().setVolume("bgmMenuCommon", static_cast <int>(255 * (1.0f - getFadeProgress())));
		return;
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		Sound::getInstance().play("uiCancel");
		setNextScene(new SceneMainMenu);
	}
}

void SceneStaff::draw()
{
	if (!isInitialized())	return;

	m_pBg->drawAll();
	m_pTitle->draw();
	m_pTelop->draw();

	Font::drawString(kTextStartX, 148, Message::getInstance().get_c("MSG_STAFF_NAME_0"), kTextColor, Font::Id::StaffName);
	Font::drawString(kTextStartX + 32, 148 + 42 * 1, Message::getInstance().get_c("MSG_STAFF_URL_0"), kTextColor, Font::Id::StaffName);
	Font::drawString(kTextStartX, 148 + 42 * 2, Message::getInstance().get_c("MSG_STAFF_NAME_1"), kTextColor, Font::Id::StaffName);
	Font::drawString(kTextStartX + 32, 148 + 42 * 3, Message::getInstance().get_c("MSG_STAFF_URL_1"), kTextColor, Font::Id::StaffName);

	Font::drawString(kTextStartX, 344, Message::getInstance().get_c("MSG_STAFF_NAME_2"), kTextColor, Font::Id::StaffName);
	Font::drawString(kTextStartX + 32, 344 + 42 * 1, Message::getInstance().get_c("MSG_STAFF_URL_2"), kTextColor, Font::Id::StaffName);

	Font::drawString(kTextStartX, 460, Message::getInstance().get_c("MSG_STAFF_NAME_3"), kTextColor, Font::Id::StaffName);
	Font::drawString(kTextStartX + 32, 460 + 42 * 1, Message::getInstance().get_c("MSG_STAFF_URL_3"), kTextColor, Font::Id::StaffName);

	Font::drawString(kTextStartX, 576, Message::getInstance().get_c("MSG_STAFF_NAME_4"), kTextColor, Font::Id::StaffName);
	Font::drawString(kTextStartX + 32, 576 + 42 * 1, Message::getInstance().get_c("MSG_STAFF_URL_4"), kTextColor, Font::Id::StaffName);
	
}

#ifdef _DEBUG
void SceneStaff::drawDebug()
{
}
#endif
