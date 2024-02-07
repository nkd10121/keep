#include "EnemyLineFromLeft.h"
#include "DxLib.h"
#include "../../Util/Game.h"

EnemyLineFromLeft::EnemyLineFromLeft()
{
}

EnemyLineFromLeft::~EnemyLineFromLeft()
{
}

void EnemyLineFromLeft::Start(Vec2 pos, int width, int firstFrame, int secondFrame)
{
	m_isExist = true;

	//����x���W�̐ݒ�
	startPos.x = 0;
	endPos.x = 0;

	//����y���W�̐ݒ�
	startPos.y = pos.y;
	endPos.y = startPos.y + width;

	m_firstFrame = firstFrame;
	m_secondFrame = secondFrame;

}

void EnemyLineFromLeft::Update()
{
	//�������݂��Ȃ�������Update�����s���Ȃ�
	if (!m_isExist)
		return;

	m_frame++;

	m_color = 0xff00ff;

	//secondTime�ȍ~(�߂��Ă���)
	if (m_frame >= m_secondFrame)
	{
		endPos.x -= 320;
	}
	//firstTime~secondTime�̊�(�{����)
	else if (m_frame >= m_firstFrame)
	{
		endPos.x += 320;
		m_color = 0xffffff;
	}
	//0~firstTime�̊�(�\������I��)
	else if (m_frame >= 0)
	{
		endPos.x += 0.4f;
	}

	//�G���W�̕␳
	if (endPos.x >= Game::kScreenWidth)
	{
		endPos.x = Game::kScreenWidth;
		if (!isShake)
		{
			m_shakeFrame = 12;
			isShake = true;
		}
		m_color = 0xff00ff;
	}

	//�G���W�̕␳&isExist�t���O�̏���
	if (endPos.x <= 0)
	{
		m_isExist = false;
		endPos.x = 0;
	}

	if (m_shakeFrame != 0)
	{
		m_shakeFrame--;
	}

	//�����蔻��̐ݒ�

	m_colRect.SetBox(startPos.x, startPos.y,
		endPos.x, endPos.y);
}

void EnemyLineFromLeft::Draw()
{
	//�������݂��Ȃ�������Update�����s���Ȃ�
	if (!m_isExist)
		return;

	//�\�����I�Ȃ̂̕`��
	if (m_frame <= m_secondFrame)
	{
		DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
			Game::kScreenWidth, static_cast<int>(endPos.y),
			0x440044, true);
	}

	DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
		static_cast<int>(endPos.x), static_cast<int>(endPos.y),
		0xff00ff, true);

#ifdef _DEBUG
	//DrawFormatString(0, 720 - 16, 0xffffff, "endPos.y : %d", endPos.y);
	m_colRect.DrawColBox(0xffffff);
#endif
}