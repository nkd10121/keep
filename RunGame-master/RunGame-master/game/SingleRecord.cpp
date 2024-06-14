#include "SingleRecord.h"
#include "DxLib.h"
#include "Vec2.h"
#include "game.h"

#include "Sound.h"
#include "Player.h"
#include "EffectPlayer.h"
#include "SaveData.h"
#include "Font.h"
#include "Message.h"
#include <string>
#include <cassert>

namespace
{
	constexpr int kDispPlayerNum = 10;
	static_assert(kDispPlayerNum <= SaveData::kSaveRankDataNum);

	// ���ʕ\���̒P��
	const char* const kRankDigit = "��";
	const char* const kRankNameId[kDispPlayerNum] =
	{
		"MSG_RANKING_01",
		"MSG_RANKING_02",
		"MSG_RANKING_03",
		"MSG_RANKING_04",
		"MSG_RANKING_05",
		"MSG_RANKING_06",
		"MSG_RANKING_07",
		"MSG_RANKING_08",
		"MSG_RANKING_09",
		"MSG_RANKING_10",
	};

	// �����L���O�\��	�z�u�f�[�^
	constexpr SingleRecord::DispData kDispDataSingle[] =
	{
		{ 184 + 64 * 0, 208, 424,	80, 1.0, 2, true },
		{ 184 + 64 * 1, 208, 424,	80, 1.0, 3, true },
		{ 184 + 64 * 2, 208, 424,	80, 1.0, 4, true },
		{ 184 + 64 * 3, 208, 424,	80, 1.0, 5, true },
		{ 184 + 64 * 4, 208, 424,	80, 1.0, 6, true },

		{ 216 + 64 * 0, 848, 1064,	720, 1.0, 8, false },
		{ 216 + 64 * 1, 848, 1064,	720, 1.0, 8, false },
		{ 216 + 64 * 2, 848, 1064,	720, 1.0, 8, false },
		{ 216 + 64 * 3, 848, 1064,	720, 1.0, 8, false },
		{ 216 + 64 * 4, 848, 1064,	720, 1.0, 8, false },
	};
	static_assert(_countof(kDispDataSingle) == kDispPlayerNum);

	// �ΐ탂�[�h�̔z�u�f�[�^
	constexpr SingleRecord::DispData kDispDataMulti[] =
	{
		// 1�ʂ͓��ʕ\��
		{ 248+32, 464+32, 680+32,	640, 4.0, 2, true },

		{ 350 + 54 * 0, 208, 424,	 80, 1.0, 3, true },
		{ 350 + 54 * 1, 208, 424,	 80, 1.0, 4, true },
		{ 350 + 54 * 2, 208, 424,	 80, 1.0, 5, true },
		{ 350 + 54 * 3, 208, 424,	 80, 1.0, 6, true },

		{ 350 + 54 * 0, 848, 1064,	720, 1.0, 8, false },
		{ 350 + 54 * 1, 848, 1064,	720, 1.0, 8, false },
		{ 350 + 54 * 2, 848, 1064,	720, 1.0, 8, false },

		// 8�l�܂ł����ꉞ
		{ 350 + 54 * 3, 848, 1064,	720, 1.0, 8, false },
		{ 350 + 54 * 4, 848, 1064,	720, 1.0, 8, false },
	};
	static_assert(_countof(kDispDataMulti) == kDispPlayerNum);

	// �ΐ탂�[�h�A5�l�ȉ��̏ꍇ�̔z�u�f�[�^
	constexpr SingleRecord::DispData kDispDataMultiFew[] =
	{
		// 1�ʂ͓��ʕ\��
		{ 248 + 32, 464 + 32, 680 + 32,	640, 4.0, 2, true },

		// �l�����Ȃ��ꍇ�̓���z�u���
		{ 350 + 54 * 0, 496, 712,	496 - 128, 1.0, 3, true },
		{ 350 + 54 * 1, 496, 712,	496 - 128, 1.0, 4, true },
		{ 350 + 54 * 2, 496, 712,	496 - 128, 1.0, 5, true },
		{ 350 + 54 * 3, 496, 712,	496 - 128, 1.0, 6, true },

		// �ȉ��͎g���Ȃ�	�킩��₷���悤�ɂ��������f�[�^�����Ă���s
		{ 0, 0, 0,	0, 1.0, 1, false },
		{ 0, 0, 0,	0, 1.0, 1, false },
		{ 0, 0, 0,	0, 1.0, 1, false },
		{ 0, 0, 0,	0, 1.0, 1, false },
		{ 0, 0, 0,	0, 1.0, 1, false },
	};
	static_assert(_countof(kDispDataMultiFew) == kDispPlayerNum);


