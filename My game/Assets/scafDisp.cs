using JetBrains.Annotations;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class scafDisp : MonoBehaviour
{
    [SerializeField] GameObject objName1;
    [SerializeField] GameObject objName2;

    GameObject obj;
    numControl numControl;

    public int[] randNum;
     //Start is called before the first frame update
    void Start()
    {

        randNum = new int[3];

        obj = GameObject.Find("test");
        numControl = obj.GetComponent<numControl>();

        for (int i = 0; i < 3; i++)
        {
            randNum[i] = Random.Range(0, 3);

            Debug.Log(randNum[i]);

            if (randNum[i] == 0)
            {
                objName1.name = "Q";
            }
            if (randNum[i] == 1)
            {
                objName1.name = "W";
            }
            if (randNum[i] == 2)
            {
                objName1.name = "E";
            }
        }
    }

    // Update is called once per frame
    void Update()
    {
        objName1.SetActive(false);
        objName2.SetActive(false);




        if(numControl.num == 1 && objName1.name == "Q")
        {
            objName1.SetActive(true);
            objName2.SetActive(true);
        }

        if (numControl.num == 2 && objName1.name == "W")
        {
            objName1.SetActive(true);
            objName2.SetActive(true);
        }

        if (numControl.num == 3 && objName1.name == "E")
        {
            objName1.SetActive(true);
            objName2.SetActive(true);
        }

    }
}
