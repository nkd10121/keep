#include "SceneMain.h"
#include "DxLib.h"
#include "game.h"

#include "Pad.h"
#include "Mouse.h"

#include <string>
#include <cassert>
#include <algorithm>

#include "SaveData.h"
#include "Sound.h"
#include "Message.h"

#include "SceneTitle.h"
#include "SceneMainMenu.h"
#include "Player.h"
#include "PlayerManager.h"
#include "Field.h"
#include "Font.h"
#include "PadUi.h"
#include "PadUiItem.h"
#include "DispRecord.h"
#include "Particle.h"
#include "ParticleManager.h"
#include "EffectString.h"
#include "EffectPlayer.h"
#include "MultiPlayScore.h"

#ifdef _DEBUG
// セーブデータに関係なくチュートリアル飛ばせる
#define SKIP_TUTORIAL
#endif

namespace
{
	// ファイル名
	const char* const kUiBorderFilename = "data/image/ui/WindowBase000.png";
	const char* const kBgTileFilename = "data/image/bg/Brown.png";

	const char* const kBgmFilename0 = "bgmPlayer0";	// ゴーグル
	const char* const kBgmFilename1 = "bgmPlayer1";	// 仮面
	const char* const kBgmFilename2 = "bgmPlayer2";	// カエル
	const char* const kBgmFilename3 = "bgmPlayer3";	// ファンシー
	const char* const kBattleBgmFilename = "bgmBattle";

	const char* const kGameOverBgmFilename = "bgmGameOver";

	// テキスト
	const char* const kSpeedupMessageId = "MSG_PLAY_SPEEDUP";

	// チュートリアル
	struct TutorialData
	{
		const char* messageId;
		bool isAbsPos;	// falseの場合はプレイヤーからの相対位置
		int x;
		int y;
	};
	constexpr TutorialData kTutorialData[] =
	{
		{"MSG_PLAY_TUTORIAL_0", false, 20, -10},
		{"MSG_PLAY_TUTORIAL_1", false, -16, -44},
		{"MSG_PLAY_TUTORIAL_2", false, -16, 24},
		{"MSG_PLAY_TUTORIAL_3", true, Game::kScreenWidth / 2 - 128, 128 + 8},
	};
	constexpr int kTutorialDataNum = _countof(kTutorialData);
	const char* const kTutorialSkipMessageId = "MSG_PLAY_STARTABUTTON";

	// 一人プレイスコア表示位置
	constexpr int kScoreDispX = Game::kScreenWidth - 200;
	constexpr int kScoreDispY = 32;

	// ゲームオーバー演出
	constexpr int kGameOverWaitFrame = 30;
	constexpr int kGameOverFadeAlpha = 192;
	constexpr int kGameOverFadeFrame = 30;

	// ゲームオーバーUI情報
	constexpr int kGameOverButtonWidth = 280;	// ボタンサイズ
	constexpr int kGameOverButtonHeight = 80;
	// 横にボタンを並べる
	constexpr int kGameOverButtonPosX = Game::kScreenWidth / 2 - 200;	// 一番上のボタン中心座標
	constexpr int kGameOverButtonPosY = 600;
	constexpr int kGameOverButtonIntervalX = 400;	// ボタンY座標差分

	enum
	{
		kGameOverButtonRetry,
		kGameOverButtonEnd,

		kGameOverButtonNum
	};
	const char* const kGameOverButtonTextId[] =
	{
		"MSG_PLAY_RETRY",
		"MSG_PLAY_QUIT"
	};
	static_assert(_countof(kGameOverButtonTextId) == kGameOverButtonNum);

	// スピードアップメッセージ表示フレーム
	constexpr int kMessageDispFrame = 60 * 3;

	// ゲームオーバー演出フレーム数
	constexpr int kGameoverFeame = 120;

	// 演出用キャラクター登場間隔
	constexpr int kMobIntervalMin = 30;
	constexpr int kMobIntervalMax = 120;

	// ランキング表示フレーム設定
	constexpr int kRankDispInterval = 10;
	// 一人プレイ	自分の順位を表示する前後の待ち時間
	constexpr int kRankMyRankWaitFrame = 60;
	// 対戦	1位を表示する前の待ち時間
	constexpr int kMultiPlayTopWaitFrame = 90;

	// 背景
#if false
	constexpr unsigned int kBgColor = 0xa0d8ef;
//	constexpr unsigned int kBgColor = 0xb7282e;
#else
	// 背景色情報
	constexpr int kBgChangeColorToSecondScore = 3000;	// 1回目の背景色変更完了距離
	constexpr int kBgChangeColorToThirdScore = 4500;	// 2回目の背景色変更完了距離

	// 初期背景色
	constexpr int kBgColorFirstR = 0xa0;
	constexpr int kBgColorFirstG = 0xd8;
	constexpr int kBgColorFirstB = 0xef;
	// 1回目の変更後カラー
	constexpr int kBgColorSecondR = 0xb7;
	constexpr int kBgColorSecondG = 0x28;
	constexpr int kBgColorSecondB = 0x2e;
	// 2回目の変更後カラー
	constexpr int kBgColorThirdR = 0x29;
	constexpr int kBgColorThirdG = 0x29;
	constexpr int kBgColorThirdB = 0x29;
#endif

