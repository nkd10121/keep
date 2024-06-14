#include "Player.h"
#include "DxLib.h"
#include "game.h"

#include "PlayerManager.h"
#include "Font.h"
#include "Sound.h"
#include "Pad.h"
#include "Field.h"
#include "ParticleManager.h"
#include "Particle.h"

#include <string>

std::vector<int>	Player::m_idleGraph;
std::vector<int>	Player::m_runGraph;

namespace
{
	// プレイヤーの種類の数
	constexpr int kPlayerKindNum = 4;

	// プレイヤーファイル情報
	const char* const kPlayerGraphFilePath[kPlayerKindNum] =
	{
		"data/image/player00/",
		"data/image/player01/",
		"data/image/player02/",
		"data/image/player03/",
	};
	const char* const kPlayerIdolGraphFileName = "Idle.png";
	const char* const kPlayerRunGraphFileName = "Run.png";

	// パーティクルの色
	constexpr unsigned int kParticleColor[kPlayerKindNum] =
	{
		0x7fbfff,
		0xffff7f,
		0x7fff7f,
		0xff7fbf,
	};
	// 掘った穴の色
	constexpr unsigned int kDigColor[kPlayerKindNum] =
	{
#if true
		0x4c2e30,
		0xa96e2d,
		0xbe884e,
		0x7d582e,
#else
		0x4C2E30,
		0x4C2E30,
		0x4C2E30,
		0x4C2E30,
#endif
	};

	// 内部的なデフォルト位置
	constexpr float kDefaultX = Game::kScreenWidth / 2;
	constexpr float kDefaultY = 0.0f;

	//　プレイヤーの表示位置
	constexpr float kDispPosX = Game::kScreenWidth / 2;
//	constexpr float kDispPosX = Game::kScreenWidth / 8;
	constexpr float kDispPosY = Game::kScreenHeight / 2;
//	constexpr float kDispPosY = Game::kScreenHeight / 4 * 3;

	// グラフィックサイズ
	constexpr int kGraphWidth = 32;
	constexpr int kGraphHeight = 32;

	// アニメコマ数
	constexpr int kIdleAnimNum = 11;
	constexpr int kRunAnimNum = 12;

	// アニメ1コマのデフォルトフレーム数
	constexpr int kAnimFrame = 8;

	constexpr int kPosLogNum = 12;

	// 
	constexpr float kDigSpeed = 2.0f;	// 掘る速度
	constexpr float kDigAngleMin = -80.0f * DX_PI_F / 180;
	constexpr float kDigAngleMax =  80.0f * DX_PI_F / 180;

	constexpr float kRotSpeed = 0.04f;	// 旋回速度

	// 掘る効果音鳴らす間隔
	constexpr float kDigSeFrame = 42.0f;

	// ゲームテンポアップ
	constexpr int kTempoDefault = 120;
	constexpr int kTempoMax = 480;

	// kTempoUpScoreごとにテンポがkTempoUpValueアップする
	constexpr int kTempoUpScore = 200;
	constexpr int kTempoUpValue = 20;
}

void Player::startLoad()
{
	// 非同期読み込みを開始する
	SetUseASyncLoadFlag(true);

	for (int i = 0; i < kPlayerKindNum; i++)
	{
		std::string fileName = kPlayerGraphFilePath[i];
		fileName += kPlayerIdolGraphFileName;
		m_idleGraph.push_back(LoadGraph(fileName.c_str()));

		fileName = kPlayerGraphFilePath[i];
		fileName += kPlayerRunGraphFileName;
		m_runGraph.push_back(LoadGraph(fileName.c_str()));
	}
	
	// デフォルトに戻す
	SetUseASyncLoadFlag(false);
}

void Player::unload()
{
	for (auto& handle : m_idleGraph)
	{
		DeleteGraph(handle);
	}
	for (auto& handle : m_runGraph)
	{
		DeleteGraph(handle);
	}
	m_runGraph.clear();
}

bool Player::isLoaded()
{
	for (auto& handle : m_idleGraph)
	{
		if (CheckHandleASyncLoad(handle))	return false;
	}
	for (auto& handle : m_runGraph)
	{
		if (CheckHandleASyncLoad(handle))	return false;
	}
	return true;
}

