#include "SceneTitle.h"
#include "DxLib.h"
#include "Pad.h"
#include "game.h"

#include "SceneMainMenu.h"
#include "SceneMain.h"
#include "Font.h"
#include "Vec2.h"
#include "StrUtil.h"

#include "Sound.h"
#include "Message.h"
#include "PadUi.h"
#include "PadUiItem.h"

#include "Player.h"
#include "EffectPlayer.h"
#include "EffectString.h"

#include <cassert>

namespace
{
	// グラフィックファイル名
//	const char* const kBgTileFilename = "data/image/bg/Yellow.png";
	const char* const kBgTileFilename = "data/image/bg/Gray.png";
	
	// タイトルロゴに使用するフォント
	constexpr Font::Id kTitleFont = Font::Id::GameTitle;

	// タイトルロゴ登場演出フレーム数
	constexpr int kTitleStartFrame = 150;
	// タイトルロゴフレーム落ち演出	何フレームに１回表示を更新するか
	constexpr int kTitleUpdateFrame = 8;

	// 背景暗くなるフレーム数
	constexpr int kBgFadeFrame = 1;
	// 背景クラスするフェードのアルファ
//	constexpr int kBgFadeAlpha = 64;
	constexpr int kBgFadeAlpha = 0;

	// タイトルロゴ色
	constexpr unsigned int kTitleColor = 0xff420e;
	constexpr unsigned int kTitleEdgeColor = 0xfff0f0;
	constexpr unsigned int kTitleShadowColor = 0xf98866;

	// タイトルロゴサイズ
	constexpr int kTitleFontSize = 192;
	constexpr int kTitleFontEdgeSize = 20;
	constexpr int kTitleShadowOffsetY = 16;	// タイトルちょっとずらして2重表示

	constexpr int kLogoGraphHeight = kTitleFontSize + kTitleFontEdgeSize + kTitleShadowOffsetY + 16;	// ちょっと上にはみ出すフォントなので調整

	// タイトルロゴ表示位置下辺(左右は中央に配置、上辺はロゴサイズによる)
	constexpr int kTitleBottomY = Game::kScreenHeight / 2;
	// タイトルロゴの文字詰め
	constexpr int  kLogoKerning = 48;
	
	// デモが始まるまでの待ち時間
	constexpr int kDemoWaitFrame = 45 * 60;
}

SceneTitle::SceneTitle():
	m_bgScreen(-1),
	m_bgTile(-1),
	m_titleGraph(-1),
	m_titleFontHandle(-1),
	m_titleWidth(0),
	m_loadFrameCount(0),
	m_titleFrameCount(0),
	m_bgScroll(0),
	m_demoWaitFrame(0)
{
}

SceneTitle::~SceneTitle()
{
}

void SceneTitle::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	m_bgTile = LoadGraph(kBgTileFilename);

	// タイトルでしか使わないフォント
	m_titleFontHandle = CreateFontToHandle("GN-キルゴUかなNA", kTitleFontSize, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, kTitleFontEdgeSize);

	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

bool SceneTitle::isLoaded() const
{
	// 常駐リソースのロード完了確認
	if (!Player::isLoaded())	return false;

	if (CheckHandleASyncLoad(m_bgTile))	return false;
	if (CheckHandleASyncLoad(m_titleFontHandle))	return false;

	return true;
}

void SceneTitle::init()
{
	m_bgScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// タイトルロゴの生成
	createLogoGraph();

	m_pText = std::make_shared<EffectString>();
	m_pText->setupCenter(Game::kScreenWidth / 2, 560, Message::getInstance().get_c("MSG_TITLE_START"), Font::getHandle(Font::Id::TitleMenu));
	m_pText->setColor(0xffffff);
	m_pText->setEffect(EffectString::Effect::AlphaBlink);
	m_pText->startIn(EffectString::In::Fade, 8);

	// タイトル演出の初期化
	m_loadFrameCount = 0;
	m_titleFrameCount = 0;
}

void SceneTitle::end()
{
	Sound::getInstance().stop("bgmTitle");
	DeleteGraph(m_bgScreen);

	DeleteGraph(m_bgTile);
	DeleteGraph(m_titleGraph);

	DeleteFontToHandle(m_titleFontHandle);
}

void SceneTitle::update()
{
	(this->*m_updateFunc)();
}

