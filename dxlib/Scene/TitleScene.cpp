#include <DxLib.h>
#include <cmath>
#include "../Util/Input.h"
#include "../Util/Application.h"
#include "../Util/Game.h"
#include "SceneManager.h"
#include "../DrawBGparts.h"
#include "TitleScene.h"
#include "StageSelect.h"
#include "OptionScene.h"

namespace
{
	constexpr int kGraphNum = 5;
	//フェードイン、フェードアウトにかかる時間
	constexpr int kFadeFrame = 30;

	constexpr int kButtonMoveSpeed = 24;

	constexpr int kBGnum= 10;
}



void TitleScene::FadeInUpdate(Input&)
{
	m_fadeFrame--;
	if (m_fadeFrame <= 0)
	{
		//フェードインが終わったら状態を遷移する
		//次の遷移先
		updateFunc_ = &TitleScene::NormalUpdate;
		drawFunc_ = &TitleScene::NormalDraw;
	}
}

void TitleScene::NormalUpdate(Input& input)
{
	//入力の処理はフェード中できないようにしたいからここに入れる
	//上方向を押したとき
	if (input.IsTriggered("UP"))
	{
		//プレイボタンを選択している場合
		if (nowButton == Play)
		{
			//下に戻す？
			/*nowButton = Quit;*/
		}
		//オプションボタンを選択している場合
		else if (nowButton == Option)
		{
			m_manager.sManager.PlaySE("moveSE");
			//プレイボタンを選択している状態にする
			nowButton = Play;
		}
		//やめるボタンを選択している場合
		else if (nowButton == Quit)
		{
			m_manager.sManager.PlaySE("moveSE");
			//オプションボタンを選択している状態にする
			nowButton = Option;
		}
	}

	//下方向を押したとき
	if (input.IsTriggered("DOWN"))
	{
		if (nowButton == Play)
		{
			m_manager.sManager.PlaySE("moveSE");
			nowButton = Option;
		}
		else if (nowButton == Option)
		{
			m_manager.sManager.PlaySE("moveSE");
			nowButton = Quit;
		}
		else if (nowButton == Quit)
		{
			//now = Play;
		}
	}

	//プレイボタンでOKを押したとき
	if (input.IsTriggered("OK") && nowButton == Play)
	{
		m_manager.sManager.PlaySE("enterSE");

		//もしEnterキーが押されたらフェードインを始める
		updateFunc_ = &TitleScene::FadeOutUpdate;
		drawFunc_ = &TitleScene::FadeDraw;
		m_fadeFrame = 0;
	}

	//オプションボタンでOKを押したとき
	if (input.IsTriggered("OK") && nowButton == Option/* || input.IsTriggered("pause")*/)
	{
		m_manager.sManager.PlaySE("enterSE");

		m_manager.PushScene(std::make_shared<OptionScene>(m_manager));
	}
	//やめるボタンでOKを押したとき
	if (input.IsTriggered("OK") && nowButton == Quit)
	{
		Application::GetInstance().Terminate();
	}
}

void TitleScene::FadeOutUpdate(Input&)
{
	m_fadeFrame++;
	m_manager.sManager.FadeOutBGM("Title", m_fadeFrame);
	if (m_fadeFrame >= kFadeFrame)
	{
		//フェードアウトが終わったらSceneを変える
		if (nowButton == Play)
		{
			m_manager.ChangeScene(std::make_shared<StageSelect>(m_manager));
		}
	}
}

