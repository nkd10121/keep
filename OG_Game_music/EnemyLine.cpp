#include "EnemyLine.h"
#include "DxLib.h"
#include "Game.h"
namespace
{
	constexpr int kLineWidth = 50;
}

EnemyLine::EnemyLine() :
	startPos(0.0f,0.0f),
	endPos(0.0f, 0.0f),
	frame(0),
	m_isExist(false)
{
}

EnemyLine::~EnemyLine()
{
}

void EnemyLine::Start()
{
	m_isExist = true;

	startPos.x = GetRand(Game::kScreenWidth - kLineWidth);
	endPos.x = startPos.x + kLineWidth;
}

void EnemyLine::Update()
{
	//もし存在しなかったらUpdateを実行しない
	if (!m_isExist)
		return;

	if (endPos.y >= 1600)
	{
		//画面下までついたら当たり判定を消してenemyLineをフェードアウトさせる
		startColPos.x = -60;
		frame += 3;
	}
	else if (endPos.y >= 30)
	{
		startColPos = startPos;
		endColPos = endPos;
		endPos.y += 100;
	}
	else
	{
		startColPos = startPos;
		endColPos = endPos;
		endPos.y += 0.5f;
	}

	if (frame >= 60)
	{
		m_isExist = false;
	}

	//当たり判定の設定

	colRect.SetLT(startColPos.x, startColPos.y,
		kLineWidth, endColPos.y - startColPos.y);
}

void EnemyLine::Draw()
{
	if (!m_isExist)
		return;

	DrawBox(startPos.x, startPos.y,
		endPos.x, endPos.y,
		0xff33a0, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	//フェード暗幕
	int alpha = 255 * (float)frame / 60.0f;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(startPos.x, startPos.y,
		endPos.x, endPos.y,
		0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

#ifdef _DEBUG
	//DrawFormatString(0, 720 - 16, 0xffffff, "endPos.y : %d", endPos.y);
	colRect.Draw(GetColor(255, 0, 0), false);
#endif
}
