#pragma once

namespace Pad
{
	// �ڑ����Ă���p�b�h�̐��擾
	int getPadNum();

	// �p�b�h�̓��͏�Ԏ擾
	void update();

	// ������������
	bool isPress(int button, int padNo = 0);
	// �g���K�[����
	bool isTrigger(int button, int padNo = 0);
	// �A�i���O�X�e�B�b�N���͏��
	int getAnalogX(int padNo = 0);
	int getAnalogY(int padNo = 0);

	// �U��
	void vibrationLow(int padNo = 0);
	void vibrationMiddle(int padNo = 0);
	void vibrationHard(int padNo = 0);
}
