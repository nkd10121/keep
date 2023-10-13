#pragma once

class Input;
class SceneManager;
/// <summary>
/// �V�[�����N���X
/// �����ȃV�[���̊�ɂȂ�N���X
/// </summary>
class Scene
{
protected:
	SceneManager& manager_;	//�V�[���Ǘ��N���X�̎Q��

public:
	/// <summary>
	/// ��������SceneManager�̎Q�Ƃ��󂯎���Ă���
	/// </summary>
	/// <param name="manager">SceneManager�̎Q��</param>
	Scene(SceneManager& manager);

	/// <summary>
	/// �V�[���̍X�V
	/// </summary>
	/// <param name="input"></param>
	virtual void Update(Input& input) = 0;

	/// <summary>
	/// �V�[���̕`��
	/// </summary>
	virtual void Draw() = 0;
};