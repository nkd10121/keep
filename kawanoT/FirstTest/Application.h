#pragma once
#include <iostream>
/// <summary>
/// �A�v���P�[�V�����S�̂��Ǘ�����N���X
/// �V���O���g���N���X
/// </summary>
class Application
{
private:
	//�V���O���g���̂��߂�private��
	Application() {};

	//�R�s�[��������֎~
	Application(const Application& app) = delete;	//�R�s�[�R���X�g���N�^�̋֎~
	void operator=(const Application& app) = delete;	//������Z�q�����łɔp�~

	/// <summary>
	/// �㏈�����s��
	/// </summary>
	void Terminate();

public:
	/// <summary>
	/// Application�̃V���O���g���C���X�^���X�̎Q�Ƃ�Ԃ�
	/// </summary>
	/// <returns>Application�C���X�^���X</returns>
	static Application& GetInstance() {
		static Application instance;	//�������g�̐ÓI�I�u�W�F�N�g�����
		return instance;
	}

	bool Init();
	void Run();

};

