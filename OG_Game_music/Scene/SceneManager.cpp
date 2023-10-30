#include "SceneManager.h"

#include "Scene.h"

SceneManager::~SceneManager()
{

}

void SceneManager::Update(Input& input)
{
	//末尾のみ実行
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//先頭から順に描画
	//最後に積んだものが最後に描画される
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes.empty())//リストが空っぽだったら入れ替えずに
	{
		scenes.push_back(nextScene);//末尾に追加
	}
	else
	{
		scenes.back() = nextScene;//既に一つ以上あれば末尾を
	}
}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes.push_back(scene);
}

void SceneManager::popScene()
{
	scenes.pop_back();
}