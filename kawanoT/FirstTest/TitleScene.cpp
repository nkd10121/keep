#include <DxLib.h>

#include "Input.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include "GamePlayingScene.h"
TitleScene::TitleScene(SceneManager& manager) : 
	Scene(manager)
{

}

void TitleScene::Update(Input& input)
{
	if (input.IsTriggered("OK"))
	{
		manager_.ChangeScene(new GamePlayingScene(manager_));
	}
}

void TitleScene::Draw()
{
	DrawString(100, 100, L"TitleScene", 0xffffff);
}
