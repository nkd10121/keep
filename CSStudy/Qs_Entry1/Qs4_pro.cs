using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using static System.Net.Mime.MediaTypeNames;

namespace Qs_Entry
{
    internal class Qs4_pro
    {
        static void Main(string[] args)
        {
            /*UnityのGetComponentの文法的再現*/
            GameObject obj1 = new GameObject();
            GameObject obj2 = new GameObject();

            //Add
            obj1.AddComponent<UI>();
            obj2.AddComponent<Text>();
            obj2.AddComponent<Pos>();

            //GetComponent
            Console.WriteLine("[GetComponent:]");
            UI temp1 = obj1.GetComoponent<UI>();
            temp1.name = "UI";
            temp1.ShowComponentName();
            Text temp2 = obj2.GetComoponent<Text>();
            temp2.name = "Text";
            temp2.ShowComponentName();
            Pos temp3 = obj2.GetComoponent<Pos>();
            temp3.name = "Pos";
            temp3.ShowComponentName();

            //上記と同じ意味です.
            Console.WriteLine("[上記と同一:]");
            obj1.GetComoponent<UI>().ShowComponentName();
            obj2.GetComoponent<Text>().ShowComponentName();
            obj2.GetComoponent<Pos>().ShowComponentName();

            //DelComponent
            obj2.DelComponent<Pos>();

            //確認
            Console.WriteLine("[全体の確認:]");
            obj1.ShowComponents();
            obj2.ShowComponents();
        }
    }

    /*UnityのGetComponentの文法的再現*/
    //厳密な再現ではなく、文法的な再現を行う。
    //多重継承せずに、複数のクラスを一つのクラスに持たせる。
    //イテレータは今回は使わない。
    class GameObject
    {
        //コンポネントを入れて置けるリストを作ろう
        //Objectは全てのクラスの親クラス
        List<Object> list = new List<Object>();

        public void AddComponent<T>() where T : new()
        {
            T obj = new T();
            list.Add(obj);
        }

        public T GetComoponent<T>()
        {
            T obj = default(T);//nullの変わり(T型に合わせたnullの作成)

            //リストから取得
            foreach (var item in list)
            {
                //型がTと同じなら操作
                if (item.GetType() == typeof(T))
                {
                    //実装
                    obj = (T)item;
                }
            }
            return obj;
        }

        public void DelComponent<T>()
        {
            T obj = default(T);
      
            foreach (var item in list)
            {
                //型がT(Pos)と同じなら操作
                if (item.GetType() == typeof(T))
                {
                    obj = (T)item;
                }
            }

            //実装
            list.Remove(obj);
        }

        public void ShowComponents()
        {
            //実装(.ToStringで型名が出ます。)
            foreach(var item in list)
            {
                Console.WriteLine(item.ToString());
            }

        }
    }

    //コンポーネント
    class Text
    {
        //メンバ変数
        public string name = "";
        //実装
        public void ShowComponentName()
        {
            Console.WriteLine("{0}です。", name);
        }
    }
    class UI
    {
        //メンバ変数
        public string name = "";
        //実装
        public void ShowComponentName()
        {
            Console.WriteLine("{0}です。", name);
        }
    }
    class Pos
    {
        //メンバ変数
        public string name = "";
        //実装
        public void ShowComponentName()
        {
            Console.WriteLine("{0}です。", name);
        }
    }
}