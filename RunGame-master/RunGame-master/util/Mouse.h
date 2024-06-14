#pragma once

#include "Vec2.h"

// �}�E�X�̓��͏�Ԃ��擾����
namespace Mouse
{
	// �}�E�X���O���̃N���A
	void clear();
	// �}�E�X�̓��͏�Ԏ擾
	void update();

	// �}�E�X���O�̐����擾
	int getLogNum();

	// ���݂̃}�E�X�ʒu�擾
	// �ߋ��̈ʒu�����擾�ł���
	// logNo = 0�Ō��݂̈ʒu���	�傫������Ɖߋ��t���[���̏��
	// getLogNum()�������w�肷��
	Vec2 getPos(int logNo = 0);

	// ������������
	bool isPressLeft();
	bool isPressRight();
	// �g���K�[����
	bool isTriggerLeft();
	bool isTriggerRight();
	// ����������
	bool isRelaseLeft();
	bool isRelaseRight();
}
