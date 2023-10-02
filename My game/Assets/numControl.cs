using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using Random = UnityEngine.Random;

public class numControl : MonoBehaviour
{
    public int num = 0;

    int[] keyNum;

    // Start is called before the first frame update
    void Start()
    {
        keyNum = new int[15];
        for (int i = 0; i < keyNum.Length; i++)
        {
            keyNum[i] = 0;
        }

        var dic = new Dictionary<int, string>()
        {
            {0,"Q"},
            {1,"W"},
            {2,"E"},
            {3,"R"},
            {4,"T"},
            {5,"A"},
            {6,"S"},
            {7,"D"},
            {8,"F"},
            {9,"G"},
            {10,"Z"},
            {11,"X"},
            {12,"C"},
            {13,"V"},
            {14,"B"},
            {15,"Y"},
            {16,"U"},
            {17,"I"},
            {18,"O"},
            {19,"P"},
            {20,"H"},
            {21,"J"},
            {22,"K"},
            {23,"L"},
            {24,"N"},
            {25,"M"},
        };

        int max = 26;
        string moji = " ";

        int rand = Random.Range(0, max);
        for (int i = 0;i < max;i++)
        {
            if (rand == i)
            {
                moji = dic[i];
            }
        }

        Debug.Log(moji);
    }

    // Update is called once per frame
    void Update()
    {
        // 何かのキーが押下されたら
        if (Input.anyKeyDown)
        {
            foreach (KeyCode code in Enum.GetValues(typeof(KeyCode)))
            {
                if (Input.GetKeyDown(code))
                {
                    for(int i = 0;i < max; i++)
                    {
                        if(code == KeyCode.dic[i])
                        {
                            num = i;
                        }
                    }
                    //if(code == KeyCode.Q)
                    //{
                    //    num = 1;
                    //}
                    //else if (code == KeyCode.W)
                    //{
                    //    num = 2;
                    //}
                    //else if (code == KeyCode.E)
                    //{
                    //    num = 3;
                    //}
                    //else if (code == KeyCode.dic[3])
                    //{
                    //    num = 3;
                    //}
                    // 入力されたキー名を表示
                    Debug.Log(code.ToString());

                }
            }
        }
    }
}
