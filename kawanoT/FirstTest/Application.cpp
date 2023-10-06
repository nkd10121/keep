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
	ChangeWindowMode(true);	//非スクリーン
	//ウィンドウ名を変更
	SetWindowText(L"ごっついアクションゲーム");
	if (DxLib_Init() == -1) {	//初期化に失敗したらアプリを落とす
		return false;	//異常終了
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
