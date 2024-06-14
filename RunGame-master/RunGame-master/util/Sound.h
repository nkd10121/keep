#pragma once
#include <array>
#include <vector>
#include <string>
#include <map>
// �V���O���g�����g�p�����T�E���h�N���X
class Sound
{
private:
	Sound() = default;
	virtual ~Sound() = default;

	static Sound* m_instance;

public:
	// �R�s�[�R���X�g���N�^�̋֎~
	Sound(const Sound&) = delete;
	Sound& operator=(const Sound&) = delete;
	Sound(Sound&&) = delete;
	Sound& operator=(Sound&&) = delete;

	static Sound& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new Sound;
		}
		return *m_instance;
	}
	static void destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}

private:
	struct Data
	{
		// �Œ�f�[�^
		bool isBgm;				// ���ꂪBGM�����ʉ���
		float volRate;			// �{�����[������
		bool isSync;			// true:����	false:�񓯊�

		// �Đ��f�[�^
		int handle;				// �T�E���h�n���h��

		// �T�E���h���
		int freq;				// �Đ����g��
	};

public:
	// �T�E���h�̃��[�h�A�A�����[�h
	void loadStart();
	void unload();
	
	// ���[�h�����m�F
	bool isLoaded();
	// ���[�h�I����̃f�[�^���W	�S�ẴT�E���h���[�h���������Ă���s��
	void collectData();

	// �T�E���h�̍Đ�	�ő剹��(255)�ɐݒ肵�Ȃ������
	void play(std::string filename, float speed = 1.0f);
	// BGM�Đ�	play�Ƃ̈Ⴂ�̓��[�v�Đ�����
	void playBgm(std::string filename, float speed = 1.0f);
	// �T�E���h�̏I��
	void stop(std::string filename);
	// �{�����[���ݒ�	0~255
	void setVolume(std::string filename, int vol);
	// �Đ����x�̕ύX
	void setSpeed(std::string filename, float speed);

private:
	// �t�@�C��������f�[�^�擾
	Data getData(std::string filename);

private:
	// �t�@�C�����
	std::map<std::string, Data>		m_data;
};
