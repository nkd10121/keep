#include "Mouse.h"
#include "DxLib.h"
#include <deque>
#include <cassert>

namespace
{
	constexpr int kLogNum = 16;
	// ���t���[�����W����}�E�X���
	struct MouseLog
	{
		int input;	// �{�^����ONOFF���
		Vec2 pos;	// ���W
	};
	std::deque<MouseLog>	mouseLog;	// �O�Ղ�\�����邽�߉ߋ��̂��c��	0���ŐV
}

namespace Mouse
{
	void clear()
	{
		mouseLog.clear();
	}
	// �}�E�X�̓��͏�Ԏ擾
	void update()
	{
		// ���݂̃}�E�X�������W
		MouseLog tempLog;
		tempLog.input = GetMouseInput();

		int mouseX = 0;
		int mouseY = 0;
		if (GetMousePoint(&mouseX, &mouseY) == -1)
		{
			// ���O��1�t���[�����ȏ゠��ꍇ�͑O��Ɠ����ʒu�ɐݒ�
			if (mouseLog.size() > 0)
			{
				tempLog.pos = mouseLog[0].pos;
			}
			else
			{
				tempLog.pos.x = 0.0f;
				tempLog.pos.y = 0.0f;
			}
		}
		else
		{
			tempLog.pos.x = static_cast<float>(mouseX);
			tempLog.pos.y = static_cast<float>(mouseY);
		}
		mouseLog.push_front(tempLog);
		if (mouseLog.size() > kLogNum)
		{
			mouseLog.pop_back();
		}
	}

	int getLogNum()
	{
		return static_cast<int>(mouseLog.size());
	}

	// ���݂̃}�E�X�ʒu�擾
	Vec2 getPos(int logNo)
	{
		assert(logNo >= 0);
		assert(logNo < kLogNum);
		if (mouseLog.size() > logNo)
		{
			return mouseLog[logNo].pos;
		}
		return Vec2(0, 0);
	}

	// GetMouseInput()�̒l��n���Ċe�{�^����������Ă��邩���擾
	bool isLeft(int input) { return (input & MOUSE_INPUT_LEFT); }
	bool isRight(int input) { return (input & MOUSE_INPUT_RIGHT); }
	bool isMiddle(int input) { return (input & MOUSE_INPUT_MIDDLE); }
		
	// ������������
	bool isPressLeft()
	{
		if (mouseLog.size() <= 0)	return false;
		return isLeft(mouseLog[0].input);
	}
	bool isPressRight()
	{
		if (mouseLog.size() <= 0)	return false;
		return isRight(mouseLog[0].input);
	}
	// �g���K�[����
	bool isTriggerLeft()
	{
		if (mouseLog.size() <= 1)	return false;
		bool isNow = isLeft(mouseLog[0].input);	// ���݂̏��
		bool isLast = isLeft(mouseLog[1].input);	// �P�t���[���O�̏��
		return (isNow && !isLast);
	}
	bool isTriggerRight()
	{
		if (mouseLog.size() <= 1)	return false;
		bool isNow = isRight(mouseLog[0].input);	// ���݂̏��
		bool isLast = isRight(mouseLog[1].input);	// �P�t���[���O�̏��
		return (isNow && !isLast);
	}
	// ����������
	bool isRelaseLeft()
	{
		if (mouseLog.size() <= 1)	return false;
		bool isNow = isLeft(mouseLog[0].input);	// ���݂̏��
		bool isLast = isLeft(mouseLog[1].input);	// �P�t���[���O�̏��
		return (!isNow && isLast);
	}
	bool isRelaseRight()
	{
		if (mouseLog.size() <= 1)	return false;
		bool isNow = isRight(mouseLog[0].input);	// ���݂̏��
		bool isLast = isRight(mouseLog[1].input);	// �P�t���[���O�̏��
		return (!isNow && isLast);
	}
}