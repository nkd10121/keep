#include "SceneConfig.h"
#include "DxLib.h"
#include "game.h"

#include "Player.h"
#include "Font.h"
#include "EffectPlayer.h"
#include "EffectString.h"
#include "Message.h"
#include "Sound.h"
#include "Pad.h"
#include "Bg.h"
#include "SceneMainMenu.h"
#include "PadUi.h"
#include "PadUiItem.h"
#include "Telop.h"
#include "ConfigData.h"

#include "CursorPlayer.h"
#include "ParticleManager.h"

#include "SelectSeveral.h"
#include "SelectValue.h"

namespace
{
	// タイトルテキスト
	const char* const kTitleTextId = "MSG_CONFIG_TITLE";

	// ボタン情報
	constexpr int kButtonPosX = 320;
	constexpr int kButtonPosY = 220;
	constexpr int kButtonIntervalY = 80;

	constexpr int kButtonWidth = 460;
	constexpr int kButtonHeight = 80;

	enum ConfigItem
	{
		Language,	// 言語設定
		BgmVol,		// BGMのボリューム
		SeVol,			// SEのボリューム
		Vibration,	// 振動ONOFF
		FullScreen,	// フルスクリーンONOFF
	//	EraseData,	// セーブデータのクリア

		ItemNum
	};

	const char* const kButtonTextId[] =
	{
		"MSG_CONFIG_LANGUAGE",
		"MSG_CONFIG_BGM",
		"MSG_CONFIG_SE",
		"MSG_CONFIG_VIBRATION",
		"MSG_CONFIG_SCREENMODE",
	//	"MSG_CONFIG_ERASE",
	};
	static_assert(ItemNum == _countof(kButtonTextId));

	// テロップに表示するテキスト
	const char* const kTelopDefaultTextId = "MSG_CONFIG_T_DEFAULT";
	const char* const kTelopTextId[] =
	{
		"MSG_CONFIG_T_LANGUAGE",
		"MSG_CONFIG_T_BGM",
		"MSG_CONFIG_T_SE",
		"MSG_CONFIG_T_VIBRATION",
		"MSG_CONFIG_T_SCREENMODE",
	//	"MSG_CONFIG_T_ERASE",
	};
	static_assert(ItemNum == _countof(kTelopTextId));

	// 選択可能言語情報
	struct LanguageData
	{
		const char* langNameId;
		Message::LANG langId;
	};
	constexpr LanguageData kLanguageData[] =
	{
		{"MSG_LANGUAGE_JP", Message::LANG_JP},
		{"MSG_LANGUAGE_US", Message::LANG_US},
	};

	// 表示情報
	constexpr unsigned int kSelectTextColor = 0xffffff;
	constexpr unsigned int kUnselectTextColor = 0xa0a0a0;

	constexpr int kBarItemCenterX = 1120;
	constexpr int kTextItemCenterX = 900;


	// BGM,SE音量
	constexpr int kBarStartX = 700;
	constexpr int kVolBarLen = 420;
	constexpr int kVolBarHeight = 24;
}

SceneConfig::SceneConfig():
	m_playerKind(0)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示を行わない

	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
}

SceneConfig::~SceneConfig()
{
}

void SceneConfig::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	m_pBg->load();

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneConfig::isLoaded() const
{
	if (!m_pBg->isLoaded())	return false;
	return true;
}

