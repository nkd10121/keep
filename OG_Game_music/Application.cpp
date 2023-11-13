#include "Application.h"
#include "Scene/SceneManager.h"
#include "Scene/TitleScene.h"
#include "Input.h"

#include <DxLib.h>
#include <assert.h>

namespace
{
	constexpr int screen_width = 1280;
	constexpr int screen_height = 720;
}

void Application::Terminate()
{
	DxLib_End();
}

bool Application::Init()
{
	windowSize_ = { screen_width,screen_height };

	ChangeWindowMode(true);	//��X�N���[��
	SetGraphMode(windowSize_.w, windowSize_.h, 32);
	//�E�B���h�E����ύX
	SetWindowText("JustShapes&beats");
	if (DxLib_Init() == -1) {	//�������Ɏ��s������A�v���𗎂Ƃ�
		return false;	//�ُ�I��
	}
	SetDrawScreen(DX_SCREEN_BACK);
	return true;
}

void Application::Run()
{
	SceneManager manager;
	manager.ChangeScene(std::make_shared<TitleScene>(manager));

	Input input;

	while (ProcessMessage() != -1) {
		LONGLONG time = GetNowHiPerformanceCount();

		ClearDrawScreen();

		input.Update();
		manager.Update(input);
		manager.Draw();

		ScreenFlip();

		while (GetNowHiPerformanceCount() - time < 16667);
	}

	Terminate();
}

const Size& Application::GetWindowSize() const
{
	return windowSize_;
}
