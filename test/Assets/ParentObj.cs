using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ParentObj : MonoBehaviour
{

    public GameObject RootObject;

    // Start is called before the first frame update
    void Start()
    {
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKey(KeyCode.X))
        {
            this.gameObject.transform.parent = RootObject.gameObject.transform;
        }

        if (Input.GetKey(KeyCode.Z))
        {
            this.gameObject.transform.parent = null;
        }
    }
}