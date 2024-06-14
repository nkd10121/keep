#include "SceneSelectPlayerNum.h"
#include "Pad.h"
#include "game.h"
#include "Font.h"
#include "Message.h"

#include "SceneMain.h"
#include "SceneMainMenu.h"

#include "Sound.h"
#include "Player.h"
#include "EffectString.h"
#include "EffectPlayer.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "Bg.h"
#include "Telop.h"

#include "PadUi.h"
#include "PadUiItem.h"

namespace
{
	// グラフィックファイル名
	const char* const kBgTileFilename = "data/image/bg/Gray.png";

	// タイトルテキスト
	const char* const kTitleTextId = "MSG_MULTI_TITLE";

	// 説明テキスト
	const char* const kTelopTextId = "MSG_MULTI_T_DEFAULT";

	// ボタン情報
	constexpr int kButtonPosX = 420;
	constexpr int kButtonPosY = 200;
	constexpr int kButtonIntervalY = 72;

	constexpr int kButtonWidth = 260;
	constexpr int kButtonHeight = 80;

	const char* const kButtonTextId[] =
	{
		"MSG_MULTI_NUM_2",
		"MSG_MULTI_NUM_3",
		"MSG_MULTI_NUM_4",
		"MSG_MULTI_NUM_5",
		"MSG_MULTI_NUM_6",
		"MSG_MULTI_NUM_7",
		"MSG_MULTI_NUM_8",
	};
	constexpr int kButtonNum = _countof(kButtonTextId);

	// 演出用アイコン
	constexpr int kPlayerIconIntervalX = 48;
	constexpr int kUnselectIconAlpha = 64;		// 選択されていないアイコンの基本アルファ
	constexpr int kUnselectIconEraseFrame = 8;	// 選択されていないアイコンを非表示にするのにかかるフレーム数

	// 人数決定後演出時間
	constexpr int kDecideEffectFrame = 72;
}

SceneSelectPlayerNum::SceneSelectPlayerNum():
	m_iconAlpha(kUnselectIconAlpha),
	m_decidePlayerNum(0),
	m_frameCount(0)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示設定
//	setFadeFrame(8);		// フェードフレームを設定	設定せずにデフォルトフレームにしても良い

	m_pBg = std::make_shared<Bg>();
	m_pBg->setTileKindRandom();
}

void SceneSelectPlayerNum::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	m_pBg->load();

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneSelectPlayerNum::isLoaded() const
{
	if (!m_pBg->isLoaded())	return false;
	return true;
}

void SceneSelectPlayerNum::init()
{
	m_pTitle = std::make_shared<EffectString>();
	m_pTitle->setupSceneTitle(Message::getInstance().get_c("MSG_MULTI_TITLE"));

	m_pUi = std::make_shared<PadUi>();
	for (int i = 0; i < kButtonNum; i++)
	{
	//	m_pUi->addItem(i, kButtonText[i], kButtonPosX, kButtonPosY + kButtonIntervalY * i, kButtonWidth, kButtonHeight);
		m_pUi->addItem(i, Message::getInstance().get_c(kButtonTextId[i]), kButtonPosX, kButtonPosY + kButtonIntervalY * i, kButtonWidth, kButtonHeight);
		m_pUi->getItem(i)->start(0);
	}
	// 縦に並んだUIの設定
	m_pUi->setupVArrange(true);

	// 最初はランダムにキャラクターを選択する
	for (int i = 0; i < Game::kMaxPlayer; i++)
	{
		m_selectPlayerKind.push_back(GetRand(Player::getKindNum()-1));
	}
	
	for (int button = 0; button < kButtonNum; button++)
	{
		int playerNum = button + 2;	// 選択肢はふたりからスタート

		IconVector iconVector;
		for (int i = 0; i < playerNum; i++)
		{
			float x = static_cast<float>(kButtonPosX + kButtonWidth / 2 + kPlayerIconIntervalX * i + 32);
			float y = static_cast<float>(kButtonPosY + kButtonIntervalY * button - 8);

			std::shared_ptr<EffectPlayer> pIcon = std::make_shared<EffectPlayer>();
			pIcon->setupIcon(Vec2{ x,y });	// いったんアイコンとして生成して必要な情報を個別で設定する
			//	pIcon->setPos(Vec2{x,y});
			pIcon->setVec(Vec2{ -1.0f,0.0f });	// 左を向ける
			pIcon->setScale(2.0);
			pIcon->setKind(m_selectPlayerKind[i]);
			pIcon->setAnimSpeed(4);
			pIcon->setRun(true);
			pIcon->setMove(false);

			iconVector.push_back(pIcon);
		}
		m_pPlayerIcon.push_back(iconVector);
	}

	m_pParticle = std::make_shared<ParticleManager>();

	m_pTelop = std::make_shared<Telop>();
	m_pTelop->setupId(kTelopTextId, false);
	m_pTelop->setDispBack(true);

	Sound::getInstance().playBgm("bgmPlayerNum");
	Sound::getInstance().setVolume("bgmPlayerNum", 0);
}

