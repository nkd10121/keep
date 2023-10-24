using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using UnityEngine.InputSystem;

public class playerMove : MonoBehaviour
{
    Rigidbody myRb;

    int rolltimer = 0;
    float moveSpeed;
    float rotate = 0;
    bool moveFrontFlag = false;
    bool moveBackFlag = false;
    bool moveRightFlag = false;
    bool moveLeftFlag = false;
    bool rollFlag = false;
    Vector3 move;
    Vector3 angle;

    Vector3 x, y, z;
    Vector3 rolling;

    bool resetCamera = false;

    GameObject enpty;
    Transform enptyTra;

    float speed = 30.0f;

    public Vector2 v;


    // Start is called before the first frame update
    void Start()
    {
        moveSpeed = 0.3f;
        angle = new Vector3(0, 1.0f, 0);
        myRb = this.GetComponent<Rigidbody>();

        rolling = new Vector3(0.1f, 0.0f, 0.0f);

        enpty = GameObject.Find("cameraPosBase");
    }

    // Update is called once per frame
    void Update()
    {
        move = transform.forward * moveSpeed;

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
            moveRightFlag = true;

        }
        else
        {
            moveRightFlag = false;
        }

        if (Input.GetKey(KeyCode.A))
        {
            moveLeftFlag = true;
        }
        else
        {
            moveLeftFlag = false;
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            rollFlag = true;
        }

        if (Input.GetKeyDown(KeyCode.F))
        {
            resetCamera = true;
        }
    }

    void FixedUpdate()
    {
        if (moveFrontFlag)
        {

        }

        if (moveBackFlag)
        {
            if (this.transform.localEulerAngles.y >= -1)
            {

                rotate -= 10f;

                this.transform.rotation = Quaternion.AngleAxis(rotate, angle);


            }

            myRb.position -= move;
        }

        //if (moveRightFlag)
        //{
        //    enptyTra = enpty.transform.localEulerAngles;

        //    if (this.transform.localEulerAngles.y >= enptyTra.y + 90 && this.transform.localEulerAngles.y <= enptyTra.y + 95)
        //    {
        //        myRb.position += move;
        //    }
        //    else
        //    {
        //        rotate += 2f;

        //        this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
        //    }
        //}

        if (moveLeftFlag)
        {
            if (this.transform.localEulerAngles.y <= 270 && this.transform.localEulerAngles.y >= 265)
            {
                myRb.position += move;
            }
            else
            {
                rotate -= 2f;

                this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
            }
        }

        if (resetCamera)
        {
            Debug.Log("reset");
            enpty.transform.forward = this.transform.forward;
            //Update�̕���false�ɂ���悤�ɂ���ƌĂ΂��Ԋu�̍��ŌĂ΂�Ȃ����Ƃ�����
            resetCamera = false;
        }
    }

    public void OnJump(InputAction.CallbackContext contest)
    {
        if (contest.phase == InputActionPhase.Performed)
        {
            Debug.Log("jumping");
        }
    }

    public void OnMove(InputAction.CallbackContext context)
    {
        // �X�e�B�b�N�̓��͂��󂯎��
        v = context.ReadValue<Vector2>();

        // �ړ��ʂ��v�Z
        var mov = new Vector3(v.x * speed * Time.deltaTime, 0, v.y * speed * Time.deltaTime);

        //switch (context.phase)
        //{
        //    case InputActionPhase.Started:
        //        // ���͊J�n

        //        // �ړ�����������
        //        transform.forward = mov;
        //        break;
        //    case InputActionPhase.Canceled:
        //        // ���͏I��
        //        break;
        //    default:
        //        // �ړ�����������
        //        transform.forward = mov;
        //        break;
        //}

        if(context.phase == InputActionPhase.Performed)
        {
            // �ړ�����������
            transform.forward = mov;

            // �ړ�������
            transform.position = transform.position + mov;
        }


    }
    public void OnCameraMove(InputAction.CallbackContext context)
    {
        // �X�e�B�b�N�̓��͂��󂯎��
        var v = context.ReadValue<Vector2>();

        // �ړ��ʂ��v�Z
        var mov = new Vector3(v.x * speed * Time.deltaTime, 0, v.y * speed * Time.deltaTime);
        //switch (context.phase)
        //{
        //    case InputActionPhase.Started:
        //        // ���͊J�n

        //        // �ړ�����������
        //        transform.forward = mov;
        //        break;
        //    case InputActionPhase.Canceled:
        //        // ���͏I��
        //        break;
        //    default:
        //        // �ړ�����������
        //        transform.forward = mov;
        //        break;
        //}

        // X�����Ɉ��ʈړ����Ă���Ή���]
        if (Mathf.Abs(v.x) > 0.001f)
        {
            // ��]���̓��[���h���W��Y��
            enpty.transform.RotateAround(enpty.transform.position, Vector3.up, v.x * 5f);
        }


        // �ړ�������
        enptyTra.localEulerAngles = enptyTra.localEulerAngles + mov;
    }
}
