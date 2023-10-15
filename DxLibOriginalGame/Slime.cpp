#include "Slime.h"
#include "DxLib.h"

namespace
{
	//�ړ����x
	constexpr float kSpeed = 3.0f;

	//�L�����N�^�[�̃T�C�Y
	constexpr int kWidth = 64;
	constexpr int kHeight = 64;

	//�L�����N�^�[�̃A�j���[�V����
	constexpr int kUseFrame[] = { 0,1,2,1 };

	//�A�j���[�V����1�R�}�̃t���[����
	constexpr int kAnimFrameNum = 8;

	//�A�j���[�V����1�T�C�N���̃t���[����
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
