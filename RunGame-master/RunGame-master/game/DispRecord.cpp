#include "DispRecord.h"
#include "DxLib.h"
#include "Font.h"
#include "Message.h"

#include "Player.h"
#include "game.h"

#include "Pad.h"
#include "SingleRecord.h"
#include "EffectString.h"
#include "EffectPlayer.h"
#include "SaveData.h"

#include <string>

namespace
{
	// タイトルとして表示する文字列
	const char* const kTitleStringId[] =
	{
		"",					// None
		"MSG_RANKING_TITLESINGLE",	// Gameover
		"MSG_RANKING_TITLERECORD",		// Ranking
		"MSG_RANKING_TITLEMULTI"	// MultiResult
	};

	// 演出
	constexpr int kFadeInFrame = 32;
}

DispRecord::DispRecord():
	m_frameCount(0),
	m_bgAlpha(0)
{
}

DispRecord::~DispRecord()
{
}

void DispRecord::setupTitle(TitleType type)
{
	int kind = static_cast<int>(type);

	m_pTitle = std::make_shared<EffectString>();
	m_pTitle->setupSceneTitle(Message::getInstance().get_c(kTitleStringId[kind]));
	m_pTitle->startIn(EffectString::In::Fade, 1);
}

void DispRecord::addData(int index, int rank, int score, int playerKind, int playerNo, int totalPlayerNum)
{
	std::shared_ptr<SingleRecord>	pRecord = std::make_shared<SingleRecord>();
	pRecord->setMultiPlayerNum(totalPlayerNum);
	pRecord->setPlayerNo(playerNo);
	pRecord->setup(index, rank, score, playerKind, Font::getHandle(Font::Id::ResultScore));
	m_pRecord.push_back(pRecord);
}

void DispRecord::setDispWait(int index, int frame)
{
	m_pRecord[index]->setDispWait(frame);
}

void DispRecord::update()
{
	m_frameCount++;
	if (m_frameCount > kFadeInFrame)	m_frameCount = kFadeInFrame;

	// 表示が終わっていない状態でボタンを押したら強制的に全部表示
	if (Pad::isTrigger(PAD_INPUT_1))
	{
		if (!isDispEnd())
		{
			forceDisp();
		}
	}

	if (m_pTitle)	m_pTitle->update();
	for (auto& record : m_pRecord)
	{
		record->update();
	}
}

void DispRecord::draw()
{
	float rate = static_cast<float>(m_frameCount) / static_cast<float>(kFadeInFrame);
	rate = min(rate, 1.0f);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(m_bgAlpha * rate));
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);

	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(255 * rate));
	for (auto& record : m_pRecord)
	{
		record->draw();
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	if (m_pTitle)	m_pTitle->draw();
}

void DispRecord::setHighlightRank(int rank)
{
	m_pRecord[rank]->setHightlight(true);
}

bool DispRecord::isDispEnd()
{
	for (auto& record : m_pRecord)
	{
		if (!record->isDisp())	return false;
	}
	return true;
}

void DispRecord::forceDisp()
{
	for (auto& record : m_pRecord)
	{
		record->forceDisp();
	}
}
