#include "Input.h"
#include <DxLib.h>

void Input::Update()
{
	lastKeyState_ = keyState_;//‘O‚ÌƒtƒŒ[ƒ€‚Ìî•ñ‚ğ‘ã“ü
	GetHitKeyStateAll(keyState_.data());//Œ»İ‚Ì“ü—Í‚ğæ“¾
}

bool Input::IsTriggered(const char* command) const
{
	return !lastKeyState_[KEY_INPUT_RETURN] && keyState_[KEY_INPUT_RETURN];
}