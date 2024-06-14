#pragma once
#include "Vec2.h"
#include <string>
#include <vector>
#include "Rect.h"

// ���o�t��������\���N���X
class EffectString
{
public:
	// �\���G�t�F�N�g�̎��
	enum class Effect
	{
		None,		// �G�t�F�N�g�����ʏ�`��
		Vibration,	// 1�������h���
		AlphaBlink,	// �_��
	};

	// In���o�̎��
	enum class In
	{
		None,		// �Ȃ��@�p�b�ƕ\��
		Fade,		// �t�F�[�h�C��
	};

	// Out���o�̎��
	enum class Out
	{
		None,		// �Ȃ��@�p�b�Ə�����
		Fade,		// �t�F�[�h�A�E�g
	};


public:
	EffectString();
	virtual ~EffectString();

	// ������W�w��
	void setup(int x, int y, const char* str, int fontHandle, int kerning = 0);
	void setup(Vec2 pos, const char* str, int fontHandle, int kerning = 0);
	// ���S���W�w��
	void setupCenter(int x, int y, const char* str, int fontHandle, int kerning = 0);
	void setupCenter(Vec2 pos, const char* str, int fontHandle, int kerning = 0);
	// �E����W�w��
	void setupRight(int x, int y, const char* str, int fontHandle, int kerning = 0);
	void setupRight(Vec2 pos, const char* str, int fontHandle, int kerning = 0);

	// �Q�[���p�ݒ�
	// �e�V�[���̃^�C�g���\���ݒ�	��ʒ����㕔�ɑ傫���\��
	void setupSceneTitle(const char* str);


	// �J�n���o
	// wait:�J�n���o���n�܂�܂ł̃t���[����
	void startIn(In type, int wait = 0);
	// �I�����o
	// wait:�I�����o���n�܂�܂ł̃t���[����
	void startOut(Out type, int wait = 0);

	// �J�n���o�I�����Ă��邩�`�F�b�N(updateStatic�̏ꍇ�̂�true��Ԃ�)
	bool isInEnd() const;

	// �\���ݒ�
	void setColor(unsigned int color);

	// �\���G�t�F�N�g�̎�ނ�ݒ�
	void setEffect(Effect effect);

	// ������N���A
	void clear();

	void update();
	void draw();

	// �����̕\���͈͂��擾����
	Rect getRect() const;

private:

	// �V�[�P���X��update
	void updateIn();
	void updateStatic();
	void updateOut();
	void updateOutEnd();

	// ���o��update����
	void updateNone();
	void updateVibration();		// �P�������h���
	void updateAlphaBlink();	// �A���t�@�_��

private:
	// �����P�������̃f�[�^
	struct CharData
	{
		std::string chr;
		Vec2 basePos;	// �ʏ�`����s�����ꍇ�̕\���ʒu
		Vec2 dispPos;	// ���ۂɕ\�����s���ʒu
		unsigned int color;
		int alpha;

		float sinRate;	// ���o�p
	};
private:
	// �V�[�P���X��update����
	void (EffectString::* m_updateFunc)() = &EffectString::updateIn;
	// ���o��update����
	void (EffectString::* m_effectFunc)() = &EffectString::updateNone;
	// �g�p����t�H���g
	int m_fontHandle;
	// �P�������ɕ��������f�[�^
	std::vector<CharData>	m_char;

	// �J�[�j���O(�����Ԋu)	�f�t�H���g0�Ń}�C�i�X�ɂ���Ƌl�܂�
	int m_kerning;

	// ���o�̎��
	Effect	m_effect;	// �\�����o
	In		m_in;		// In���o
	Out		m_out;		// Out���o

	// �\������
	int m_waitFrame;
	int m_frameCount;
};