int Player::getKindNum()
{
	return kPlayerKindNum;
}

int Player::getIdleGraph(int kind)
{
	return m_idleGraph[kind];
}

int Player::getRunGraph(int kind)
{
	return m_runGraph[kind];
}

int Player::getColor(int kind)
{
	return kParticleColor[kind];
}

int Player::getIdleAnimeNum()
{
	return kIdleAnimNum;
}

int Player::getRunAnimeNum()
{
	return kRunAnimNum;
}

Player::Player(bool isDemo) :
	m_playerNo(0),
	m_kind(0),
	m_isDispPlayerNo(false),
	m_tempo(kTempoDefault),
	m_animFrame(0.0f),
	m_angle(0.0f),
	m_playFrameCount(0),
	m_updateFrameCount(0),
	m_digFrameCount(0.0f),
	m_tempoUpFrame(999),
	m_isDemo(isDemo)
{
}

Player::~Player()
{
}

void Player::init(int playerNo)
{
	m_playerNo = playerNo;
	m_kind = GetRand(Player::getKindNum()-1);

	m_pos.x = kDefaultX;
	m_pos.y = kDefaultY;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;

	setScroll();

	m_angle = 0.0f;

	m_animFrame = 0.0f;
	m_updateFrameCount = 0;
//	// 初期状態を表示用データに追加		setStartY()で初期位置を設定した後にデータを追加するよう修正
//	addDispDataIdle();
}

void Player::update()
{
	(this->*m_updateFunc)();
}

void Player::draw()
{
	for (int i = static_cast<int>(m_dispData.size()) - 1; i >= 0; i--)
	{
		float alphaRate = static_cast<float>(i) / static_cast<float>(kPosLogNum);	// 0.0:最新	1.0:最古
		alphaRate = 1.0f - alphaRate;
		alphaRate *= alphaRate;

		int alpha = static_cast<int>(255 * alphaRate);

		int handle = m_dispData[i].grphHandle;
		int animIndex = m_dispData[i].animIndex;

		// 足元基準のm_posを表示用の中心座標に変換
		Vec2 center = m_dispData[i].pos;
	//	center += m_scroll;
		center += m_pManager->getScroll();

		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);

		SetDrawBright( alpha, alpha, 255 );

		// 死んだら真っ黒表示
		if (i == 0 && isDead())
		{
			SetDrawBright(0, 0, 0);
		}

		DrawRectRotaGraph(
			static_cast<int>(center.x), static_cast<int>(center.y),
			animIndex * kGraphWidth, 0, kGraphWidth, kGraphHeight,
			1.0, m_dispData[i].angle,
			handle, true, false
		);
	}
	// プレイヤー番号の表示
	if(m_isDispPlayerNo && !isDemo())	// デモの時のプレイヤー番号は表示しない
	{
		int width = GetDrawFormatStringWidthToHandle(Font::getHandle(Font::Id::PlayerNo), "%dP→", m_playerNo + 1);

		Vec2 pos = m_pos;
	//	pos += m_scroll;
		pos += m_pManager->getScroll();
		pos.x -= width + 16;
		pos.y -= 6;
		DrawFormatStringToHandle(static_cast<int>(pos.x), static_cast<int>(pos.y), kParticleColor[m_kind], Font::getHandle(Font::Id::PlayerNo), "%dP→", m_playerNo + 1);
	}
	
	// 表示中に変更した設定を元に戻しておく
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	SetDrawBright(255, 255, 255);
}

unsigned int Player::getParticleColor()
{
	return kParticleColor[getKind()];
}

unsigned int Player::getDigColor()
{
	return kDigColor[getKind()];
}

void Player::setStartY(float y)
{
	m_pos.y = y;
	addDispDataIdle();	// 決定した初期位置を表示データに追加
}

//float Player::getMoveDistance()
//{
//	return m_pos.x - kDefaultX;
//}

int Player::getScore()
{
	float move = m_pos.x - kDefaultX;
	return static_cast<int>(move / 16);
}

void Player::startIdling()
{
	m_updateFunc = &Player::updateIdling;
	m_updateFrameCount = 0;
}

void Player::startDig()
{
	m_updateFunc = &Player::updateDig;
	m_playFrameCount = 0;
	m_updateFrameCount = 0;
	if(!isDemo())	Sound::getInstance().play("dig");
	m_digFrameCount = kDigSeFrame;
}