void SceneTitle::draw()
{
	if (!isLoaded())	return;
	drawBg();

	for (auto& player : m_pPlayer)
	{
		player->draw();
	}

#ifdef EX_VER	// エンクリバージョン
	if (Font::isLoaded())
	{
		int width = Font::getStringWidth(Game::kExVerName, Font::Id::Size24_4);
		Font::drawString(Game::kScreenWidth - width - 8, Game::kScreenHeight - 32, Game::kExVerName, 0xffffff, Font::Id::Size24_4);
	}
#endif

	drawTitleLogo();

	m_pText->draw();
}

void SceneTitle::updateLoadWait()
{
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

	m_loadFrameCount++;
	if( (m_loadFrameCount >= 8) && (!isLoading) )
	{
		m_loadFrameCount = 0;

	//	//	// タイトルロゴの生成
	//	createLogoGraph();
		
		// ロードしたリソースの情報収集を行う
		// サウンドの情報収集
		Sound::getInstance().collectData();
#if false	// 処理重いので止まらないようメインメニュー開始のタイミングで止める
	//	// フォントの情報収集
	//	Font::collectData();
#endif
		// updateTitleAppearに切り替え
		m_updateFunc = &SceneTitle::updateTitleAppear;

		Sound::getInstance().play("jingle");
		Sound::getInstance().play("titleStart");

		Sound::getInstance().playBgm("bgmTitle");
		Sound::getInstance().setVolume("bgmTitle", 0);
	}
}

void SceneTitle::updateTitleAppear()
{
	int lastTitleFrame = m_titleFrameCount;
	m_titleFrameCount++;

	m_bgScroll++;
	if (m_bgScroll >= 64)	m_bgScroll -= 64;

	float volRate = static_cast<float>(m_titleFrameCount) / static_cast<float>(kTitleStartFrame);
	volRate = 1.0f - volRate;
	int vol = static_cast<int>(255 * volRate);
	Sound::getInstance().setVolume("titleStart", vol);

	Sound::getInstance().setVolume("bgmTitle", 255 - vol);

	if ( (lastTitleFrame < kTitleStartFrame && m_titleFrameCount >= kTitleStartFrame) ||
		(Pad::isTrigger(PAD_INPUT_1)) )
	{
		Sound::getInstance().setVolume("bgmTitle", 255);

	//	Sound::getInstance().play("fanfare");
		// 登場演出スキップ
		m_titleFrameCount = kTitleStartFrame;

		// updateWaitに切り替え
		m_updateFunc = &SceneTitle::updateWait;
		m_demoWaitFrame = 0;
	}
}

void SceneTitle::updateWait()
{
	if (getFadeProgress() > 0.0f)
	{
		int vol = static_cast<int>(255 * (1.0f - getFadeProgress()));
		Sound::getInstance().setVolume("bgmTitle", vol);
		return;
	}

	m_bgScroll++;
	if (m_bgScroll >= 64)	m_bgScroll -= 64;
	m_demoWaitFrame++;

	m_pText->update();

	if (Pad::isTrigger(PAD_INPUT_1) || Pad::isTrigger(PAD_INPUT_2))
	{
		setNextScene(new SceneMainMenu);
	}
	else if (m_demoWaitFrame > kDemoWaitFrame)
	{
		setNextScene(new SceneMain{Player::getKindNum(),true});
	}

	{
		// 毎フレーム背景演出プレイヤー1体生成
		std::shared_ptr<EffectPlayer> pPlayer = std::make_shared<EffectPlayer>();
		pPlayer->setupTitle();
		m_pPlayer.push_back(pPlayer);
	}

	for (auto& player : m_pPlayer)
	{
		player->update();
	}
	// 画面外に出たら削除
	m_pPlayer.remove_if(
		[](auto& player) {
			return !player->isExist();
		});
}

