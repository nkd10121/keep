#include "EnemyLineFromUpper.h"
#include "DxLib.h"
#include "../../Util/Game.h"

EnemyLineFromUpper::EnemyLineFromUpper()
{
}

EnemyLineFromUpper::~EnemyLineFromUpper()
{
}

void EnemyLineFromUpper::Start(Vec2 pos, int width, int firstFrame, int secondFrame)
{
	m_isExist = true;

	//初期x座標の設定
	startPos.x = pos.x;
	endPos.x = startPos.x + width;

	//初期y座標の設定
	startPos.y = 0;
	endPos.y = 0;

	m_firstFrame = firstFrame;
	m_secondFrame = secondFrame;

}

void EnemyLineFromUpper::Update()
{
	//もし存在しなかったらUpdateを実行しない
	if (!m_isExist)
		return;

	m_frame++;

	m_color = 0xff00ff;

	//secondTime以降(戻っていく)
	if (m_frame >= m_secondFrame)
	{
		endPos.y -= 180;
	}
	//firstTime~secondTimeの間(本動作)
	else if (m_frame >= m_firstFrame)
	{
		endPos.y += 180;
		m_color = 0xffffff;
	}
	//0~firstTimeの間(予備動作的な)
	else if (m_frame >= 0)
	{
		endPos.y += 0.4f;
	}

	//敵座標の補正
	if (endPos.y >= Game::kScreenHeight)
	{
		endPos.y = Game::kScreenHeight;
		if (!isShake)
		{
			m_shakeFrame = 12;
			isShake = true;
		}
		m_color = 0xff00ff;
	}

	//敵座標の補正&isExistフラグの処理
	if (endPos.y <= 0)
	{
		endPos.y = 0;
		m_isExist = false;
	}

	if (m_shakeFrame != 0)
	{
		m_shakeFrame--;
	}


	//当たり判定の設定
	m_colRect.SetBox(startPos.x, startPos.y,
		endPos.x, endPos.y);
}

void EnemyLineFromUpper::Draw()
{
	//もし存在しなかったらUpdateを実行しない
	if (!m_isExist)
		return;

	//予測線的なのの描画
	if (m_frame <= m_secondFrame)
	{
		DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
			static_cast<int>(endPos.x), Game::kScreenHeight,
			0x440044, true);
	}

	//本体の描画
	DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
		static_cast<int>(endPos.x), static_cast<int>(endPos.y),
		m_color, true);


#ifdef _DEBUG
	//DrawFormatString(0, 720 - 16, 0xffffff, "endPos.y : %d", endPos.y);
	m_colRect.DrawColBox(0xffffff);
#endif
}