void SceneSelectPlayerNum::end()
{
	Sound::getInstance().stop("bgmPlayerNum");
	m_pBg->unload();
}

void SceneSelectPlayerNum::update()
{
	if (getFadeProgress() > 0.0f)
	{
		Sound::getInstance().setVolume("bgmPlayerNum", static_cast <int>(255 * (1.0f - getFadeProgress())));
	}
	(this->*m_updateFunc)();
}

void SceneSelectPlayerNum::draw()
{
	if (!isInitialized())	return;

	m_pBg->drawAll();
	m_pTitle->draw();

	for (int button = 0; button < kButtonNum; button++)
	{
		bool isSelect = (m_pUi->getSelectIndex() == button);
		if (isSelect)
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
		}
		else
		{
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_iconAlpha);
		}
		for(int i = 0; i < m_pPlayerIcon[button].size(); i++)
		{
			if (isSelect)
			{
				std::string text = std::to_string(i + 1);
				text += "P";
				Vec2 pos = m_pPlayerIcon[button][i]->getPos();
				pos.x -= 16;
				pos.y -= 48;
				int kind = m_selectPlayerKind[i];
				unsigned int color = Player::getColor(kind);
				Font::drawString(static_cast<int>(pos.x), static_cast<int>(pos.y), text.c_str(), color, Font::Id::PlayerNumPlayerNo);
			}

			m_pPlayerIcon[button][i]->draw();
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	m_pParticle->draw();
	m_pUi->draw();

	m_pTelop->draw();
}

#ifdef _DEBUG
void SceneSelectPlayerNum::drawDebug()
{
	DrawFormatString(8, 128 + 32, 0xffffff, "Pad: %d", Pad::getPadNum());
}
#endif

