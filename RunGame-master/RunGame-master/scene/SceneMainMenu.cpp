#include "SceneMainMenu.h"

#include "game.h"
#include "Font.h"
#include "Message.h"
#include "Sound.h"
#include "Bg.h"
#include "EffectString.h"
#include "EffectPlayer.h"
#include "CursorPlayer.h"
#include "PadUi.h"
#include "PadUiItem.h"
#include "Telop.h"
#include "ParticleManager.h"

#include "SceneTitle.h"
#include "SceneMain.h"
#include "SceneSelectPlayerNum.h"
#include "SceneRecord.h"
#include "SceneConfig.h"
#include "SceneStaff.h"

#include <cassert>

namespace
{
	const char* const kUiBorderFilename = "data/image/ui/WindowBase000.png";
	const char* const kBgTileFilename = "data/image/bg/Yellow.png";

	struct ButtonData
	{
		//　表示するテキスト
		const char* textId;
		// 配置
		int x;
		int y;
		// ボタンサイズ
		int width;
		int height;

		// キー入力時の遷移先	trg,rep共通
		int nextUp;
		int nextDown;
		int nextLeft;
		int nextRight;

		// 使用するフォント
		Font::Id font;
		int karning;
	};

	// UI情報
	enum UiItem
	{
		PlaySingle,
		PlayMulti,
		Ranking,
		Config,
		Staff,
		ToTitle,
		End,

		UiItemNum
	};
	constexpr ButtonData kButtonData[UiItemNum] =
	{
		// PlaySingle,
		{
			"MSG_MAIN_SINGLE",	340, 320, 580, 300,
			-1, Ranking, -1, PlayMulti,
			Font::Id::MainMenuItemL, -8
		},
		// PlayMulti,
		{
			"MSG_MAIN_MULTI",	940, 320, 580, 300,
			-1, Config, PlaySingle, -1,
			Font::Id::MainMenuItemL, -8
		},
		// Ranking,
		{
			"MSG_MAIN_RANKING",			340, 520, 580, 80,
			PlaySingle, Staff, -1, Config,
			Font::Id::MainMenuItemL, -8
		},
		// Config,
		{
			"MSG_MAIN_CONFIG",		940, 520, 580, 80,
			PlayMulti, ToTitle, Ranking, -1,
			Font::Id::MainMenuItemL, -8
		},

		// Staff,
		{
			"MSG_MAIN_STAFF",		490, 610, 280, 80,
			Ranking, -1, -1, ToTitle,
			Font::Id::MainMenuItemS, -4
		},
		// ToTitle,
		{
			"MSG_MAIN_TOTITLE",		790, 610, 280, 80,
			Config, -1, Staff, End,
			Font::Id::MainMenuItemS, -4
		},
		// End,
		{
			"MSG_MAIN_END",			1090, 610, 280, 80,
			Config, -1, ToTitle, -1,
			Font::Id::MainMenuItemS, -4
		},
	};

	// テロップのテキスト
	constexpr const char* kTelopDefaultTextId = "MSG_MAIN_T_DEFAULT";
	constexpr const char* kTelopTextId[UiItemNum] =
	{
		// PlaySingle,
		"MSG_MAIN_T_SINGLE",
		// PlayMulti,
		"MSG_MAIN_T_MULTI",
		// Ranking,
		"MSG_MAIN_T_RANKING",
		// Config
		"MSG_MAIN_T_CONFIG",
		// Staff,
		"MSG_MAIN_T_STAFF",
		// ToTitle,
		"MSG_MAIN_T_TOTITLE",
		// End,
		"MSG_MAIN_T_END",
	};
}

SceneMainMenu::SceneMainMenu():
	m_uiBorder(-1)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示設定
	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
//	m_pBg->setPlayerInterval(1);
//	m_pBg->setPlayerCreateNum(1);
}

SceneMainMenu::~SceneMainMenu()
{
}

void SceneMainMenu::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	m_uiBorder = LoadGraph(kUiBorderFilename);
	m_pBg->load();

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneMainMenu::isLoaded() const
{
	if (CheckHandleASyncLoad(m_uiBorder))	return false;
	if (!m_pBg->isLoaded())	return false;
	return true;
}

void SceneMainMenu::init()
{
	m_pParticle = std::make_shared<ParticleManager>();

	m_pTitle = std::make_shared<EffectString>();
	m_pTitle->setupSceneTitle(Message::getInstance().get_c("MSG_MAIN_TITLE"));

	m_pTelop = std::make_shared<Telop>();
	m_pTelop->setupId(kTelopDefaultTextId, false);

	m_pUi = std::make_shared<PadUi>();
	m_pUi->setButtonGraph(m_uiBorder);

	for (int i = 0; i < UiItemNum; i++)
	{
		addUiItem(i);
	}

	// 最初はどこも選択していないのでタイトルの左に表示
	m_cursorPos.x = m_pTitle->getRect().getLeft() - 48.0f;
	m_cursorPos.y = 96.0f;

	m_pCursor = std::make_shared<CursorPlayer>();
	m_pCursor->setPos(m_cursorPos);
	m_pCursor->setParticle(m_pParticle);

	Sound::getInstance().playBgm("bgmMainMenu");
	Sound::getInstance().setVolume("bgmMainMenu", 0);

	// フォントの情報収集
	Font::collectData();
}