	// �\�����n�߂��牉�o���������Ċ��S�ɕ\�������܂ł̃t���[����
	constexpr int kAlphaDispFrame = 30;
}

SingleRecord::SingleRecord():
	m_index(0),
	m_rank(0),
	m_score(0),
	m_playerKind(0),
	m_fontHandle(-1),
	m_playerNo(-1),
	m_multiPlayerNum(-1),
	m_isHighlight(false),
	m_maxWidth(0),
	m_dispWait(0),
	m_dispAlphaFrame(0),
	m_isPlaySe(false),
	m_sinRate(0.0f)
{
}

SingleRecord::~SingleRecord()
{
}

void SingleRecord::setup(int index, int rank, int score, int playerKind, int fontHandle)
{
	// �f�[�^�̎擾
	m_index = index;
	m_rank = rank;
	m_score = score;
//	m_score = 888888;	// �����e�X�g
	m_playerKind = playerKind;
	m_fontHandle = fontHandle;

	// �\���p�Ƀf�[�^�̃Z�b�g�A�b�v
	// 0~9�̊e�����̉������擾����
	m_maxWidth = 0;
	for (int i = 0; i < 10; i++)
	{
		std::string str = std::to_string(i);
		int width = GetDrawFormatStringWidthToHandle(m_fontHandle, str.c_str());
		m_numWidth.push_back(width);
		m_maxWidth = max(m_maxWidth, width);	// ��ԉ����̍L�������̉���
	}

	m_isHighlight = false;	// �f�t�H���g�ł͋����\���Ȃ�

	m_pIcon = std::make_shared<EffectPlayer>();

	// ���ʁA���[�h�ɂ���ĕ\���ʒu���ς��
	if (isMulti())
	{
		if (m_multiPlayerNum <= 5)
		{
			m_dispData = kDispDataMultiFew[m_index];
		}
		else
		{
			m_dispData = kDispDataMulti[m_index];
		}
	}
	else
	{
		m_dispData = kDispDataSingle[m_index];
	}

	m_pIcon->setupIcon(getIconPos());
	m_pIcon->setKind(m_playerKind);
	m_pIcon->setScale(m_dispData.iconScale);
	m_pIcon->setAnimSpeed(m_dispData.iconAnimSpeed);
	m_pIcon->setRun(m_dispData.isIconRun);
}

void SingleRecord::update()
{
	m_dispWait--;
	if (m_dispWait <= 0)
	{
		// �\�����n�߂̏u��
		if (!m_isPlaySe)
		{
			if (m_isHighlight)
			{
				Sound::getInstance().play("fanfare");
			}
			else
			{
				Sound::getInstance().play("dispRank");
			}
			m_isPlaySe = true;
		}
		m_dispWait = 0;
		m_dispAlphaFrame++;
		if (m_dispAlphaFrame >= kAlphaDispFrame)	m_dispAlphaFrame = kAlphaDispFrame;
	}

	m_sinRate += 0.2f;
	// �����\���������A�C�R�����㉺�ɗh�炷
	float iconOffsetY = 0.0f;
	if (m_isHighlight)
	{
		iconOffsetY = abs(sinf(m_sinRate)) * -8.0f;
		Vec2 pos = getIconPos();
		pos.y += iconOffsetY;
		m_pIcon->setPos(pos);
	}

	m_pIcon->update();
}

void SingleRecord::draw()
{
	if (m_dispWait > 0)	return;

	float alphaRate = static_cast<float>(m_dispAlphaFrame) / static_cast<float>(kAlphaDispFrame);
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, static_cast<int>(alphaRate * 255));

	int y = m_dispData.y;
	if (m_isHighlight)
	{
		drawIconHighlight();
	}
	m_pIcon->draw();
	drawPlayerNo();
	drawRank(m_dispData.rankX, y);
	if (isMulti())
	{
		drawScoreMulti(m_dispData.scoreX, y);
	}
	else
	{
		drawScore(m_dispData.scoreX, y);
	}
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

bool SingleRecord::isDisp()
{
	// �\���J�n�҂�
	if (m_dispWait > 0)	return false;
	// �\���J�n���o��
	if (m_dispAlphaFrame < kAlphaDispFrame)	return false;
	return true;
}

