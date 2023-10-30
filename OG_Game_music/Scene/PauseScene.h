#pragma once
#include "Scene.h"

class Input;
class SceneManager;

class PauseScene :public Scene
{
private:
	int frame_ = 0;
	//更新メンバ関数ポインタ
	using UpdateFunc_f = void (PauseScene::*)(Input& input);
	UpdateFunc_f updateFunc_;

	//描画メンバ関数ポインタ
	using DrawFunc_t = void (PauseScene::*)();
	DrawFunc_t drawFunc_;

	//更新関数
	void AppearUpdate(Input&);		//登場状態
	void NormalUpdate(Input&);		//通常状態
	void DisappearUpdate(Input&);	//退場状態

	//描画関数
	void ExpandDraw();		//拡張縮小描画
	void NormalDraw();	//通常描画

public:
	PauseScene(SceneManager& manager);
	void Update(Input& input);
	void Draw();
};