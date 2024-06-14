#pragma once

// �t�H���g�֘A����
namespace Font
{
	enum class Id
	{
		Size200_8,
		Size96_8,
		Size96_4,
		Size64_4,
		Size48_4,
		Size32_4,
		Size24_4,
		Size16_4,
		Normal,	// �S�V�b�N

		// �����܂ł����������f�[�^

		Num,	// �t�H���g�̎�ނ̐�

		// �����ȍ~�͏��������f�[�^�̂ǂ���g�������w�肷��

		// SceneTitle
		GameTitle = Size200_8,
		TitleMenu = Size48_4,

		// SceneMainMenu
		MainMenuTitle = Size96_4,
		MainMenuItemL = Size64_4,
		MainMenuItemS = Size32_4,

		// SceneMain
		PlayTutorial = Size32_4,
		TutorialSkip = Size48_4,
		PlayerNo = Size16_4,
		CountDown = Size200_8,
		DispDistance = Size16_4,
		GameScore = Size32_4,
		GameScoreMulti = Size16_4,
		GameOver = Size96_8,
		GameMessage = Size96_8,
		ResultScore = Size32_4,

		// SceneRecord
		RecordBack = Size48_4,

		// SceneSelectPlayerNum
		PlayerNumTitle = Size96_4,
		PlayerNumPlayerNo = Size16_4,

		// SceneRecord
		RecordTitle = Size96_4,

		// SceneStaff
		StaffName = Size32_4,

		// UI
		TelopText = Size32_4,
	};
#if false
	// ���[�h�A�A�����[�h
	void setup();
	void release();
#else
	// �t�H���g�̃��[�h�A�A�����[�h
	void loadStart();
	void unload();

	// ���[�h�����m�F
	bool isLoaded();
	// ���[�h�I����̃f�[�^���W	�S�Ẵt�H���g���[�h���������Ă���s��
	void collectData();
#endif
	// �t�H���g�n���h���擾
	int getHandle(Id id);
	// �t�H���g�T�C�Y�擾
	int getSize(Id id);

	// ������̕��擾
	int getStringWidth( const char* pText, Id id );
	// kerning:�����Ԃ̕�	-�ŕ����Ԃ��l�߂�
	int getStringWidth(const char* pText, int handle, int kerning);

	// ������\��
	void drawString(int x, int y, const char* pText, int color, Id id);

	// �������ʒu�ɕ�����\��
	void drawStringCenter( int y, const char* pText, int color, Id id );

	// �t���[���������Ԃɕϊ����ĕ\��
	// ������W���w��	�Ƃ肠�����Q�[���Ŏg�p����"%2d:%02d.%03d"�\�L�̂�,100���𒴂���ꍇ��99:59.999��
	void drawTimeFromFrame(int x, int y, int frameCount, int color, Id id);
	// ���̊֐��Ŏ��Ԃ�\������Ƃ��̕\����
	int getDrawTimeWidth(Id id);
}