void SceneConfig::init()
{
	// 言語を変更した場合はコンフィグ画面でセーブデータの設定変更→コンフィグに入り直しを行う
	// 実際に使用する言語の変更は入り直しのタイミングで行う
	int lang = ConfigData::getInstance().getLanguage();
	Message::getInstance().load(static_cast<Message::LANG>(lang));

	m_pTitle = std::make_shared<EffectString>();
	m_pTitle->setupSceneTitle(Message::getInstance().get_c(kTitleTextId));

	m_pUi = std::make_shared<PadUi>();
	for (int i = 0; i < ItemNum; i++)
	{
		addUiItem(i);
	}
	// 縦に並んだUIの設定
	m_pUi->setupVArrange(true);

	m_pTelop = std::make_shared<Telop>();
	m_pTelop->setupId(kTelopDefaultTextId, false);
	m_pTelop->setDispBack(true);

	m_playerKind = GetRand(Player::getKindNum()-1);

	m_pParticle = std::make_shared<ParticleManager>();

	// 最初はどこも選択していないのでタイトルの左に表示
	m_cursorPos.x = m_pTitle->getRect().getLeft() - 48.0f;
	m_cursorPos.y = 96.0f;

	m_pCursor = std::make_shared<CursorPlayer>();
	m_pCursor->setPos(m_cursorPos);
	m_pCursor->setParticle(m_pParticle);
	m_pCursor->setPlayerKind(m_playerKind);

	// 言語設定選択項目
	{
		m_pItemLanguage = std::make_shared<SelectSeveral>();
		Vec2 pos;
		pos.x = kTextItemCenterX;
		pos.y = kButtonPosY + kButtonIntervalY * Language;
		m_pItemLanguage->init(pos);

		for (int i = 0; i < _countof(kLanguageData); i++)
		{
			m_pItemLanguage->addItem(Message::getInstance().get_c(kLanguageData[i].langNameId), kLanguageData[i].langId);
		}

		m_pItemLanguage->setSelectValue(Message::getInstance().getCurrentLanguage());
		m_pItemLanguage->setActive(false);

		m_pItemLanguage->setup();
	}

	// BGM音量設定
	{
		m_pItemBgmVol = std::make_shared<SelectValue>();
		Vec2 pos;
		pos.x = kBarItemCenterX;
		pos.y = kButtonPosY + kButtonIntervalY * BgmVol;

		m_pItemBgmVol->init(pos, 0, ConfigData::getInstance().getMaxBgmVol(), ConfigData::getInstance().getBgmVol());
	}
	// SE音量設定
	{
		m_pItemSeVol = std::make_shared<SelectValue>();
		Vec2 pos;
		pos.x = kBarItemCenterX;
		pos.y = kButtonPosY + kButtonIntervalY * SeVol;

		m_pItemSeVol->init(pos, 0, ConfigData::getInstance().getMaxSeVol(), ConfigData::getInstance().getSeVol());
	}
	
	// 振動設定選択項目
	{
		m_pItemVibration = std::make_shared<SelectSeveral>();
		Vec2 pos;
		pos.x = kTextItemCenterX;
		pos.y = kButtonPosY + kButtonIntervalY * Vibration;
		m_pItemVibration->init(pos);
		m_pItemVibration->addItem(Message::getInstance().get_c("MSG_COMMON_ON"), 1);
		m_pItemVibration->addItem(Message::getInstance().get_c("MSG_COMMON_OFF"), 0);
		int defaultValue = 0;
		if (ConfigData::getInstance().isOn(ConfigData::Vibration))	defaultValue = 1;
		m_pItemVibration->setSelectValue(defaultValue);
		m_pItemVibration->setActive(false);

		m_pItemVibration->setup();
	}

	// フルスクリーン設定選択項目
	{
		m_pItemFullScreen = std::make_shared<SelectSeveral>();
		Vec2 pos;
		pos.x = kTextItemCenterX;
		pos.y = kButtonPosY + kButtonIntervalY * FullScreen;
		m_pItemFullScreen->init(pos);
		m_pItemFullScreen->addItem(Message::getInstance().get_c("MSG_CONFIG_ITEM_WINDOW"), 0);
		m_pItemFullScreen->addItem(Message::getInstance().get_c("MSG_CONFIG_ITEM_FULLSCREEN"), 1);
		int defaultValue = 0;
		if (!GetWindowModeFlag())	defaultValue = 1;
		m_pItemFullScreen->setSelectValue(defaultValue);
		m_pItemFullScreen->setActive(false);

		m_pItemFullScreen->setup();
	}

	m_pChangeLanguage = std::make_shared<EffectString>();
	m_pChangeLanguage->setup(kTextItemCenterX + 160, kButtonPosY + kButtonIntervalY * Language - 16, Message::getInstance().get_c("MSG_CONFIG_CHANGE"), Font::getHandle(Font::Id::Size32_4));
	m_pChangeLanguage->setColor(0xff0000);
	m_pChangeLanguage->setEffect(EffectString::Effect::AlphaBlink);
	m_pChangeLanguage->startIn(EffectString::In::None, 0);

	m_pChangeFullScreen = std::make_shared<EffectString>();
	m_pChangeFullScreen->setup(kTextItemCenterX + 160, kButtonPosY + kButtonIntervalY * FullScreen - 16, Message::getInstance().get_c("MSG_CONFIG_CHANGE"), Font::getHandle(Font::Id::Size32_4));
	m_pChangeFullScreen->setColor(0xff0000);
	m_pChangeFullScreen->setEffect(EffectString::Effect::AlphaBlink);
	m_pChangeFullScreen->startIn(EffectString::In::None, 0);


	Sound::getInstance().playBgm("bgmMenuCommon");
	Sound::getInstance().setVolume("bgmMenuCommon", 0);
}

