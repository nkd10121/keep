#pragma once
#include <iostream>
/// <summary>
/// �A�v���P�[�V�����S�̂��Ǘ�����N���X
/// �V���O���g���N���X
/// </summary>
class Application
{
private:
	Application() {};

	//�R�s�[��������֎~
	Application(const Application& app) = delete;
	void operator=(const Application& app) = delete;

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
		static Application instance;
		return instance;
	}

	bool Init();
	void Run();

};

