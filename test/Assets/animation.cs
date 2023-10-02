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
        //�ړ�
        //�����ړ��L�[�������Ă���ꍇ�A�ړ��A�j���[�V����������悤��
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

        //�W�����v
        if (Input.GetKey(KeyCode.Space) && !(Input.GetKey(KeyCode.LeftShift)))
        {
            animator.SetTrigger("jumpTrigger");
        }

        //�_�b�V��
        //�ړ��L�[�������Ă��邩�_�b�V���L�[�������Ă���Ƃ�
        if ((Input.GetKey(KeyCode.LeftShift)) && (moveFlag == true))
        {
            animator.SetBool("dashBool", true);
        }
        else
        {
            animator.SetBool("dashBool", false);
        }

        //�U��
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
