using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Qs_Entry
{
    internal class Qs3_2
    {
        static void Main(string[] args)
        {
            /*クラスへのアクセス(this(),base())*/
            Console.WriteLine("【クラスへのアクセス(this(),base())】");
            Derived x = new Derived();
            x.Show();
            x.Show2();


            /*オーバーライド*/
            Console.WriteLine("【オーバーライド】");
            Derived2 x2 = new Derived2();
            x2.Show();
            x2.Show2();
            //newは変数依存なので、Derived2ならnew側が。
            //Base2なら、基本クラスの方が実行される。
            Base2 x3 = x2;
            x3.Show();
            x3.Show2();
        }

        /*クラスへのアクセス(this(),base())*/
        //インスタンスを作成する際に、自身の引数無しコンストラクタにアクセスしたり、
        //基本クラスのコンストラクタにアクセスする必要がある場合があります。
        //その際には、this(),base() キーワードを使用します。
        public class Base
        {
            public Base()
            {
                Console.WriteLine("Base.");
            }
            public Base(string name) : this()
            {
                Console.WriteLine("名前付きBase.");
            }
            public void Show()
            {
                Console.WriteLine("Hello");
            }
        }

        public class Derived : Base
        {
            public Derived() : base("")
            {
                Console.WriteLine("Derived.");
            }
            public void Show2()
            {
                base.Show();
                Console.WriteLine("Hello2");
            }
        }
    }

    /*オーバーライド(オーバーロードとは違います)*/
    //基本クラスのメンバーを派生クラスで書き換える際に使う機能です。
    //基本クラスの書き換えられるかもしれないメンバーに　virtual
    //派生クラスの書き換えたメンバーに override を付けます。
    //その他似たような機能にnewがあります。
    public class Base2
    {
        public virtual void Show()
        {
            Console.WriteLine("Show_base2.");
        }
        public void Show2()
        {
            Console.WriteLine("Show2_Base2.");
        }
    }

    public class Derived2 : Base2
    {
        public override void Show()
        {
            Console.WriteLine("show_drived");
        }
    }
}