void TitleScene::FadeDraw()
{
	//通常の描画(NormalDrawに書いたものをコピペする)

	m_manager.Draw(300, titlePosY, titleSize, 0, "Title");

	m_manager.Draw(playButtonPosX, 400, 1.0, 0, "Button1");
	DrawStringToHandle(playButtonPosX + 148, 220, "スタート", 0xffffff, m_manager.ReturnFontHandle());

	m_manager.Draw(optionButtonPosX, 540, 1.0, 0, "Button2");
	DrawStringToHandle(optionButtonPosX + 148, 360, "オプション", 0xffffff, m_manager.ReturnFontHandle());

	m_manager.Draw(quitButtonPosX, 680, 1.0, 0, "Button3");
	DrawStringToHandle(quitButtonPosX + 148, 500, "やめる", 0xffffff, m_manager.ReturnFontHandle());

#ifdef _DEBUG
	DrawString(0, 0, "TitleScene", 0xffffff);
#endif

	//フェード暗幕
	int alpha = 255 * (float)m_fadeFrame / (float)kFadeFrame;
	SetDrawBlendMode(DX_BLENDMODE_MULA, alpha);
	DrawBox(0, 0, Game::kScreenWidth, Game::kScreenHeight, 0x000000, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
}

void TitleScene::NormalDraw()
{
	m_manager.Draw(300, titlePosY, titleSize, 0, "Title");

	m_manager.Draw(playButtonPosX, 400, 1.0, 0, "Button1");
	DrawStringToHandle(playButtonPosX + 148, 220,"スタート",0xffffff,m_manager.ReturnFontHandle());

	m_manager.Draw(optionButtonPosX, 540, 1.0, 0, "Button2");
	DrawStringToHandle(optionButtonPosX + 148, 360, "オプション", 0xffffff, m_manager.ReturnFontHandle());

	m_manager.Draw(quitButtonPosX, 680, 1.0, 0, "Button3");
	DrawStringToHandle(quitButtonPosX + 148, 500, "やめる", 0xffffff, m_manager.ReturnFontHandle());


#ifdef _DEBUG
	DrawString(0, 0, "TitleScene", 0xffffff);
#endif
}

TitleScene::TitleScene(SceneManager& manager) :
	Scene(manager),
	playButtonPosX(680),
	optionButtonPosX(800),
	quitButtonPosX(800)
{
	parts.resize(kBGnum);

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i] = new DrawBGparts;
		parts[i]->Init(false);
	}

	//BGMのロード
	//m_manager.LoadS("kitai","musicFile/MusMus-BGM-142.mp3",false);

	m_fadeFrame = 60;
	updateFunc_ = &TitleScene::FadeInUpdate;
	drawFunc_ = &TitleScene::FadeDraw;
}

TitleScene::~TitleScene()
{

}

void TitleScene::Update(Input& input)
{
	m_manager.sManager.PlayBGM("Title", true);

	(this->*updateFunc_)(input);
	frame++;

	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Update();
	}

	//if (frame % 30 == 0)
	//{
	//	titlePosY -= 10;
	//}
	//else
	//{
	//	titlePosY = 280;
	//}

	if (frame == 64)
	{
		titleSize = titleSize * 1.08f;
	}
	else if (frame== 142)
	{
		titleSize = titleSize * 1.08f;
		frame = 0;
	}
	else
	{
		titleSize = 0.28f;
	}

	//playボタンを選択している場合
	if (nowButton == Play)
	{
		//playボタンを左に動かす
		if (playButtonPosX >= 680)
		{
			playButtonPosX -= kButtonMoveSpeed;
		}
	}
	//選択していない場合
	else
	{
		//右に動かす
		if (playButtonPosX <= 800)
		{
			playButtonPosX += kButtonMoveSpeed;
		}
	}

	if (nowButton == Option)
	{
		if (optionButtonPosX >= 680)
		{
			optionButtonPosX -= kButtonMoveSpeed;
		}
	}
	else
	{
		if (optionButtonPosX <= 800)
		{
			optionButtonPosX += kButtonMoveSpeed;
		}
	}

	if (nowButton == Quit)
	{
		if (quitButtonPosX >= 680)
		{
			quitButtonPosX -= kButtonMoveSpeed;
		}
	}
	else
	{
		if (quitButtonPosX <= 800)
		{
			quitButtonPosX += kButtonMoveSpeed;
		}
	}
}

void TitleScene::Draw()
{
	//BG
	for (int i = 0; i < parts.size(); i++)
	{
		parts[i]->Draw();
	}
	(this->*drawFunc_)();
}
