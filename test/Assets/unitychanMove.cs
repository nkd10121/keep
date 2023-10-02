using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static Unity.VisualScripting.Member;

public class unitychanMove : MonoBehaviour
{
    //unitychan��Rigidbody
    Rigidbody myRb;
    //�ړ����x
    float moveSpeed;

 

    //���_�̈ړ����x
    float rotate = 0;
    //�O�ɐi��ł��邩
    bool moveFrontFlag = false;
    //���ɐi��ł��邩�ǂ���
    bool moveBackFlag = false;
    //�E�ɐi��ł��邩�ǂ���
    bool moveRightFlag = false;
    //���ɐi��ł��邩�ǂ���
    bool moveLeftFlag = false;

    //�O�������Vector
    Vector3 move1;
    //���E������Vector
    Vector3 move2;
        
    //�W�����v�̌���
    Vector3 forceDirection;
    //�W�����v��
    float forcePower;
    //����*�W�����v��
    Vector3 force;
    //�W�����v�L�[�������ꂽ��
    bool jumpFlag = false;
    //�W�����v�����ǂ���
    public bool jumpNow = false;
    //�_�b�V���L�[�������ꂽ��
    bool runFlag = false;

    Vector3 angle;

    // Start is called before the first frame update
    void Start()
    {
        //�ړ����x�̐ݒ�
        moveSpeed = 0.15f;
        //Rigidbody�̎擾
        myRb = this.GetComponent<Rigidbody>();

        angle = new Vector3(0, 0.1f, 0);

        //�W�����v�����̐ݒ�(�������)
        forceDirection = new Vector3(0f, 1.0f, 0f);
        //�W�����v�͂̐ݒ�
        forcePower = 6f;
        //�W�����v����*�W�����v��
        force = forcePower * forceDirection;
    }

    // Update is called once per frame
    void Update()
    {
        //player�̌����Ă���������擾���ړ����x���|����
        move1 = transform.forward * moveSpeed;
        move2 = transform.right * moveSpeed;

        //// �}�E�X�̈ړ���(X�������̂�)���擾
        //float mouseX = Input.GetAxis("Mouse X");

        //// X�����Ɉ��ʈړ����Ă���Ή���]
        //if (Mathf.Abs(mouseX) > 0.00001f)
        //{
        //    // ��]���̓��[���h���W��Y��
        //    transform.RotateAround(myRb.transform.position, Vector3.up, mouseX * 1.0f);
        //}


        if (Input.GetKey(KeyCode.W))
        {
            moveFrontFlag = true;
        }
        else
        {
            moveFrontFlag = false;
        }

        if (Input.GetKey(KeyCode.S))
        {
            moveBackFlag = true;
        }
        else
        {
            moveBackFlag = false;
        }

        if (Input.GetKey(KeyCode.D))
        {
            //moveRightFlag = true;
            rotate += 0.5f;

            this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
        }
        else
        {
            moveRightFlag = false;
        }

        if (Input.GetKey(KeyCode.A))
        {
            //moveLeftFlag = true;
            rotate -= 0.5f;

            this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
        }
        else
        {
            //moveLeftFlag = false;
        }

        if(Input.GetMouseButton(2))
        {
            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Locked;
        }

  
        if (Input.GetKey(KeyCode.Space) && !jumpNow)
        {
            jumpFlag = true;

        }
        else
        {
            jumpFlag = false;
        }

        if (Input.GetKey(KeyCode.LeftShift))
        {
            runFlag = true;
        }
        else
        {
            runFlag = false;
            moveSpeed = 0.15f;

        }
    }

    void FixedUpdate()
    {
        if (moveFrontFlag)
        {
            myRb.position += move1;
        }

        if (moveBackFlag)
        {
            myRb.position -= move1;
        }

        if(moveRightFlag)
        {
            myRb.position += move2;
        }

        if (moveLeftFlag)
        {
            myRb.position -= move2;
        }

        if (jumpFlag)
        {
            jumpNow = true;
            myRb.AddForce(force, ForceMode.Impulse);
        }

        if(runFlag)
        {
            moveSpeed = 0.4f;
        }
    }

    private void OnCollisionEnter(Collision other)
    {
        if(other.gameObject.tag == "ground")
        {
            jumpNow = false;
        }
    }
}
