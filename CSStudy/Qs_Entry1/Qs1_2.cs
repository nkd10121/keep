using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;

namespace Qs_Entry
{
    internal class Qs1_2
    {
        static void Main(string[] args)
        {
            /*関数の作成*/
            int IAdd(int a,int b)  //intの足し算をする関数
            {
                int ans;
                ans = a + b;
                return ans;
            }
            
            float FAdd(float a, float b)  //intの足し算をする関数
            {
                float ans;
                ans = a + b;
                return ans;
            }
            //文字列の足し算
            string SAdd(string a, string b)
            {
                string ans;
                ans = a + b;
                return ans;
            }

            //実行結果の確認
            Console.WriteLine("【関数の作成と実行(値渡し)：】");
            Console.WriteLine("IAdd:{0}+{1}={2}", 3, 2, IAdd(3, 2));
            Console.WriteLine("DAdd:{0}-{1}={2}", 3.2, 2.5, FAdd(3.2f, 2.5f));
            Console.WriteLine("SAdd:{0}+{1}={2}", "Hello", "C#", SAdd("Hello", "C#"));

            /*関数(ref参照渡し)*/
            //refは事前の初期化処理がいる
            int a = 1;
            float b = 1.1f;
            string c = "test";
            void CheckRefReference(ref int a, ref float b, ref string c)
            {
                a = 2;
                b = 3.2f;
                c = "tete";
            }

            //実行
            Console.WriteLine("【関数の作成と実行(参照渡し)：】");
            Console.WriteLine("a:{0}, b:{1}, c:{2}", a, b, c);
            CheckRefReference(ref a, ref b, ref c);//refと付ける。
            Console.WriteLine("a:{0}, b:{1}, c:{2}", a, b, c);

            /*関数の作成と実行(out参照渡し)*/
            //事前に初期化が必要ない。
            void CheckOutReference(out int a,out float b,out string c)
            {
                a = 8;
                b = 8.2f;
                c = "papas";
            }

            //実行
            Console.WriteLine("【関数の作成と実行(out参照渡し)：】");
            //初期化せずに使える。
            CheckOutReference(out int a2, out float b2, out string c2); //変数の作成と同時に関数を実行
            Console.WriteLine("a:{0}, b:{1}, c:{2}", a2, b2, c2);

            /*重要コメント！*/
            //C#では殆どの型（値型以外）が参照渡しになっており、
            //C++のようにポインタや参照を乱用するのは宜しくない。
            //(意識しなくても参照型で渡した方が良いものは殆ど参照型)
            //参照渡しはそれでしか難しい場合以外はなるべく使わないように。
            //可読性向上のため、基本的にreturnで返しましょう。

            /*配列を扱う関数*/
            int ASum(int[] a)
            {
                int ans = 0;
                //合計の計算
                //forでもいいが、foreachのほうがC#っぽいし楽
                foreach (int s in a)
                {
                    ans += s;
                }

                a[1] = 0;   //参照渡しのため2回目に実行するとa(ar)[1]が0に書き換えられる

                return ans;
            }
            //実行
            Console.WriteLine("【配列を扱う関数(配列は参照渡し)：】");
            int[] ar = { 1, 2, 3, 4 };
            Console.WriteLine("ASum:{0}", ASum(ar));
            //参照渡しなので、a[1]を書き換えるとar[1]も書き換えられ結果が変化している。
            Console.WriteLine("ASum(2回目):{0}", ASum(ar));

            /*可変引数の関数*/
            int ASum2(params int[] a)
            {
                int ans = 0;
                //合計の計算
                //forでもいいが、foreachのほうがC#っぽいし楽
                foreach (int s in a)
                {
                    ans += s;
                }

                return ans;
            }

            //実行
            Console.WriteLine("【可変引数の関数：】");
            //いちいち配列を作ってそれを送らなくても配列変数として渡せる。
            //配列よりも楽
            Console.WriteLine(ASum2(1, 2, 3, 4));

            /*オーバーロードの実行*/
            Console.WriteLine("【関数のオーバーロード：】");
            Console.WriteLine(Add(1, 2));
            Console.WriteLine(Add(1, 2, 3));
            Console.WriteLine(Add(1.1f, 2.1f));
            Console.WriteLine(Add(1.1f, 2.1f, 3.1f));
        }

        /*関数のオーバーロード*/
        //Main()内ではオーバーロードできないので外に出す。
        //今回はインスタンスを作らず使いたいので、staticを付ける。
        static int Add(params int[] a)
        {
            int ans = 0;

            foreach(int i in a)
            {
                ans += i;
            }

            return ans;
        }

        static float Add(params float[] a)
        {
            float ans = 0;

            foreach(float f in a)
            {
                ans += f;
            }

            return ans;
        }
    }
}