void SceneSelectPlayerNum::updateSelect()
{
	if (!isInitialized())
	{
		return;
	}

	m_pBg->update();
	m_pParticle->update();
	m_pTitle->update();
	m_pTelop->update();
	int result = m_pUi->update();
	for (int button = 0; button < kButtonNum; button++)
	{
		// 選択されているアイコンのみupdate(アニメーションさせる)
		if (m_pUi->getSelectIndex() != button)	continue;

		for (auto& icon : m_pPlayerIcon[button])
		{
			icon->update();
		}
	}

	if (result >= 0)
	{
		// 決定演出
		for (auto& icon : m_pPlayerIcon[result])
		{
			icon->setVec(Vec2{ 4.0f,0.0f });
			icon->setMove(true);
		}
		m_updateFunc = &SceneSelectPlayerNum::updateOut;
		m_decidePlayerNum = result + 2;
		return;
	}

	if (false)
	{
		ReSetupJoypad();	// パッドの再セットアップ	0.3秒ほどかかるらしい
	}

	for (int i = 0; i < Game::kMaxPlayer; i++)
	{
		int lastKind = m_selectPlayerKind[i];
		int kind = m_selectPlayerKind[i];
		if (Pad::isTrigger(PAD_INPUT_LEFT, i))
		{
			kind--;
			if (kind < 0)	kind = Player::getKindNum() - 1;
		}
		else if (Pad::isTrigger(PAD_INPUT_RIGHT, i))
		{
			kind++;
			if (kind >= Player::getKindNum())	kind = 0;

		}
		if (kind != lastKind)
		{
			Sound::getInstance().play("changePlayer");
			m_selectPlayerKind[i] = kind;
			for (int j = 0; j < m_pPlayerIcon.size(); j++)
			{
				if (m_pPlayerIcon[j].size() <= i)	continue;
				m_pPlayerIcon[j][i]->setKind(kind);
				if (m_pUi->getSelectIndex() == j)
				{
					createKindChangeParticle(m_pPlayerIcon[j][i]->getPos(), kind);
				}
			}
		}
	}

	if (getFadeProgress() > 0.0f)
	{
		return;
	}
	if (Pad::isTrigger(PAD_INPUT_2))
	{
		Sound::getInstance().play("uiCancel");
		setNextScene(new SceneMainMenu);
	}
}

void SceneSelectPlayerNum::updateOut()
{
	if (getFadeProgress() > 0.0f)
	{
		// フェード中も背景動かしたり待機アニメする場合はここで
		return;
	}

	m_pBg->update();
	m_pParticle->update();

	m_pTitle->update();
	m_pTelop->update();
	m_pUi->update();

	for (auto& icon : m_pPlayerIcon[m_decidePlayerNum-2])
	{
		// 加速しながら画面外へ
		Vec2 vec = icon->getVec();
		vec.x += 0.4f;
		icon->setVec(vec);

		icon->update();
	}


	m_frameCount++;
	// 一定フレームをかけて選択されていないアイコンを非表示に
	float iconAlphaRate = static_cast<float>(m_frameCount) / static_cast<float>(kUnselectIconEraseFrame);
	iconAlphaRate = min(iconAlphaRate, 1.0f);
	m_iconAlpha = static_cast<int>(kUnselectIconAlpha * (1.0f - iconAlphaRate));

	// 一定フレーム経過したら終了
	if (m_frameCount > kDecideEffectFrame)
	{
		SceneBase* pMain = new SceneMain{ m_decidePlayerNum, false };
		// 選択したプレイヤーを反映させる
		for (int i = 0; i < m_selectPlayerKind.size(); i++)
		{
			dynamic_cast<SceneMain*>(pMain)->setPlayerKind(i, m_selectPlayerKind[i]);
		}
		setNextScene(pMain);
		return;
	}
}

void SceneSelectPlayerNum::createKindChangeParticle(Vec2 iconPos, int nextKind)
{
	for (int i = 0; i < 128; i++)
	{
		unsigned int color = Player::getColor(nextKind);

		float angle = GetRand(360) * DX_PI_F / 180.0f;
		float speed = GetRand(200) / 100.0f + 2.0f;
	//	float speed = GetRand(3) + 1.0f;

		Vec2 pos = iconPos;
		pos.x -= 2;	// 見た目いい感じにするため微調整

		Vec2 vec;
		vec.x = cosf(angle) * speed;
		vec.y = sinf(angle) * speed;

		std::shared_ptr<Particle> pPart = std::make_shared<Particle>(m_pParticle);
		pPart->init();
		pPart->setPos(pos);
		pPart->setVec(vec);
		pPart->setGravity(0.05f);
		pPart->setRadius(GetRand(2)+1.0f);
		pPart->setColor(color);
		pPart->setExistFrame(30);
		pPart->setAlphaAcc(-8);

		m_pParticle->add(pPart);
	}
}