void SceneMainMenu::end()
{
	Sound::getInstance().stop("bgmMainMenu");

	DeleteGraph(m_uiBorder);
	m_pBg->unload();
}

void SceneMainMenu::update()
{
//	if (getFadeProgress() > 0.0f)
//	{
//		// フェード中も背景動かしたり待機アニメする場合はここで
//
//		return;
//	}
	float bgmRate = 1.0f - getFadeProgress();
	Sound::getInstance().setVolume("bgmMainMenu", static_cast<int>(255 * bgmRate));

	if (!isInitialized())	return;

	m_pBg->update();
	m_pTitle->update();
	m_pTelop->update();
	m_pParticle->update();

	// カーソルの移動
	m_pCursor->update();

	int lastSelect = m_pUi->getSelectIndex();
	int result = m_pUi->update();

	// 選択されている項目が変わった
	if (lastSelect != m_pUi->getSelectIndex())
	{
		int next = m_pUi->getSelectIndex();

		m_pTelop->setupId(kTelopTextId[next], false);

		Rect rect = m_pUi->getItem(next)->getEffectString()->getRect();
		m_cursorPos.x = kButtonData[next].x - rect.getWidth() / 2 - 32.0f;
		m_cursorPos.y = static_cast<float>(kButtonData[next].y) - 4.0f;

		m_pCursor->setTarget(m_cursorPos);

		// カーソル移動の度にプレイヤー１体出てくる
		m_pBg->addPlayer();
	}
	if (result >= 0)
	{
		switch (result)
		{
		case PlaySingle:
			setNextScene(new SceneMain{1, false });
			break;
		case PlayMulti:
			setNextScene(new SceneSelectPlayerNum);
			break;
		case Ranking:
			setNextScene(new SceneRecord);
			break;
		case Config:
			setNextScene(new SceneConfig);
			break;
		case Staff:
			setNextScene(new SceneStaff);
			break;
		case ToTitle:
			setNextScene(new SceneTitle);
			break;
		case End:
			setNextScene(nullptr);
			break;
		default:
			assert(false);
			setNextScene(nullptr);
			break;
		}
	}
}

void SceneMainMenu::draw()
{
	if (!isInitialized())	return;

	m_pBg->drawAll();

//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
//	DrawBox(0,0,Game::kScreenWidth, Game::kScreenHeight,0x000000, true);
//	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	m_pTitle->draw();
	m_pTelop->draw();
	m_pUi->draw();
	m_pParticle->draw();
	m_pCursor->draw();
}

#ifdef _DEBUG
void SceneMainMenu::drawDebug()
{
	if (!isInitialized())	return;
	DrawString(8,8,"SceneMainMenu",0xffffff);
}
#endif

void SceneMainMenu::addUiItem(int index)
{
	ButtonData data = kButtonData[index];

	// 範囲矩形の生成
	Rect rect;
	Vec2 center;
	center.x = static_cast<float>(data.x);
	center.y = static_cast<float>(data.y);
	rect.setup(Rect::PosType::Center, center, static_cast<float>(data.width), static_cast<float>(data.height));

	std::shared_ptr<PadUiItem>	pItem = std::make_shared<PadUiItem>(index, Message::getInstance().get_c(data.textId));
	pItem->setBorderHandle(m_uiBorder);
	pItem->setRect(rect);
	pItem->setSelectScale(1.0);
	pItem->setUnselectScale(1.0);	// 拡縮なし
	// カーソル移動情報の追加
	pItem->setTriggerUp(data.nextUp);
	pItem->setRepeatUp(data.nextUp);
	pItem->setTriggerDown(data.nextDown);
	pItem->setRepeatDown(data.nextDown);
	pItem->setTriggerLeft(data.nextLeft);
	pItem->setRepeatLeft(data.nextLeft);
	pItem->setTriggerRight(data.nextRight);
	pItem->setRepeatRight(data.nextRight);
	// フォントを個別に設定
	pItem->setFont(Font::getHandle(data.font));
	pItem->setKarning(data.karning);

	pItem->setup();

	pItem->onUnselect();	// いったん非選択状態に
	pItem->start(0);

	m_pUi->addItem(pItem);
#if false
	m_pUi->addItem(index, kButtonData[index].text, kButtonData[index].x, kButtonData[index].y, kButtonData[index].width, kButtonData[index].height);
	m_pUi->getItem(index)->start(0);
	m_pUi->getItem(index)->setSelectScale(1.0);
	m_pUi->getItem(index)->setUnselectScale(1.0);

	//	// addItem内で指定したデフォルトフォントから変更
	//	m_pUi->getItem(i)->setFont(Font::getHandle(Font::Id::Size32_4));

		// 上下左右キーを押したときの遷移先を設定する
	m_pUi->getItem(index)->setTriggerUp(kButtonData[index].nextUp);
	m_pUi->getItem(index)->setRepeatUp(kButtonData[index].nextUp);
	m_pUi->getItem(index)->setTriggerDown(kButtonData[index].nextDown);
	m_pUi->getItem(index)->setRepeatDown(kButtonData[index].nextDown);
	m_pUi->getItem(index)->setTriggerLeft(kButtonData[index].nextLeft);
	m_pUi->getItem(index)->setRepeatLeft(kButtonData[index].nextLeft);
	m_pUi->getItem(index)->setTriggerRight(kButtonData[index].nextRight);
	m_pUi->getItem(index)->setRepeatRight(kButtonData[index].nextRight);
#endif
}

