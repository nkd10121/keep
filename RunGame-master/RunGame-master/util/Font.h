#pragma once

// フォント関連処理
namespace Font
{
	enum class Id
	{
		Size200_8,
		Size96_8,
		Size96_4,
		Size64_4,
		Size48_4,
		Size32_4,
		Size24_4,
		Size16_4,
		Normal,	// ゴシック

		// ここまでが準備されるデータ

		Num,	// フォントの種類の数

		// ここ以降は準備したデータのどれを使うかを指定する

		// SceneTitle
		GameTitle = Size200_8,
		TitleMenu = Size48_4,

		// SceneMainMenu
		MainMenuTitle = Size96_4,
		MainMenuItemL = Size64_4,
		MainMenuItemS = Size32_4,

		// SceneMain
		PlayTutorial = Size32_4,
		TutorialSkip = Size48_4,
		PlayerNo = Size16_4,
		CountDown = Size200_8,
		DispDistance = Size16_4,
		GameScore = Size32_4,
		GameScoreMulti = Size16_4,
		GameOver = Size96_8,
		GameMessage = Size96_8,
		ResultScore = Size32_4,

		// SceneRecord
		RecordBack = Size48_4,

		// SceneSelectPlayerNum
		PlayerNumTitle = Size96_4,
		PlayerNumPlayerNo = Size16_4,

		// SceneRecord
		RecordTitle = Size96_4,

		// SceneStaff
		StaffName = Size32_4,

		// UI
		TelopText = Size32_4,
	};
#if false
	// ロード、アンロード
	void setup();
	void release();
#else
	// フォントのロード、アンロード
	void loadStart();
	void unload();

	// ロード完了確認
	bool isLoaded();
	// ロード終了後のデータ収集	全てのフォントロードが完了してから行う
	void collectData();
#endif
	// フォントハンドル取得
	int getHandle(Id id);
	// フォントサイズ取得
	int getSize(Id id);

	// 文字列の幅取得
	int getStringWidth( const char* pText, Id id );
	// kerning:文字間の幅	-で文字間を詰める
	int getStringWidth(const char* pText, int handle, int kerning);

	// 文字列表示
	void drawString(int x, int y, const char* pText, int color, Id id);

	// 横中央位置に文字列表示
	void drawStringCenter( int y, const char* pText, int color, Id id );

	// フレーム数を時間に変換して表示
	// 左上座標を指定	とりあえずゲームで使用する"%2d:%02d.%03d"表記のみ,100分を超える場合は99:59.999に
	void drawTimeFromFrame(int x, int y, int frameCount, int color, Id id);
	// ↑の関数で時間を表示するときの表示幅
	int getDrawTimeWidth(Id id);
}
