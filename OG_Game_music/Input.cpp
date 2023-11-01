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
	lastInputData_ = inputData_;	//直前入力をコピーしておく(押した瞬間を取得する用)

	//ハードウェア入力チェック
	char keystate[256];
	GetHitKeyStateAll(keystate);//現在のキーボード入力を取得
	int padstate = GetJoypadInputState(DX_INPUT_PAD1);//パッド情報の取得

	//登録された情報とハードの情報を照らし合わせながら
	//inputData_の内容を更新していく
	for (const auto& cmd : commandTable)
	{
		auto& input = inputData_[cmd.first];//コマンドの名前から入力データを作る

		for (const auto& hardIO : cmd.second)
		{
			//キーボードのチェック
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
	if (it == inputData_.end())	//情報がなければfalseを返す
	{
		return false;
	}
	return (inputData_.at(command) && !lastInputData_.at(command));
}

bool Input::IsPushed(const char* command) const
{
	auto it = inputData_.find(command);
	if (it == inputData_.end())	//情報がなければfalseを返す
	{
		return false;
	}
	return (inputData_.at(command)&& lastInputData_.at(command));
}
