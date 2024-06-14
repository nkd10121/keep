#include "SaveData.h"
//#include "DxLib.h"	// DxLib_Init()より前に使用するのでDxLib使用できない
#include "game.h"

#include <cassert>
#include <fstream>
SaveData* SaveData::m_instance = nullptr;

namespace
{
	// セーブデータのバージョン
	constexpr int kCurrentSaveVersion = 0;
	// セーブデータファイル名
	const char* const kSaveDataFilename = "save/data.dat";

	// 音量の段階	音量がkVolMaxValueの場合100%再生
	constexpr int kVolMaxValue = 5;
	constexpr int kVolDefaultValue = 3;
}

void SaveData::load()
{
	// データのクリア
	clearData();

	std::ifstream ifs;
	ifs.open(kSaveDataFilename, std::ios_base::binary);
	if (ifs.fail())
	{
		// ファイル読み込み失敗 セーブデータを作る
	//	printfDx("失敗\n");
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
			// 読み込んだデータを実際に使用するデータにコピー
			m_data = data;
		}
		else
		{
			// リリース後にセーブデータのバージョンが変わったら実装しよう
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
	int result = -1;	// ランクインしない場合-1を返す

	for (int i = 0; i < kSaveRankDataNum; i++)
	{
		if (m_data.rankData[i].score < score)
		{
			result = i;
			break;
		}
	}

	// ランクインしなかったので終了
	if (result < 0)	return result;

	// 入ったところよりも下のスコアをずらしていく
	for (int i = kSaveRankDataNum-1; i >= result + 1; i--)
	{
		m_data.rankData[i] = m_data.rankData[i - 1];
	}
	// 自分のデータを順位データに入れる
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
		// フラグ立てる
		m_data.gameFlag |= (1 << flag);
	}
	else
	{
		unsigned int mask = ~(1 << flag);
		m_data.gameFlag &= mask;
	}
}
