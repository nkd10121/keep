#pragma once
class Telop
{
public:
	Telop();
	virtual ~Telop();

	// �\������e�L�X�g��ύX����Ƃ����g��
	void setup(const char* text, bool isUpper);
	// ���b�Z�[�WID���g�p���ĕ\������e�L�X�g��ݒ肷��
	void setupId(const char* textId, bool isUpper);

	void update();
	void draw();

	// �J���[�ݒ�	�f�t�H���g�͍��w�i�ɔ�����
	void setBgColor(unsigned int color) { m_bgColor = color; }
	void setTextColor(unsigned int color) { m_textColor = color; }

	void setBgAlpha(int alpha) { m_bgAlpha = alpha; }

	// �߂�{�^���\���ݒ�
	void setDispBack(bool isDisp) { m_isDispBack = isDisp; }

private:

	const char* m_text;
	bool	m_isUpper;

	unsigned int m_bgColor;
	unsigned int m_textColor;
	int m_bgAlpha;

	int m_scroll;
	int m_textWidth;

	// �߂�{�^���\��
	bool m_isDispBack;
};

