#include "EffectString.h"
#include "DxLib.h"
#include "Font.h"
#include "game.h"

EffectString::EffectString():
	m_fontHandle(-1),
	m_kerning(0),
	m_effect(Effect::None),
	m_in(In::None),
	m_out(Out::None),
	m_waitFrame(0),
	m_frameCount(0)
{
}

EffectString::~EffectString()
{
}

void EffectString::setup(int x, int y, const char* str, int fontHandle, int kerning)
{
	if (!str)	return;

	m_updateFunc = &EffectString::updateIn;
	m_in = In::None;	// �ݒ肵�Ȃ����INOUT���o����
	m_out = Out::None;
	m_waitFrame = 0;
	m_frameCount = 0;

	m_fontHandle = fontHandle;
	m_kerning = kerning;
	
	// ��������P��������������
	std::string temp = str;
	int byteCount = 0;
	int dispX = x;
	int dispY = y;
	while (1)
	{
		if (byteCount > temp.size())
		{
			// �I��
			break;
		}
		// 1�������̃f�[�^
		CharData data;

		// �\�����镶���̃o�C�g���`�F�b�N
		int size = 0;
		unsigned char charData = temp[byteCount];	// �`�F�b�N���镶��
		if (charData < 0x80)
		{
			size = 1;
		}
		else
		{
			size = 2;
		}

		// ���O���镶��
		if (temp.substr(byteCount, size) == "\0")
		{
			byteCount += size;
			continue;
		}

		// �f�[�^�쐬
		data.chr = temp.substr(byteCount, size);
		data.basePos.x = static_cast<float>(dispX);
		data.basePos.y = static_cast<float>(dispY);
		data.dispPos = data.basePos;
		data.color = 0xffffff;
		data.alpha = 255;
		data.sinRate = 0.0;

		// �P�����i�߂�
		dispX += GetDrawStringWidthToHandle(temp.substr(byteCount, size).c_str(), size, m_fontHandle);
		dispX += m_kerning;
		byteCount += size;
		// 1�������̃f�[�^��o�^
		m_char.push_back(data);
	}
}

void EffectString::setup(Vec2 pos, const char* str, int fontHandle, int kerning)
{
	setup(static_cast<int>(pos.x), static_cast<int>(pos.y), str, fontHandle, kerning);
}

void EffectString::setupCenter(int x, int y, const char* str, int fontHandle, int kerning)
{
	int width = Font::getStringWidth(str, fontHandle, kerning);
	int height = 0;
	GetFontStateToHandle(nullptr, &height, nullptr, fontHandle);

	setup(x - width / 2, y - height / 2, str, fontHandle, kerning);
}

void EffectString::setupCenter(Vec2 pos, const char* str, int fontHandle, int kerning)
{
	setupCenter(static_cast<int>(pos.x), static_cast<int>(pos.y), str, fontHandle, kerning);
}

void EffectString::setupRight(int x, int y, const char* str, int fontHandle, int kerning)
{
	int width = Font::getStringWidth(str, fontHandle, kerning);
	int height = 0;
	GetFontStateToHandle(nullptr, &height, nullptr, fontHandle);

	setup(x - width, y, str, fontHandle, kerning);
}

void EffectString::setupRight(Vec2 pos, const char* str, int fontHandle, int kerning)
{
	setupRight(static_cast<int>(pos.x), static_cast<int>(pos.y), str, fontHandle, kerning);
}

void EffectString::setupSceneTitle(const char* str)
{
	setupCenter(Game::kScreenWidth / 2, 96, str, Font::getHandle(Font::Id::PlayerNumTitle), -16);
	setColor(0xff0000);
	setEffect(EffectString::Effect::Vibration);
	startIn(EffectString::In::None, 0);
}

void EffectString::startIn(In type, int wait)
{
	m_updateFunc = &EffectString::updateIn;
	m_in = type;
	m_waitFrame = wait;
	// �t�F�[�h�C���J�n
	for (auto& data : m_char)
	{
		if (wait <= 0)
		{
			// wait��0���w�肳�ꂽ�ꍇ�͍ŏ�����\�����ꂽ��Ԃ�
			data.alpha = 255;
		}
		else
		{
			data.alpha = 0;
		}
	}
}

void EffectString::startOut(Out type, int wait)
{
	m_updateFunc = &EffectString::updateOut;
	m_out = type;
	// �t�F�[�h�A�E�g�J�n
	for (auto& data : m_char)
	{
		if (wait <= 0)
		{
			// wait��0���w�肳�ꂽ�ꍇ�͍ŏ��������
			data.alpha = 0;
		}
		else
		{
			data.alpha = 255;
		}
	}
}

bool EffectString::isInEnd() const
{
	return (m_updateFunc == &EffectString::updateStatic);
}

void EffectString::setColor(unsigned int color)
{
	for (auto& data : m_char)
	{
		data.color = color;
	}
}

