//#include <iostream>
//
//using namespace std;
//
//constexpr int kSize = 256;
//
////kSize*kSize�̃}�X������
////x,y���W�ƃT�C�Y���w�肵��
////�w�肵�����W����T�C�Y�̃}�X��h��Ԃ�
//
////����
//// x,y,size
//// x : �h��n�߂�X���W 0�n�܂� 0 <= x <= 9
//// y : �h��n�߂�Y���W 0�n�܂� 0 <= x <= 9
//// size : �h��͈�
//
////�h�����}�X��"#",�h���Ă��Ȃ��}�X��"."�ŕ\������
//
////�ċA���g����ł̒��ӓ_
////�������A�����đ�ʂɌĂ΂��\��������
////���̏����͌y���Ă����(100����Ƃ�����ȃ��x��)��
////�֐����Ă΂��̂ŃX�^�b�N���������͊�������
//// �����ɂƂ�ł��Ȃ����Ԃ����������肷��
//// 
//// PAIZA��A�Ƃ��ɂȂ��Ă���ƁA�������ԂƂ̏����ɂȂ�̂�
//// ���������炷�H�v���K�v
//// 
//// �h���Ă��镔����h��ɍs�����Ƃ���
//// �@�����łɓh���Ă��镔���͓h��Ȃ��A�Ƃ�
//// �@�@size�`�F�b�N���ďカ���Ȃ��悤�ɂ���@�ȂǕK�v
//// 
//// Paiza��邤���ł͒l�͈̔͂��w�肳��Ă���̂�
//// �l�͈̔͂��`�F�b�N���ď������Ԃ��C�ɂ��邩�ǂ����𔻒f�����肷��
////
//
//
//void Draw(int dotData[kSize][kSize], int x, int y, int size)
//{
//	//�h��Ȃ�
//	if (size <= 0)
//		return;
//
//	//�͈͊O�͓h��Ȃ�
//	if (x < 0)
//		return;
//	if (y < 0)
//		return;
//	if (x >= kSize)
//		return;
//	if (y >= kSize)
//		return;
//
//	dotData[x][y] = 1;
//
//	size--;
//
//	Draw(dotData, x - 1, y, size);	//�����h��
//	Draw(dotData, x + 1, y, size);	//�E���h��
//	Draw(dotData, x, y - 1, size);	//����h��
//	Draw(dotData, x, y + 1, size);	//�����h��
//}
//
//int main()
//{
//	//�h����Ֆʂ̃f�[�^
//	int dotData[kSize][kSize];
//	//�Ֆʂ̏�����
//	for (int y = 0; y < kSize; y++)
//	{
//		for (int x = 0; x < kSize; x++)
//		{
//			dotData[x][y] = 0;
//		}
//	}
//
//	int startX, startY,size;
//	cin >> startX >> startY >> size;
//	//test
//	dotData[startX][startY] = 1;
//
//	Draw(dotData, startX, startY, size);
//
//
//	//�ŏI�I�ȔՖʂ̕\��
//	for (int y = 0; y < kSize; y++)
//	{
//		for (int x = 0; x < kSize; x++)
//		{
//			if (dotData[x][y] == 0)
//			{
//				cout << ".";
//			}
//			else
//			{
//				cout << "#";
//			}
//		}
//
//		//���s
//		cout << endl;
//	}
//}
//
//#if false	//�ċA�̊�{
//void func(int count)
//{
//	cout << "�ċA���Ă݂�" << count << endl;
//	count--;
//	if (count > 0)
//	{
//		func(count);
//	}
//
//}
//
//int main()
//{
//	// �ċA�Ƃ́H
//	// 
//	// �ċA�Ƃ͂���֐����玩�g���Ăяo���֐��̏����̂���
//
//	// �����l�����ɍċA����Ɩ������[�v
//	// �����X�^�b�N���������g��������Ď~�܂�
//
//	// �Ȃ̂ŉ�������̏����Ŏ��g���Ăяo���̂���߂�
//	
//	int callCount;
//	cin >> callCount;
//
//	func(callCount);
//
//	return 0;
//}
//#endif