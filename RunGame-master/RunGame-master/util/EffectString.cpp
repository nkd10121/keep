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
	m_in = In::None;	// 設定しなければINOUT演出無し
	m_out = Out::None;
	m_waitFrame = 0;
	m_frameCount = 0;

	m_fontHandle = fontHandle;
	m_kerning = kerning;
	
	// 文字列を１文字ずつ分解する
	std::string temp = str;
	int byteCount = 0;
	int dispX = x;
	int dispY = y;
	while (1)
	{
		if (byteCount > temp.size())
		{
			// 終了
			break;
		}
		// 1文字分のデータ
		CharData data;

		// 表示する文字のバイト数チェック
		int size = 0;
		unsigned char charData = temp[byteCount];	// チェックする文字
		if (charData < 0x80)
		{
			size = 1;
		}
		else
		{
			size = 2;
		}

		// 除外する文字
		if (temp.substr(byteCount, size) == "\0")
		{
			byteCount += size;
			continue;
		}

		// データ作成
		data.chr = temp.substr(byteCount, size);
		data.basePos.x = static_cast<float>(dispX);
		data.basePos.y = static_cast<float>(dispY);
		data.dispPos = data.basePos;
		data.color = 0xffffff;
		data.alpha = 255;
		data.sinRate = 0.0;

		// １文字進める
		dispX += GetDrawStringWidthToHandle(temp.substr(byteCount, size).c_str(), size, m_fontHandle);
		dispX += m_kerning;
		byteCount += size;
		// 1文字分のデータを登録
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
	// フェードイン開始
	for (auto& data : m_char)
	{
		if (wait <= 0)
		{
			// waitに0を指定された場合は最初から表示された状態に
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
	// フェードアウト開始
	for (auto& data : m_char)
	{
		if (wait <= 0)
		{
			// waitに0を指定された場合は最初から消す
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
	// 終了演出が終わっていたら表示しない
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
		// 文字のサイズ
		int width = GetDrawStringWidthToHandle(data.chr.c_str(), static_cast<int>(data.chr.size()), m_fontHandle);
		int height = 0;
		GetFontStateToHandle(nullptr, &height, nullptr, m_fontHandle);
		// 文字の上下左右位置を取得
		float left = data.dispPos.x;
		float top = data.dispPos.y;
		float right = left + width;
		float bottom = top + height;

		if (!isInit)
		{
			// 未初期化	最初の1文字の表示範囲をRectに設定する
			result.setup(left, top, right, bottom);
			isInit = true;
		}
		else
		{
			// 2文字目以降 rectのサイズを広げていく
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
	// in中も行う演出
	(this->*m_effectFunc)();

	m_waitFrame--;
	if (m_waitFrame > 0)	return;	// 演出開始までの待ち時間

	m_waitFrame = 0;

	bool isEnd = false;	// In演出終了
	switch (m_in)
	{
	case In::None:
		// 即staticに遷移
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
				// Inしきっていない文字があったら続ける
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
	// out中も行う演出
	(this->*m_effectFunc)();

	m_waitFrame--;
	if (m_waitFrame > 0)	return;	// 演出開始までの待ち時間

	m_waitFrame = 0;

	bool isEnd = false;	// out演出終了
	switch (m_in)
	{
	case In::None:
		// 即OutEndに遷移
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
				// Outしきっていない文字があったら続ける
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
	// 何もしない
}

void EffectString::updateNone()
{
	// 最初に決めた位置を表示位置に
	for (auto& data : m_char)
	{
		data.dispPos.x = data.basePos.x;
		data.dispPos.y = data.basePos.y;
	}
}

void EffectString::updateVibration()
{
	// １文字ずつ揺らす
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
		data.sinRate += DX_PI_F / 60;	// 60フレーム１サイクル
		if (data.sinRate > DX_PI_F)	data.sinRate -= DX_PI_F;

		data.alpha = static_cast<int>(sinf(data.sinRate) * 255);
	}
}
