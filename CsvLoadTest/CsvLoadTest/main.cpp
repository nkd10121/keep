#include <iostream>
#include <cassert>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>

/// <summary>
/// �����֐�
/// </summary>
/// <param name="str">���̕�����</param>
/// <param name="del">�������镶��</param>
/// <returns>�������������Q</returns>
std::vector<std::string> Split(std::string& str, char del);


enum class MapDir
{
	kUp,
	kDown,
	kRight,
	kLeft
};

enum class ConditionsType
{
	kTime,
	kKilled,
	kSumTime
};

// ���X�e�[�W�̏��\����
struct NextStageInfo
{
	// �������
	MapDir dir;
	// ���O
	std::string name;
	// �������
	ConditionsType type;
	// �������
	int info;
	std::vector<std::string> infoGroup;
};

// �������\����
struct CreateInfo
{
	// ����������
	int startNum;
	// ���������Ԋu
	int startInterval;
	// �����f�B���C�t���[��
	int startDelayFrame;
	// �����Ԋu
	int createInterval;
};

// �G���\����
struct EnemyInfo
{
	// ���O
	std::string name;
	// ������
	int num;
	// �������
	std::vector<CreateInfo> info;
};

struct StageData
{
	// ���X�e�[�W���
	int nextNum;
	std::vector<NextStageInfo> stageInfo;
	// �G���
	int enemyNum;
	std::vector<EnemyInfo> enemyInfo;
	// �{�X�X�e�[�W���
	bool isBoss;
};

/// <summary>
/// �X�e�[�W�̎�ȓ��e�̓ǂݍ���
/// </summary>
/// <param name="strConmaBuf">�R���}��������������</param>
/// <param name="m_stageData">����͌������ł̓����o�ϐ���</param>
/// <param name="stageName">�X�e�[�W��</param>
/// <param name="isLoadAllEnemys">�G����S�Ď擾������</param>
/// <param name="enemyTypeIndex">�G��ނ̗v�f�ԍ�</param>
/// <param name="isLoadAllNextStages">�אڏ���S�Ď擾������</param>
/// <param name="nextStageIndex">�אڏ��̗v�f�ԍ�</param>
void LoadImportantStageInfo(std::vector<std::string>& strConmaBuf, std::unordered_map<std::string, StageData>& m_stageData, std::string& stageName, bool& isLoadAllEnemys, int& enemyTypeIndex, bool& isLoadAllNextStages, int& nextStageIndex);

/// <summary>
/// �G���̓ǂݍ���
/// </summary>
/// <param name="strConmaBuf">�R���}��������������</param>
/// <param name="data">�X�e�[�W�f�[�^</param>
/// <param name="isLoadAllEnemys">�G����S�Ď擾������</param>
/// <param name="enemyTypeIndex">�G��ނ̗v�f�ԍ�</param>
/// <param name="isLoadAllEnmeyInfo">�G1�̂̏���S�Ď擾������</param>
/// <param name="enemyInfoIndex">�G1�̗̂v�f�ԍ�</param>
void LoadEnemys(std::vector<std::string>& strConmaBuf, StageData& data, bool& isLoadAllEnemys, int& enemyTypeIndex, bool& isLoadAllEnmeyInfo, int& enemyInfoIndex);

/// <summary>
/// �אڏ��̓ǂݍ���
/// </summary>
/// <param name="strConmaBuf">�R���}��������������</param>
/// <param name="data">�X�e�[�W�f�[�^</param>
/// <param name="isLoadAllNextStages">�אڏ���S�Ď擾������</param>
/// <param name="nextStageIndex">�אڏ��̗v�f�ԍ�</param>
void LoadNextStages(std::vector<std::string>& strConmaBuf, StageData& data, bool& isLoadAllNextStages, int& nextStageIndex);

