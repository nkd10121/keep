using System;

namespace Qs_Entry
{
    internal class Qs1_1
    {
        static void Main(string[] args)
        {
            /*コーディング規約に関して(Main()関数内)*/
            //キャメルケース
            //パスカルケース

            /*変数の宣言と初期化*/
            //デバッグでは勝手に初期化されるが
            //リリースだと初期化されないので初期化はしておく

            //int
            int ansInt = 0, tempInt = 0;
            //long
            long ansLong = 0, temLong = 0;
            //float
            float ansFloat = 0, tempFloat = 0;
            //double
            double ansDouble = 0, tempDouble = 0;
            //decimal
            decimal ansDecimal = 0, tempDecimal = 0;
            //char
            char ansChar = '\0', tempChar = '\0';
            //string
            string ansString = "", tempString = "";

            /*変数の代入*/
            ansInt = 1;
            ansLong = 1L;
            ansFloat = 1.0f;
            ansDouble = 1.0d;
            ansDecimal = 1.0m;
            ansChar = 'あ';
            ansString = "あいうえお";

            /*データの表示(基本)*/
            Console.WriteLine("【データの表示(基本)：】");
            //改行して表示
            Console.WriteLine("hey");
            //改行せずに表示
            Console.Write("hey1");
            Console.Write("hey2");
            Console.WriteLine("");//改行用

            /*基本の計算*/
            //五則演算
            int ans = 0, val1 = 9, val2 = 2;
            //足し算
            ans = val1 + val2;
            Console.WriteLine(ans);
            //引き算
            ans = val1 - val2;
            Console.WriteLine(ans);
            //掛け算
            ans = val1 * val2;
            Console.WriteLine(ans);
            //割り算
            ans = val1 / val2;
            Console.WriteLine(ans);
            //あまりの計算
            ans = val1 % val2;
            Console.WriteLine(ans);

            /*配列の作成*/
            //通常の作成
            int[] ar;   //この段階では単なる参照を持てる変数
            ar = new int[5];    //5個データを入れる配列を作っっている
            //初期化を作成を同時に
            int[] ar2 = new int[5];
            //中身も同時に
            int[] ar3 = { 1, 2, 3, 4, 5 };

            /*配列の使い方*/
            Console.WriteLine("【配列の使い方：】");
            ar[0] = 1; ar[1] = 2; ar[2] = 3;
            Console.WriteLine("ar[0]:{0},ar[1]:{1},ar[2]:{2}", ar[0], ar[1], ar[2]);
            Console.WriteLine("配列のサイズ:{0}", ar.Length);

            ///*条件分岐(if文)*/
            //Console.WriteLine("【条件分岐(if分)：】");
            //Console.Write("数値を入力して下さい:");
            ////int.Parse()は文字列を整数に変換するメソッド
            //int num = int.Parse(Console.ReadLine());
            //if (num == 0)
            //{
            //    Console.WriteLine("入力された値は0です。");
            //}
            //else if (num == 1)
            //{
            //    Console.WriteLine("入力された値は1です。");
            //}
            //else
            //{
            //    Console.WriteLine("入力された値は0~1以外です。");
            //}

            ///*条件分岐(switch)*/
            //Console.WriteLine("【条件分岐(switch文)：】");
            //Console.Write("数値を入力して下さい(0~3):");
            //num = int.Parse(Console.ReadLine());
            //switch (num)
            //{
            //    case 0:
            //    case 1:
            //    case 2:
            //        Console.WriteLine("0~2です。");
            //        break;
            //    case 3:
            //        Console.WriteLine("3です。");
            //        break;
            //    default:
            //        Console.WriteLine("それ以外です。");
            //        break;
            //}

            /*繰り返し(while)*/
            Console.WriteLine("【繰り返し(while文)：】");
            int count = 0;//ループカウンタとして作成
            while (count < 5)//5回ループ
            {
                count++;
                Console.WriteLine("while:{0}回目", count);
            }

            /*繰り返し(do~while)*/
            Console.WriteLine("【繰り返し(do~while文)：】");
            int count2 = 0;//ループカウンタとして作成
            do
            {
                count2++;
                Console.WriteLine("do~while:{0}回目", count2);
            } while (count2 < 5);

            /*繰り返し(for)*/
            Console.WriteLine("【繰り返し(for文)：】");
            for (int s = 0; s < 5; s++)
            {
                Console.WriteLine("for:{0}回目", s);
            }

            /*繰り返し(foreach)*/
            Console.WriteLine("【繰り返し(foreach文1)：】");
            int[] ar4 = { 1, 2, 3 };
            foreach (var x in ar4)
            {
                Console.WriteLine(x);
            }

            /*繰り返し(foreach文2)*/
            Console.WriteLine("【繰り返し(foreach文2)：】");
            //多次元構造を持つ配列
            int[,] ar5 = { { 1, 2, 3 }, { 4, 5, 6 } };
            //どの順番で書き出されるか知っておく
            foreach (var v in ar5)
            {
                Console.WriteLine("foreach2:{0}", v);
            }

            /*繰り返し(foreach文3)*/
            Console.WriteLine("【繰り返し(foreach文3)：】");
            string tempStr = "春夏秋冬";
            //stringを一文字ずつcharにして出力される
            //inは右辺にある要素を群として判断する
            foreach (var v in tempStr)
            {
                Console.WriteLine("foreach3:{0}", v);
            }
        }
    }
}
