#include "Player.h"
#include "DxLib.h"

Player::Player():
	posUp(10),
	posRight(10),
	posLeft(25),
	posDown(25)
{
}

Player::~Player()
{
}

void Player::Init()
{
}

void Player::Update()
{
	//padの十字キーを使用してプレイヤーを移動させる
	int pad = GetJoypadInputState(DX_INPUT_KEY_PAD1);

	if ((pad & PAD_INPUT_UP) != 0)
	{

	}

	if ((pad & PAD_INPUT_RIGHT) != 0)
	{
		posRight++;
		posLeft++;
	}

	if ((pad & PAD_INPUT_LEFT) != 0)
	{

	}

	if ((pad & PAD_INPUT_DOWN) != 0)
	{

	}

}

void Player::Draw()
{
	DrawBox(posRight, posUp, posLeft, posDown, GetColor(255, 255, 0), true);
}
