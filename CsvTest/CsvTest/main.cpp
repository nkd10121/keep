#include <iostream>
#include <cassert>
// ����g���̂ɕK�v
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

struct StageData
{
	std::string BGMname;
	int endFrame;
	int enemyNum;
};

struct EnemyData
{
	std::string enemyKind;
	int entryFrame;
	float posX;
	float posY;
	float VecX;
	float VecY;
	int size;
	int moveSpeed;
	int firstFrame;
	int secondFrame;
};

namespace
{
	constexpr int kStageNum = 0;
	constexpr int kBGMname = 1;
	constexpr int kEndFrame = 2;
	constexpr int kEnemyNum = 3;
	constexpr int kPosX = 4;
	constexpr int kPosY = 5;
	constexpr int kVecX = 6;
	constexpr int kVecY = 7;
	constexpr int kSize = 8;
	constexpr int kMoveSpeed = 9;
	constexpr int kFirstFrame = 10;
	constexpr int kSecondFrame = 11;
}

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

void LoadStageData(std::vector<std::string> inData, std::unordered_map<int, StageData> stageData);
void LoadEnemyData(std::vector<std::string> inData, std::unordered_map<int, StageData> stageData, std::unordered_map<int, EnemyData> enemyData);

int main()
{
	// �擾���镶��������Ă����p�̕ϐ�
	std::string strBuf;
	// �擾����������𕪊��������̂����Ă����p�̕ϐ�
	std::vector<std::string> strConmaBuf;


	//std::unordered_map<int,StageData> m_stageData;
	//std::unordered_map<int,EnemyData> m_enemyData;

	std::unordered_map<int, StageData> m_data;

	// �t�@�C���ǂݍ���
	std::ifstream ifs("StageInfo.csv");
	if (!ifs)
	{
		assert(false);
		return 0;
	}

//	// �ǂݍ��񂾃t�@�C������P�s���ǂݍ���

	std::getline(ifs, strBuf);

	// �S�s�ǂݍ��ނ܂ŌJ��Ԃ�
	while (std::getline(ifs, strBuf))
	{
#if true
		strConmaBuf = Split(strBuf, ',');

		int idx = 0;
		for (int i = 0;i < strConmaBuf.size();i++)
		{
			//data.stageNum = stoi(str);
			std::cout << strConmaBuf[i].c_str() << "," << std::flush;
			LoadStageData(strConmaBuf, m_data);
			//return 0;
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

void LoadStageData(std::vector<std::string> inData, std::unordered_map<int, StageData> stageData)
{
	int tempStageNum = stoi(inData[kStageNum]);
	stageData[tempStageNum].BGMname = inData[kBGMname];
	stageData[tempStageNum].endFrame = stoi(inData[kEndFrame]);
	stageData[tempStageNum].enemyNum = stoi(inData[kEnemyNum]);
}
