#pragma once
#include <list> 
#include <memory>
class Input;
class Scene;

class SceneManager
{
private:
	std::list < std::shared_ptr<Scene>> scenes;

public:
	~SceneManager();

	/// <summary>
	/// �����Ă���V�[����Update�֐����Ăяo��
	/// </summary>
	/// <param name="input">���̓N���X</param>
	void Update(Input& input);

	/// <summary>
	/// �����Ă���V�[����Draw�֐����Ăяo��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���s���̃V�[���������Ŏw�肵���V�[���ɐ؂�ւ���
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// ���ݐ擪�Ŏ��s���̃V�[���̏�ɃV�[�����������
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// ���݂̐擪�V�[�����폜����
	/// </summary>
	void popScene();
};

