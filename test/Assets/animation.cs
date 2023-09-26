using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class animation : MonoBehaviour
{
    Animator animator;

    public string parameterName = "";
    public bool parameterValue = true;

    bool pushFlag;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        pushFlag = false;
    }

    // Update is called once per frame
    void Update()
    {
        if(Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.S))
        {
            animator.SetBool("move", true);
        }
        else
        {
            animator.SetBool("move", false);
        }

        if(Input.GetMouseButton(0))
        {
            if(pushFlag == false)
            {
                pushFlag = true;
                animator.SetBool(parameterName, parameterValue);
            }
        }
        else
        {
            pushFlag = false;
        }
    }
}
