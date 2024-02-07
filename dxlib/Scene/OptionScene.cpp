#include "OptionScene.h"
#include "../Util/Input.h"
#include "../Util/Game.h"
#include "SceneManager.h"
#include "TitleScene.h"
#include <DxLib.h>

#include "../Util/Application.h"
#include "../Efect/AfterImagePlayer.h"

namespace
{
	//残像の最大数
	constexpr int kAfterImageNumMax = 64;

	constexpr int kBoxSize = 20;
}

OptionScene::OptionScene(SceneManager& manager) :
	Scene(manager)
{
	//プレイヤーハンドルの取得
	pHandle = LoadGraph("data/player/player0.png");
	checkHandle = LoadGraph("data/UI_check.png");

	//項目の初期化
	test[0].item = Setting;
	test[0].pos = { static_cast<float>(120), static_cast<float>(124) };
	test[1].item = Operation;
	test[1].pos = { static_cast<float>(80), static_cast<float>(224) };
	test[2].item = Credit;
	test[2].pos = { static_cast<float>(80), static_cast<float>(324) };
	test[3].item = Close;
	test[3].pos = { static_cast<float>(110), static_cast<float>(424) };
	test[4].item = BGM;
	test[4].pos = { static_cast<float>(376), static_cast<float>(110) };
	test[5].item = SE;
	test[5].pos = { static_cast<float>(376), static_cast<float>(210) };
	test[6].item = FullScreen;
	test[6].pos = { static_cast<float>(376), static_cast<float>(310) };

	//カーソルは最初に設定のところに
	cursol = test[0];

	BGMnum = m_manager.GetBGMvolume();
	SEnum = m_manager.GetSEvolume();
	isFullScreen = m_manager.GetisFull();

	//残像のサイズ
	afterImage.resize(kAfterImageNumMax);

	updateFunc_ = &OptionScene::DefaultUpdate;
	drawFunc_ = &OptionScene::SettingDraw;
}

OptionScene::~OptionScene()
{
	DeleteGraph(pHandle);
	DeleteGraph(checkHandle);

	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			delete afterImage[i];
			afterImage[i] = nullptr;
		}
	}
}

void OptionScene::Update(Input& input)
{
	//オプション画面を開いたときもならないように
	if (cursolLog.pos != Vec2{})
	{
		//カーソル移動時に音声を流す
		if (cursol.item != cursolLog.item)
		{
			m_manager.sManager.PlaySE("moveSE");
		}
	}

	cursolLog = cursol;

	m_frame++;
	angle += 0.08f;

	(this->*updateFunc_)(input);

	/*カーソルの残像関係*/
	if (m_frame % 4 == 0)
	{
		CreateAfterImage(cursol.pos);
	}

	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			afterImage[i]->Update();

			//使用済みの敵キャラクタを削除する必要がある
			if (!afterImage[i]->isExist())
			{
				//メモリを解放する
				delete afterImage[i];
				afterImage[i] = nullptr;	//使っていないとわかるように
			}
		}
	}
}

void OptionScene::Draw()
{
	/*枠の描画*/
	SetDrawBlendMode(DX_BLENDMODE_MUL, 255);
	DrawBox(50, 50, Game::kScreenWidth - 50, Game::kScreenHeight - 50, 0x222222, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	DrawBox(50, 50, Game::kScreenWidth - 50, Game::kScreenHeight - 50, 0xffffff, false);

	/*項目の描画*/
	DrawStringToHandle(150, 100, "設定", 0xffffff, m_manager.ReturnFontHandle());
	DrawStringToHandle(100, 200, "操作説明", 0xffffff, m_manager.ReturnFontHandle());
	DrawStringToHandle(100, 300, "権利表記", 0xffffff, m_manager.ReturnFontHandle());
	DrawStringToHandle(130, 400, "閉じる", 0xffffff, m_manager.ReturnFontHandle());

	/*残像の描画*/
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (afterImage[i])
		{
			afterImage[i]->Draw();
		}
	}

	/*カーソルの描画*/
	DrawRotaGraph(cursol.pos.x, cursol.pos.y, 0.8f, angle, pHandle, true);

	(this->*drawFunc_)();
}

void OptionScene::CreateAfterImage(Vec2 pos)
{
	for (int i = 0; i < afterImage.size(); i++)
	{
		if (!afterImage[i])
		{
			afterImage[i] = new AfterImagePlayer;
			afterImage[i]->Init(pos, { 1,0 }, 4, false);
			return;
		}
	}
}

