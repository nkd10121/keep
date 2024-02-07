#include "EnemyBox.h"
#include "DxLib.h"

EnemyBox::EnemyBox()
{
}

EnemyBox::~EnemyBox()
{
}

void EnemyBox::Start(Vec2 pos, int size,int speed, int firstFrame, int secondFrame,bool isPre)
{
	m_isExist = true;

	m_pos = pos;
	sizeMax = size;
	m_firstFrame = firstFrame;
	m_secondFrame = secondFrame;
	m_speed = speed;
	m_isDrawPre = isPre;
}

void EnemyBox::Update()
{
	if (!m_isExist)
	{
		return;
	}
	m_frame++;

	//�ŏ��Ɏw�肵���t���[�����߂���Ǝ��̂��o�Ă���
	if (m_frame >= m_firstFrame)
	{
		//���̂̓����蔻��
		m_colRect.SetBox(m_pos.x - size, m_pos.y - size,
			m_pos.x + size, m_pos.y + size);

		if (m_frame < m_secondFrame)
		{
			//�����ő�T�C�Y�ɂȂ�����
			if (size > sizeMax + static_cast<int>(sizeMax * 0.1f))
			{
				m_isMax = true;
				color = 0xffffff;
			}
			else
			{
				color = 0xff00ff;
			}

			//�ő�ɂȂ��Ă��Ȃ��Ƃ��͑傫���Ȃ�
			if (!m_isMax)
			{
				size += m_speed;
			}
			//��u�ő�T�C�Y���傫���Ȃ邽�ߕ␳����
			else if (size > sizeMax)
			{
				size -= 8;
			}
		}
	}
	//��ԖڂɎw�肵���t���[�����߂���Ə������Ȃ�
	if (m_frame >= m_secondFrame)
	{
		size -= m_speed;
	}

	//�T�C�Y��0��菬�����Ȃ�Ƒ��݂�����
	if (size < 0)
	{
		m_isExist = false;
	}


}

void EnemyBox::Draw()
{
	if (!m_isExist)
	{
		return;
	}

	if (m_isDrawPre)
	{
		//�\���̕`��
		if (!m_isMax)
		{
			DrawBox(m_pos.x - sizeMax, m_pos.y - sizeMax,
				m_pos.x + sizeMax, m_pos.y + sizeMax, 0x440044, true);
		}
	}

	//�{�̂̕`��
	DrawBox(m_pos.x - size, m_pos.y - size,
		m_pos.x + size, m_pos.y + size, color, true);

#ifdef _DEBUG
	m_colRect.DrawColBox(0xffffff);
#endif
}
