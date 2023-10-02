using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static Unity.VisualScripting.Member;

public class unitychanMove : MonoBehaviour
{
    //unitychanのRigidbody
    Rigidbody myRb;
    //移動速度
    float moveSpeed;

 

    //視点の移動速度
    float rotate = 0;
    //前に進んでいるか
    bool moveFrontFlag = false;
    //後ろに進んでいるかどうか
    bool moveBackFlag = false;
    //右に進んでいるかどうか
    bool moveRightFlag = false;
    //左に進んでいるかどうか
    bool moveLeftFlag = false;

    //前後方向のVector
    Vector3 move1;
    //左右方向のVector
    Vector3 move2;
        
    //ジャンプの向き
    Vector3 forceDirection;
    //ジャンプ力
    float forcePower;
    //向き*ジャンプ力
    Vector3 force;
    //ジャンプキーが押されたか
    bool jumpFlag = false;
    //ジャンプ中かどうか
    public bool jumpNow = false;
    //ダッシュキーが押されたか
    bool runFlag = false;

    Vector3 angle;

    // Start is called before the first frame update
    void Start()
    {
        //移動速度の設定
        moveSpeed = 0.15f;
        //Rigidbodyの取得
        myRb = this.GetComponent<Rigidbody>();

        angle = new Vector3(0, 0.1f, 0);

        //ジャンプ方向の設定(上方向に)
        forceDirection = new Vector3(0f, 1.0f, 0f);
        //ジャンプ力の設定
        forcePower = 6f;
        //ジャンプ方向*ジャンプ力
        force = forcePower * forceDirection;
    }

    // Update is called once per frame
    void Update()
    {
        //playerの向いている方向を取得しつつ移動速度を掛ける
        move1 = transform.forward * moveSpeed;
        move2 = transform.right * moveSpeed;

        //// マウスの移動量(X軸方向のみ)を取得
        //float mouseX = Input.GetAxis("Mouse X");

        //// X方向に一定量移動していれば横回転
        //if (Mathf.Abs(mouseX) > 0.00001f)
        //{
        //    // 回転軸はワールド座標のY軸
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