void SceneTitle::createLogoGraph()
{
	assert(!CheckHandleASyncLoad(m_titleFontHandle));

	// タイトルを1文字ずつ分解
	std::vector<std::string>	splitTitle = StrUtil::splitString(Message::getInstance().get_c("MSG_GAMETITLE"));

	// 文字の横幅をチェックして必要なグラフィックのサイズを計算
	m_titleWidth = 0;
	for (auto& chr : splitTitle)
	{
		const char* pText = chr.c_str();
		m_titleWidth += GetDrawStringWidthToHandle(pText, static_cast<int>(strlen(pText)), m_titleFontHandle);
		m_titleWidth -= kLogoKerning;
	}
	m_titleWidth += kLogoKerning;	// 最後の文字の文字詰めの分は戻しておく

	m_titleGraph = MakeScreen(m_titleWidth, kLogoGraphHeight, true);
//	m_titleGraph = MakeScreen(m_titleWidth, kLogoGraphHeight, false);	// アルファを無効にしてグラフィックをわかりやすくするためのテスト

	SetDrawScreen(m_titleGraph);

	// 1文字ずつ詰めて描画
	int x = 0;

	for (auto& chr : splitTitle)
	{
		const char* pText = chr.c_str();

	//	printfDx("%s : (%d, %d)\n", pText, x, 16 + kTitleShadowOffsetY);

		DrawStringToHandle(x, 16 + kTitleShadowOffsetY, pText, kTitleShadowColor, m_titleFontHandle, kTitleShadowColor);
		x += GetDrawStringWidthToHandle(pText, static_cast<int>(strlen(pText)), m_titleFontHandle);
		x -= kLogoKerning;
	}

	x = 0;
	for (auto& chr : splitTitle)
	{
		const char* pText = chr.c_str();

	//	printfDx("%s : (%d, %d)\n", pText, x, 16 + kTitleShadowOffsetY);

		DrawStringToHandle(x, 16, pText, kTitleColor, m_titleFontHandle, kTitleEdgeColor);
		x += GetDrawStringWidthToHandle(pText, static_cast<int>(strlen(pText)), m_titleFontHandle);
		x -= kLogoKerning;
	}
#if false	// タイトルロゴをグラフィックで出力
	SaveDrawScreenToPNG(0, 0, m_titleWidth, kLogoGraphHeight, "save.png");
#endif
	SetDrawScreen(DX_SCREEN_BACK);
}

void SceneTitle::drawTitleLogo()
{
	int tempFrame = m_titleFrameCount;
	if (tempFrame < kTitleStartFrame)
	{
		tempFrame /= kTitleUpdateFrame;
		tempFrame *= kTitleUpdateFrame;
	}

	float rate = static_cast<float>(tempFrame) / static_cast<float>(kTitleStartFrame);
	if (rate > 1.0f)	rate = 1.0f;
	rate *= rate;
	float revRate = 1.0f - rate;

	// 完成時の矩形
	const int left = Game::kScreenWidth / 2 - m_titleWidth / 2;
	const int right = Game::kScreenWidth / 2 + m_titleWidth / 2;
	const int bottom = kTitleBottomY;
	const int top = bottom - kLogoGraphHeight;

	DrawModiGraph(static_cast<int>(left + kLogoGraphHeight / 2 * revRate),
		static_cast<int>(top + kLogoGraphHeight * revRate),
		static_cast<int>(right - kLogoGraphHeight / 2 * revRate),
		static_cast<int>(top + kLogoGraphHeight * revRate),
		right, bottom,
		left, bottom,
		m_titleGraph, true);
}

void SceneTitle::drawBg()
{
	constexpr int kLineNum = 16;

	const int kCenterX = Game::kScreenWidth / 2;
	const int kCenterY = kTitleBottomY - kLogoGraphHeight / 2 - 32;
//	const int kCenterY = Game::kScreenHeight / 2;

	SetDrawScreen(m_bgScreen);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, 8);
	for (int x = 0; x < Game::kScreenWidth; x += 64)
	{
		for (int y = 0 - m_bgScroll; y < Game::kScreenWidth; y += 64)
		{
			DrawGraph(x, y, m_bgTile, true);
		}
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	// 集中線っぽいもの
	for (int i = 0; i < kLineNum; i++)
	{
		int min = GetRand(100) + 120;
		int max = GetRand(100) + 600;

		float angle = GetRand(2048) / 1024.0f * DX_PI_F;

		Vec2 start;
		start.x = cosf(angle) * min + kCenterX;
		start.y = sinf(angle) * min + kCenterY;
		Vec2 end;
		end.x = cosf(angle) * max + kCenterX;
		end.y = sinf(angle) * max + kCenterY;

		DrawLineAA(start.x, start.y, end.x, end.y, 0xf0f000, 3.0f);
	}

	SetDrawScreen(DX_SCREEN_BACK);

//	SetDrawBright(0xa0, 0xa0, 0xa0);
	for (int x = 0; x < Game::kScreenWidth; x += 64)
	{
		for (int y = 0 - m_bgScroll; y < Game::kScreenWidth; y += 64)
		{
			DrawGraph(x, y, m_bgTile, true);
		}
	}
//	SetDrawBright(0xff, 0xff, 0xff);

	DrawGraph(0,0,m_bgScreen,true);
}

bool SceneTitle::isTitleAppearEnd()
{
	return (m_titleFrameCount >= kTitleStartFrame);
}

