#include "StringUtility.h"
#include <DxLib.h>
#include <cassert>

std::wstring StringUtility::StringToWString(const std::string& str)
{
    //MultiByteToWideCharは、２回呼び出すことを期待されている
    //１回目の呼び出しは、変換後文字列のサイズを得るため
    //２回目の呼び出しで、変換後文字列を得る
    //in : 情報側はstring(あらかじめわかっている)
    //out : 戻り値はwstring(文字数もわからない)

    //最終的に返すワイド文字列(最初は何も入っていない)
    std::wstring ret;

    //一回目の呼び出し
    int result = MultiByteToWideChar(
        CP_ACP,         //元の文字列のコードページを書く
        0,              //変換オプションだが、今回は特に指定しないので０
        str.data(),     //元の文字列の先頭ポインタ
        str.length(),   //元の文字列の文字列
        nullptr,        //out,optiona;lなのでnullptrを渡しておく
        0);             //ここでは意味がないため0にしておく

    //一度目の呼びだしの戻り値が、変換後文字列の文字列数になっている
    assert(result >= 0);

    //受け取れる文字列のバッファを確保する
    ret.resize(result);
    result = MultiByteToWideChar(
        CP_ACP,         //元のコードページ
        0,              //オプション
        str.data(),     //元の文字列のポインタ
        str.length(),   //元の文字列の文字列数
        ret.data(),     //変換後文字列のアドレス
        ret.size());    //変換後の文字列数

    return ret;
}
