#include "Input.h"
#include <DxLib.h>

void Input::Update()
{
	lastKeyState_ = keyState_;//前のフレームの情報を代入
	GetHitKeyStateAll(keyState_.data());//現在の入力を取得
}

bool Input::IsTriggered(const char* command) const
{
	//KEY_INPUT_RETURN == Enterキー
	return !lastKeyState_[KEY_INPUT_RETURN] && keyState_[KEY_INPUT_RETURN];
}