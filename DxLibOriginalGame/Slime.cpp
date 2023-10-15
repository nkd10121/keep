#include "Slime.h"
#include "DxLib.h"

namespace
{
	//移動速度
	constexpr float kSpeed = 3.0f;

	//キャラクターのサイズ
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//キャラクターのアニメーション
	constexpr int kUseFrame[] = { 0,1,2,1 };

	//アニメーション1コマのフレーム数
	constexpr int kAnimFrameNum = 8;

	//アニメーション1サイクルのフレーム数
	constexpr int kAnimFrameCycle = _countof(kUseFrame) * kAnimFrameNum;
}

Slime::Slime() :
	m_handle(-1),
	m_pos(640 / 2, 480/ 2),
	m_dir(kDirLeft),
	m_walkAnimFrame(0)
{
}

Slime::~Slime()
{
}

void Slime::Init()
{
}

void Slime::Update()
{
}

void Slime::Draw()
{
}
