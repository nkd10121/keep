#pragma once
#include <string>
#include <vector>

// ������֗��֐�
namespace StrUtil
{
	// �������1��������������vector�ɂ���
	// 3�o�C�g�ȏ�̕����͔�Ή�	�Ō��\0�͎�菜��
	std::vector<std::string> splitString(const std::string str);
}
