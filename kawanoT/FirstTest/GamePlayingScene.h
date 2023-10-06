#pragma once
#include "Scene.h"
class GamePlayingScene : public Scene
{
public:
	GamePlayingScene(SceneManager& mgr);
	void Update(Input& input);
	void Draw();
};

