#include "SceneManager.h"
#include "Scene.h"

SceneManager::SceneManager() :
	m_isFull(false)
{
	//�g�p����t�H���g����������
	font_path = "data/font/PixelMplus12-Bold.ttf"; // �ǂݍ��ރt�H���g�t�@�C���̃p�X
	if (AddFontResourceEx(font_path, FR_PRIVATE, NULL) > 0) {
	}
	else {
		// �t�H���g�Ǎ��G���[����
		MessageBox(NULL, "�t�H���g�Ǎ����s", "", MB_OK);
	}
	//�^�C�g���\���p�̃t�H���g
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

	//�v���C���[��������������SE
	sManager.Load("hitSE", "data/se/�q�b�g�Q����3.wav", false);
	//���肵������SE
	sManager.Load("enterSE", "data/se/����Q������iSF�n�j.wav", false);
	//�J�[�\���𓮂������Ƃ���SE
	sManager.Load("moveSE", "data/se/�J�[�\���i�_�炩���j2.wav", false);
	//�S�[����������SE
	sManager.Load("GoalSE", "data/se/maou_se_magical27.mp3", false);
	//�Q�[���I�[�o�[���畜������Ƃ�
	sManager.Load("RevivalSE", "data/se/�Q�[�W��1.mp3", false);
	//�Q�[���I�[�o�[�ł�����߂��Ƃ�
	sManager.Load("deathSE", "data/se/�ˌ��Q�s�X�g��.wav", false);
}

SceneManager::~SceneManager()
{
	// ********** �t�H���g�̃A�����[�h **********
	if (RemoveFontResourceEx(font_path, FR_PRIVATE, NULL)) {
	}

	//�쐬�����t�H���g������������������
	DeleteFontToHandle(fontHandle);
}

void SceneManager::Update(Input& input)
{
	//BG
	DrawBox(0, 0, 1280, 720, 0x0d1118, true);

	sManager.ChangeBGMVolume(m_BGMvolume);
	sManager.ChangeSEVolume(m_SEvolume);

	//�����̂ݎ��s
	scenes.back()->Update(input);
}

void SceneManager::Draw()
{
	//�擪���珇�ɕ`��
	//�Ō�ɐς񂾂��̂��Ō�ɕ`�悳���
	for (auto& scenes : scenes)
	{
		scenes->Draw();
	}
}

void SceneManager::ChangeScene(std::shared_ptr<Scene> nextScene)
{
	if (scenes.empty())//���X�g������ۂ����������ւ�����
	{
		scenes.push_back(nextScene);//�����ɒǉ�
	}
	else
	{
		logScene = *(scenes.begin());
		scenes.back() = nextScene;//���Ɉ�ȏ゠��Ζ�����
	}
}

void SceneManager::ChangeAndClearScene(std::shared_ptr<Scene> nextScene)
{
	scenes.clear();

	scenes.push_back(nextScene);//�����ɒǉ�
	
}

void SceneManager::PushScene(std::shared_ptr<Scene> scene)
{
	scenes.push_back(scene);
}

void SceneManager::popScene(bool isToTitle)
{
	//�V�[���̃��O���X�V����
	logScene = *(scenes.begin());
	if (!isToTitle)
	{
		//�������O�̃V�[����stage1��������
		//stage1��BGM��r������Đ�����
		if (logScene == stage1)
		{
			sManager.PlayBGM("stage1", false);
		}
		//�������O�̃V�[����stage2��������
		//stage2��BGM��r������Đ�����
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
