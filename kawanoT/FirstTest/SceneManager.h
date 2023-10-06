#pragma once
class Input;
class Scene;

/// <summary>
/// 各シーンの遷移と操作をコントロールするクラス
/// </summary>
class SceneManager
{
private:
	Scene* scene_ = nullptr;
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
	/// 現在実行中のシーンを引数で指定されたシーンに切り替える
	/// </summary>
	void ChangeScene(Scene* nextScene);
};

