#pragma once
#include "Scene.h"
#include "DxLib.h"

#include <vector>
/// <summary>
/// 選択しているボタン
/// </summary>
enum ButtonName
{
	Play,
	Option,
	Quit
};

class DrawBGparts;

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{
private:
	//選択しているボタン
	int nowButton = Play;

	int m_fadeFrame = 0;
	int frame = 3;

	//背景を振動させる倍率
	float mag = 1.0f;
	//タイトルロゴのサイズ
	float titleSize = 0.28f;
	//タイトルのY座標
	int titlePosY = 280;

	//プレイボタンのX座標
	int playButtonPosX;
	//オプションボタンのX座標
	int optionButtonPosX;
	//やめるボタンのX座標
	int quitButtonPosX;

	std::vector<DrawBGparts*> parts;

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