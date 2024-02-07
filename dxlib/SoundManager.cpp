#include "SoundManager.h"

namespace
{
	constexpr float kFadeFrame = 30.0f;
}

struct Sound
{
private:
	string SoundName = "";
	string SoundPath = "";
	int SoundHandle;

public:

	void Set(std::string name, std::string path)
	{
		SoundName = name;
		SoundPath = path;
		SoundHandle = LoadSoundMem(path.c_str());
	}

	std::string GetName()const
	{
		return SoundName;
	}

	std::string GetPath()const
	{
		return SoundPath;
	}

	int GetHandle()const
	{
		return SoundHandle;
	}

	void DeleteSound()
	{
		DeleteSoundMem(SoundHandle);
	}
};

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
	InitSoundMem();
}

void SoundManager::Load(string name, string path, bool isBGM)
{
	//BGM�t���O��true�̎��́ABGM��vector�ɓ����
	if (isBGM)
	{
		BGM.resize(BGM.size() + 1);

		for (int i = 0; i < BGM.size(); i++)
		{
			//���݂��Ă���
			if (BGM[i])
			{
				//�p�X�������ꍇ�͑��₵���g�����炵�ĕԂ�
				if (BGM[i]->GetPath() == path)
				{
					BGM.pop_back();
					return;
				}
			}
			//�p�X���������̂����݂��Ă��Ȃ��ꍇ�A���[�h������
			else
			{
				BGM[i] = new Sound;
				BGM[i]->Set(name, path);
			}
		}
	}
	//BGM�t���O��false�̎��́ASE��vector�ɓ����
	else
	{
		SE.resize(SE.size() + 1);

		for (int i = 0; i < SE.size(); i++)
		{
			//���݂��Ă���
			if (SE[i])
			{
				//�p�X�������ꍇ�͑��₵���g�����炵�ĕԂ�
				if (SE[i]->GetPath() == path)
				{
					SE.pop_back();
					return;
				}
			}
			//�p�X���������̂����݂��Ă��Ȃ��ꍇ�A���[�h������
			else
			{
				SE[i] = new Sound;
				SE[i]->Set(name, path);
			}
		}
	}
}

void SoundManager::PlayBGM(string name, bool isFromStart)
{
	for (int i = 0; i < BGM.size(); i++)
	{
		//���݂��Ă��邩�A�����̖��O�ƈ�v���閼�O
		if (BGM[i] && BGM[i]->GetName() == name)
		{
			//����Ă����牽�����Ȃ�
			if (CheckPlaying(BGM[i]->GetHandle()))
			{
				return;
			}

			PlaySoundMem(BGM[i]->GetHandle(), DX_PLAYTYPE_BACK, isFromStart);
			return;
		}
	}
}

void SoundManager::PlaySE(string name)
{
	for (int i = 0; i < SE.size(); i++)
	{
		//���݂��Ă��邩�A�����̖��O�ƈ�v���閼�O
		if (SE[i] && SE[i]->GetName() == name)
		{
			////����Ă����牽�����Ȃ�
			//if (CheckPlaying(SE[i]->GetHandle()))
			//{
			//	return;
			//}

			PlaySoundMem(SE[i]->GetHandle(), DX_PLAYTYPE_BACK, true);
			return;
		}
	}
}

void SoundManager::FadeOutBGM(string name,int fadeFrame)
{

	float dif = BGMvolume * ((kFadeFrame - static_cast<float>(fadeFrame)) / kFadeFrame);
	for (int i = 0; i < BGM.size(); i++)
	{
		//���݂��Ă��邩�A�����̖��O�ƈ�v���閼�O
		if (BGM[i] && BGM[i]->GetName() == name)
		{
			//BGMvolume = dif;
			ChangeVolumeSoundMem(255 * dif, BGM[i]->GetHandle());

			if (255 * dif <= 0.0f)
			{
				StopSoundMem(BGM[i]->GetHandle());
			}
			return;
		}
	}
	return;
}

void SoundManager::StopBGM(string name)
{
	for (int i = 0; i < BGM.size(); i++)
	{
		//���݂��Ă��邩�A�����̖��O�ƈ�v���閼�O
		if (BGM[i] && BGM[i]->GetName() == name)
		{
			int tempHandle = BGM[i]->GetHandle();

			//����Ă��Ȃ������牽�����Ȃ�
			if (!CheckPlaying(tempHandle))
			{
				return;
			}

			StopSoundMem(tempHandle);

			return;
		}
	}
}

void SoundManager::Delete()
{
	for (int i = 0; i < BGM.size(); i++)
	{
		//���݂��Ă���
		if (BGM[i])
		{
			BGM[i]->DeleteSound();
			delete BGM[i];
			BGM[i] = nullptr;
		}
	}

	for (int i = 0; i < SE.size(); i++)
	{
		//���݂��Ă���
		if (SE[i])
		{
			SE[i]->DeleteSound();
			delete SE[i];
			SE[i] = nullptr;
		}
	}
	return;
}

bool SoundManager::isPlayingSound(string name)
{
	for (int i = 0; i < BGM.size(); i++)
	{
		//���݂��Ă��邩�A�����̖��O�ƈ�v���閼�O
		if (BGM[i] && BGM[i]->GetName() == name)
		{
			//����Ă��Ȃ������牽�����Ȃ�
			return CheckPlaying(BGM[i]->GetHandle());
		}
	}
	return false;
}

void SoundManager::ChangeBGMVolume(int volume)
{
	BGMvolume = static_cast<float>(volume * 0.1f);
	for (int i = 0; i < BGM.size(); i++)
	{
		ChangeVolumeSoundMem(static_cast<int>(255 * BGMvolume), BGM[i]->GetHandle());
	}
	return;
}

void SoundManager::ChangeSEVolume(int volume)
{
	SEvolume = static_cast<float>(volume * 0.1f);
	for (int i = 0; i < SE.size(); i++)
	{
		ChangeVolumeSoundMem(static_cast<int>(255 * SEvolume), SE[i]->GetHandle());
	}
	return;
}
