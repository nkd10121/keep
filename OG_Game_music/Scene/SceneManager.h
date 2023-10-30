#pragma once
#include <list> 
#include <memory>
class Input;
class Scene;

class SceneManager
{
private:
	std::list < std::shared_ptr<Scene>> scenes;

public:
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
	/// 現在先頭で実行中のシーンの上にシーンを乗っける
	/// </summary>
	/// <param name="scene"></param>
	void PushScene(std::shared_ptr<Scene> scene);

	/// <summary>
	/// 現在の先頭シーンを削除する
	/// </summary>
	void popScene();
};

