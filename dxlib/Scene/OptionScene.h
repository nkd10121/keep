#pragma once
#include "Scene.h"
#include "../Util/Vec2.h"

#include <vector>

/// <summary>
/// 左の項目
/// </summary>
enum Item
{
	//設定
	Setting,
	//操作説明
	Operation,
	//権利表記
	Credit,
	//閉じる
	Close,
	//BGM
	BGM,
	//SE
	SE,
	//フルスクリーン
	FullScreen
};

/// <summary>
/// 項目名と座標を持つ
/// </summary>
struct Info
{
	//項目名
	Item item;
	//座標
	Vec2 pos;
};

class AfterImagePlayer;

class OptionScene :  public Scene
{
public:
	OptionScene(SceneManager& manager);
	~OptionScene();
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

	//カーソルの情報
	Info cursol;
	Info cursolLog;

	//項目の選択肢の情報
	Info test[7];

	//残像
	std::vector<AfterImagePlayer*> afterImage;
	//残像生成の関数
	void CreateAfterImage(Vec2 pos);

	//更新メンバ関数ポインタ
	void (OptionScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	void (OptionScene::* drawFunc_)();

	//通常状態のUpdate
	void DefaultUpdate(Input& input);
	//設定状態のUpdate
	void SettingUpdate(Input& input);

	//設定状態のDraw
	void SettingDraw();
	//操作説明状態のDraw
	void OperationDraw();
	//権利表記状態のDraw
	void CreditDraw();
	//閉じる状態のDraw
	void CloseDraw();
};

