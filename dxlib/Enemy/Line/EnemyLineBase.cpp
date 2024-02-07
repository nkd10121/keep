#include "EnemyLineBase.h"
#include "DxLib.h"
#include "../../Util/Game.h"

namespace
{
	constexpr int kLineWidth = 112;
}

EnemyLineBase::EnemyLineBase() :
	startPos(0.0f, 0.0f),
	endPos(0.0f, 0.0f),
	m_frame(0),
	m_firstFrame(0),
	m_secondFrame(0),
	lineWidth(0),
	m_isExist(false)
{
}

EnemyLineBase::~EnemyLineBase()
{
}
