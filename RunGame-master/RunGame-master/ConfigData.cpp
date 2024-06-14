#include "ConfigData.h"
//#include "DxLib.h"	// DxLib_Init()���O�Ɏg�p����̂�DxLib�g�p�ł��Ȃ�
#include "game.h"

#include <cassert>
#include <fstream>
ConfigData* ConfigData::m_instance = nullptr;

namespace
{
	// �Z�[�u�f�[�^�̃o�[�W����
	constexpr int kCurrentSaveVersion = 0;
	// �Z�[�u�f�[�^�t�@�C����
	const char* const kSaveDataFilename = "save/config.dat";

	// ���ʂ̒i�K	���ʂ�kVolMaxValue�̏ꍇ100%�Đ�
	constexpr int kVolMaxValue = 5;
	constexpr int kVolDefaultValue = 3;
}

void ConfigData::load()
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

void ConfigData::write()
{
	assert(m_data.version == kCurrentSaveVersion);
	std::ofstream ofs(kSaveDataFilename, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(DataCore));
}


int ConfigData::getLanguage() const
{
	return m_data.language;
}

void ConfigData::setLanguage(int lang)
{
	m_data.language = lang;
}

int ConfigData::getBgmVol() const
{
	return m_data.volBgm;
}

int ConfigData::getSeVol() const
{
	return m_data.volSe;
}

int ConfigData::getMaxBgmVol() const
{
	return kVolMaxValue;
}

int ConfigData::getMaxSeVol() const
{
	return kVolMaxValue;
}

void ConfigData::setBgmVol(int vol)
{
	assert(vol >= 0);
	assert(vol <= getMaxBgmVol());
	m_data.volBgm = vol;
}

void ConfigData::setSeVol(int vol)
{
	assert(vol >= 0);
	assert(vol <= getMaxSeVol());
	m_data.volSe = vol;
}

float ConfigData::getBgmVolRate() const
{
	return static_cast<float>(getBgmVol()) / static_cast<float>(getMaxBgmVol());
}

float ConfigData::getSeVolRate() const
{
	return static_cast<float>(getSeVol()) / static_cast<float>(getMaxSeVol());
}

void ConfigData::incBgmVol(bool isLoop)
{
	m_data.volBgm++;
	if (m_data.volBgm > kVolMaxValue)
	{
		if(isLoop)		m_data.volBgm = 0;
		else			m_data.volBgm = kVolMaxValue;
	}
}

void ConfigData::decBgmVol(bool isLoop)
{
	m_data.volBgm--;
	if (m_data.volBgm < 0)
	{
		if (isLoop)		m_data.volBgm = kVolMaxValue;
		else			m_data.volBgm = 0;
	}
}

void ConfigData::incSeVol(bool isLoop)
{
	m_data.volSe++;
	if (m_data.volSe > kVolMaxValue)
	{
		if (isLoop)		m_data.volSe = 0;
		else			m_data.volSe = kVolMaxValue;
	}
}

void ConfigData::decSeVol(bool isLoop)
{
	m_data.volSe--;
	if (m_data.volSe < 0)
	{
		if (isLoop)		m_data.volSe = kVolMaxValue;
		else			m_data.volSe = 0;
	}
}

void ConfigData::flagOn(Flag flag)
{
	setFlag(flag, true);
}

void ConfigData::flagOff(Flag flag)
{
	setFlag(flag, false);
}

bool ConfigData::isOn(Flag flag)
{
	assert(flag < 32);
	return (m_data.flag & (1 << flag));
}

void ConfigData::createNewData()
{
	clearData();

	std::ofstream ofs(kSaveDataFilename, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(DataCore));
}

#ifdef _DEBUG
void ConfigData::setAllFlag()
{
	m_data.flag = 0xffffffff;

	std::ofstream ofs(kSaveDataFilename, std::ios_base::binary);
	ofs.write((char*)&m_data, sizeof(DataCore));
}
#endif

void ConfigData::clearData()
{
	m_data.version = kCurrentSaveVersion;
	m_data.language = 0;
	m_data.volBgm = kVolDefaultValue;		// BGM����
	m_data.volSe = kVolDefaultValue;		// SE����
	m_data.reserved0 = 0;

	m_data.flag = 0;
	// ������ON�̍���
	m_data.flag |= (1 << Vibration);
	if (!Game::kDefaultWindowMode)
	{
		m_data.flag |= (1 << FullScreen);
	}

	m_data.reserved1 = 0;	// �\���̈�

}

void ConfigData::setFlag(Flag flag, bool isOn)
{
	if (isOn)
	{
		// �t���O���Ă�
		m_data.flag |= (1 << flag);
	}
	else
	{
		unsigned int mask = ~(1 << flag);
		m_data.flag &= mask;
	}
}
