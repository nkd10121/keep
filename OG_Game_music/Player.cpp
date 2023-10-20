#include "Player.h"
#include "DxLib.h"

Player::Player()
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
}

void Player::Draw()
{
	DrawBox(10, 10, 25, 25, GetColor(255, 255, 0), true);
}
