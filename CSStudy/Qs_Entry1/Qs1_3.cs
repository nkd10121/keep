using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Qs_Entry
{
    internal class Qs1_3
    {
        static void Main(string[] args)
        {
            /*クラスの基本*/
            Console.WriteLine("【クラスの基本：】");
            //左辺で作成されているのは参照型の変数(つまりポインタ)です。
            //右辺でVector2の実態を作成（メモリに配置）し、そのアドレスを左辺の参照型の変数(ポインタ)に渡している。
            Vector2 v1 = new Vector2();
            Vector2 v2 = new Vector2(2.0f,2.0f);
            Console.WriteLine("v1:" + v1.OutString());
            Console.WriteLine("v2:" + v2.OutString());
            //publicは外からアクセス可能
            v1.X = 1.0f;
            v1.Y = 2.0f;
            Console.WriteLine("v1:" + v1.OutString());
            //メンバ変数は各インスタンスからアクセスできる
            Console.WriteLine("v1(長さ):" + v1.Length());
            Console.WriteLine("v2(長さ):" + v2.Length());

            /*Vector2型が値型でなく、参照型であることの確認*/
            Console.WriteLine("【参照型であることの確認：】");
            v1 = v2;    //もし値型ならv1とv2は同じ数値になる
            Console.WriteLine("v1(=直後):" + v1.OutString());
            v2.Y = 1.0f;    //値型ならv2だけを変更してもv1の値も変更される
            Console.WriteLine("v1(v2変更後):" + v1.OutString());   //変更されない->参照型である

            /*プロパティを持つクラス*/
            Console.WriteLine("【プロパティを持つクラス：】");
            Enemy ene = new Enemy();
            Console.WriteLine("ene(初期):" +  ene.OutString());
            ene.Hp = 6;
            //Hpが減少するとAtも上昇
            Console.WriteLine("ene(Hp減少):" + ene.OutString());
            //ene.At = 8; Atは読み取り専用で、コメント外すとエラー

            /*自動実装プロパティ*/
            Console.WriteLine("【自動実装プロパティ：】");
            Enemy2 ene2 = new Enemy2();
            Console.WriteLine("ene2(初期値):" + ene2.OutString());
            ene2.Hp = 6;
            Console.WriteLine("ene2(Hp減少):" + ene2.OutString());
            //ene.At = 8; Atは読み取り専用で、コメント外すとエラー
        }
    }

    /*クラスの基本*/
    //クラスは基本的には以下の４つで構成されています。
    //・フィールド(メンバ変数)
    //・コンストラクタ
    //・デストラクタ
    //・メソッド(メンバ関数)
    //ここに関してはC++と同じです。
    //C#のクラスで最も注意すべき点は、
    //C++と違って値型がなく、参照型しかないということです。
    //つまり、*とかつけなくても常にクラス変数はポインタです。
    //例外はありますが、基本的に参照渡ししかできませんので注意しましょう。

    /*Vector2*/
    public class Vector2
    {
        //フィールド(メンバ変数)  public->X private->_xと作る
        public float X;
        public float Y;

        //コンストラクタ
        public Vector2()
        {
            this.X = 0;
            this.Y = 0;
        }
        public Vector2(float x, float y)
        {
            //thisは自分自身のポインタです。引数名と名前が被ったりしたときに使用
            this.X = x;
            this.Y = y;
        }

        //デストラクタ
        ~Vector2 ()
        {
            //メモリ管理を自分で行うC++では
            //大変便利なデストラクタだが、C#では殆ど役に立たない
            //何故ならC#にはガベージコレクションという機能があり、
            //メモリ管理はそれが行うため、いつデストラクタが呼ばれるか予測不能である。
            //なので、必要になった時のために書き方を知っておく程度でよい。
            //(どーせC++で嫌になるほど書くでしょう)
        }

        //メソッド
        //長さを返す
        public float Length()
        {
            //平方根の計算
            return MathF.Sqrt(X * X + Y * Y);
        }
        //成分の値を文字列にして返す
        public string OutString()
        {
            return "X:" + X.ToString() + ", Y:" + Y.ToString();
        }
    }

    /*プロパティを持つクラス*/
    //C#ではクラスはプロパティを持つことが出来ます。
    //プロパティとは
    //クラス外部から見るとメンバー変数のように振る舞い、
    //クラス内部から見るとメソッドのように振舞うものです。
    //つまり、メンバ変数の値を変えたり、与えたりする際に
    //決められてた行動を起こすことが出来ます。
    //C++ではgetterとかsetterという形でメンバ関数で実装されることが多いです。

    //プロパティを持つクラスの例
    //Hpが減ると攻撃力が上がるエネミー
    public class Enemy
    {
        private int _hp = 8;
        private int _at = 8;

        //プロパティ
        public int Hp
        {
            //外部に渡すとき
            get {  return _hp; }

            //外部から値を受け取るときの処理
            set
            {
                //外部から与えられた数値の分だけ攻撃力が増加する
                _at += _hp - value;
                _hp = value;
            }
        }
        public int At
        {
            get { return _at; }
            //setが無いので、外部から_atを変更する事はできない
        }

        //自分の値を文字列にして返す
        public string OutString()
        {
            return "Hp:" + _hp.ToString() + ", At:" + _at.ToString();
        }
    }

    /*自動実装プロパティ*/
    public class Enemy2
    {
        //自動実装プロパティ
        public int Hp { get; set; } = 8;//読み込み書き込み可　 _hpも実装されている
        public int At { get; } = 8;     //読み込み可、書き込み不可

        //自分の値を文字列にして返す
        public string OutString()
        {
            return "Hp:" + Hp.ToString() + ", At:" + At.ToString();
        }
    }
}