namespace
{
	// �C���f�b�N�X�ԍ�
	constexpr int kIndexStageName			= 0;
	constexpr int kIndexEnemyTypeNum		= 1;
	constexpr int kIndexEnemyName			= 2;
	constexpr int kIndexEnemyInfoNum		= 3;
	constexpr int kIndexStartCreateNum		= 4;
	constexpr int kIndexStartCreateFrame	= 5;
	constexpr int kIndexStartDelayFrame		= 6;
	constexpr int kIndexCreateFrame			= 7;
	constexpr int kIndexIsCreateBoss		= 8;
	constexpr int kIndexNextStageNum		= 9;
	constexpr int kIndexNextStageName		= 10;
	constexpr int kIndexDir					= 11;
	constexpr int kIndexInfoType			= 12;
	constexpr int kIndexInfo				= 13;
	constexpr int kIndexInfoGroupNum		= 14;
	constexpr int kIndexInfoGroup			= 15;
}

// �v���O������ WinMain ����n�܂�܂�
int main()
{

	// �ꎞ�ۑ��pstring
	std::string strBuf;
	// �J���}�����ꎞ�ۑ��pstring
	std::vector<std::string> strConmaBuf;

	// �X�e�[�W���ۑ�
	std::unordered_map<std::string, StageData> m_stageData;

	// �t�@�C���ǂݍ���
	std::ifstream ifs("StageData.csv");
	if (!ifs)
	{
		assert(false);
		return 0;
	}

	// �X�e�[�W���ۑ�
	std::string stageName;
	// �G��ސ����
	int enemyTypeIndex = 0;
	bool isLoadAllEnemys = true;
	// �G1�̂̏��
	int enemyInfoIndex = 0;
	bool isLoadAllEnmeyInfo = true;
	// �אڃX�e�[�W���
	int nextStageIndex = 0;
	bool isLoadAllNextStages = true;

	// �ŏ��͑Ή��\��񂪓����Ă��邾���Ȃ̂Ŗ�������
	std::getline(ifs, strBuf);
	// ����ǂݐ؂�܂Ń��[�v
	while (std::getline(ifs, strBuf))
	{
		strConmaBuf = Split(strBuf, ',');

		LoadImportantStageInfo(strConmaBuf, m_stageData, stageName, isLoadAllEnemys, enemyTypeIndex, isLoadAllNextStages, nextStageIndex);
		auto& data = m_stageData[stageName];
		LoadEnemys(strConmaBuf, data, isLoadAllEnemys, enemyTypeIndex, isLoadAllEnmeyInfo, enemyInfoIndex);
		LoadNextStages(strConmaBuf, data, isLoadAllNextStages, nextStageIndex);
	}

	return 0;				// �\�t�g�̏I��
}


std::vector<std::string> Split(std::string& str, char del)
{
	// ��؂�J�n�ʒu
	int first = 0;
	// ��؂�ŏI�ʒu
	int last = str.find_first_of(del);

	std::vector<std::string> result;
	
	while (first < str.size())
	{
		// ��؂������̂����ʂɓ���Ă���
		std::string subStr(str, first, last - first);

		result.push_back(subStr);

		// �ʒu�X�V
		first = last + 1;
		last = str.find_first_of(del, first);
		if (last == std::string::npos)
		{
			last = str.size();
		}
	}

	return result;
}

void LoadImportantStageInfo(std::vector<std::string>& strConmaBuf, std::unordered_map<std::string, StageData>& m_stageData, std::string& stageName, bool& isLoadAllEnemys, int& enemyTypeIndex, bool& isLoadAllNextStages, int& nextStageIndex)
{
	// �S�Ă̏���ǂݍ���ł���ꍇ�̂ݎ��̏��Q�Ɉڍs����
	if (!isLoadAllEnemys || !isLoadAllNextStages) return;
	
	// �X�e�[�W���ǂݍ���
	stageName = strConmaBuf[kIndexStageName];
	// �G��ސ��ǂݍ���
	int enemyTypeNum = std::stoi(strConmaBuf[kIndexEnemyTypeNum]);
	// �אڃX�e�[�W���ǂݍ���
	int nextStageNum = std::stoi(strConmaBuf[kIndexNextStageNum]);
	// �{�X�����t���O�ǂݍ���
	bool isCreateBoss = static_cast<bool>(std::stoi(strConmaBuf[kIndexIsCreateBoss]));

	// ���̑��
	auto& data = m_stageData[stageName];
	data.enemyNum = enemyTypeNum;
	data.enemyInfo.resize(enemyTypeNum);
	data.nextNum = nextStageNum;
	data.stageInfo.resize(nextStageNum);
	data.isBoss = isCreateBoss;

	// ���ǂݍ���ł��Ȃ��Ƃ���
	isLoadAllEnemys = false;
	enemyTypeIndex = 0;
	isLoadAllNextStages = false;
	nextStageIndex = 0;
}

