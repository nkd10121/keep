#pragma once
#include "DxLib.h"
#include <string>
#include <vector>

using namespace std;

struct Sound;

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	/// <summary>
	/// �T�E���h��ǂݍ���
	/// </summary>
	/// <param name="name">�T�E���h�l�[��</param>
	/// <param name="path">�T�E���h�p�X</param>
	/// <param name="isBGM">true = BGM,false = SE</param>
	void Load(string name,string path,bool isBGM);

	/// <summary>
	/// �w�肵�����O�̃T�E���h�𗬂�
	/// </summary>
	/// <param name="name">���������T�E���h�l�[��</param>
	/// <param name="isFromStart">true = �ŏ�����,false = �r������</param>
	void PlayBGM(string name,bool isFromStart);

	void PlaySE(string name);

	void FadeOutBGM(string name,int fadeFrame);

	/// <summary>
	/// �w�肵�����O�̃T�E���h���~�߂�
	/// </summary>
	/// <param name="name">�~�߂����T�E���h�l�[��</param>
	void StopBGM(string name);

	/// <summary>
	/// eternal�t���O��false�̃T�E���h���폜����
	/// </summary>
	void Delete();

	/// <summary>
	/// �w�肵���T�E���h������Ă���ǂ���
	/// </summary>
	/// <param name="name">�T�E���h�l�[��</param>
	/// <returns>true = ����Ă���,false = ����Ă��Ȃ�</returns>
	bool isPlayingSound(string name);

	void ChangeBGMVolume(int volume);
	void ChangeSEVolume(int volume);

private:
	vector<Sound*> BGM;
	vector<Sound*> SE;

	float BGMvolume = 0.5f;
	float SEvolume = 0.5f;
	/// <summary>
	/// �w�肵���n���h���̃T�E���h������Ă��邩�ǂ���
	/// </summary>
	/// <param name="handle">�`�F�b�N�������n���h��</param>
	/// <returns>true = ����Ă���,false = ����Ă��Ȃ�</returns>
	bool CheckPlaying(int handle) { return CheckSoundMem(handle); }
};