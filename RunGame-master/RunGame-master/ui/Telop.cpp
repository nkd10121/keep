#include "Telop.h"
#include "DxLib.h"
#include "game.h"
#include "Font.h"
#include "Pad.h"
#include "Message.h"

namespace
{
	constexpr int kTelopBgHeight = 48;

	// �f�t�H���g�J���[
	constexpr unsigned int kDefaultBgColor = 0x000000;
	constexpr unsigned int kDefaultTextColor = 0xffffff;
	constexpr int kDefaultBgAlpha = 160;

	// �e�L�X�g�̃X�N���[�����x
	constexpr int kScrollSpeed = 2;
	constexpr int kScrollSpeedHigh = kScrollSpeed * 4;

	// �e�L�X�g�����[�v������Ƃ��̑O�̕�����Ƃ̊Ԋu
	constexpr int kLoopTextSpace = 64;
}

Telop::Telop():
	m_text(nullptr),
	m_isUpper(false),
	m_bgColor(kDefaultBgColor),
	m_textColor(kDefaultTextColor),
	m_bgAlpha(kDefaultBgAlpha),
	m_scroll(0),
	m_textWidth(0),
	m_isDispBack(false)
{
}

Telop::~Telop()
{
}

void Telop::setup(const char* text, bool isUpper)
{
	m_text = text;
	m_isUpper = isUpper;
	m_textWidth = GetDrawStringWidthToHandle(m_text, static_cast<int>(strlen(m_text)), Font::getHandle(Font::Id::TelopText));
}

void Telop::setupId(const char* textId, bool isUpper)
{
	setup(Message::getInstance().get_c(textId), isUpper);
}

void Telop::update()
{
	if (Pad::isPress(PAD_INPUT_5) || Pad::isPress(PAD_INPUT_6))
	{
		// LR�L�[�Ńe�L�X�g�����X�N���[��		5or6
		m_scroll += kScrollSpeedHigh;
	}
	else
	{
		m_scroll += kScrollSpeed;
	}
	

	if (m_scroll >= m_textWidth + kLoopTextSpace)
	{
		m_scroll -= m_textWidth + kLoopTextSpace;
	}
}

void Telop::draw()
{
	int y = 0;
	if (!m_isUpper)	y = Game::kScreenHeight - kTelopBgHeight;
	// �e���b�v��BG
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, m_bgAlpha);
	DrawBox(0, y, Game::kScreenWidth, y + kTelopBgHeight, m_bgColor, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	int textX = -m_scroll;
	y += (kTelopBgHeight - Font::getSize(Font::Id::TelopText)) / 2;	// �����ɕ\�������悤����

	while (1)
	{
		Font::drawString(textX, y, m_text, m_textColor, Font::Id::TelopText);
		textX += m_textWidth + kLoopTextSpace;

		if (textX >= Game::kScreenWidth)	break;
	}
	if (m_isDispBack)
	{
		// B�{�^���Ŗ߂�\��
		y = 0;
		if (!m_isUpper)	y = Game::kScreenHeight - kTelopBgHeight;

		DrawBox(Game::kScreenWidth - 160, y, Game::kScreenWidth, y + kTelopBgHeight, 0xff0000, true);
		DrawBox(Game::kScreenWidth - 160 + 2, y + 2, Game::kScreenWidth - 2, y + kTelopBgHeight - 2, 0xffffff, false);
		int width = Font::getStringWidth(Message::getInstance().get_c("MSG_COMMON_T_BACK"), Font::Id::TelopText);
		Font::drawString(Game::kScreenWidth - 80 - width / 2, y + 10, Message::getInstance().get_c("MSG_COMMON_T_BACK"), 0xffffff, Font::Id::TelopText);
	}
}
