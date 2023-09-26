using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class numControl : MonoBehaviour
{
    public int num = 0;
    // Start is called before the first frame update
    void Start()
    {

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
                    if(code == KeyCode.Q)
                    {
                        Debug.Log("pushed Q");
                        num = 1;
                    }
                    else if (code == KeyCode.W) 
                    {
                        num = 2;
                    }
                    // 入力されたキー名を表示
                    Debug.Log(code.ToString());

                }
            }
        }
    }
}
