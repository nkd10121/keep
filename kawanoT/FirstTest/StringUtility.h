#pragma once
#include <string>

class StringUtility
{
public:
	/// <summary>
	/// �}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
	/// </summary>
	/// <param name="str">�ϊ����̃}���`�o�C�g������</param>
	/// <returns>�ϊ���̃��C�h������</returns>
	static std::wstring
		StringToWString(const std::string& str);
};

