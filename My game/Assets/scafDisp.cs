using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class scafDisp : MonoBehaviour
{
    [SerializeField] GameObject objName1;
    [SerializeField] GameObject objName2;

    numControl numControl;
    GameObject obj;
     //Start is called before the first frame update
    void Start()
    {
        obj = GameObject.Find("test");
        numControl = obj.GetComponent<numControl>();
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

    }
}
