#include "Sound.h"
#include "DxLib.h"
#include "ConfigData.h"

#include <cassert>
#include <fstream>
#include <sstream>

Sound* Sound::m_instance = nullptr;

namespace
{
	// サウンドのファイルパス
	const char* const kDataFilePath = "data/sound/";
	// サウンドの拡張子
	const char* const kDataExtension = ".mp3";

	// inputした文字列をdelimiterで分割して
	// 分割後の文字列を返す
	std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);	// stringをgetlineで使えるデータに変換？
		std::string field;					// 分割した文字列1つ分を格納する？
		std::vector<std::string> result;	// 分割後の文字列の配列

		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	}
}

void Sound::loadStart()
{
	// ファイル情報の読み込み
	std::ifstream ifs("data/csv/Sound.csv");
	std::string line;
	while (getline(ifs, line))
	{
		// csvデータ1行を','で複数の文字列に分割
		std::vector<std::string>	strvec = split(line, ',');

		// strvec[0]	: ファイル名		string
		// strvec[1]	: BGMフラグ			string (BGM or SE)
		// strvec[2]	: 音量				float
		// strvec[3]	: 非同期読み込み	string (SYNC or ASYNC)

		// 文字列を適切なデータ型に変換して格納
		Data data;
		//	ファイル名strvec[0]はmapのkeyにする
		if (strvec[1] == "SE")
		{
			data.isBgm = false;
		}
		else if (strvec[1] == "BGM")
		{
			data.isBgm = true;
		}
		else
		{
			assert(false);
		}
		data.volRate = stof(strvec[2]);
		if (strvec[3] == "ASYNC")
		{
			data.isSync = false;
		}
		else if (strvec[3] == "SYNC")
		{
			data.isSync = true;
		}
		else
		{
			assert(false);
		}

		data.handle = -1;

		m_data[strvec[0]] = data;
	}
	// サウンドの読み込み
	for (auto& data : m_data)
	{
		std::string filename = kDataFilePath + data.first + kDataExtension;
		// サウンドの非同期読み込み設定
		SetUseASyncLoadFlag(!data.second.isSync);
		data.second.handle = LoadSoundMem(filename.c_str());
		assert(data.second.handle != -1);
	//	data.second.freq = GetFrequencySoundMem(data.second.handle);	// ロード完了後に行う
	}
	SetUseASyncLoadFlag(false);
}

void Sound::unload()
{
	for (auto& data : m_data)
	{
		DeleteSoundMem(data.second.handle);
	}
}

bool Sound::isLoaded()
{
	for (auto& data : m_data)
	{
		if (data.second.isSync)	continue;

		if (CheckHandleASyncLoad(data.second.handle))	return false;
	}

	return true;
}

void Sound::collectData()
{
	for (auto& data : m_data)
	{
		assert(!CheckHandleASyncLoad(data.second.handle));
		ResetFrequencySoundMem(data.second.handle);	// 変更した状態で周波数を取得するとおかしくなるのでリセット
		data.second.freq = GetFrequencySoundMem(data.second.handle);
	}
}

void Sound::play(std::string filename, float speed)
{
	Data data = getData(filename);
	PlaySoundMem(data.handle, DX_PLAYTYPE_BACK);
	SetFrequencySoundMem(static_cast<int>(data.freq * speed), data.handle);
	setVolume(filename, 255);
}

void Sound::playBgm(std::string filename, float speed)
{
	Data data = getData(filename);
	PlaySoundMem(data.handle, DX_PLAYTYPE_LOOP);
	SetFrequencySoundMem(static_cast<int>(data.freq * speed), data.handle);
	setVolume(filename, 255);
}

void Sound::stop(std::string filename)
{
	StopSoundMem(getData(filename).handle);
}

void Sound::setVolume(std::string filename, int vol)
{
	int setVol = vol;
	// 音に設定された音量調整
	setVol = static_cast<int>(vol * getData(filename).volRate);
	// コンフィグで設定した音量調整
	float confRate = 1.0f;
	if (getData(filename).isBgm)
	{
		confRate = ConfigData::getInstance().getBgmVolRate();
	}
	else
	{
		confRate = ConfigData::getInstance().getSeVolRate();
	}
	setVol = static_cast<int>(setVol * confRate);
	ChangeVolumeSoundMem(setVol, getData(filename).handle);
}

void Sound::setSpeed(std::string filename, float speed)
{
	Data data = getData(filename);
	SetFrequencySoundMem(static_cast<int>(data.freq * speed), data.handle);
}

Sound::Data Sound::getData(std::string filename)
{
	assert(m_data.find(filename) != m_data.end());
	return m_data[filename];
}
