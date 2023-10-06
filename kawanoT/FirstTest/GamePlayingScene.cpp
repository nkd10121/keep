#include "GamePlayingScene.h"
#include "Input.h"
#include "GameOverScene.h"
#include "SceneManager.h"
#include <DxLib.h>

GamePlayingScene::GamePlayingScene(SceneManager& mgr) : 
	Scene(mgr)
{
}
void GamePlayingScene::Update(Input& input)
{
	if(input.IsTriggered("OK"))
	{
		manager_.ChangeScene(new GameOverScene(manager_));
	}
}

void GamePlayingScene::Draw()
{
	DrawString(100, 100, L"GamePlayingScene", 0xffffff);
}
