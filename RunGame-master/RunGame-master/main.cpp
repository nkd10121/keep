#include "DxLib.h"

#include "SaveData.h"
#include "ConfigData.h"
#include "Sound.h"
#include "Message.h"

#include <memory>
#include "game.h"
#include "SceneManager.h"
#include "Font.h"
#include "Player.h"

#include <filesystem>

#ifdef _DEBUG
//#define DISP_LOADTIME
#endif // _DEBUG

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
#ifdef DISP_LOADTIME
	LONGLONG  loadStart = 0;
#endif

#ifndef _DEBUG
	SetOutApplicationLogValidFlag(false);
#endif


#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif // DISP_LOADTIME
	// �Z�[�u�f�[�^�ۑ��p�̃t�H���_���Ȃ��ꍇ��������
	if (!std::filesystem::is_directory("save"))
	{
		std::filesystem::create_directory("save");
	}

	// �Z�[�u�f�[�^�ǂݍ���	�t���X�N���[���ݒ��ǂݍ��ނ̂ōŏ���
	SaveData::getInstance().load();
	ConfigData::getInstance().load();
#ifdef DISP_LOADTIME
	printfDx("savedata load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// window���[�h�ݒ�
	ChangeWindowMode(!ConfigData::getInstance().isOn(ConfigData::FullScreen));
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);
	// ��ʂ���A�N�e�B�u�ł�����
	SetAlwaysRunFlag(true);
	// �E�C���h�E�A�t���X�N���[���؂�ւ��ɑΉ�
	SetChangeScreenModeGraphicsSystemResetFlag(false);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif // DISP_LOADTIME
	// ���b�Z�[�W�̃��[�h
	Message::getInstance().load(static_cast<Message::LANG>(ConfigData::getInstance().getLanguage()));
#ifdef DISP_LOADTIME
	printfDx("messagedata load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// �T�E���h�̃��[�h
#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif // DISP_LOADTIME
	Sound::getInstance().loadStart();
#ifdef DISP_LOADTIME
	printfDx("sound load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// �t�H���g�̓ǂݍ��݁A����
#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif
	Font::loadStart();
#ifdef DISP_LOADTIME
	printfDx("font load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

#ifdef DISP_LOADTIME
	loadStart = GetNowHiPerformanceCount();
#endif
	// �풓���\�[�X�̓ǂݍ��݊J�n
	Player::startLoad();
#ifdef DISP_LOADTIME
	printfDx("player graph load : %d\n", GetNowHiPerformanceCount() - loadStart);
#endif

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	SceneManager* pScene = new SceneManager;
	pScene->init();

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		if (!pScene->update())	break;

		pScene->draw();

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}

	pScene->end();

	// �풓���\�[�X�̉��
	Player::unload();

	// �T�E���h�̉��
	Sound::getInstance().unload();

	// �t�H���g�̉��
	Font::unload();

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}