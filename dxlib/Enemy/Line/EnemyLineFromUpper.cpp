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

	//����x���W�̐ݒ�
	startPos.x = pos.x;
	endPos.x = startPos.x + width;

	//����y���W�̐ݒ�
	startPos.y = 0;
	endPos.y = 0;

	m_firstFrame = firstFrame;
	m_secondFrame = secondFrame;

}

void EnemyLineFromUpper::Update()
{
	//�������݂��Ȃ�������Update�����s���Ȃ�
	if (!m_isExist)
		return;

	m_frame++;

	m_color = 0xff00ff;

	//secondTime�ȍ~(�߂��Ă���)
	if (m_frame >= m_secondFrame)
	{
		endPos.y -= 180;
	}
	//firstTime~secondTime�̊�(�{����)
	else if (m_frame >= m_firstFrame)
	{
		endPos.y += 180;
		m_color = 0xffffff;
	}
	//0~firstTime�̊�(�\������I��)
	else if (m_frame >= 0)
	{
		endPos.y += 0.4f;
	}

	//�G���W�̕␳
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

	//�G���W�̕␳&isExist�t���O�̏���
	if (endPos.y <= 0)
	{
		endPos.y = 0;
		m_isExist = false;
	}

	if (m_shakeFrame != 0)
	{
		m_shakeFrame--;
	}


	//�����蔻��̐ݒ�
	m_colRect.SetBox(startPos.x, startPos.y,
		endPos.x, endPos.y);
}

void EnemyLineFromUpper::Draw()
{
	//�������݂��Ȃ�������Update�����s���Ȃ�
	if (!m_isExist)
		return;

	//�\�����I�Ȃ̂̕`��
	if (m_frame <= m_secondFrame)
	{
		DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
			static_cast<int>(endPos.x), Game::kScreenHeight,
			0x440044, true);
	}

	//�{�̂̕`��
	DrawBox(static_cast<int>(startPos.x), static_cast<int>(startPos.y),
		static_cast<int>(endPos.x), static_cast<int>(endPos.y),
		m_color, true);


#ifdef _DEBUG
	//DrawFormatString(0, 720 - 16, 0xffffff, "endPos.y : %d", endPos.y);
	m_colRect.DrawColBox(0xffffff);
#endif
}