bool Player::isDead()
{
	if (m_updateFunc == &Player::updateDeadHit)	return true;		// ぶつかって死んだ

	return false;
}

float Player::getDt()
{
	return static_cast<float>(m_tempo) / static_cast<float>(kTempoDefault);
}

bool Player::isDemo()
{
	return m_isDemo;
}

void Player::addDispData()
{
	int animFrame = static_cast<int>(m_animFrame);

	DispData data;
	data.pos = m_pos;
	data.grphHandle = Player::getRunGraph(m_kind);
	data.animIndex = animFrame / kAnimFrame;
	data.angle = static_cast<double>(m_angle);
	
	if( (m_updateFunc == &Player::updateDig) ||
		(m_updateFunc == &Player::updateIdling) )
	{
		data.pos.x += GetRand(2) - 1;
		data.pos.y += GetRand(2) - 1;
	}

	m_dispData.push_front(data);
	if (m_dispData.size() > kPosLogNum)
	{
		m_dispData.pop_back();
	}
}

void Player::addDispDataIdle()
{
	int animFrame = static_cast<int>(m_animFrame);

	DispData data;
	data.pos = m_pos;
	data.grphHandle = Player::getIdleGraph(m_kind);
	data.animIndex = animFrame / kAnimFrame;
	data.angle = static_cast<double>(m_angle);

	m_dispData.push_front(data);
	if (m_dispData.size() > kPosLogNum)
	{
		m_dispData.pop_back();
	}
	
}

void Player::updateWait()
{
	float dt = getDt();

	m_updateFrameCount++;

	// プレイヤーが基本位置に表示されるようスクロール量を設定する
	setScroll();

	m_animFrame += dt;
	if (m_animFrame >= kAnimFrame * kIdleAnimNum)
	{
		m_animFrame -= kAnimFrame * kIdleAnimNum;
	}
#if false
	// 一定時間経過で状態遷移
	if (m_updateFrameCount > 120)
	{
		m_updateFunc = &Player::updateIdling;
		m_updateFrameCount = 0;
	}
#endif

	// 最新情報を表示用データに追加
	addDispDataIdle();
}

void Player::updateIdling()
{
	float dt = getDt();

	// 操作しなくても移動方向ぶれる
	float noise = static_cast<float>(GetRand(512) - 256) / 10000.0f;
	if (!isDemo())
	{
		m_angle += noise;
	}

	if (Pad::isPress(PAD_INPUT_UP, m_playerNo))
	{
		m_angle -= kRotSpeed * dt;
	}
	if (Pad::isPress(PAD_INPUT_DOWN, m_playerNo))
	{
		m_angle += kRotSpeed * dt;
	}
	m_angle = max(m_angle, kDigAngleMin);
	m_angle = min(m_angle, kDigAngleMax);


	m_updateFrameCount++;

	// プレイヤーが基本位置に表示されるようスクロール量を設定する
	setScroll();

	m_animFrame += dt;
	if (m_animFrame >= kAnimFrame * kIdleAnimNum)
	{
		m_animFrame -= kAnimFrame * kIdleAnimNum;
	}
#if false
	// 一定時間経過で動き始める
	if (m_updateFrameCount > 120)
	{
		m_updateFunc = &Player::updateDig;
		m_updateFrameCount = 0;
		Sound::getInstance().play("dig");
		m_digFrameCount = kDigSeFrame;
	}
#endif

	// 最新情報を表示用データに追加
	addDispDataIdle();
}