	// デモプレイの終了時間
	constexpr int kDemoFrameCount = 30 * 60;
}

SceneMain::SceneMain(int playerNum, bool isDemo) :
	m_playerNum(playerNum),
	m_gameScreen(-1),
	m_fieldGraph(-1),
	m_uiBorder(-1),
	m_bgTile(-1),
	m_mobInterval(0),
	m_tutorialMessageNo(0),
	m_tutorialMessageSinRate(0.0f),
	m_countDownNum(-1),
	m_countDownAlpha(0),
	m_countDownScale(0.0),
	m_isDispMessage(false),
	m_messageFrameCount(0),
	m_messageDispFrame(kMessageDispFrame),
	m_updateFrame(0),
	m_isPause(false),
	m_isDemo(isDemo)
{
	// シーン設定
	setDispLoading(false);	// ロード中表示を行わない

	m_selectPlayerKind.resize(Game::kMaxPlayer, -1);
}

void SceneMain::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	m_fieldGraph = LoadGraph("data/image/field/field.png");
	m_uiBorder = LoadGraph(kUiBorderFilename);
	m_bgTile = LoadGraph(kBgTileFilename);

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneMain::isLoaded() const
{
	if (!Player::isLoaded())	return false;
	if (CheckHandleASyncLoad(m_fieldGraph))	return false;
	if (CheckHandleASyncLoad(m_uiBorder))	return false;
	if (CheckHandleASyncLoad(m_bgTile))	return false;
	return true;
}

void SceneMain::init()
{
	m_gameScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight,true);

	m_pParticle = std::make_shared<ParticleManager>();

//	m_pPlayer = std::make_shared<Player>();
//	m_pPlayer->init();

	m_pField = std::make_shared<Field>(m_isDemo);
	m_pField->setHandle(m_fieldGraph);
//	m_pField->setPlayer(m_pPlayer);
//	m_pField->init();

	// プレイヤーが地形データを参照できるように
//	m_pPlayer->setField(m_pField);
//	m_pPlayer->setParticle(m_pParticle);

	m_pPlayer = std::make_shared<PlayerManager>(m_isDemo);
	m_pPlayer->setField(m_pField);
	m_pPlayer->setParticleManager(m_pParticle);

	for (int i = 0; i < m_playerNum; i++)
	{
		if (isDemo())
		{
			int no = i;
			if (i >= Player::getKindNum())	i = 0;
			m_pPlayer->addPlayer(no);
		}
		else
		{
			m_pPlayer->addPlayer(m_selectPlayerKind[i]);
		}
	}
	m_pField->setPlayerManager(m_pPlayer);
	m_pField->init();

	// ポーズ中に表示するテキスト
	m_pPauseText = std::make_shared<EffectString>();
	m_pPauseText->setupCenter(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 
		Message::getInstance().get_c("MSG_PLAY_PAUSE"), Font::getHandle(Font::Id::GameTitle));
	m_pPauseText->setColor(0xffffff);
	m_pPauseText->setEffect(EffectString::Effect::Vibration);
	//	m_pTitle->startIn(EffectString::In::Fade, 1);
	m_pPauseText->startIn(EffectString::In::None, 0);

	// ゲームオーバー画面UI作成だけしておく
	m_pGameOver = std::make_shared<PadUi>();
	m_pGameOver->setButtonGraph(m_uiBorder);
	m_pGameOver->setLoop(false);

	for (int i = 0; i < kGameOverButtonNum; i++)
	{
	//	m_pGameOver->addItem(i, kGameOverButtonText[i], kGameOverButtonPosX + kGameOverButtonIntervalX * i, kGameOverButtonPosY, kGameOverButtonWidth, kGameOverButtonHeight);
		m_pGameOver->addItem(i, Message::getInstance().get_c(kGameOverButtonTextId[i]),
			kGameOverButtonPosX + kGameOverButtonIntervalX * i, 
			kGameOverButtonPosY, kGameOverButtonWidth, kGameOverButtonHeight);
		m_pGameOver->getItem(i)->start(-1);	// 生成はするがゲームオーバーになるまで始まらない
	}
	// 横に並んだUIの設定
	m_pGameOver->setupHArrange(false);

	m_pPlayer->playSetting();

	// 対戦プレイスコア表示の準備
	if (isMulti())
	{
		int playerNum = m_pPlayer->getPlayerNum();
		for (int i = 0; i < playerNum; i++)
		{
			std::shared_ptr<MultiPlayScore>	pScore = std::make_shared<MultiPlayScore>(m_pPlayer->getPlayer(i), playerNum);
			m_pMultiPlayScore.push_back(pScore);
		}
	}

	if (isDemo())
	{
		m_pDemoText = std::make_shared<EffectString>();
		m_pDemoText->setupCenter(Game::kScreenWidth / 2, 560, Message::getInstance().get_c("MSG_TITLE_START"), Font::getHandle(Font::Id::TitleMenu));
		m_pDemoText->setColor(0xffffff);
		m_pDemoText->setEffect(EffectString::Effect::AlphaBlink);
		m_pDemoText->startIn(EffectString::In::Fade, 8);
	}


	m_updateFrame = 0;
	m_mobInterval = GetRand(kMobIntervalMax - kMobIntervalMin) + kMobIntervalMin;

	m_tutorialMessageNo = 0;
