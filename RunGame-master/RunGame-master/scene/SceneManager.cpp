#include "SceneManager.h"
#include <cassert>
#include "SceneBase.h"
#ifdef _DEBUG
#include "SceneDebug.h"
#include "SceneTest.h"
#include "SceneTitle.h"
#else
#include "SceneTitle.h"
#endif

#include "SceneLoading.h"

#include "Pad.h"
#include "Mouse.h"

SceneManager::SceneManager():
	m_pScene()
{
}
SceneManager::~SceneManager()
{

}

void SceneManager::init()
{
#if true
#ifdef _DEBUG
	m_pScene.reset(new SceneDebug);
//	m_pScene.reset(new SceneTitle);
#else
	m_pScene.reset(new SceneTitle);
#endif
#else
	// ゲーム開始前にロード画面を挟む	デバッグ版はその後デバッグメニューに、リリース版はタイトルへ
	m_pScene.reset(new SceneLoading);
#endif
	m_pScene->startLoad();	
}

void SceneManager::end()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->endAll();
}

bool SceneManager::update()
{
	assert(m_pScene);
	if (!m_pScene)	return false;

	Pad::update();
	Mouse::update();

	m_pScene->updateAll();
	if (m_pScene->isSceneEnd())
	{
		// シーン遷移

		m_pScene->endAll();	// 前のシーンの終了処理
		SceneBase* pNext = m_pScene->getNextScene();
		if (!pNext)
		{
			return false;	// nullptrで終了
		}
		m_pScene.reset(pNext);
		m_pScene->startLoad();
	}
	return true;
}

void SceneManager::draw()
{
	assert(m_pScene);
	if (!m_pScene)	return;

	m_pScene->drawAll();
}