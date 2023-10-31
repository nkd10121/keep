#pragma once
#include<array>
#include<map>
#include<string>

enum class InputType
{
	KeyBoard,
	Pad
};

class Input
{
private:
	std::map < std::string, std::map<InputType, int>> commandTable;

	//�R�}���h�̓��͂��o���Ă���
	std::map < std::string, bool> inputData_;		//���݂̓���
	std::map < std::string, bool> lastInputData_;	//���O�̓���

public:
	Input();

	/// <summary>
	/// ���͏����X�V����
	/// </summary>
	void Update();

	/// <summary>
	/// �w��̃R�}���h�������ꂽ�u�ԂȂ̂�
	/// </summary>
	/// <param name="command">�R�}���h������</param>
	/// <returns> true : �����ꂽ�u��, false : ������Ă��Ȃ����A��������</returns>
	bool IsTriggered(const char* command)const;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="command"></param>
	/// <returns></returns>
	bool IsPushed(const char* command)const;

};

