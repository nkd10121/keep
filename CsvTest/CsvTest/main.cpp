#include <iostream>
#include <cassert>
// ����g���̂ɕK�v
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

struct Data
{
	int stageNum;
	int enemyNum;
	int enemyKind;
	int enemyFrame;
};

std::vector<std::string> Split(std::string str, const char sprit)
{
	std::vector<std::string> result;

	// ���������łǂ�����n�߂邩�̈ʒu
	int first = 0;
	// ���������łǂ��܂Ŏ擾���邩�̈ʒu
	int last = str.find_first_of(sprit);

	while(first < str.size())
	{
		// ��؂������̂����ʂɓ���Ă���
		std::string subStr(str, first, last - first);

		// ������ǉ�
		result.push_back(subStr);

		// �ʒu�X�V
		first = last + 1;
		last = str.find_first_of(sprit, first);
		if (last == std::string::npos)
		{
			last = str.size();
		}
	}

	return result;
}

int main()
{
	// �擾���镶��������Ă����p�̕ϐ�
	std::string strBuf;
	// �擾����������𕪊��������̂����Ă����p�̕ϐ�
	std::vector<std::string> strConmaBuf;


	Data data;


	// �t�@�C���ǂݍ���
	std::ifstream ifs("test.csv");
	if (!ifs)
	{
		assert(false);
		return 0;
	}

//	// �ǂݍ��񂾃t�@�C������P�s���ǂݍ���
//	std::getline(ifs, strBuf);

	// �S�s�ǂݍ��ނ܂ŌJ��Ԃ�
	while (std::getline(ifs, strBuf))
	{
#if true
		strConmaBuf = Split(strBuf, ',');

		int idx = 0;
		for (const auto& str : strConmaBuf)
		{
			//data.stageNum = stoi(str);
			std::cout << str.c_str() << "," << std::flush;
		}

		//std::cout << strConmaBuf[0] << std::flush;

#else
		std::cout << strBuf.c_str() << std::flush;
#endif

		std::cout << std::endl;
	}

	// �t�@�C������
	ifs.close();

	return 0;
}