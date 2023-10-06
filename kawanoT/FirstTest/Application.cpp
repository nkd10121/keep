#include "Application.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "Input.h"

#include <DxLib.h>
#include <assert.h>


int MyLoadGraph(const wchar_t* path) {
	int handle = LoadGraph(path);
	assert(handle != -1);
	return handle;
}


void Application::Terminate()
{
	DxLib_End();
}

bool Application::Init()
{
	ChangeWindowMode(true);	//��X�N���[��
	//�E�B���h�E����ύX
	SetWindowText(L"�������A�N�V�����Q�[��");
	if (DxLib_Init() == -1) {	//�������Ɏ��s������A�v���𗎂Ƃ�
		return false;	//�ُ�I��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void Application::Run()
{
	SceneManager manager;
	manager.ChangeScene(new TitleScene(manager));

	Input input;

	while (ProcessMessage() != -1) {
		ClearDrawScreen();

		input.Update();
		manager.Update(input);
		manager.Draw();

		ScreenFlip();
	}
	
	Terminate();
}
