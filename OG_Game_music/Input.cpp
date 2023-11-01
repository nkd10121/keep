#include "Input.h"
#include <DxLib.h>
#include <string>

using namespace std;

Input::Input()
{
	commandTable["OK"] = { {InputType::KeyBoard, KEY_INPUT_RETURN},
							{InputType::Pad,PAD_INPUT_A} };

	commandTable["pause"] = { {InputType::KeyBoard, KEY_INPUT_ESCAPE},
								{InputType::Pad, PAD_INPUT_R}};

	commandTable["dash"] = { {InputType::KeyBoard, KEY_INPUT_SPACE},
								{InputType::Pad, PAD_INPUT_Y} };

	commandTable["UP"] = { {InputType::KeyBoard, KEY_INPUT_W},
								{InputType::Pad, PAD_INPUT_UP} };

	commandTable["RIGHT"] = { {InputType::KeyBoard, KEY_INPUT_D},
								{InputType::Pad, PAD_INPUT_RIGHT} };

	commandTable["DOWN"] = { {InputType::KeyBoard, KEY_INPUT_S},
								{InputType::Pad, PAD_INPUT_DOWN} };

	commandTable["LEFT"] = { {InputType::KeyBoard, KEY_INPUT_A},
								{InputType::Pad, PAD_INPUT_LEFT} };
}

void Input::Update()
{
	lastInputData_ = inputData_;	//���O���͂��R�s�[���Ă���(�������u�Ԃ��擾����p)

	//�n�[�h�E�F�A���̓`�F�b�N
	char keystate[256];
	GetHitKeyStateAll(keystate);//���݂̃L�[�{�[�h���͂��擾
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);//�p�b�h���̎擾

	//�o�^���ꂽ���ƃn�[�h�̏����Ƃ炵���킹�Ȃ���
	//inputData_�̓��e���X�V���Ă���
	for (const auto& cmd : commandTable)
	{
		auto& input = inputData_[cmd.first];//�R�}���h�̖��O������̓f�[�^�����

		for (const auto& hardIO : cmd.second)
		{
			//�L�[�{�[�h�̃`�F�b�N
			input = false;
			if (hardIO.first == InputType::KeyBoard)
			{
				if (keystate[hardIO.second])
				{
					input = true;
					break;
				}
			}
			else if (hardIO.first == InputType::Pad)
			{
				if (padstate & hardIO.second)
				{
					input = true;
					break;
				}
			}
		}
	}
}

bool Input::IsTriggered(const char* command) const
{
	auto it = inputData_.find(command);
	if (it == inputData_.end())	//��񂪂Ȃ����false��Ԃ�
	{
		return false;
	}
	return (inputData_.at(command) && !lastInputData_.at(command));
}

bool Input::IsPushed(const char* command) const
{
	auto it = inputData_.find(command);
	if (it == inputData_.end())	//��񂪂Ȃ����false��Ԃ�
	{
		return false;
	}
	return (inputData_.at(command)&& lastInputData_.at(command));
}
