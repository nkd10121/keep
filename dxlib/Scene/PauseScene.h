#pragma once
#pragma once
#include "Scene.h"
#include "../Util/Vec2.h"

#include <vector>

/// <summary>
/// 左の項目
/// </summary>
enum Item
{
	Setting,
	Operation,
	ToTitle,
	Close,
	BGM,
	SE,
	FullScreen,
	ReturnTitle

};

struct Info
{
	Item item;
	Vec2 pos;
};

class AfterImagePlayer;

class PauseScene :public Scene
{
public:
	PauseScene(SceneManager& manager);
	~PauseScene();
	void Update(Input& input);
	void Draw();

private:
	int m_frame = 0;

	int pHandle = -1;
	int checkHandle = -1;

	//プレイヤーの角度
	float angle = 0;

	int BGMnum = 5;
	int SEnum = 5;
	bool isFullScreen = false;

	bool isFromToTitle = false;
	bool isReturn = false;

	//カーソルの情報
	Info cursol;
	Info cursolLog;

	//項目の選択肢の情報
	Info test[8];

	//残像
	std::vector<AfterImagePlayer*> afterImage;
	//残像生成の関数
	void CreateAfterImage(Vec2 pos);

	//更新メンバ関数ポインタ
	void (PauseScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	void (PauseScene::* drawFunc_)();

	//通常状態のUpdate
	void DefaultUpdate(Input& input);
	//設定状態のUpdate
	void SettingUpdate(Input& input);

	void ReturnTitleUpdate(Input& input);

	//設定状態のDraw
	void SettingDraw();
	//操作説明状態のDraw
	void OperationDraw();

	void ReturnTitleDraw();
	//閉じる状態のDraw
	void CloseDraw();
};