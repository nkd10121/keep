using System;
using System.Collections.Generic;
using System.Data;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Qs_Entry
{
    internal class Qs2_1
    {
        static void Main(string[] args)
        {
            /*クラス内でのstatic(静的メンバー)*/
            Console.WriteLine("【クラス内でのstatic(静的メンバー)】");
            //インスタンスの作成
            Enemy.CountEnemy();
            Enemy ene = new Enemy();
            Enemy.CountEnemy();         
            Enemy ene2 = new Enemy();
            Enemy.CountEnemy();          
            Enemy ene3 = new Enemy();
            Enemy.CountEnemy();

            //疑似的な削除
            Enemy.deleteEnemy(ref ene);
            Enemy.CountEnemy();
            Enemy.deleteEnemy(ref ene2);
            Enemy.CountEnemy();

            /*staticクラス*/
            Console.WriteLine("【staticクラス】");
            Console.WriteLine(Math.Power(2, 8));
            Console.WriteLine(Math.Power(2.8f, 8));
        }
    }

    /*クラス内でのstatic(静的メンバー)*/
    //staticが付いたメンバ変数やメンバ関数は、
    //同じクラスから作られた全てのインスタンスで共有している。
    //private または internal である static フィールドを使用する場合は、s_ プレフィックスを使用
    public class Enemy
    {
        private static int s_enemyCount = 0;

        //コンストラクタ
        public Enemy() { s_enemyCount++; }

        //数を表示
        public static void CountEnemy()
        {
            Console.WriteLine("現在のエネミーの総数は:" + s_enemyCount);
        }

        //C#だとメモリ開放を明示的にやれないので疑似的なものです。
        public static void deleteEnemy(ref Enemy enemy)
        {
            //参照されなくなり、
            //いずれはGC(ガベレージコレクタ)が消してくれる(いつ消してくれるかは分からない)。
            enemy = null;
            s_enemyCount--;
        }
    }

    /*staticクラス*/
    //インスタンスを作成しないことを前提としたクラスです。
    //オブジェクト的なふるまいを必要としない便利な機能をまとめたりするのに使います。
    //(C++ではなく、C言語の構造体に近い)
    //staticクラスではstaticなメンバ以外を定義する事はできません。
    static class  Math
    {
        static private int s_itemp = 0;
        static private float s_ftemp = 0.0f;

        //nのm乗の計算
        static public int Power(int n,int m)
        {
            s_itemp = 1;

            for(int i = 0; i < m; i++) 
            {
                s_itemp *= n;
            }

            return s_itemp;
        }

        static public float Power(float n,float m)
        {
            s_ftemp = 1;

            for (int i = 0; i < m; i++)
            {
                s_ftemp *= n;
            }

            return s_ftemp;
        }
    }
}