#ifdef SKIP_TUTORIAL
	if(true)
#else
	if (SaveData::getInstance().isGameOn(SaveData::TutorialEnd))
#endif
	{
		// チュートリアル1回見ていたらすぐ飛ばせる
		m_tutorialMessageNo = kTutorialDataNum;
	}
	m_tutorialMessageSinRate = 0.0f;

	if (isDemo())
	{
		m_pPlayer->startDig();
		m_updateFunc = &SceneMain::updatePlay;
		m_updateFrame = 0;
		startDemoRanking();
	}
}

void SceneMain::end()
{
	Sound::getInstance().stop(kGameOverBgmFilename);

	DeleteGraph(m_gameScreen);

	DeleteGraph(m_fieldGraph);
	DeleteGraph(m_uiBorder);
	DeleteGraph(m_bgTile);
}

void SceneMain::update()
{
	(this->*m_updateFunc)();
}

void SceneMain::draw()
{
	// リソースのロードが終わるまでは描画しないのがよさそう
	// (どちらにしろフェード仕切っているので何も見えないはず)
	if (!isLoaded())	return;
	if (!isInitialized())	return;

	// ゲーム画面の生成
	SetDrawScreen(m_gameScreen);

	ClearDrawScreen();
	
	drawBg();

	m_pField->draw();
	for (auto& mob : m_pMob)
	{
		mob->draw();
	}
	m_pParticle->draw();
	m_pPlayer->draw();

	SetDrawScreen(DX_SCREEN_BACK);

	int shakeX = 0;
	int shakeY = 0;
	// ゲームオーバー演出
	if (m_updateFunc == &SceneMain::updateGameover)
	{
		float rate = static_cast<float>(m_updateFrame) / static_cast<float>(kGameoverFeame);
		rate *= rate;
		rate = 1.0f - rate;
		int shakeRange = static_cast<int>(16 * rate);
		if (shakeRange > 0)
		{
			shakeX = GetRand(shakeRange) - shakeRange / 2;
			shakeY = GetRand(shakeRange) - shakeRange / 2;
		}
	}

	DrawGraph(shakeX, shakeY, m_gameScreen,true);
//	DrawRectExtendGraph(0, 0, Game::kScreenWidth, Game::kScreenHeight, Game::kScreenWidth / 4, Game::kScreenHeight / 4, Game::kScreenWidth / 2, Game::kScreenHeight / 2, m_gameScreen, true);
//	DrawRectRotaGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, 0, 0, Game::kScreenWidth, Game::kScreenHeight, 2.0, 0.0, m_gameScreen, true);
//	DrawRectRotaGraph(Game::kScreenWidth / 6, Game::kScreenHeight / 6 * 4, 0, 0, Game::kScreenWidth, Game::kScreenHeight, 2.0, 0.0, m_gameScreen, true);

#if false	// 4画面分割での見え方チェック
	DrawExtendGraph(0, 0, Game::kScreenWidth/2, Game::kScreenHeight/2,
		m_gameScreen, true);
	DrawExtendGraph(Game::kScreenWidth / 2, 0, Game::kScreenWidth, Game::kScreenHeight / 2,
		m_gameScreen, true);
	DrawExtendGraph(0, Game::kScreenHeight / 2, Game::kScreenWidth / 2, Game::kScreenHeight,
		m_gameScreen, true);
	DrawExtendGraph(Game::kScreenWidth / 2, Game::kScreenHeight / 2, Game::kScreenWidth, Game::kScreenHeight,
		m_gameScreen, true);
#endif
	
	// 移動距離の表示
	drawScore();

	// ゲームメッセージ表示
	drawMessage();
	drawTutorial();

	// カウントダウン演出
	if(m_countDownNum >= 0)
	{
		std::string dispStr = std::to_string(m_countDownNum);
		int width = GetDrawStringWidthToHandle(dispStr.c_str(), static_cast<int>(strlen(dispStr.c_str())), Font::getHandle(Font::Id::CountDown));
		int height = Font::getSize(Font::Id::CountDown);

		width = static_cast<int>(width * (1.0 - m_countDownScale));
		height = static_cast<int>(height * (1.0 + m_countDownScale));

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_countDownAlpha);
	//	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 255);
	//	Font::drawStringCenter(240, std::to_string(m_countDownNum).c_str(), 0xff0000, Font::Id::CountDown);
		DrawExtendStringToHandle(Game::kScreenWidth / 2 - width / 2, 360 - height / 2, (1.0 - m_countDownScale), (1.0 + m_countDownScale), dispStr.c_str(), 0xff0000, Font::getHandle(Font::Id::CountDown));
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}

	// リザルト画面
	if (m_updateFunc == &SceneMain::updateResult)
	{
		if (m_pRecord)	m_pRecord->draw();

		m_pGameOver->draw();
	}

	// デモ	常にランキング表示
	if (isDemo())
	{
		if (m_pRecord)	m_pRecord->draw();
		if (m_pDemoText)	m_pDemoText->draw();
	}

	if (m_isPause)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 128);
		DrawBox(0,0,Game::kScreenWidth, Game::kScreenHeight,0x000000, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	//	Font::drawStringCenter(240,"ポーズ", 0xffffff, Font::Id::GameTitle);
		m_pPauseText->draw();
	}
}

