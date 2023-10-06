#include "SceneManager.h"
#include "Scene.h"

SceneManager::~SceneManager()
{
	delete scene_;
}

void SceneManager::Update(Input& input)
{
	scene_->Update(input);
}

void SceneManager::Draw()
{
	scene_->Draw();
}

void SceneManager::ChangeScene(Scene* nextScene)
{
	//‘O‚ÌƒV[ƒ“‚ª‚ ‚Á‚½‚ç‰ğ•ú‚µ‚Ä‚¨‚­
	if (scene_ != nullptr)
	{
		delete scene_;
	}
	scene_ = nextScene;
}
