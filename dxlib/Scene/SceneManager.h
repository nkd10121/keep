#pragma once
#include <list> 
#include <memory>
#include <windows.h>
#include "../SoundManager.h"
#include "../GraphManager.h"

struct SettingInfo
{
	int BGMvolume = 5;
	int SEvolume = 5;
	bool m_sFull = false;
};

class Input;
class Scene;

class SceneManager
{
private:
	std::list < std::shared_ptr<Scene>> scenes;

	LPCSTR font_path;
	int fontHandle;
	int fontHandle2;

	bool clearStage1 = false;
	bool clearStage2 = false;

	int m_BGMvolume = 5;
	int m_SEvolume = 3;
	bool m_isFull;

	void SetBGMvolume(int volume) { m_BGMvolume = volume; }
	void SetSEvolume(int volume) { m_SEvolume = volume; }
	void SetIsFull(bool isFull) { m_isFull = isFull; }

public:
	/// <summary>
	/// ���O�̃V�[�����c��
	/// </summary>
	std::shared_ptr<Scene> logScene;

	std::shared_ptr<Scene> StageTutorial;
	std::shared_ptr<Scene> stage1;
	std::shared_ptr<Scene> stage2;

	std::shared_ptr<Scene> pauseScene;
	//std::shared_ptr<Scene> stage3;

	SoundManager sManager;
	GraphManager gManager;

public:
	SceneManager();
	~SceneManager();

	/// <summary>
	/// �����Ă���V�[����Update�֐����Ăяo��
	/// </summary>
	/// <param name="input">���̓N���X</param>
	void Update(Input& input);

	/// <summary>
	/// �����Ă���V�[����Draw�֐����Ăяo��
	/// </summary>
	void Draw();

	/// <summary>
	/// ���s���̃V�[���������Ŏw�肵���V�[���ɐ؂�ւ���
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// Scene���N���A���ăV�[����؂�ւ���
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeAndClearScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// ���ݐ擪�Ŏ��s���̃V�[���̏�ɃV�[�����������
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// ���݂̐擪�V�[�����폜����
	/// </summary>
	void popScene(bool isToTitle = false);

	//TODO:�X�e�[�W���Ƃ̃A�h���X�Ƃ���ۑ�����GameoverScene����retry�Ō��̃X�e�[�W�ɖ߂��悤�ɂ���

	void GetPtr(int stageNum);

	void LoadG(std::string name, std::string path);

	void Draw(float x, float y, float exRate, float angle, std::string name);

	int ReturnFontHandle() { return fontHandle; }
	int ReturnFontHandle2() { return fontHandle2; }

	void SetStageClearFlag(int stageNum);

	/// <summary>
	/// �X�e�[�W�N���A�t���O��Ԃ�
	/// </summary>
	/// <param name="stageNum">1:stage1, 2:stage2</param>
	/// <returns>�N���A�t���O</returns>
	bool GetStageClearFlag(int stageNum);

	void SetInfo(int BGMvolume, int SEvolume, bool isFull);

	int GetBGMvolume() { return m_BGMvolume; }
	int GetSEvolume() { return m_SEvolume; }
	bool GetisFull() { return m_isFull; }

};