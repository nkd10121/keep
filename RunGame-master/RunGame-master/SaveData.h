#pragma once
// シングルトンを使用したセーブデータ管理クラス
class SaveData
{
public:
	// セーブデータに保存するフラグ
	enum GameFlag
	{
		TutorialEnd = 0,

	//	// アチーブメント関連	数値は変更されているかも
	//	Achieve_TutorialClear,	// チュートリアルを最後までプレイした
	};
#if false
	// 設定
	enum ConfigFlag
	{
		FullScreen = 0,	// フルスクリーン設定
		Vibration = 1,	// 振動ONOFF
	};
#endif
	// ランキングデータ残す人数
	static constexpr int kSaveRankDataNum = 10;
	
private:
	SaveData() = default;
	virtual ~SaveData() = default;

	static SaveData* m_instance;

public:
	// コピーコンストラクタの禁止
	SaveData(const SaveData&) = delete;
	SaveData& operator=(const SaveData&) = delete;
	SaveData(SaveData&&) = delete;
	SaveData& operator=(SaveData&&) = delete;

	static SaveData& getInstance()
	{
		if (!m_instance)
		{
			m_instance = new SaveData;
		}
		return *m_instance;
	}
	static void destroy()
	{
		delete m_instance;
		m_instance = nullptr;
	}
public:
	// データの読み込み
	void load();
	// セーブデータの書き込み
	void write();

	// プレイデータの設定	書き込みは行わないので設定が終わったらwrite()する
	void gameFlagOn(GameFlag flag);
	void gameFlagOff(GameFlag flag);
	// 指定したフラグが立っているか
	bool isGameOn(GameFlag flag);

	// ランキング取得	0~kSaveRankDataNum-1　を指定して取得
	int getRankPlayerKind(int rank);
	int getRankPlayerScore(int rank);

	// スコアの登録	ランクインしたらその順位を0~kSaveRankDataNum-1で返す	入らなかったら-1
	int entryScore(int score, int playerKind);


	// アチーブメント関連
	void updateAchieve();	// プレイ記録をチェックしてアチーブメントのフラグを立てる

	// セーブデータを新規作成して上書き(新規保存)
	void createNewData();

#ifdef _DEBUG
	// 全てのフラグをONにする
	void setAllFlag();
#endif

private:
	void clearData();
	// フラグON,OFF
	// isOn:　trueでフラグを立てる、falseで落とす
	void setFlag(GameFlag flag, bool isOn);

private:
	struct RankData
	{
		int playerKind;
		int score;
		unsigned int reserved0 = 0;	// 予備領域
		unsigned int reserved1 = 0;	// 予備領域
	};

	// 保存するセーブデータ本体
	struct DataCore
	{
		int version = 0;		// データのバージョン
		// 1ビットのフラグ
		unsigned int gameFlag = 0;	// 各種フラグ(MAX32)
		unsigned int reserved0 = 0;	// 予備領域
		unsigned int reserved1 = 0;	// 予備領域

		// ランキング
		RankData rankData[kSaveRankDataNum];
	};

private:
	DataCore m_data;
};

