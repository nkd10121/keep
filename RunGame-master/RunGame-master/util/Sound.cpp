#include "Sound.h"
#include "DxLib.h"
#include "ConfigData.h"

#include <cassert>
#include <fstream>
#include <sstream>

Sound* Sound::m_instance = nullptr;

namespace
{
	// �T�E���h�̃t�@�C���p�X
	const char* const kDataFilePath = "data/sound/";
	// �T�E���h�̊g���q
	const char* const kDataExtension = ".mp3";

	// input�����������delimiter�ŕ�������
	// ������̕������Ԃ�
	std::vector<std::string> split(std::string& input, char delimiter)
	{
		std::istringstream stream(input);	// string��getline�Ŏg����f�[�^�ɕϊ��H
		std::string field;					// ��������������1�����i�[����H
		std::vector<std::string> result;	// ������̕�����̔z��

		while (getline(stream, field, delimiter))
		{
			result.push_back(field);
		}
		return result;
	}
}

void Sound::loadStart()
{
	// �t�@�C�����̓ǂݍ���
	std::ifstream ifs("data/csv/Sound.csv");
	std::string line;
	while (getline(ifs, line))
	{
		// csv�f�[�^1�s��','�ŕ����̕�����ɕ���
		std::vector<std::string>	strvec = split(line, ',');

		// strvec[0]	: �t�@�C����		string
		// strvec[1]	: BGM�t���O			string (BGM or SE)
		// strvec[2]	: ����				float
		// strvec[3]	: �񓯊��ǂݍ���	string (SYNC or ASYNC)

		// �������K�؂ȃf�[�^�^�ɕϊ����Ċi�[
		Data data;
		//	�t�@�C����strvec[0]��map��key�ɂ���
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
	// �T�E���h�̓ǂݍ���
	for (auto& data : m_data)
	{
		std::string filename = kDataFilePath + data.first + kDataExtension;
		// �T�E���h�̔񓯊��ǂݍ��ݐݒ�
		SetUseASyncLoadFlag(!data.second.isSync);
		data.second.handle = LoadSoundMem(filename.c_str());
		assert(data.second.handle != -1);
	//	data.second.freq = GetFrequencySoundMem(data.second.handle);	// ���[�h������ɍs��
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
		ResetFrequencySoundMem(data.second.handle);	// �ύX������ԂŎ��g�����擾����Ƃ��������Ȃ�̂Ń��Z�b�g
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
	// ���ɐݒ肳�ꂽ���ʒ���
	setVol = static_cast<int>(vol * getData(filename).volRate);
	// �R���t�B�O�Őݒ肵�����ʒ���
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
