#pragma once
#include <string>

class StringUtility
{
public:
	/// <summary>
	/// �����ɐ���
	/// </summary>
	/// <param name="a">����1�̐���</param>
	/// <param name="b">����2�̐���</param>
	/// <param name="c">����3�̐���</param>
	/// <returns> true:true�̎��̏�� , false:false�̎��̏��</returns>
	bool dummy(int a, int b, int c)
	{

	}


	/// <summary>
	/// �}���`�o�C�g�����񂩂烏�C�h������ւ̕ϊ�
	/// </summary>
	/// <param name="str">�ϊ����̃}���`�o�C�g������</param>
	/// <returns>�ϊ���̃��C�h������</returns>
	static std::wstring
		StringToWString(const std::string& str);
};

