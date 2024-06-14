#pragma once
#include <array>
#include <vector>
#include <string>
#include <map>
// シングルトンを使用したサウンドクラス
class Sound
{
private:
	Sound() = default;
	virtual ~Sound() = default;

	static Sound* m_instance;

public:
	// コピーコンストラクタの禁止
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
		// 固定データ
		bool isBgm;				// これがBGMか効果音か
		float volRate;			// ボリューム調整
		bool isSync;			// true:同期	false:非同期

		// 再生データ
		int handle;				// サウンドハンドル

		// サウンド情報
		int freq;				// 再生周波数
	};

public:
	// サウンドのロード、アンロード
	void loadStart();
	void unload();
	
	// ロード完了確認
	bool isLoaded();
	// ロード終了後のデータ収集	全てのサウンドロードが完了してから行う
	void collectData();

	// サウンドの再生	最大音量(255)に設定しなおされる
	void play(std::string filename, float speed = 1.0f);
	// BGM再生	playとの違いはループ再生だけ
	void playBgm(std::string filename, float speed = 1.0f);
	// サウンドの終了
	void stop(std::string filename);
	// ボリューム設定	0~255
	void setVolume(std::string filename, int vol);
	// 再生速度の変更
	void setSpeed(std::string filename, float speed);

private:
	// ファイル名からデータ取得
	Data getData(std::string filename);

private:
	// ファイル情報
	std::map<std::string, Data>		m_data;
};