#ifdef _DEBUG
void SceneMain::drawDebug()
{
	if (!isInitialized())	return;
	if (!isLoaded())	return;

	DrawString(8, 8, "SceneMain", 0xffffff);
	DrawFormatString(8, 8 + 16, 0xffffff, "SCROLL(%.2f,%.2f)", m_pPlayer->getPlayer(0)->getScroll().x, m_pPlayer->getPlayer(0)->getScroll().y);
	DrawFormatString(8, 8 + 32, 0xffffff, "TEMPO:%d", m_pPlayer->getPlayer(0)->getTempo());
}
#endif

void SceneMain::setPlayerKind(int playerNo, int kind)
{
	m_selectPlayerKind[playerNo] = kind;
}


void SceneMain::updateWait()
{
	m_pPlayer->update();
	m_pField->update();
	m_pParticle->setScroll(m_pPlayer->getScroll());
	m_pParticle->update();
	for (auto& score : m_pMultiPlayScore)
	{
		score->update();
	}

	if (getFadeProgress() > 0.0f)
	{
		return;
	}

	m_tutorialMessageSinRate += 0.05f;
	if (m_tutorialMessageSinRate >= DX_TWO_PI_F * 3)
	{
		m_tutorialMessageNo++;
		// 何周したかカウントできるよう増やし続けるので戻さない
	//	if (m_tutorialMessageNo >= kTutorialDataNum)
	//	{
	//		m_tutorialMessageNo = 0;
	//	}
		m_tutorialMessageSinRate = 0;
	}

//	updateMob();
	m_updateFrame++;
	bool isEnd = false;
	if (isMulti())
	{
		// 対戦モード	時間経過でスタート
		if (m_updateFrame > 180)
	//	if(false)
		{
			isEnd = true;
		}
	}
	else
	{
		// 一人	Aボタンでスタート
		if(m_tutorialMessageNo >= kTutorialDataNum && (Pad::isTrigger(PAD_INPUT_1)))
		{
			isEnd = true;
		}
	}
	
	if(isEnd)
	{
		// チュートリアル初回終了フラグを立てる
		if (!isMulti() && !SaveData::getInstance().isGameOn(SaveData::TutorialEnd))
		{
			SaveData::getInstance().gameFlagOn(SaveData::TutorialEnd);
			SaveData::getInstance().write();
		}

		m_pPlayer->startIdling();
		m_updateFunc = &SceneMain::updateCountdown;
		Sound::getInstance().play("countDown");
		m_updateFrame = 0;
		// カウントダウン初期化
		m_countDownNum = 3;
		m_countDownAlpha = 180;
		m_countDownScale = 0.0;
		
	}
}

void SceneMain::updateCountdown()
{
	m_pPlayer->update();
	m_pField->update();
	m_pParticle->setScroll(m_pPlayer->getScroll());
	m_pParticle->update();
	for (auto& score : m_pMultiPlayScore)
	{
		score->update();
	}

	if (getFadeProgress() > 0.0f)
	{
		return;
	}

//	updateMob();

	m_updateFrame++;
	m_countDownAlpha = 180 - m_updateFrame * 3 * 1;
	if (m_updateFrame < 30)
	{
		m_countDownScale = 0.0;
	}
	else
	{
		float rate = static_cast<float>((m_updateFrame - 30)) / 30.0f;
		rate *= rate;
	//	rate = 1.0f - rate;
	//	m_countDownScale = 0.0 + (m_updateFrame - 30) * 0.03;
		m_countDownScale = rate * 1.0;
	}

	if (m_updateFrame >= 60)
	{
		m_countDownNum--;
		if (m_countDownNum <= 0)
		{
			Sound::getInstance().playBgm(getBgmName());
			Sound::getInstance().setVolume(getBgmName(), 0);

			Sound::getInstance().play("gameStart");
			m_pPlayer->startDig();
			m_updateFunc = &SceneMain::updatePlay;
			m_updateFrame = 0;

			// カウントダウン表示消す
			m_countDownNum = -1;
		}
		else
		{
		//	m_updateFunc = &SceneMain::updateCountdown;

			Sound::getInstance().play("countDown");
			// カウントダウン初期化
			m_updateFrame = 0;
			m_countDownAlpha = 60;
			m_countDownScale = 0.0;
		}
	}
}