void SceneConfig::end()
{
	Sound::getInstance().stop("bgmMenuCommon");
	m_pBg->unload();
}

void SceneConfig::update()
{
	if (getFadeProgress() > 0.0f)
	{
		Sound::getInstance().setVolume("bgmMenuCommon", static_cast <int>(255 * (1.0f - getFadeProgress())));
	}

	m_pBg->update();
	m_pTitle->update();
//	if (getFadeProgress() > 0.0f)
//	{
//		return;
//	}
	if (!isInitialized())	return;
	m_pTelop->update();
	// カーソルの移動
	m_pCursor->update();
	m_pParticle->update();

	m_pChangeLanguage->update();
	m_pChangeFullScreen->update();

	if (isChangeLanguageWait())
	{
		if (m_pUi->getSelectIndex() == Language)
		{
			// フェード中は変更不可
			if (Pad::isTrigger(PAD_INPUT_1) && getFadeProgress() <= 0.0f)
			{
				// セーブデータの書き換え	再度コンフィグに入るときに言語の変更を行う
				int next = m_pItemLanguage->getSelectValue();
				ConfigData::getInstance().setLanguage(next);
				ConfigData::getInstance().write();
				setNextScene(new SceneConfig);
			}
		}
		else
		{
			// 違う項目に選択を変更したら戻す
			m_pItemLanguage->setSelectValue(Message::getInstance().getCurrentLanguage());
		}
	}
	else if (isChangeWindowModeWait())
	{
		if (m_pUi->getSelectIndex() == FullScreen)
		{
			// フェード中は変更不可
			if (Pad::isTrigger(PAD_INPUT_1) && getFadeProgress() <= 0.0f)
			{
				// 切り替えてデータ保存
				if (m_pItemFullScreen->getSelectValue())
				{
					ChangeWindowMode(false);
					ConfigData::getInstance().flagOn(ConfigData::FullScreen);
				}
				else
				{
					ChangeWindowMode(true);
					ConfigData::getInstance().flagOff(ConfigData::FullScreen);
				}
				ConfigData::getInstance().write();
			}
		}
		else
		{
			// 違う項目に選択を変更したら戻す
			int value = 1;
			if (GetWindowModeFlag())	value = 0;
			m_pItemFullScreen->setSelectValue(value);
		}
	}

	int lastSelect = m_pUi->getSelectIndex();
	int result = m_pUi->update();
	// 選択されている項目が変わった
	if (lastSelect != m_pUi->getSelectIndex())
	{
		int next = m_pUi->getSelectIndex();

		Rect rect = m_pUi->getItem(next)->getEffectString()->getRect();
		m_cursorPos.x = kButtonPosX - rect.getWidth() / 2 - 32.0f;
		m_cursorPos.y = static_cast<float>(kButtonPosY + kButtonIntervalY * next) - 4.0f;

		m_pCursor->setTarget(m_cursorPos);

		m_pTelop->setupId(kTelopTextId[next], false);

	//	// カーソル移動の度にプレイヤー１体出てくる
	//	m_pBg->addPlayer();
	}

	m_pItemLanguage->setActive(false);
	m_pItemBgmVol->setActive(false);
	m_pItemSeVol->setActive(false);
	m_pItemVibration->setActive(false);
	m_pItemFullScreen->setActive(false);

	switch (m_pUi->getSelectIndex())
	{
	case Language:	// 言語設定
		m_pItemLanguage->setActive(true);
		procLanguage();
		break;
	case BgmVol:		// BGMのボリューム
		m_pItemBgmVol->setActive(true);
		procBgmVol();
		break;
	case SeVol:		// SEのボリューム
		m_pItemSeVol->setActive(true);
		procSeVol();
		break;
	case Vibration:	// 振動ONOFF
		m_pItemVibration->setActive(true);
		procVibration();
		break;
	case FullScreen:// フルスクリーンONOFF
		m_pItemFullScreen->setActive(true);
		procFullScreen();
		break;
	
//	case EraseData:	// セーブデータのクリア
	default:
		break;
	}

	if (getFadeProgress() > 0.0f)
	{
		return;
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		Sound::getInstance().play("uiCancel");
		ConfigData::getInstance().write();
		setNextScene(new SceneMainMenu);
	}
}

