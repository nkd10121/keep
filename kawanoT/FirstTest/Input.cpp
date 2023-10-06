#include "Input.h"
#include <DxLib.h>

void Input::Update()
{
	lastKeyState_ = keyState_;//�O�̃t���[���̏�����
	GetHitKeyStateAll(keyState_.data());//���݂̓��͂��擾
}

bool Input::IsTriggered(const char* command) const
{
	return !lastKeyState_[KEY_INPUT_RETURN] && keyState_[KEY_INPUT_RETURN];
}