void EffectString::setEffect(Effect effect)
{
	m_effect = effect;
	switch (m_effect)
	{
	case Effect::None:
		m_effectFunc = &EffectString::updateNone;
		break;
	case Effect::Vibration:
		m_effectFunc = &EffectString::updateVibration;
		break;
	case Effect::AlphaBlink:
		m_effectFunc = &EffectString::updateAlphaBlink;
		break;
	}
}

void EffectString::clear()
{
	m_char.clear();
}

void EffectString::update()
{
	(this->*m_updateFunc)();
}

void EffectString::draw()
{
	// �I�����o���I����Ă�����\�����Ȃ�
	if (m_updateFunc == &EffectString::updateOutEnd)	return;

	for (auto& data : m_char)
	{
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, data.alpha);
		DrawStringToHandle(static_cast<int>(data.dispPos.x), static_cast<int>(data.dispPos.y), data.chr.c_str(), data.color, m_fontHandle);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
}

Rect EffectString::getRect() const
{
	Rect result;
	bool isInit = false;

	for (auto& data : m_char)
	{
		// �����̃T�C�Y
		int width = GetDrawStringWidthToHandle(data.chr.c_str(), static_cast<int>(data.chr.size()), m_fontHandle);
		int height = 0;
		GetFontStateToHandle(nullptr, &height, nullptr, m_fontHandle);
		// �����̏㉺���E�ʒu���擾
		float left = data.dispPos.x;
		float top = data.dispPos.y;
		float right = left + width;
		float bottom = top + height;

		if (!isInit)
		{
			// ��������	�ŏ���1�����̕\���͈͂�Rect�ɐݒ肷��
			result.setup(left, top, right, bottom);
			isInit = true;
		}
		else
		{
			// 2�����ڈȍ~ rect�̃T�C�Y���L���Ă���
			if (left < result.getLeft())		result.setLeft(left);
			if (right > result.getRight())		result.setRight(right);
			if (top < result.getTop())			result.setTop(top);
			if (bottom > result.getBottom())	result.setBottom(bottom);
		}
	}

	return result;
}

void EffectString::updateIn()
{
	// in�����s�����o
	(this->*m_effectFunc)();

	m_waitFrame--;
	if (m_waitFrame > 0)	return;	// ���o�J�n�܂ł̑҂�����

	m_waitFrame = 0;

	bool isEnd = false;	// In���o�I��
	switch (m_in)
	{
	case In::None:
		// ��static�ɑJ��
		for (auto& data : m_char)
		{
			data.alpha = 255;
		}
		isEnd = true;
		break;
	case In::Fade:
		isEnd = true;
		for (auto& data : m_char)
		{
			data.alpha += 8;
			if (data.alpha >= 255)
			{
				data.alpha = 255;
			}
			else
			{
				// In�������Ă��Ȃ��������������瑱����
				isEnd = false;
			}
		}
		break;
	}

	if (isEnd)
	{
		m_updateFunc = &EffectString::updateStatic;
	}
}

void EffectString::updateStatic()
{
	(this->*m_effectFunc)();
}

void EffectString::updateOut()
{
	// out�����s�����o
	(this->*m_effectFunc)();

	m_waitFrame--;
	if (m_waitFrame > 0)	return;	// ���o�J�n�܂ł̑҂�����

	m_waitFrame = 0;

	bool isEnd = false;	// out���o�I��
	switch (m_in)
	{
	case In::None:
		// ��OutEnd�ɑJ��
		for (auto& data : m_char)
		{
			data.alpha = 0;
		}
		isEnd = true;
		break;
	case In::Fade:
		isEnd = true;
		for (auto& data : m_char)
		{
			data.alpha -= 8;
			if (data.alpha <= 0)
			{
				data.alpha = 0;
			}
			else
			{
				// Out�������Ă��Ȃ��������������瑱����
				isEnd = false;
			}
		}
		break;
	}

	if (isEnd)
	{
		m_updateFunc = &EffectString::updateOutEnd;
	}
}

void EffectString::updateOutEnd()
{
	// �������Ȃ�
}

void EffectString::updateNone()
{
	// �ŏ��Ɍ��߂��ʒu��\���ʒu��
	for (auto& data : m_char)
	{
		data.dispPos.x = data.basePos.x;
		data.dispPos.y = data.basePos.y;
	}
}

void EffectString::updateVibration()
{
	// �P�������h�炷
	m_frameCount++;
	if (m_frameCount >= 4)
	{
		for (auto& data : m_char)
		{
			data.dispPos.x = data.basePos.x + GetRand(4) - 2;
			data.dispPos.y = data.basePos.y + GetRand(4) - 2;
		}

		m_frameCount = 0;
	}
}

void EffectString::updateAlphaBlink()
{
	for (auto& data : m_char)
	{
		data.sinRate += DX_PI_F / 60;	// 60�t���[���P�T�C�N��
		if (data.sinRate > DX_PI_F)	data.sinRate -= DX_PI_F;

		data.alpha = static_cast<int>(sinf(data.sinRate) * 255);
	}
}