void OptionScene::DefaultUpdate(Input& input)
{
	/*入力関係*/
	if (input.IsTriggered("pause") || cursol.item == Close && input.IsTriggered("OK")/*|| input.IsTriggered("CANCEL")*/)
	{
		m_manager.popScene();
	}

	if (input.IsTriggered("UP"))
	{
		if (cursol.item == Operation)
		{
			cursol = test[0];
		}

		if (cursol.item == Credit)
		{
			cursol = test[1];
		}

		if (cursol.item == Close)
		{
			cursol = test[2];
		}
	}

	if (input.IsTriggered("DOWN"))
	{
		if (cursol.item == Credit)
		{
			cursol = test[3];
		}

		if (cursol.item == Operation)
		{
			cursol = test[2];
		}

		if (cursol.item == Setting)
		{
			cursol = test[1];
		}
	}

	/*状態遷移関係*/
	if (cursol.item == test[0].item)
	{
		drawFunc_ = &OptionScene::SettingDraw;
		if (input.IsTriggered("OK"))
		{
			cursol = test[4];
			updateFunc_ = &OptionScene::SettingUpdate;
		}
	}

	if (cursol.item == test[1].item)
	{
		drawFunc_ = &OptionScene::OperationDraw;
	}

	if (cursol.item == test[2].item)
	{
		drawFunc_ = &OptionScene::CreditDraw;
	}

	if (cursol.item == test[3].item)
	{
		drawFunc_ = &OptionScene::CloseDraw;
	}

}

void OptionScene::SettingUpdate(Input& input)
{
	//ここにカーソル移動とかと
	//音量設定とかをいじれるようにする

	if (input.IsTriggered("UP"))
	{
		if (cursol.item == test[5].item)
		{
			cursol = test[4];
		}
		if (cursol.item == test[6].item)
		{
			cursol = test[5];
		}
	}

	if (input.IsTriggered("DOWN"))
	{
		if (cursol.item == test[5].item)
		{
			cursol = test[6];
		}
		if (cursol.item == test[4].item)
		{
			cursol = test[5];
		}
	}

	{
		if (input.IsTriggered("RIGHT"))
		{
			if (BGMnum < 10)
			{
				BGMnum++;
			}
			m_manager.SetInfo(BGMnum, SEnum, isFullScreen);
		}
		if (input.IsTriggered("LEFT"))
		{
			if (BGMnum > 0)
			{
				BGMnum--;
			}
			m_manager.SetInfo(BGMnum, SEnum, isFullScreen);
		}
	}

	if (cursol.item == test[5].item)
	{
		if (input.IsTriggered("RIGHT"))
		{
			if (SEnum < 10)
			{
				SEnum++;
			}
			m_manager.SetInfo(BGMnum, SEnum, isFullScreen);
		}
		if (input.IsTriggered("LEFT"))
		{
			if (SEnum > 0)
			{
				SEnum--;
			}
			m_manager.SetInfo(BGMnum, SEnum, isFullScreen);
		}
	}

	if (cursol.item == test[6].item)
	{
		if (input.IsTriggered("OK"))
		{
			isFullScreen = !isFullScreen;
			Application::GetInstance().ChangeScreenSize();
		}
	}

	if (input.IsTriggered("pause") || input.IsTriggered("CANCEL"))
	{
		m_manager.SetInfo(BGMnum, SEnum, isFullScreen);
		cursol = test[0];
		updateFunc_ = &OptionScene::DefaultUpdate;
	}
}

void OptionScene::SettingDraw()
{
	DrawStringToHandle(400, 100, "BGM音量", 0xffffff, m_manager.ReturnFontHandle2());
	for (int i = 0; i < 10; i++)
	{
		DrawBox(410 + (kBoxSize + 40) * i, 150, 410 + kBoxSize + (kBoxSize + 40) * i, 150 + kBoxSize, 0xffffff, false);
	}

	for (int i = 0; i < BGMnum; i++)
	{
		//TODO:見た目を本家みたいにしたい
		DrawBox(400 + 60 * i, 140, 440 + 60 * i, 180, 0xff00ff, true);
	}

	DrawStringToHandle(400, 200, "SE音量", 0xffffff, m_manager.ReturnFontHandle2());
	for (int i = 0; i < 10; i++)
	{
		DrawBox(410 + (kBoxSize + 40) * i, 250, 410 + kBoxSize + (kBoxSize + 40) * i, 250 + kBoxSize, 0xffffff, false);
	}

	for (int i = 0; i < SEnum; i++)
	{
		//TODO:見た目を本家みたいにしたい
		DrawBox(400 + 60 * i, 240, 440 + 60 * i, 280, 0xff00ff, true);
	}

	DrawStringToHandle(400, 300, "フルスクリーン", 0xffffff, m_manager.ReturnFontHandle2());
	DrawBox(420, 340, 460, 380, 0xffffff, false);

	if (isFullScreen)
	{
		//DrawBox(420, 340, 460, 380, 0xff0000, true);
		DrawRotaGraph(440, 360, 0.08f, 0.0f, checkHandle, true);
	}

}

void OptionScene::OperationDraw()
{
	DrawStringToHandle(380, 100, "キーボード:", 0xffffff, m_manager.ReturnFontHandle2());
	m_manager.gManager.Draw(640, 260, 0.8f, 0.0f, "sousaKey");

	DrawStringToHandle(380, 400, "コントローラー:", 0xffffff, m_manager.ReturnFontHandle2());
	m_manager.gManager.Draw(710, 540, 1.4f, 0.0f, "sousaCon");

}

void OptionScene::CreditDraw()
{
	DrawStringToHandle(400, 100, "15 80's Graffiti", 0xffffff, m_manager.ReturnFontHandle2());
	DrawStringToHandle(480, 126, "aoya128 https://twitter.com/aoya128", 0xffffff, m_manager.ReturnFontHandle2());

}

void OptionScene::CloseDraw()
{
	//何も書かない(予定)
}
