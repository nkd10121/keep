#pragma once
#include "Scene.h"
class GameOverScene : public Scene
{
public:
	GameOverScene(SceneManager& mgr);
	void Update(Input& input);
	void Draw();
};