void SceneConfig::draw()
{
	if (!isInitialized())	return;

	m_pBg->drawAll();
	m_pTitle->draw();
	m_pUi->draw();
	m_pTelop->draw();

	m_pItemLanguage->draw();
	m_pItemBgmVol->draw();
	m_pItemSeVol->draw();
	m_pItemVibration->draw();
	m_pItemFullScreen->draw();
//	drawEraseData();

	m_pParticle->draw();
	m_pCursor->draw();

	if (isChangeLanguageWait())
	{
		m_pChangeLanguage->draw();
	}
	else if (isChangeWindowModeWait())
	{
		m_pChangeFullScreen->draw();
	}
}

#ifdef _DEBUG
void SceneConfig::drawDebug()
{
	DrawString(8,8,"SceneConfig", 0xffffff);
}
#endif

void SceneConfig::addUiItem(int index)
{
//	m_pUi->addItem(index, kButtonText[index], kButtonPosX, kButtonPosY + kButtonIntervalY * index, kButtonWidth, kButtonHeight);
	m_pUi->addItem(index, Message::getInstance().get_c(kButtonTextId[index]), kButtonPosX, kButtonPosY + kButtonIntervalY * index, kButtonWidth, kButtonHeight);
	m_pUi->getItem(index)->start(0);

	// 拡縮なし
	m_pUi->getItem(index)->setSelectScale(1.0);
	m_pUi->getItem(index)->setUnselectScale(1.0);

	// 決定はできない(項目選択にのみ使用する)
	m_pUi->getItem(index)->setDecideEnable(false);	
}

void SceneConfig::procLanguage()
{
	int last = m_pItemLanguage->getSelectValue();
	m_pItemLanguage->update();
	if (last != m_pItemLanguage->getSelectValue())
	{
		Sound::getInstance().play("changePlayer");
	}
}

void SceneConfig::procBgmVol()
{
	int lastVol = ConfigData::getInstance().getSeVol();
	m_pItemBgmVol->update();
	ConfigData::getInstance().setBgmVol(m_pItemBgmVol->getValue());

	if (lastVol != ConfigData::getInstance().getBgmVol())
	{
		Sound::getInstance().setVolume("bgmMenuCommon", static_cast <int>(255 * (1.0f - getFadeProgress())));
	}
}

void SceneConfig::procSeVol()
{
	int lastVol = ConfigData::getInstance().getSeVol();
	m_pItemSeVol->update();
	ConfigData::getInstance().setSeVol(m_pItemSeVol->getValue());

	if (lastVol != ConfigData::getInstance().getSeVol())
	{
		Sound::getInstance().play("uiDecide");
	}
}

void SceneConfig::procVibration()
{
	int last = m_pItemVibration->getSelectValue();
	m_pItemVibration->update();

	bool isSelectVibration = false;
	if (m_pItemVibration->getSelectValue())	isSelectVibration = true;

	if (last != m_pItemVibration->getSelectValue())
	{
		Sound::getInstance().play("changePlayer");
	}

	if (!ConfigData::getInstance().isOn(ConfigData::Vibration))
	{
		if (isSelectVibration)
		{
			// ONに変更したら振動
			ConfigData::getInstance().flagOn(ConfigData::Vibration);
			Pad::vibrationMiddle();
		}
	}
	else
	{
		if (!isSelectVibration)
		{
			ConfigData::getInstance().flagOff(ConfigData::Vibration);
		}
	}
}

void SceneConfig::procFullScreen()
{
	int last = m_pItemFullScreen->getSelectValue();
	m_pItemFullScreen->update();

	if (last != m_pItemFullScreen->getSelectValue())
	{
		Sound::getInstance().play("changePlayer");
	}
}

void SceneConfig::drawEraseData()
{
}

bool SceneConfig::isChangeLanguageWait()
{
	// 現在使用されているメッセージとコンフィグで選択したメッセージが違う場合A待ち
	int next = m_pItemLanguage->getSelectValue();
	return (Message::getInstance().getCurrentLanguage() != next);
}

bool SceneConfig::isChangeWindowModeWait()
{
	// 現在のウインドウモードとコンフィグで選択されているウインドウモードが違う場合A待ち
	bool isSelectWindowMode = true;
	if (m_pItemFullScreen->getSelectValue())	isSelectWindowMode = false;

	if (GetWindowModeFlag() && !isSelectWindowMode)	return true;
	if (!GetWindowModeFlag() && isSelectWindowMode)	return true;

	return false;
}

