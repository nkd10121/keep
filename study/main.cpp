#include "DxLib.h"
#include "DrawLib.h"

#include <string>
#include <fstream>
#include <sstream>

using namespace std;

namespace Window
{
	constexpr int kWidth = 1280;
	constexpr int kHeight = 720;

	constexpr int kHalfWidth = static_cast<int>(kWidth * 0.5f);
	constexpr int kHalfHeight = static_cast<int>(kHeight * 0.5f);
}

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);
	SetGraphMode(Window::kWidth, Window::kHeight, 32);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	std::string data;
	//std::string info;
	//std::string str_conma_buf;
	//std::string input_csv_file_path = "testData.csv";

	// �ǂݍ���csv�t�@�C�����J��(std::ifstream�̃R���X�g���N�^�ŊJ��)
	std::ifstream openFile("testData.csv");


	//// getline�֐���1�s���ǂݍ���(�ǂݍ��񂾓��e��str_buf�Ɋi�[)
	//while (getline(openFile, data)) {
	//	// �u,�v��؂育�ƂɃf�[�^��ǂݍ��ނ��߂�istringstream�^�ɂ���
	//	std::istringstream i_stream(data);

	//	// �u,�v��؂育�ƂɃf�[�^��ǂݍ���
	//	getline(i_stream, info, ',');
	//}

	getline(openFile, data);

	//printfDx("");

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		// ���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		// �Q�[���̏���
		
		DrawFormatString(0, 0, 0xffffff, "%s", data);


		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		// esc�L�[�ŃQ�[���I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		// FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			// 16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}