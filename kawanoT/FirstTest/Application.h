#pragma once
#include <iostream>
/// <summary>
/// アプリケーション全体を管理するクラス
/// シングルトンクラス
/// </summary>
class Application
{
private:
	Application() {};

	//コピー＆代入を禁止
	Application(const Application& app) = delete;
	void operator=(const Application& app) = delete;

	/// <summary>
	/// 後処理を行う
	/// </summary>
	void Terminate();

public:
	/// <summary>
	/// Applicationのシングルトンインスタンスの参照を返す
	/// </summary>
	/// <returns>Applicationインスタンス</returns>
	static Application& GetInstance() {
		static Application instance;
		return instance;
	}

	bool Init();
	void Run();

};