void SceneMain::updatePlay()
{
	if (getFadeProgress() > 0.0f)
	{
		return;
	}

	if (m_isPause)
	{
		float volRate = static_cast<float>(m_updateFrame) / 60.0f;
		volRate = min(volRate, 1.0f);
		volRate *= 0.5f;	// ポーズ中音量半分
		Sound::getInstance().setVolume(getBgmName(), static_cast<int>(volRate * 255));

		m_pPauseText->update();
		if (Pad::isTrigger(PAD_INPUT_8))
		{
			Sound::getInstance().play("uiCancel");
			m_isPause = false;
		}
		return;
	}

	updateMob();
	m_updateFrame++;
//	printfDx("frame : %d\n", m_updateFrame);

	// BGM音量
	float volRate = static_cast<float>(m_updateFrame) / 60.0f;
	volRate = min(volRate, 1.0f);
	Sound::getInstance().setVolume(getBgmName(), static_cast<int>(volRate * 255));

	int lastTempo = m_pPlayer->getMaxTempo();

	m_pPlayer->update();
	m_pField->update();
	m_pParticle->setScroll(m_pPlayer->getScroll());
	m_pParticle->update();
	for (auto& score : m_pMultiPlayScore)
	{
		score->update();
	}

	// メッセージ表示の更新
	if (m_isDispMessage)
	{
		m_messageFrameCount++;
		if (m_messageFrameCount >= m_messageDispFrame)
		{
			m_isDispMessage = false;
			m_messageFrameCount = 0;
		}
	}

	if (lastTempo < m_pPlayer->getMaxTempo())
	{
		// スピードアップした瞬間
		Sound::getInstance().setSpeed(getBgmName(), m_pPlayer->getMaxDt());

		// 一人プレイの場合はスピードアップ表示
		if (!isMulti())
		{
			Sound::getInstance().play("speedUp", m_pPlayer->getPlayer(0)->getDt());
			m_isDispMessage = true;
			m_messageFrameCount = 0;
			m_messageDispFrame = static_cast<int>(kMessageDispFrame / m_pPlayer->getPlayer(0)->getDt());
		}
	}

	// 死んだ瞬間
	if(m_pPlayer->getActiveNum() <= 0)	// 全滅で終了
	{
		m_updateFunc = &SceneMain::updateGameover;
		m_updateFrame = 0;
	}

	// ポーズ	対戦ではポーズ不可
	if (!isMulti() && Pad::isTrigger(PAD_INPUT_8))
	{
		Sound::getInstance().play("uiDecide");
		m_isPause = true;
	}

	// デモプレイ専用の処理
	if (isDemo())
	{
		if (m_pRecord)
		{
			m_pRecord->update();
		}
		if (m_pDemoText)
		{

			m_pDemoText->update();
		}
		if ( Pad::isTrigger(PAD_INPUT_1) ||
			Pad::isTrigger(PAD_INPUT_2) ||
			(m_updateFrame >= kDemoFrameCount))
		{
			setNextScene(new SceneTitle);
		}
	}
}

void SceneMain::updateGameover()
{
	if (getFadeProgress() > 0.0f)
	{
		return;
	}
	updateMob();
	m_updateFrame++;

	// BGM音量
	float volRate = static_cast<float>(m_updateFrame) / 60.0f;
	volRate = min(volRate, 1.0f);
	volRate = 1.0f - volRate;
	Sound::getInstance().setVolume(getBgmName(), static_cast<int>(volRate * 255));

	m_pPlayer->update();
	m_pField->update();
	m_pParticle->setScroll(m_pPlayer->getScroll());
	m_pParticle->update();
	for (auto& score : m_pMultiPlayScore)
	{
		score->update();
	}
	if (m_updateFrame >= kGameoverFeame)
	{
		Sound::getInstance().stop(getBgmName());

		if (!isMulti())
		{
			// スコアを登録
			int score = m_pPlayer->getPlayer(0)->getScore();
			int rank = SaveData::getInstance().entryScore(score, m_pPlayer->getPlayer(0)->getKind());
			if (rank >= 0)
			{
				// ランクインしたのでセーブ
				SaveData::getInstance().write();
			}
			startGameOver(rank);

			Sound::getInstance().playBgm(kGameOverBgmFilename);
			Sound::getInstance().setVolume(kGameOverBgmFilename, 0);
		}
		else
		{
			startBattleResult();

			Sound::getInstance().playBgm(kGameOverBgmFilename);
			Sound::getInstance().setVolume(kGameOverBgmFilename, 0);
		}
		
		m_updateFunc = &SceneMain::updateResult;
		m_updateFrame = 0;
	}
}

