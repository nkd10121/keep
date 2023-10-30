#include "SceneManager.h"

#include "Scene.h"

SceneManager::~SceneManager()
{

}

void SceneManager::Update(Input& input)
{
	//�����̂ݎ��s
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//�擪���珇�ɕ`��
	//�Ō�ɐς񂾂��̂��Ō�ɕ`�悳���
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes.empty())//���X�g������ۂ����������ւ�����
	{
		scenes.push_back(nextScene);//�����ɒǉ�
	}
	else
	{
		scenes.back() = nextScene;//���Ɉ�ȏ゠��Ζ�����
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