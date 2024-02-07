#include "Application.h"
#include "../Scene/SceneManager.h"
#include "../Scene/TitleScene.h"
#include "Input.h"
#include "Game.h"

#include <DxLib.h>
#include <assert.h>

//�ꎞ�I�Ȃ���
#include "../Scene/Stage/Stage3.h"
#include "../Scene/GameoverScene.h"
namespace
{
	constexpr int screen_width = Game::kScreenWidth;
	constexpr int screen_height = Game::kScreenHeight;
}

void Application::Terminate()
{
	DxLib_End();
}

bool Application::Init()
{
	SetChangeScreenModeGraphicsSystemResetFlag(false);
	windowSize_ = { screen_width,screen_height };
	ChangeWindowMode(true);	//��X�N���[��

	SetWindowIconID(111);

	SetGraphMode(windowSize_.w, windowSize_.h, 32);
	//�E�B���h�E����ύX
	SetWindowText("AvoidanceOfShapes");
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
	//manager.ChangeScene(std::make_shared<Stage3>(manager));
	//manager.ChangeScene(std::make_shared<GameoverScene>(manager));

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

void Application::ChangeScreenSize()
{
	isFullScreen = !isFullScreen;
	ChangeWindowMode(isFullScreen);
}

