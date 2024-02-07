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
	/// 直前のシーンを残す
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
	/// 持っているシーンのUpdate関数を呼び出す
	/// </summary>
	/// <param name="input">入力クラス</param>
	void Update(Input& input);

	/// <summary>
	/// 持っているシーンのDraw関数を呼び出す
	/// </summary>
	void Draw();

	/// <summary>
	/// 実行中のシーンを引数で指定したシーンに切り替える
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// Sceneをクリアしてシーンを切り替える
	/// </summary>
	/// <param name="nextScene"></param>
	void ChangeAndClearScene(std::shared_ptr<Scene> nextScene);

	/// <summary>
	/// 現在先頭で実行中のシーンの上にシーンを乗っける
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// 現在の先頭シーンを削除する
	/// </summary>
	void popScene(bool isToTitle = false);

	//TODO:ステージごとのアドレスとかを保存してGameoverSceneからretryで元のステージに戻れるようにする

	void GetPtr(int stageNum);

	void LoadG(std::string name, std::string path);

	void Draw(float x, float y, float exRate, float angle, std::string name);

	int ReturnFontHandle() { return fontHandle; }
	int ReturnFontHandle2() { return fontHandle2; }

	void SetStageClearFlag(int stageNum);

	/// <summary>
	/// ステージクリアフラグを返す
	/// </summary>
	/// <param name="stageNum">1:stage1, 2:stage2</param>
	/// <returns>クリアフラグ</returns>
	bool GetStageClearFlag(int stageNum);

	void SetInfo(int BGMvolume, int SEvolume, bool isFull);

	int GetBGMvolume() { return m_BGMvolume; }
	int GetSEvolume() { return m_SEvolume; }
	bool GetisFull() { return m_isFull; }

};