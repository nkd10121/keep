#pragma once

#include <memory>

class SceneBase;
class SceneManager
{
public:
	SceneManager();
	virtual ~SceneManager();

	void init();
	void end();

	bool update();	// �Q�[���I����false��Ԃ�
	void draw();
private:
//	SceneBase* m_pScene;
	std::unique_ptr<SceneBase>	m_pScene;
};