#pragma once
// �V���O���g�����g�p�����R���t�B�O�f�[�^�Ǘ��N���X
class ConfigData
{
public:
	// �ݒ�
	enum Flag
	{
		FullScreen = 0,	// �t���X�N���[���ݒ�
		Vibration = 1,	// �U��ONOFF
	};
	
private:
	ConfigData() = default;
	virtual ~ConfigData() = default;

	static ConfigData* m_instance;

public:
	// �R�s�[�R���X�g���N�^�̋֎~
	ConfigData(const ConfigData&) = delete;
	ConfigData& operator=(const ConfigData&) = delete;
	ConfigData(ConfigData&&) = delete;
	ConfigData& operator=(ConfigData&&) = delete;

	static ConfigData& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new ConfigData;
		}
		return *m_instance;
	}
	static void destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}
public:
	// �f�[�^�̓ǂݍ���
	void load();
	// �Z�[�u�f�[�^�̏�������
	void write();

	// �R���t�B�O
	int getLanguage() const;
	void setLanguage(int lang);

	int getBgmVol() const;	// 0~getMaxBgmVol()
	int getSeVol() const;	// 0~getMaxSeVol()
	int getMaxBgmVol() const;	// ���ʍő�l
	int getMaxSeVol() const;	// 

	void setBgmVol(int vol);
	void setSeVol(int vol);

	float getBgmVolRate() const;	// 0.0~1.0
	float getSeVolRate() const;	// 0.0~1.0

	// ���ʕύX	�ύX��Z�[�u�f�[�^�������ޕK�v����
	void incBgmVol(bool isLoop);	// ���ʃA�b�v	isLoop = true�̏ꍇ�ő�l�𒴂����0��
	void decBgmVol(bool isLoop);	// ���ʃ_�E��	isLoop = true�̏ꍇ�ő�l�𒴂����0��
	void incSeVol(bool isLoop);
	void decSeVol(bool isLoop);

	// �v���C�f�[�^�̐ݒ�	�������݂͍s��Ȃ��̂Őݒ肪�I�������write()����
	void flagOn(Flag flag);
	void flagOff(Flag flag);

	bool isOn(Flag flag);

	// �Z�[�u�f�[�^��V�K�쐬���ď㏑��(�V�K�ۑ�)
	void createNewData();

#ifdef _DEBUG
	// �S�Ẵt���O��ON�ɂ���
	void setAllFlag();
#endif

private:
	// �f�[�^�̃N���A
	void clearData();
	// �t���OON,OFF
	// isOn:�@true�Ńt���O�𗧂Ă�Afalse�ŗ��Ƃ�
	void setFlag(Flag flag, bool isOn);

private:

	// �ۑ�����Z�[�u�f�[�^�{��
	struct DataCore
	{
		int version = 0;		// �f�[�^�̃o�[�W����

		// �R���t�B�O
		char language = 0;
		char volBgm = 3;		// BGM����	0~5
		char volSe = 3;		// SE����	0~5
		unsigned char reserved0 = 0;		// �\���̈�

		unsigned int flag = 0;
		unsigned int reserved1 = 0;	// �\���̈�
	};

private:
	DataCore m_data;
};