void SceneMain::updateResult()
{
	if (getFadeProgress() > 0.0f)
	{
		float rate = 1.0f - getFadeProgress();
		int vol = static_cast<int>(rate * 255);
		Sound::getInstance().setVolume(kGameOverBgmFilename, vol);
		return;
	}

	updateMob();
	m_updateFrame++;

	// 音量変化
//	if (!isMulti())
	{
		float rate = static_cast<int>(m_updateFrame) / 8.0f;
		rate = min(rate, 1.0f);
		int vol = static_cast<int>(rate * 255);
		Sound::getInstance().setVolume(kGameOverBgmFilename, vol);
	}

	
	m_pPlayer->update();
	m_pField->update();
	m_pParticle->setScroll(m_pPlayer->getScroll());
	m_pParticle->update();
	for (auto& score : m_pMultiPlayScore)
	{
		score->update();
	}

	if (m_pRecord)
	{
		m_pRecord->update();
		if (m_pRecord->isDispEnd())
		{
			int result = m_pGameOver->update();
			if (result == 0)
			{
				// リトライ
				SceneBase* pMain = new SceneMain{ m_playerNum, false };
				if (m_playerNum > 1)
				{
					// 複数人プレイの場合最初に選んだキャラクターをそのまま反映
					for (int i = 0; i < m_playerNum; i++)
					{
						dynamic_cast<SceneMain*>(pMain)->setPlayerKind(i, m_selectPlayerKind[i]);
					}
				}

				setNextScene(pMain);
			}
			else if (result == 1)
			{
				// ヤメル
				setNextScene(new SceneMainMenu);
			}
		}
	}
}

void SceneMain::drawTutorial()
{
	if (m_updateFunc != &SceneMain::updateWait)	return;
	if (isMulti())
	{
		drawTutorialMulti();
	}
	else
	{
		drawTutorialSingle();
	}
}

void SceneMain::drawTutorialSingle()
{
	int messageNo = m_tutorialMessageNo % kTutorialDataNum;

	TutorialData data = kTutorialData[messageNo];
	int x = data.x;
	int y = data.y;
	if (!data.isAbsPos)
	{
		Vec2 pos = m_pPlayer->getPlayer(0)->getPos() + m_pPlayer->getScroll();
		x += static_cast<int>(pos.x);
		y += static_cast<int>(pos.y);
	}
	//	float rate = (sinf(m_tutorialMessageSinRate) * 0.5f + 0.5f);
	float rate = (cosf(m_tutorialMessageSinRate + DX_PI_F) * 0.5f + 0.5f);	// いい感じに非表示の時にメッセージが切り替わるよう計算
	int alpha = static_cast<int>(255 * rate);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	Font::drawString(x, y, Message::getInstance().get_c(data.messageId), 0xffffff, Font::Id::PlayTutorial);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_tutorialMessageNo >= kTutorialDataNum)
	{
		y = 60 + static_cast<int>(sinf(m_tutorialMessageSinRate) * 16);
		Font::drawStringCenter(y, Message::getInstance().get_c(kTutorialSkipMessageId), 0xff0000, Font::Id::TutorialSkip);
	}
}

void SceneMain::drawTutorialMulti()
{
	float rate = (cosf(m_tutorialMessageSinRate + DX_PI_F) * 0.5f + 0.5f);
	int alpha = static_cast<int>(255 * rate);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
	for (int y = 160; y <= 640; y += 80)
	{
		Font::drawString(8, y, Message::getInstance().get_c("MSG_PLAY_TUTORIAL_MULTI"), 0xffffff, Font::Id::PlayTutorial);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void SceneMain::drawBg()
{
#if false
	// 空色の背景
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight / 4, kBgColor, true);	// 上のほうしか見えないので全部は塗りつぶさない
#else
	int score = m_pPlayer->getMaxScore();
	int r = 0;
	int g = 0;
	int b = 0;

	if (score >= kBgChangeColorToThirdScore)
	{
		// 3
		r = kBgColorThirdR;
		g = kBgColorThirdG;
		b = kBgColorThirdB;
	}
	else if (score >= kBgChangeColorToSecondScore)
	{
		// 2 -> 3
		int tempMax = kBgChangeColorToThirdScore - kBgChangeColorToSecondScore;
		int tempVal = score - kBgChangeColorToSecondScore;
		float rate = static_cast<float>(tempVal) / static_cast<float>(tempMax);

		r = kBgColorSecondR * (1.0f - rate) + kBgColorThirdR * rate;
		g = kBgColorSecondG * (1.0f - rate) + kBgColorThirdG * rate;
		b = kBgColorSecondB * (1.0f - rate) + kBgColorThirdB * rate;
	}
	else
	{
		// 1 -> 2
		float rate = static_cast<float>(score) / static_cast<float>(kBgChangeColorToSecondScore);

		r = kBgColorFirstR * (1.0f - rate) + kBgColorSecondR * rate;
		g = kBgColorFirstG * (1.0f - rate) + kBgColorSecondG * rate;
		b = kBgColorFirstB * (1.0f - rate) + kBgColorSecondB * rate;
	}

	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight / 4, GetColor(r, g, b), true);	// 上のほうしか見えないので全部は塗りつぶさない
#endif
}

