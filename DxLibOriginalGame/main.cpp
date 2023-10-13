#include "DxLib.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// �ꕔ�̊֐���DxLib_Init()�̑O�Ɏ��s����K�v������
	ChangeWindowMode(true);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	SetDrawScreen(DX_SCREEN_BACK);

	int count = 0;

	int span = 9;

	int drawX = 320;
	int drawY = 240;

	int handle0 = LoadGraph("img/�X���C��A_�U��000.png");
	int handle1 = LoadGraph("img/�X���C��A_�U��001.png");
	int handle2 = LoadGraph("img/�X���C��A_�U��002.png");
	int handle3 = LoadGraph("img/�X���C��A_�U��003.png");
	int handle4 = LoadGraph("img/�X���C��A_�U��004.png");

	// �Q�[�����[�v
	while (ProcessMessage() != -1)
	{
		//���̃t���[���̊J�n�������o���Ă���
		LONGLONG start = GetNowHiPerformanceCount();

		// �`����s���O�ɉ�ʂ��N���A����
		ClearDrawScreen();

		//�Q�[���̏���
		count++;
		if (count >= span * 6)
		{
			DrawGraph(drawX, drawY, handle0, true);
			count = 0;
		}
		else if (count >= span * 5)
		{
			DrawGraph(drawX, drawY, handle1, true);
		}
		else if (count >= span * 4)
		{
			DrawGraph(drawX, drawY, handle4, true);
		}
		else if (count >= span * 3)
		{
			DrawGraph(drawX, drawY, handle3, true);
		}
		else if (count >= span * 2)
		{
			DrawGraph(drawX, drawY, handle2, true);
		}
		else if (count >= span * 1)
		{
			DrawGraph(drawX, drawY, handle1, true);
		}
		else if (count >= span * 0)
		{
			DrawGraph(drawX, drawY, handle0, true);
		}

		// ��ʂ��؂�ւ��̂�҂�
		ScreenFlip();

		//esc�L�[�ŃQ�[�����I��
		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

		//FPS60�ɌŒ肷��
		while (GetNowHiPerformanceCount() - start < 16667)
		{
			//16.66�~���b(16667�}�C�N���b)�o�߂���܂ő҂�
		}
	}

	DeleteGraph(handle0);
	DeleteGraph(handle1);
	DeleteGraph(handle2);
	DeleteGraph(handle3);
	DeleteGraph(handle4);

	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}