void SingleRecord::forceDisp()
{
	m_dispWait = 0;
	m_dispAlphaFrame = kAlphaDispFrame;
}

bool SingleRecord::isMulti()
{
	// �f�t�H���g(-1)�̏ꍇ�͈�l�v���C
	if (m_multiPlayerNum >= 0)	return true;
	return false;
}

Vec2 SingleRecord::getIconPos()
{
	float posX = static_cast<float>(m_dispData.iconX);
	float posY = static_cast<float>(m_dispData.y + 16);
	if (isMulti() && m_index == 0)
	{
		posY = 208.0f;
	}

	return Vec2{ posX,posY };
}

void SingleRecord::drawRank(int x, int y)
{
	// ?��	�̕\��	�E�[��X���W, ��[��Y���W���w�肷��
	unsigned int color = 0xffffff;
	if (m_isHighlight)	color = 0xffff00;

	assert(m_rank >= 0);
	assert(m_rank < kDispPlayerNum);

	const char* msg = Message::getInstance().get_c(kRankNameId[m_rank]);
	int tempX = x;
	int width = GetDrawFormatStringWidthToHandle(m_fontHandle, msg);

	DrawFormatStringToHandle(tempX - width, y, color, m_fontHandle, msg);
}

void SingleRecord::drawScore(int x, int y)
{
	unsigned int color = 0xffffff;
	if (m_isHighlight)	color = 0xffff00;

	int tempX = x;
	int tempScore = m_score;
	int dispDigit = 0;
	while (1)
	{
		int num = tempScore % 10;

		int width = m_numWidth[num];
		// �ő�T�C�Y�̕����̕\���͈͂���ɂ��̒����ɕ\������
		int x = tempX - m_maxWidth + (m_maxWidth - width) / 2;
		DrawFormatStringToHandle(x, y, color, m_fontHandle, std::to_string(num).c_str());

		tempX -= m_maxWidth;
		dispDigit++;

		tempScore /= 10;
		// ��̈ʂ܂ł�0�ɂȂ��Ă��悤�ƕ\������
		if (tempScore <= 0 && dispDigit >= 1)	break;

	}

	if (m_score == 1)
	{
		DrawFormatStringToHandle(x + 2, y, color, m_fontHandle, Message::getInstance().get_c("MSG_COMMON_UNIT"));
	}
	else
	{
		DrawFormatStringToHandle(x + 2, y, color, m_fontHandle, Message::getInstance().get_c("MSG_COMMON_UNITS"));
	}
}

void SingleRecord::drawScoreMulti(int x, int y)
{
	unsigned int color = 0xffffff;
	if (m_isHighlight)	color = 0xffff00;
	// �t���[���������Ԃɕϊ����ĕ\��
	Font::drawTimeFromFrame(x - 120, y, m_score, color, Font::Id::ResultScore);
}

void SingleRecord::drawPlayerNo()
{
	// �ݒ肳��Ă��Ȃ��ꍇ�͕\�����Ȃ�(��l�v���C�̏ꍇ�Ȃ�)
	if (m_playerNo < 0)	return;

	unsigned int color = Player::getColor(m_playerKind);
	Vec2 pos = m_pIcon->getPos();
	
	if (isMulti() && m_index == 0)
	{
		int width = GetDrawFormatStringWidthToHandle(Font::getHandle(Font::Id::PlayerNo), "%dP", m_playerNo + 1);
		pos.x -= width / 2;
		pos.y -= 64;
	}

	DrawFormatStringToHandle(static_cast<int>(pos.x + 8), static_cast<int>(pos.y), color, Font::getHandle(Font::Id::PlayerNo), "%dP", m_playerNo+1);
}

void SingleRecord::drawIconHighlight()
{
	int x = static_cast<int>(getIconPos().x);
	int y = static_cast<int>(getIconPos().y);

	int lineNum = 64;
	int minLen = 8;
	int randRangeLen = 32;
	float lineWidth = 2.0f;
	if (isMulti())
	{
		lineNum *= 3;
		minLen *= 3;
		randRangeLen *= 3;
		lineWidth *= 2.0f;
	}

	for (int i = 0; i < lineNum; i++)
	{
		int max = GetRand(randRangeLen) + minLen;

		float angle = DX_PI_F * i / 32;

		Vec2 end;
		end.x = cosf(angle) * max + x;
		end.y = sinf(angle) * max + y;

		DrawLineAA(static_cast<float>(x), static_cast<float>(y), end.x, end.y, 0xf0f000, lineWidth);
	}
}