void SceneMain::drawScore()
{
	// デモプレイはスコア表示なし
	if (isDemo())	return;

	if (isMulti())
	{
		for(auto& score : m_pMultiPlayScore)
		{
			score->draw();
		}
	}
	else
	{
		int score = m_pPlayer->getPlayer(0)->getScore();
		drawScoreSingle(kScoreDispX, kScoreDispY, score);
	}
}

void SceneMain::drawScoreSingle(int x, int y, int score)
{
	const int font = Font::getHandle(Font::Id::GameScore);
	int numWidth = GetDrawFormatStringWidthToHandle(font, "%d", score);
	DrawFormatStringToHandle(x - numWidth - 2, y, 0xffffff, font, "%d", score);
	if (score == 1)
	{
		DrawFormatStringToHandle(x + 2, y, 0xffffff, font, Message::getInstance().get_c("MSG_COMMON_UNIT"));
	}
	else
	{
		DrawFormatStringToHandle(x + 2, y, 0xffffff, font, Message::getInstance().get_c("MSG_COMMON_UNITS"));
	}
}

void SceneMain::drawMessage()
{
	if (!m_isDispMessage)	return;

	int font = Font::getHandle(Font::Id::GameMessage);

	const char* speedUpText = Message::getInstance().get_c(kSpeedupMessageId);
	int width = GetDrawStringWidthToHandle(speedUpText, static_cast<int>(strlen(speedUpText)), font);
	int start = Game::kScreenWidth;
	int end = -width;
	int center = (end - start) / 2 + start;

	int x = 0;
	if (m_messageFrameCount < m_messageDispFrame / 3)
	{
		// in
		float rate = static_cast<float>(m_messageFrameCount) / static_cast<float>(m_messageDispFrame/3);
		rate *= rate;
		x = static_cast<int>(center * rate + start * (1.0f - rate));
	}
	else if (m_messageFrameCount < m_messageDispFrame / 3 * 2)
	{
		// stop
		x = center;
	}
	else
	{
		// out
		int now = m_messageFrameCount - m_messageDispFrame / 3 * 2;
		int total = m_messageDispFrame / 3;

		float rate = static_cast<float>(now) / static_cast<float>(total);
		rate *= rate;
		x = static_cast<int>(end * rate + center * (1.0f - rate));
	}

	Font::drawString(x, 24, speedUpText, 0xff0000, Font::Id::GameMessage);
}

void SceneMain::startGameOver(int rank)
{
	for (int i = 0; i < kGameOverButtonNum; i++)
	{
	//	m_pGameOver->getItem(i)->start(kGameOverWaitFrame + kGameOverFadeFrame + i * 8);
		m_pGameOver->getItem(i)->start(1);
	}

	m_pRecord = std::make_shared<DispRecord>();
	m_pRecord->setupTitle(DispRecord::TitleType::Gameover);
	// セーブデータの記録を表示データとして登録
	for (int i = 0; i < SaveData::kSaveRankDataNum; i++)
	{
		m_pRecord->addData(i, i, SaveData::getInstance().getRankPlayerScore(i), SaveData::getInstance().getRankPlayerKind(i));
	}

	int waitFrame = 0;
	for (int i = SaveData::kSaveRankDataNum - 1; i >= 0; i--)
	{
		// 自分の順位はもったいぶって表示する
		// 自分の順位表示前後にウェイト
		if(i == rank)		waitFrame += kRankMyRankWaitFrame;
		if (i == rank-1)	waitFrame += kRankMyRankWaitFrame;
		
		m_pRecord->setDispWait(i, waitFrame);
		waitFrame += kRankDispInterval;
	}

	m_pRecord->setBgAlpha(kGameOverFadeAlpha);
	if (rank >= 0)
	{
		// 自分の順位を強調表示
		m_pRecord->setHighlightRank(rank);
	}
}

