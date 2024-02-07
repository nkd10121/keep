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

	//最初に指定したフレームを過ぎると実体が出てくる
	if (m_frame >= m_firstFrame)
	{
		//実体の当たり判定
		m_colRect.SetBox(m_pos.x - size, m_pos.y - size,
			m_pos.x + size, m_pos.y + size);

		if (m_frame < m_secondFrame)
		{
			//もし最大サイズになったら
			if (size > sizeMax + static_cast<int>(sizeMax * 0.1f))
			{
				m_isMax = true;
				color = 0xffffff;
			}
			else
			{
				color = 0xff00ff;
			}

			//最大になっていないときは大きくなる
			if (!m_isMax)
			{
				size += m_speed;
			}
			//一瞬最大サイズより大きくなるため補正する
			else if (size > sizeMax)
			{
				size -= 8;
			}
		}
	}
	//二番目に指定したフレームを過ぎると小さくなる
	if (m_frame >= m_secondFrame)
	{
		size -= m_speed;
	}

	//サイズが0より小さくなると存在を消す
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
		//予測の描画
		if (!m_isMax)
		{
			DrawBox(m_pos.x - sizeMax, m_pos.y - sizeMax,
				m_pos.x + sizeMax, m_pos.y + sizeMax, 0x440044, true);
		}
	}

	//本体の描画
	DrawBox(m_pos.x - size, m_pos.y - size,
		m_pos.x + size, m_pos.y + size, color, true);

#ifdef _DEBUG
	m_colRect.DrawColBox(0xffffff);
#endif
}
