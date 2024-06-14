#include "DxLib.h"
#include "Pad.h"
#include "ConfigData.h"

#include <array>
#include <deque>
#include <cassert>

namespace
{
	// ���O�L�^�t���[����
	constexpr int kLogNum = 16;
	// 
	constexpr int kUsePadData[] =
	{
		DX_INPUT_KEY_PAD1,
		DX_INPUT_PAD2,
		DX_INPUT_PAD3,
		DX_INPUT_PAD4,
		DX_INPUT_PAD5,
		DX_INPUT_PAD6,
		DX_INPUT_PAD7,
		DX_INPUT_PAD8,
	};
	// �p�b�h�ő吔
	constexpr int kMaxPad = _countof(kUsePadData);

	// ���t���[�����W����p�b�h���͏��
	struct PadLog
	{
		int key;	// �{�^����ONOFF���
		int stickX;	// �A�i���O�p�b�h���͏��
		int stickY;
	};

	std::array<std::deque<PadLog>, kMaxPad>	padLog;
}

namespace Pad
{
	int getPadNum()
	{
		return GetJoypadNum();
	}
	// �p�b�h�̓��͏�Ԏ擾
	void update()
	{
		for (int padNo = 0; padNo < kMaxPad; padNo++)
		{
			// ���݂̃p�b�h�̏�Ԃ��擾
			PadLog input;
			input.key = GetJoypadInputState(kUsePadData[padNo]);
			GetJoypadAnalogInput(&input.stickX, &input.stickY, kUsePadData[padNo]);

			padLog[padNo].push_front(input);
			if (padLog[padNo].size() > kLogNum)
			{
				padLog[padNo].pop_back();
			}
		}
	}

	// ������������
	bool isPress(int button, int padNo)
	{
		assert(padNo < kMaxPad);
		return (padLog[padNo][0].key & button);
	}
	// �g���K�[����
	bool isTrigger(int button, int padNo)
	{
		assert(padNo < kMaxPad);
		bool isNow = (padLog[padNo][0].key & button);	// ���݂̏��
		bool isLast = (padLog[padNo][1].key & button);	// �P�t���[���O�̏��
		return (isNow && !isLast);
	}
	int getAnalogX(int padNo)
	{
		assert(padNo < kMaxPad);
		return padLog[padNo][0].stickX;
	}
	int getAnalogY(int padNo)
	{
		assert(padNo < kMaxPad);
		return padLog[padNo][0].stickY;
	}
	void vibrationLow(int padNo)
	{
		// �U��OFF
		if (!ConfigData::getInstance().isOn(ConfigData::Vibration))	return;
		StartJoypadVibration(kUsePadData[padNo], 200, 30);
	//	StartJoypadVibration(DX_INPUT_PAD8, 100, 100);	// test
	}
	void vibrationMiddle(int padNo)
	{
		// �U��OFF
		if (!ConfigData::getInstance().isOn(ConfigData::Vibration))	return;
		StartJoypadVibration(kUsePadData[padNo], 500, 200);
	}
	void vibrationHard(int padNo)
	{
		// �U��OFF
		if (!ConfigData::getInstance().isOn(ConfigData::Vibration))	return;
		StartJoypadVibration(kUsePadData[padNo], 1000, 500);
	}
}