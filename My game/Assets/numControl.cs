using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

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

        var dic = new Dictionary<int, char>()
        {
            {0,'Q'},
            {1,'W'},
            {2,'E'},
            {3,'R'},
            {4,'T'},
            {5,'A'},
            {6,'S'},
            {7,'D'},
            {8,'F'},
            {9,'G'},
            {10,'Z'},
            {11,'X'},
            {12,'C'},
            {13,'V'},
            {14,'B'},

        };

        foreach (char value in dic.Values)
        {
            Debug.Log("�o�����[��" + value + "�ł��B");
        }

    }

    // Update is called once per frame
    void Update()
    {
        // �����̃L�[���������ꂽ��
        if (Input.anyKeyDown)
        {
            foreach (KeyCode code in Enum.GetValues(typeof(KeyCode)))
            {
                if (Input.GetKeyDown(code))
                {
                    if(code == KeyCode.Q)
                    {
                        num = 1;
                    }
                    else if (code == KeyCode.W)
                    {
                        num = 2;
                    }
                    else if (code == KeyCode.E)
                    {
                        num = 3;
                    }
                    // ���͂��ꂽ�L�[����\��
                    Debug.Log(code.ToString());

                }
            }
        }
    }
}
