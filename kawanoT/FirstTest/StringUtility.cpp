#include "StringUtility.h"
#include <DxLib.h>
#include <cassert>

std::wstring StringUtility::StringToWString(const std::string& str)
{
    //MultiByteToWideChar�́A�Q��Ăяo�����Ƃ����҂���Ă���
    //�P��ڂ̌Ăяo���́A�ϊ��㕶����̃T�C�Y�𓾂邽��
    //�Q��ڂ̌Ăяo���ŁA�ϊ��㕶����𓾂�
    //in : ��񑤂�string(���炩���߂킩���Ă���)
    //out : �߂�l��wstring(���������킩��Ȃ�)

    //�ŏI�I�ɕԂ����C�h������(�ŏ��͉��������Ă��Ȃ�)
    std::wstring ret;

    //���ڂ̌Ăяo��
    int result = MultiByteToWideChar(
        CP_ACP,         //���̕�����̃R�[�h�y�[�W������
        0,              //�ϊ��I�v�V���������A����͓��Ɏw�肵�Ȃ��̂łO
        str.data(),     //���̕�����̐擪�|�C���^
        str.length(),   //���̕�����̕�����
        nullptr,        //out,optiona;l�Ȃ̂�nullptr��n���Ă���
        0);             //�����ł͈Ӗ����Ȃ�����0�ɂ��Ă���

    //��x�ڂ̌Ăт����̖߂�l���A�ϊ��㕶����̕����񐔂ɂȂ��Ă���
    assert(result >= 0);

    //�󂯎��镶����̃o�b�t�@���m�ۂ���
    ret.resize(result);
    result = MultiByteToWideChar(
        CP_ACP,         //���̃R�[�h�y�[�W
        0,              //�I�v�V����
        str.data(),     //���̕�����̃|�C���^
        str.length(),   //���̕�����̕�����
        ret.data(),     //�ϊ��㕶����̃A�h���X
        ret.size());    //�ϊ���̕�����

    return ret;
}
