#include "GameOverScene.h"
#include "Input.h"
#include "TitleScene.h"
#include "SceneManager.h"
#include <DxLib.h>

GameOverScene::GameOverScene(SceneManager& mgr) : Scene(mgr)
{
}

void GameOverScene::Update(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		manager_.ChangeScene(new TitleScene(manager_));
	}
}

void GameOverScene::Draw()
{
	DrawString(100, 100, L"GameOverScene", 0xffffff);
}
