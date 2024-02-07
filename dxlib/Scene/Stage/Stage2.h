#pragma once
#include <vector>
#include <memory>
#include "StageBase.h"

class Stage2 : public StageBase
{
public:
	Stage2(SceneManager& mgr);
	~Stage2();
	void Update(Input& input);
	void Draw();

private:
	void CreateLineRush(int pattern, int firstFrame);

	int baseFrame = 0;

};