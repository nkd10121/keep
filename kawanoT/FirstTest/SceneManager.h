#pragma once
class Input;
class Scene;

/// <summary>
/// �e�V�[���̑J�ڂƑ�����R���g���[������N���X
/// </summary>
class SceneManager
{
private:
	Scene* scene_ = nullptr;
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
	/// ���ݎ��s���̃V�[���������Ŏw�肳�ꂽ�V�[���ɐ؂�ւ���
	/// </summary>
	void ChangeScene(Scene* nextScene);
};

