#include "SaveData.h"
//#include "DxLib.h"	// DxLib_Init()���O�Ɏg�p����̂�DxLib�g�p�ł��Ȃ�
#include "game.h"

#include <cassert>
#include <fstream>
SaveData* SaveData::m_instance = nullptr;

namespace
{
	// �Z�[�u�f�[�^�̃o�[�W����
	constexpr int kCurrentSaveVersion = 0;
	// �Z�[�u�f�[�^�t�@�C����
	const char* const kSaveDataFilename = "save/data.dat";

	// ���ʂ̒i�K	���ʂ�kVolMaxValue�̏ꍇ100%�Đ�
	constexpr int kVolMaxValue = 5;
	constexpr int kVolDefaultValue = 3;
}

void SaveData::load()
{
	// �f�[�^�̃N���A
	clearData();

	std::ifstream ifs;
	ifs.open(kSaveDataFilename, std::ios_base::binary);
	if (ifs.fail())
	{
		// �t�@�C���ǂݍ��ݎ��s �Z�[�u�f�[�^�����
	//	printfDx("���s\n");
		createNewData();
		return;
	}
	else
	{
		DataCore data;
		ifs.read((char*)&data, sizeof(DataCore));
	//	printfDx("version %d\n", data.version);
		ifs.close();

		if (data.version == kCurrentSaveVersion)
		{
			// �ǂݍ��񂾃f�[�^�����ۂɎg�p����f�[�^�ɃR�s�[
			m_data = data;
		}
		else
		{
			// �����[�X��ɃZ�[�u�f�[�^�̃o�[�W�������ς������������悤
			assert(false);
		}
	}
}

void SaveData::write()
{
	assert(m_data.version == kCurrentSaveVersion);
	std::ofstream ofs(kSaveDataFilename, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(DataCore));
}

void SaveData::gameFlagOn(GameFlag flag)
{
	setFlag(flag, true);
}

void SaveData::gameFlagOff(GameFlag flag)
{
	setFlag(flag, false);
}

bool SaveData::isGameOn(GameFlag flag)
{
	assert(flag < 32);
	return ( m_data.gameFlag & (1 << flag) );
}

int SaveData::getRankPlayerKind(int rank)
{
	assert(rank >= 0);
	assert(rank < kSaveRankDataNum);
	return m_data.rankData[rank].playerKind;
}

int SaveData::getRankPlayerScore(int rank)
{
	assert(rank >= 0);
	assert(rank < kSaveRankDataNum);
	return m_data.rankData[rank].score;
}

int SaveData::entryScore(int score, int playerKind)
{
	int result = -1;	// �����N�C�����Ȃ��ꍇ-1��Ԃ�

	for (int i = 0; i < kSaveRankDataNum; i++)
	{
		if (m_data.rankData[i].score < score)
		{
			result = i;
			break;
		}
	}

	// �����N�C�����Ȃ������̂ŏI��
	if (result < 0)	return result;

	// �������Ƃ���������̃X�R�A�����炵�Ă���
	for (int i = kSaveRankDataNum-1; i >= result + 1; i--)
	{
		m_data.rankData[i] = m_data.rankData[i - 1];
	}
	// �����̃f�[�^�����ʃf�[�^�ɓ����
	m_data.rankData[result].score = score;
	m_data.rankData[result].playerKind = playerKind;

	return result;
}


void SaveData::updateAchieve()
{

}

void SaveData::createNewData()
{
	clearData();

	std::ofstream ofs(kSaveDataFilename, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(SaveData));
}

#ifdef _DEBUG
void SaveData::setAllFlag()
{
	m_data.gameFlag = 0xffffffff;

	std::ofstream ofs(kSaveDataFilename, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(SaveData));
}
#endif

void SaveData::clearData()
{
	m_data.version = kCurrentSaveVersion;
	m_data.gameFlag = 0;
	m_data.reserved0 = 0;
	m_data.reserved1 = 0;

	for (int i = 0; i < kSaveRankDataNum; i++)
	{
		m_data.rankData[i].playerKind = 0;
		m_data.rankData[i].score = (kSaveRankDataNum - i) * 10;
		m_data.rankData[i].reserved0 = 0;
		m_data.rankData[i].reserved1 = 0;
	}
}

void SaveData::setFlag(GameFlag flag, bool isOn)
{
	if (isOn)
	{
		// �t���O���Ă�
		m_data.gameFlag |= (1 << flag);
	}
	else
	{
		unsigned int mask = ~(1 << flag);
		m_data.gameFlag &= mask;
	}
}
