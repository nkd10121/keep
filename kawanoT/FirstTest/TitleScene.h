#pragma once
#include "Scene.h"

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{
private:
	int handle_ = 0;
	int frame_ = 0;
	//更新メンバ関数ポインタ
	void (TitleScene::* updateFunc_)(Input& input);
	//描画メンバ関数ポインタ
	using DrawFunc_t = void (TitleScene::*)();
	DrawFunc_t drawFunc_;

	//更新関数
	void FadeInUpdate(Input&);	//フェードイン状態
	void NormalUpdate(Input& input);	//通常状態
	void FadeOutUpdate(Input&);	//フェードアウト状態

	//描画関数
	void FadeDraw();
	void NormalDraw();

public:
	TitleScene(SceneManager& manager);
	~TitleScene();
	void Update(Input& input);
	void Draw();
};

