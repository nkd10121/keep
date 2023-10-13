#pragma once
#include "Scene.h"
class GameOverScene : public Scene
{
private:
	int handle_;
	int frame_ = 0;

	//状態遷移用メンバ関数ポインタの宣言
	using UpdateFunc_t = void (GameOverScene::*)(Input&);
	using DrawFunc_t = void (GameOverScene::*)();

	UpdateFunc_t updateFunc_ = nullptr;
	DrawFunc_t drawFunc_ = nullptr;

	//更新関数
	void FadeInUpdate(Input& input);
	void NormalUpdate(Input& input);
	void FadeOutUpdate(Input& input);

	//描画関数
	void FadeDraw();
	void NormalDraw();

public:
	GameOverScene(SceneManager& mgr);
	~GameOverScene();
	void Update(Input& input);
	void Draw();
};

