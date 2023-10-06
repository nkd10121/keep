#pragma once
#include "Scene.h"

/// <summary>
/// タイトルシーンクラス
/// </summary>
class TitleScene : public Scene
{
public:
	TitleScene(SceneManager& manager);
	void Update(Input& input);
	void Draw();
};

