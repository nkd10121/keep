#include "EnemyLineDown.h"
#include "DxLib.h"
#include "../../Util/Game.h"

EnemyLineDown::EnemyLineDown()
{
}

EnemyLineDown::~EnemyLineDown()
{
}


void EnemyLineDown::Start(Vec2 pos, int width, int firstFrame, int secondFrame)
{
	m_isExist = true;

	//����x���W�̐ݒ�
	startPos.x = pos.x;
	endPos.x = startPos.x + width;

	//����y���W�̐ݒ�
	startPos.y = Game::kScreenHeight;
	endPos.y = Game::kScreenHeight;

	m_firstFrame = firstFrame;
	m_secondFrame = secondFrame;

}

void EnemyLineDown::Update()
{
	//�������݂��Ȃ�������Update�����s���Ȃ�
	if (!m_isExist)
		return;

	m_frame++;

	m_color = 0xff00ff;


	//secondTime�ȍ~(�߂��Ă���)
	if (m_frame >= m_secondFrame)
	{
		endPos.y += 180;
	}
	//firstTime~secondTime�̊�(�{����)
	else if (m_frame >= m_firstFrame)
	{
		endPos.y -= 180;
		m_color = 0xffffff;
	}
	//0~firstTime�̊�(�\������I��)
	else if (m_frame >= 0)
	{
		endPos.y -= 0.4f;
	}

	//�G���W�̕␳&isExist�t���O�̏���
	if (endPos.y >= Game::kScreenHeight)
	{
		endPos.y = Game::kScreenHeight;
		m_isExist = false;
	}

	//�G���W�̕␳
	if (endPos.y <= 0)
	{
		endPos.y = 0;
		if (!isShake)
		{
			m_shakeFrame = 12;
			isShake = true;
		}
		m_color = 0xff00ff;
	}

	if (m_shakeFrame != 0)
	{
		m_shakeFrame--;
	}

	//�����蔻��̐ݒ�
	m_colRect.SetBox(startPos.x, endPos.y,
		endPos.x, startPos.y);
}

void EnemyLineDown::Draw()
{
	//�������݂��Ȃ�������Update�����s���Ȃ�
	if (!m_isExist)
		return;

	//�\�����I�Ȃ̂̕`��
	if (m_frame <= m_secondFrame)
	{
		DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
			static_cast<int>(endPos.x), 0,
			0x440044, true);
	}

	//�{�̂̕`��
	DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
		static_cast<int>(endPos.x), static_cast<int>(endPos.y),
		0xff00ff, true);


#ifdef _DEBUG
	//DrawFormatString(0, 720 - 16, 0xffffff, "endPos.y : %d", endPos.y);
	m_colRect.DrawColBox(0xffffff);
#endif
}