void LoadEnemys(std::vector<std::string>& strConmaBuf, StageData& data, bool& isLoadAllEnemys, int& enemyTypeIndex, bool& isLoadAllEnmeyInfo, int& enemyInfoIndex)
{
	// �G��񂷂ׂēǂݍ���ł����瑁�����^�[��
	if (isLoadAllEnemys) return;

	auto& enemy = data.enemyInfo[enemyTypeIndex];

	if (isLoadAllEnmeyInfo)
	{
		// ���O�ǂݍ���
		std::string enemyName = strConmaBuf[kIndexEnemyName];
		// �����ʏ������ǂݍ���
		int enemyInfoNum = std::stoi(strConmaBuf[kIndexEnemyInfoNum]);

		// �����
		enemy.name = enemyName;
		enemy.num = enemyInfoNum;
		enemy.info.resize(enemyInfoNum);

		// ���ǂݍ��ݏ�����
		isLoadAllEnmeyInfo = false;
		enemyInfoIndex = 0;
	}

	auto& info = enemy.info[enemyInfoIndex];

	// �����������ǂݍ���
	int startNum = std::stoi(strConmaBuf[kIndexStartCreateNum]);
	// ���������Ԋu�ǂݍ���
	int startCreateFrame = std::stoi(strConmaBuf[kIndexStartCreateFrame]);
	// �����x���t���[��
	int startDelayFrame = std::stoi(strConmaBuf[kIndexStartDelayFrame]);
	// �����Ԋu
	int CreateFrame = std::stoi(strConmaBuf[kIndexCreateFrame]);

	// �����
	info.startNum = startNum;
	info.startInterval = startCreateFrame;
	info.startDelayFrame = startDelayFrame;
	info.createInterval = CreateFrame;

	// ���X�V
	enemyInfoIndex++;
	if (enemyInfoIndex >= enemy.num)
	{
		isLoadAllEnmeyInfo = true;

		enemyTypeIndex++;
		if (enemyTypeIndex >= data.enemyNum)
		{
			isLoadAllEnemys = true;
		}
	}
}

void LoadNextStages(std::vector<std::string>& strConmaBuf, StageData& data, bool& isLoadAllNextStages, int& nextStageIndex)
{
	// �אڏ�񂷂ׂēǂݍ���ł����瑁�����^�[��
	if (isLoadAllNextStages) return;

	// �X�e�[�W���ǂݍ���
	std::string name = strConmaBuf[kIndexNextStageName];
	// �����ǂݍ���
	int dir = std::stoi(strConmaBuf[kIndexDir]);
	// �����^�C�v�ǂݍ���
	int infoType = std::stoi(strConmaBuf[kIndexInfoType]);
	// �������ǂݍ���
	int info = std::stoi(strConmaBuf[kIndexInfo]);

	// �����
	auto& stage = data.stageInfo[nextStageIndex];
	stage.name = name;
	stage.dir = static_cast<MapDir>(dir);
	stage.type = static_cast<ConditionsType>(infoType);
	stage.info = info;

	// ���v���Ԍn�̂ݒǉ����ǂݍ���
	if (static_cast<ConditionsType>(infoType) == ConditionsType::kSumTime)
	{
		// ���Q���ǂݍ���
		int infoNum = std::stoi(strConmaBuf[kIndexInfoGroupNum]);
		stage.infoGroup.resize(infoNum);

		// ���Q�ǂݍ���
		for (int i = 0; i < infoNum; i++)
		{
			stage.infoGroup[i] = strConmaBuf[i + kIndexInfoGroup];
		}
	}

	// ���X�V
	nextStageIndex++;
	if (nextStageIndex >= data.nextNum)
	{
		isLoadAllNextStages = true;
	}
}