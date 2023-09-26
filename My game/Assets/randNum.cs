using Mono.Cecil.Cil;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class randNum : MonoBehaviour
{
    bool stay;

    // Start is called before the first frame update
    void Start()
    {
        stay = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(!stay)
        {
            stay =true;
            int ranNum = Random.Range(0, 0);
            switch (ranNum)
            {
                case 0:
                    Debug.Log("push Q");
                    if (Input.GetKey(KeyCode.Q))
                    {
                        stay = false;
                    }
                    break;

                case 1:
                    Debug.Log("push W");
                    if (Input.GetKey(KeyCode.W))
                    {
                        stay = false;
                    }
                    break;

                case 2:
                    Debug.Log("push E");
                    if (Input.GetKey(KeyCode.E))
                    {
                        stay = false;
                    }
                    break;
                case 3:
                    Debug.Log("push R");
                    if (Input.GetKey(KeyCode.R))
                    {
                        stay = false;
                    }
                    break;
                case 4:
                    Debug.Log("push T");
                    if (Input.GetKey(KeyCode.T))
                    {
                        stay = false;
                    }
                    break;
                case 5:
                    Debug.Log("push Y");
                    if (Input.GetKey(KeyCode.Y))
                    {
                        stay = false;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}
