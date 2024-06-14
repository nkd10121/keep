#pragma once
class Telop
{
public:
	Telop();
	virtual ~Telop();

	// 表示するテキストを変更するときも使う
	void setup(const char* text, bool isUpper);
	// メッセージIDを使用して表示するテキストを設定する
	void setupId(const char* textId, bool isUpper);

	void update();
	void draw();

	// カラー設定	デフォルトは黒背景に白文字
	void setBgColor(unsigned int color) { m_bgColor = color; }
	void setTextColor(unsigned int color) { m_textColor = color; }

	void setBgAlpha(int alpha) { m_bgAlpha = alpha; }

	// 戻るボタン表示設定
	void setDispBack(bool isDisp) { m_isDispBack = isDisp; }

private:

	const char* m_text;
	bool	m_isUpper;

	unsigned int m_bgColor;
	unsigned int m_textColor;
	int m_bgAlpha;

	int m_scroll;
	int m_textWidth;

	// 戻るボタン表示
	bool m_isDispBack;
};

