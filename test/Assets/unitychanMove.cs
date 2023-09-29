using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static Unity.VisualScripting.Member;

public class unitychanMove : MonoBehaviour
{
    Rigidbody myRb;
    //移動速度
    float moveSpeed;

 

    //視点の移動速度
    float rotate = 0;
    //前に進んでいるか
    bool moveFrontFlag = false;
    //後ろに進んでいるかどうか
    bool moveBackFlag = false;

    bool moveRightFlag = false;

    bool moveLeftFlag = false;

    Vector3 move1;
    Vector3 move2;
        
    Vector3 angle;

    Vector3 forceDirection;
    float forcePower;
    Vector3 force;
    bool jumpFlag = false;
    public bool flag = false;

    bool runFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        moveSpeed = 0.15f;

        angle = new Vector3(0, 1.0f, 0);
        myRb = this.GetComponent<Rigidbody>();

        forceDirection = new Vector3(0f, 1.0f, 0f);
        forcePower = 6f;
        force = forcePower * forceDirection;
    }

    // Update is called once per frame
    void Update()
    {
        move1 = transform.forward * moveSpeed;
        move2 = transform.right * moveSpeed;

        // マウスの移動量を取得
        float mx = Input.GetAxis("Mouse X");

        // X方向に一定量移動していれば横回転
        if (Mathf.Abs(mx) > 0.00001f)
        {
            // 回転軸はワールド座標のY軸
            transform.RotateAround(myRb.transform.position, Vector3.up, mx * 1.5f);
        }


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

        if(Input.GetMouseButton(2))
        {
            Cursor.visible = false;
            Cursor.lockState = CursorLockMode.Locked;
        }

  
        if (Input.GetKey(KeyCode.Space) && !flag)
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
            flag = true;
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
            flag = false;
        }
    }
}
