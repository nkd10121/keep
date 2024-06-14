#include "StrUtil.h"
#include <cassert>

namespace
{
	
}

namespace StrUtil
{
	std::vector<std::string> splitString(const std::string str)
	{
		std::vector<std::string>	result;

		std::string temp = str;
		int byteCount = 0;
		while (1)
		{
			if (byteCount > temp.size())
			{
				// �I��
				break;
			}

			std::string chr;	// 1�������̃f�[�^

			// �����̃o�C�g���`�F�b�N
			int size = 0;
			unsigned char charData = temp[byteCount];	// �`�F�b�N���镶��
			if (charData < 0x80)
			{
				size = 1;
			}
			else
			{
				size = 2;
			}
			// �K�v�ꕪ�̂ݐ؂���
			chr = temp.substr(byteCount, size);

			// �P�����i�߂�
			byteCount += size;
			if (chr != "\0")	// ���O���镶��
			{
				result.push_back(chr);
			}
		}

		return result;
	}
}