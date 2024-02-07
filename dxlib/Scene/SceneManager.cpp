#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() :
	m_isFull(false)
{
	//使用するフォントを準備する
	font_path = "data/font/PixelMplus12-Bold.ttf"; // 読み込むフォントファイルのパス
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// フォント読込エラー処理
		MessageBox(NULL, "フォント読込失敗", "", MB_OK);
	}
	//タイトル表示用のフォント
	fontHandle = CreateFontToHandle("PixelMplus12", 48, -1);
	fontHandle2 = CreateFontToHandle("PixelMplus12", 24, -1);

	LoadG("BG", "data/titleParts.png");
	LoadG("Title", "data/title.png");
	LoadG("Button1", "data/Button1.png");
	LoadG("Button2", "data/Button2.png");
	LoadG("Button3", "data/Button3.png");

	LoadG("sousaCon", "data/sousa.png");
	LoadG("sousaKey", "data/sousaKeyboard.png");
	LoadG("stageTutorialDetail", "data/stageTutorialDetail.png");
	LoadG("stage1Detail", "data/stage1Detail.png");
	LoadG("stage2Detail", "data/stage2Detail.png");

	LoadG("Tutorial1", "data/text.png");
	LoadG("Tutorial2", "data/text2.png");
	LoadG("Tutorial3", "data/text3.png");

	sManager.Load("Title", "data/sound/Player.mp3",true);
	sManager.Load("Tutorial", "data/sound/Electric_Shine.mp3", true);
	sManager.Load("stage1", "data/sound/Kagura.wav", true);
	sManager.Load("stage2", "data/sound/15 80's Graffiti .mp4", true);

	//プレイヤーが当たった時のSE
	sManager.Load("hitSE", "data/se/ヒット＿強打3.wav", false);
	//決定した時のSE
	sManager.Load("enterSE", "data/se/決定＿小決定（SF系）.wav", false);
	//カーソルを動かしたときのSE
	sManager.Load("moveSE", "data/se/カーソル（柔らかい）2.wav", false);
	//ゴールした時のSE
	sManager.Load("GoalSE", "data/se/maou_se_magical27.mp3", false);
	//ゲームオーバーから復活するとき
	sManager.Load("RevivalSE", "data/se/ゲージ回復1.mp3", false);
	//ゲームオーバーであきらめたとき
	sManager.Load("deathSE", "data/se/射撃＿ピストル.wav", false);
}

SceneManager::~SceneManager()
{
	// ********** フォントのアンロード **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}

	//作成したフォントをメモリから解放する
	DeleteFontToHandle(fontHandle);
}

void SceneManager::Update(Input& input)
{
	//BG
	DrawBox(0, 0, 1280, 720, 0x0d1118, true);

	sManager.ChangeBGMVolume(m_BGMvolume);
	sManager.ChangeSEVolume(m_SEvolume);

	//末尾のみ実行
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//先頭から順に描画
	//最後に積んだものが最後に描画される
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes.empty())//リストが空っぽだったら入れ替えずに
	{
		scenes.push_back(nextScene);//末尾に追加
	}
	else
	{
		logScene = *(scenes.begin());
		scenes.back() = nextScene;//既に一つ以上あれば末尾を
	}
}

void SceneManager::ChangeAndClearScene(std::shared_ptr<Scene> nextScene)
{
	scenes.clear();

	scenes.push_back(nextScene);//末尾に追加
	
}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes.push_back(scene);
}

void SceneManager::popScene(bool isToTitle)
{
	//シーンのログを更新して
	logScene = *(scenes.begin());
	if (!isToTitle)
	{
		//もし直前のシーンがstage1だったら
		//stage1のBGMを途中から再生する
		if (logScene == stage1)
		{
			sManager.PlayBGM("stage1", false);
		}
		//もし直前のシーンがstage2だったら
		//stage2のBGMを途中から再生する
		else if (logScene == stage2)
		{
			sManager.PlayBGM("stage2", false);
		}
		else if (logScene == StageTutorial)
		{
			sManager.PlayBGM("Tutorial", false);
		}
	}

	scenes.pop_back();
}

void SceneManager::GetPtr(int stageNum)
{
	switch (stageNum)
	{
	case 0:
		{
			StageTutorial = *(scenes.begin());
		}
		break;
	case 1:
		{
			stage1 = *(scenes.begin());
		}
		break;
	case 2:
		{
			stage2 = *(scenes.begin());
		}
		break;
	case 3:
		pauseScene = *(scenes.begin());
		break;
	}
}

void SceneManager::LoadG(std::string name, std::string path)
{
	gManager.Load(name, path);
}

void SceneManager::Draw(float x, float y, float exRate, float angle, std::string name)
{
	gManager.Draw(x, y, exRate, angle, name);
}


void SceneManager::SetStageClearFlag(int stageNum)
{
	switch (stageNum)
	{
	case 1:
		clearStage1 = true;
		return;
	case 2:
		clearStage2 = true;
		return;
	default:
		return;
	}
}

bool SceneManager::GetStageClearFlag(int stageNum)
{
	switch (stageNum)
	{
	case 1:
		return clearStage1;
	case 2:
		return clearStage2;
	default:
		return false;
	}
}

void SceneManager::SetInfo(int BGMvolume, int SEvolume, bool isFull)
{
	SetBGMvolume(BGMvolume);
	SetSEvolume(SEvolume);
	SetIsFull(isFull);
}
