#pragma once

// �C�x���g���ʔ�
#define EX_VER

namespace Game
{
	// �E�C���h�E���[�h�ݒ�
//	constexpr bool kWindowMode = true;
	// �E�C���h�E���[�h�����ݒ�
	constexpr bool kDefaultWindowMode = true;
	// �E�C���h�E��
	const char* const kTitleText = "�z���Q�[���I";
	// �E�C���h�E�T�C�Y
	constexpr int kScreenWidth = 1280;
	constexpr int kScreenHeight = 720;
	// �J���[���[�h
	constexpr int kColorDepth = 32;		// 32 or 16


	// �ő�v���C�l��
	constexpr int kMaxPlayer = 8;

#ifdef EX_VER
//	const char* const kExVerName = "Ver.�G���N����ƃ~�[�e�B���O";	// �G���N���o�[�W����
	const char* const kExVerName = "�I�[�v���L�����p�X�ɎQ�����Ă���Ă��肪�Ƃ��I";
#endif
};