using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class animation : MonoBehaviour
{
    Animator animator;

    public string parameterName = "";
    public bool parameterValue = true;

    public bool moveFlag;

    bool pushFlag;
    // Start is called before the first frame update
    void Start()
    {
        animator = GetComponent<Animator>();
        pushFlag = false;
        moveFlag = false;
    }

    // Update is called once per frame
    void Update()
    {
        //移動
        //もし移動キーを押している場合、移動アニメーションをするように
        if (Input.GetKey(KeyCode.W) || Input.GetKey(KeyCode.S) ||
            Input.GetKey(KeyCode.D) || Input.GetKey(KeyCode.A))
        {
            animator.SetBool("move", true);
            moveFlag = true;
        }
        else
        {
            animator.SetBool("move", false);
            moveFlag = false;
        }

        //ジャンプ
        if (Input.GetKey(KeyCode.Space) && !(Input.GetKey(KeyCode.LeftShift)))
        {
            animator.SetTrigger("jumpTrigger");
        }

        //ダッシュ
        //移動キーを押しているかつダッシュキーを押しているとき
        if ((Input.GetKey(KeyCode.LeftShift)) && (moveFlag == true))
        {
            animator.SetBool("dashBool", true);
        }
        else
        {
            animator.SetBool("dashBool", false);
        }

        //攻撃
        if (Input.GetMouseButton(0))
        {
            if (pushFlag == false)
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
