#include "SceneManager.h"

#include "Scene.h"

SceneManager::~SceneManager()
{

}

void SceneManager::Update(Input& input)
{
	//––”ö‚Ì‚İÀs
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//æ“ª‚©‚ç‡‚É•`‰æ
	//ÅŒã‚ÉÏ‚ñ‚¾‚à‚Ì‚ªÅŒã‚É•`‰æ‚³‚ê‚é
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes.empty())//ƒŠƒXƒg‚ª‹ó‚Á‚Û‚¾‚Á‚½‚ç“ü‚ê‘Ö‚¦‚¸‚É
	{
		scenes.push_back(nextScene);//––”ö‚É’Ç‰Á
	}
	else
	{
		scenes.back() = nextScene;//Šù‚Éˆê‚ÂˆÈã‚ ‚ê‚Î––”ö‚ğ
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