void SceneMain::startBattleResult()
{
	for (int i = 0; i < kGameOverButtonNum; i++)
	{
	//	m_pGameOver->getItem(i)->start(kGameOverWaitFrame + kGameOverFadeFrame + i * 8);
		m_pGameOver->getItem(i)->start(1);
	}

	m_pRecord = std::make_shared<DispRecord>();
	m_pRecord->setupTitle(DispRecord::TitleType::MultiResult);

	// スコア順に並べ替える
	struct TempScore
	{
		int playerNo;
		int kind;
		int score;
	};
	std::vector<TempScore>	tempData;
	// プレイヤーのスコアを登録
	for (int i = 0; i < m_pPlayer->getPlayerNum(); i++)
	{
		TempScore data;
		data.playerNo = i;
		data.kind = m_pPlayer->getPlayer(i)->getKind();
	//	data.score = m_pPlayer->getPlayer(i)->getScore();
		data.score = m_pPlayer->getPlayer(i)->getPlayFrame();	// 対戦は生きのこり時間を競う
		tempData.push_back(data);
	}

	std::sort(tempData.begin(), tempData.end(),
		[](TempScore x, TempScore y) -> int {
			return (x.score > y.score);
		});

	
	int index = 0;
	int rank = 0;
	int lastScore = -1;

	// 順位ごとに一緒に表示したいので各プレイヤーの順位を覚えておく
	std::vector<int>	rankTbl;
	rankTbl.resize(m_pPlayer->getPlayerNum());

	for (auto& data : tempData)
	{
		// 同じスコアは同じ順位表示
		if ((lastScore != -1) && (lastScore > data.score))
		{
			rank = index;
		}
		m_pRecord->addData(index, rank, data.score, data.kind, data.playerNo, m_playerNum);
		rankTbl[index] = rank;
		if (rank == 0)
		{
			// 1位を強調表示
			m_pRecord->setHighlightRank(index);
		}

		lastScore = data.score;
		index++;
	}

	int waitFrame = 0;
	int lastRank = rankTbl[m_pPlayer->getPlayerNum() - 1];
	for (int i = m_pPlayer->getPlayerNum() - 1; i >= 0; i--)
	{
		if (lastRank != rankTbl[i])
		{
			// 同じ順位は同時に表示するので前の人と順位が違う場合のみ待ち時間を更新
			if(rankTbl[i] == 0)	waitFrame += kMultiPlayTopWaitFrame;
			else				waitFrame += kRankDispInterval;
		}
		lastRank = rankTbl[i];

		m_pRecord->setDispWait(i, waitFrame);
	}

	m_pRecord->setBgAlpha(kGameOverFadeAlpha);
	
}

void SceneMain::updateMob()
{
	m_mobInterval--;
	if (m_mobInterval <= 0)
	{
		m_mobInterval = GetRand(kMobIntervalMax - kMobIntervalMin) + kMobIntervalMin;

		std::shared_ptr<EffectPlayer> pPlayer = std::make_shared<EffectPlayer>();
		pPlayer->setupPlayMob(m_pPlayer->getMaxDt());
		m_pMob.push_back(pPlayer);
	}

	for (auto& mob : m_pMob)
	{
		mob->update();
		createMobParticle(mob);
	}
	// 画面外に出たら削除
	m_pMob.remove_if(
		[](auto& player) {
			return !player->isExist();
		});
}

void SceneMain::createMobParticle(std::shared_ptr<EffectPlayer> pMob)
{
	unsigned int color = Player::getColor(pMob->getPlayerKind());
	Vec2 mobVec = pMob->getVec();

	for (int i = 0; i < 3; i++)
	{
		Vec2 pos = pMob->getPos() - m_pPlayer->getScroll();

		if (mobVec.x > 0)
		{
			pos.x += -GetRand(8) - 2;
		}
		else
		{
			pos.x += GetRand(8) + 2;
		}
		pos.y += 12;

		float vecX = static_cast<float>(GetRand(200));
		vecX /= 100.0f;
		if (mobVec.x > 0)	vecX *= -1.0f;
		float vecY = static_cast<float>(-GetRand(80) - 80);
		vecY /= 40;

		std::shared_ptr<Particle> pPart = std::make_shared<Particle>(m_pParticle);
		pPart->init();
		pPart->setPos(pos);
		pPart->setVec(Vec2{ vecX, vecY });
		pPart->setGravity(0.5f);
		pPart->setRadius(1.0f);
		pPart->setColor(color);
		pPart->setExistFrame(16);
		pPart->setAlphaAcc(-16);

		m_pParticle->add(pPart);
	}
}

const char* SceneMain::getBgmName()
{
	if (isMulti())
	{
		return kBattleBgmFilename;
	}
	else
	{
		switch (m_pPlayer->getPlayer(0)->getKind())
		{
		default:	assert(false);
		case 0:
			return kBgmFilename0;
		case 1:
			return kBgmFilename1;
		case 2:
			return kBgmFilename2;
		case 3:
			return kBgmFilename3;
		}
	}
	assert(false);
}

bool SceneMain::isMulti()
{
	return (m_pPlayer->getPlayerNum() > 1);
}

bool SceneMain::isDemo()
{
	return m_isDemo;
}

void SceneMain::startDemoRanking()
{
	m_pRecord = std::make_shared<DispRecord>();
	m_pRecord->setupTitle(DispRecord::TitleType::Ranking);
	m_pRecord->setBgAlpha(128);
	// セーブデータの記録を表示データとして登録
	for (int i = 0; i < SaveData::kSaveRankDataNum; i++)
	{
		m_pRecord->addData(i, i, SaveData::getInstance().getRankPlayerScore(i), SaveData::getInstance().getRankPlayerKind(i));
	}
	int waitFrame = 0;
	for (int i = SaveData::kSaveRankDataNum - 1; i >= 0; i--)
	{
		// 最初から全部表示
		m_pRecord->setDispWait(i, waitFrame);
	}
}