void Player::updateDig()
{
	float dt = getDt();

	m_digFrameCount -= dt;
	if (m_digFrameCount <= 0.0f)
	{
		if (!isDemo())	Sound::getInstance().play("dig", dt);
		m_digFrameCount += kDigSeFrame;
	}

	m_vec.x = (kDigSpeed * dt) * cosf(m_angle);
	m_vec.y = (kDigSpeed * dt) * sinf(m_angle);
	m_pos += m_vec;

	m_playFrameCount++;

	m_updateFrameCount++;
	if (m_updateFrameCount % 2 == 0)	// データを間引くために毎フレームはデータを置かない
	{
		m_pField->addDigData(m_pos, getDigColor(), m_playerNo);
	}

	// 操作しなくても移動方向ぶれる
	float noise = static_cast<float>(GetRand(512) - 256) / 10000.0f;
	if (!isDemo())
	{
		m_angle += noise;
		if (Pad::isPress(PAD_INPUT_UP, m_playerNo))
		{
			m_angle -= kRotSpeed * dt;
		}
		if (Pad::isPress(PAD_INPUT_DOWN, m_playerNo))
		{
			m_angle += kRotSpeed * dt;
		}
	}
	
	m_angle = max(m_angle, kDigAngleMin);
	m_angle = min(m_angle, kDigAngleMax);

	// 進行度に合わせてゲームテンポを変更する
	m_tempoUpFrame++;
	int lastTempo = m_tempo;
	if (!isDemo())
	{
		int upCount = getScore() / kTempoUpScore;
		m_tempo = kTempoDefault + upCount * kTempoUpValue;
		m_tempo = min(m_tempo, kTempoMax);
	}
	if (lastTempo != m_tempo)
	{
		Pad::vibrationMiddle(m_playerNo);
		m_tempoUpFrame = 0;
	}


	// プレイヤーが基本位置に表示されるようスクロール量を設定する
	setScroll();
	// 移動経路にパーティクル生成
	createMoveParticle();

	m_animFrame += dt;
	if (m_animFrame >= kAnimFrame * kIdleAnimNum)
	{
		m_animFrame -= kAnimFrame * kIdleAnimNum;
	}
	// 最新情報を表示用データに追加
	addDispData();

	if (isCheckDead())
	{
		// ぶつかって死亡
		Pad::vibrationHard(m_playerNo);
		Sound::getInstance().play("hitField");
		m_updateFunc = &Player::updateDeadHit;
		m_updateFrameCount = 0;
	}
}

void Player::updateDeadHit()
{
	m_updateFrameCount++;

	// アニメーションは止める

	// 死亡後も別色のパーティクルを生成する
	createMoveParticle();

	// 最新情報を表示用データに追加
	addDispData();
}

bool Player::isCheckDead()
{
	// 壁にぶつかって死亡
	if (m_pField->isCol(m_pos))	return true;
	// 画面外に出て死亡(対戦用)
	Vec2 dispPos = m_pos;
	dispPos += m_pManager->getScroll();
	// 一応上下左右チェック
	if (dispPos.x < 0 - 16.0f)	return true;
	if (dispPos.x > Game::kScreenWidth + 16.0f)		return true;
	if (dispPos.y < 0 - 16.0f)	return true;
	if (dispPos.y > Game::kScreenHeight + 16.0f)	return true;

	return false;
}

void Player::setScroll()
{
	m_scroll.x = kDispPosX - m_pos.x;
//	m_scroll.y = kDispPosY - m_pos.y;
	m_scroll.y = kDispPosY - 0.0f;	// 上下スクロールはしない
}

void Player::createMoveParticle()
{
	int createNum = 1;
	// 速くなるとたくさんパーティクル生成
	createNum *= static_cast<int>(getDt() * getDt());

	// 速度アップ直後はたくさん生成
	if (m_tempoUpFrame < 8)
	{
		createNum += 8 - m_tempoUpFrame;
	}

	unsigned int color = kParticleColor[m_kind];

	// 死亡演出用のパーティクル
	if (isDead())
	{
		createNum = 4;
		color = 0x000000;
	}

	for (int i = 0; i < createNum; i++)
	{
		Vec2 pos = getPos();
		
		pos.x += GetRand(20) - 10;
		pos.y += GetRand(20) - 10;

		float vecY = static_cast<float>(-GetRand(300));
		vecY /= 1000;

		std::shared_ptr<Particle> pPart = std::make_shared<Particle>(m_pParticle);
		pPart->init();
		pPart->setPos(pos);
		pPart->setVec(Vec2{ 0.0f, vecY });
		pPart->setRadius(1.0f);
		pPart->setColor(color);
		if (m_tempoUpFrame < 8)
		{
			pPart->setExistFrame(240);
			pPart->setAlphaAcc(-1);
		}
		else
		{
			pPart->setExistFrame(120);
			pPart->setAlphaAcc(-2);
		}

		m_pParticle->add(pPart);
	}
}
