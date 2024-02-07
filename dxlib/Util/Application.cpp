#include "Application.h"
#include "../Scene/SceneManager.h"
#include "../Scene/TitleScene.h"
#include "Input.h"
#include "Game.h"

#include <DxLib.h>
#include <assert.h>

//一時的なもの
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
	ChangeWindowMode(true);	//非スクリーン

	SetWindowIconID(111);

	SetGraphMode(windowSize_.w, windowSize_.h, 32);
	//ウィンドウ名を変更
	SetWindowText("AvoidanceOfShapes");
	if (DxLib_Init() == -1) {	//初期化に失敗したらアプリを落とす
		return false;	//異常終了
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

