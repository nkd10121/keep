#include <DxLib.h>
#include <cassert>
#include <iostream>
#include "StringUtility.h"

using namespace std;

//int main()
//{
//	int a[] = { 0,1,2,3,4,5,6,7,8,9 };
//
//	cout << a[7] << endl;
//	cout << 7[a] << endl;
//	cout << *(a + 7) << endl;
//
//	constexpr int row = 0;
//	constexpr int col = 0;
//
//	int b[row][col] == int c[row * col]
//
//}

//int MyLoadGraph(const wchar_t* path) {
//	int handle = LoadGraph(path);
//	assert(handle != -1);
//	return handle;
//}

/*�ЂƂ�Ńf�o�b�O�ł���悤��*/
//�@�u���[�N�|�C���g(�u�����Ƃ���Ŏ~�܂�)
//	�����t���u���[�N�|�C���g
//	�������𖞂������Ƃ��̂ݎ~�܂�
//	1.�l�����������ꍇ�����~�߂���
//	2.���僋�[�v��n�ԖڂŎ~�߂���
//	�f�����b�g���߂���߂���d���Ȃ�
//�A���̓u���[�N���ɕϐ��̒l��ύX�ł��܂�
//	1.�ϐ��ɃJ�[�\�������킹��ƒl��������̂�
//		������N���b�N����ƒl�̕ύX���\�ł�
//	2.�u���[�N���Ɂu���[�J���v�Ƃ����f�o�b�O�E�B���h�E��
//		����ƃ��[�J���ϐ��������������܂��B���̃��[�J���E�B���h�E����
//		�ϐ���ύX�\�ł��B
// 
// �u���[�N���Ƀf�o�b�O���E�B���h�E����\�����Ȃ������Ƃ��ł���
//	�X�e�b�v���s(F10)�u���[�N������F10��1�s���i�ށB
//	�������A�֐��R�[���̕����ł͒��ɓ���Ȃ����߂��̎���
//	F11���g���Ɗ֐��̒��ɓ����Ă���
//	���̉��F�����̓h���b�O���h���b�v�œ�������
// 
//	Debug/Release
// Debug:�f�o�b�O���₷������ɒx��(�]�v�ȏ�񂪊܂܂�Ă���)
// Release:��������Ƀf�o�b�O�����炢
// 
// ��Ƃ�R���e�X�g�ɒ�o����Ƃ���Release�Œ�o
// Debug�͗]�v�ȏ�񂪓����Ă��邽�߃T�C�Y���傫���Ȃ邤����
// �����������x���̂ő����PC�Ŏv�����悤�ɓ����Ȃ��\��������
// 
// �f�o�b�O�ɖ𗧂b
//	1.�u���[�N�|�C���g�̎g�������o����
//	�E�u���[�N�|�C���g�Œ��f���́A���[�J�����W���m�F�ł���
//	�E���łɏo�͂������DxLib�����O���o���Ă���̂Ŏ��s�̃��O���Ȃ����m�F����
//	2.���f�����Ƃ��납��F10��i�s���m�F����
//	 Release���[�h�͗L���ł͂Ȃ�
// �@   2�̗��R
//		�@�f�o�b�O��񂪂Ȃ����ߊ֐����A�l���킩��Ȃ�
//		�A�v���O���������ԂɎ��s����Ȃ�
//	3.F11���g���Ǝ���֐��̒��ɓ����Ă���
//	4.���̉��F�����̓h���b�O���h���b�v�œ�������
//	5.�u���[�N���ɕϐ����ɃJ�[�\�������킹�Đ��l��ύX�ł���
//	6.�u���[�N�|�C���g���E�N���ŏ�����ǉ��ł���
//		�����𖞂������Ƃ��̂ݏ����𒆒f����
//	7.�f�[�^�u���[�N�|�C���g
//	->����̃������̓��e�������ς�������ɒ��f
//	1�x���s���n�߂Ă���łȂ��ƃ������̈ʒu���m�肵�Ȃ�����
//	���s������
// ->�v���O�����̂ǂ��œ��e�����������Ă��邩�킩��Ȃ�
//	���Ƀ������j��̎��́A�����Ăɒl���ύX����Ă��邱�Ƃ�����
//	����Ȏ��Ɏg����@�\
//	8.�Ăяo������
//	 �u���[�N�����Ƃ�����Ăяo�����֐��������̂ڂ邱�Ƃ��ł���
//	�@�܂��A�Ăяo�������_�ł̎��ӂ̕ϐ����m�F�ł���
//	9.�E�H�b�`�@�\
//	�@�w�肵���ϐ��̒l���A�h���X���m�F�ł���
//	
//


//int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
//{
	//ChangeWindowMode(true);	//��X�N���[��
	//if (DxLib_Init() == -1) {	//�������Ɏ��s������A�v���𗎂Ƃ�
	//	return -1;	//�ُ�I��
	//}

	//const char* bgPath = ("bg.png");
	//OutputDebugStringA("bg.png");

	//int bgH = MyLoadGraph(L"./bg.png");

	//���͕\�������`���ɂ�2���̃X�N���[��������܂�
	//����������Ńt���b�v(����ւ�)���s�����Ƃ�
	//��ʂ̂�����𖳂����Ă��܂�
	//SetDrawScreen���̊֐���DxLib_Init()�̌ザ��Ȃ���
	//�L���ł͂Ȃ����ߒ���
	//auto result = SetDrawScreen(DX_SCREEN_BACK);

	//int a = 0;

	//std::string titleStr = "���";

	//while(ProcessMessage() != -1){
	//	ClearDrawScreen();

	//	auto wstr = StringUtility::StringToWString(titleStr);

	//	DrawString(50, 50, wstr.c_str(), 0xffffff);

	//	DrawFormatString(50, 50, 0xffffff, L"%s", wstr.c_str());

	//	ScreenFlip();

	//}
	//DxLib_End();

	//return 0;	//����I��
//}

