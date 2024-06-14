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
	// �O���t�B�b�N�t�@�C����
//	const char* const kBgTileFilename = "data/image/bg/Yellow.png";
	const char* const kBgTileFilename = "data/image/bg/Gray.png";
	
	// �^�C�g�����S�Ɏg�p����t�H���g
	constexpr Font::Id kTitleFont = Font::Id::GameTitle;

	// �^�C�g�����S�o�ꉉ�o�t���[����
	constexpr int kTitleStartFrame = 150;
	// �^�C�g�����S�t���[���������o	���t���[���ɂP��\�����X�V���邩
	constexpr int kTitleUpdateFrame = 8;

	// �w�i�Â��Ȃ�t���[����
	constexpr int kBgFadeFrame = 1;
	// �w�i�N���X����t�F�[�h�̃A���t�@
//	constexpr int kBgFadeAlpha = 64;
	constexpr int kBgFadeAlpha = 0;

	// �^�C�g�����S�F
	constexpr unsigned int kTitleColor = 0xff420e;
	constexpr unsigned int kTitleEdgeColor = 0xfff0f0;
	constexpr unsigned int kTitleShadowColor = 0xf98866;

	// �^�C�g�����S�T�C�Y
	constexpr int kTitleFontSize = 192;
	constexpr int kTitleFontEdgeSize = 20;
	constexpr int kTitleShadowOffsetY = 16;	// �^�C�g��������Ƃ��炵��2�d�\��

	constexpr int kLogoGraphHeight = kTitleFontSize + kTitleFontEdgeSize + kTitleShadowOffsetY + 16;	// ������Ə�ɂ͂ݏo���t�H���g�Ȃ̂Œ���

	// �^�C�g�����S�\���ʒu����(���E�͒����ɔz�u�A��ӂ̓��S�T�C�Y�ɂ��)
	constexpr int kTitleBottomY = Game::kScreenHeight / 2;
	// �^�C�g�����S�̕����l��
	constexpr int  kLogoKerning = 48;
	
	// �f�����n�܂�܂ł̑҂�����
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
	// �񓯊��ǂݍ��݂��J�n����
	SetUseASyncLoadFlag(true);

	m_bgTile = LoadGraph(kBgTileFilename);

	// �^�C�g���ł����g��Ȃ��t�H���g
	m_titleFontHandle = CreateFontToHandle("GN-�L���SU����NA", kTitleFontSize, 4, DX_FONTTYPE_ANTIALIASING_EDGE_8X8, -1, kTitleFontEdgeSize);

	// �f�t�H���g�ɖ߂�
	SetUseASyncLoadFlag(false);
}

bool SceneTitle::isLoaded() const
{
	// �풓���\�[�X�̃��[�h�����m�F
	if (!Player::isLoaded())	return false;

	if (CheckHandleASyncLoad(m_bgTile))	return false;
	if (CheckHandleASyncLoad(m_titleFontHandle))	return false;

	return true;
}

void SceneTitle::init()
{
	m_bgScreen = MakeScreen(Game::kScreenWidth, Game::kScreenHeight, true);

	// �^�C�g�����S�̐���
	createLogoGraph();

	m_pText = std::make_shared<EffectString>();
	m_pText->setupCenter(Game::kScreenWidth / 2, 560, Message::getInstance().get_c("MSG_TITLE_START"), Font::getHandle(Font::Id::TitleMenu));
	m_pText->setColor(0xffffff);
	m_pText->setEffect(EffectString::Effect::AlphaBlink);
	m_pText->startIn(EffectString::In::Fade, 8);

	// �^�C�g�����o�̏�����
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

#ifdef EX_VER	// �G���N���o�[�W����
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

	//	//	// �^�C�g�����S�̐���
	//	createLogoGraph();
		
		// ���[�h�������\�[�X�̏����W���s��
		// �T�E���h�̏����W
		Sound::getInstance().collectData();
#if false	// �����d���̂Ŏ~�܂�Ȃ��悤���C�����j���[�J�n�̃^�C�~���O�Ŏ~�߂�
	//	// �t�H���g�̏����W
	//	Font::collectData();
#endif
		// updateTitleAppear�ɐ؂�ւ�
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
		// �o�ꉉ�o�X�L�b�v
		m_titleFrameCount = kTitleStartFrame;

		// updateWait�ɐ؂�ւ�
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
		// ���t���[���w�i���o�v���C���[1�̐���
		std::shared_ptr<EffectPlayer> pPlayer = std::make_shared<EffectPlayer>();
		pPlayer->setupTitle();
		m_pPlayer.push_back(pPlayer);
	}

	for (auto& player : m_pPlayer)
	{
		player->update();
	}
	// ��ʊO�ɏo����폜
	m_pPlayer.remove_if(
		[](auto& player) {
			return !player->isExist();
		});
}

void SceneTitle::createLogoGraph()
{
	assert(!CheckHandleASyncLoad(m_titleFontHandle));

	// �^�C�g����1����������
	std::vector<std::string>	splitTitle = StrUtil::splitString(Message::getInstance().get_c("MSG_GAMETITLE"));

	// �����̉������`�F�b�N���ĕK�v�ȃO���t�B�b�N�̃T�C�Y���v�Z
	m_titleWidth = 0;
	for (auto& chr : splitTitle)
	{
		const char* pText = chr.c_str();
		m_titleWidth += GetDrawStringWidthToHandle(pText, static_cast<int>(strlen(pText)), m_titleFontHandle);
		m_titleWidth -= kLogoKerning;
	}
	m_titleWidth += kLogoKerning;	// �Ō�̕����̕����l�߂̕��͖߂��Ă���

	m_titleGraph = MakeScreen(m_titleWidth, kLogoGraphHeight, true);
//	m_titleGraph = MakeScreen(m_titleWidth, kLogoGraphHeight, false);	// �A���t�@�𖳌��ɂ��ăO���t�B�b�N���킩��₷�����邽�߂̃e�X�g

	SetDrawScreen(m_titleGraph);

	// 1�������l�߂ĕ`��
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
#if false	// �^�C�g�����S���O���t�B�b�N�ŏo��
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

	// �������̋�`
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

	// �W�������ۂ�����
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

