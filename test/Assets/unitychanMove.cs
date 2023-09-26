using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;
using static Unity.VisualScripting.Member;

public class unitychanMove : MonoBehaviour
{
    Rigidbody myRb;

    int rolltimer = 0;
    float moveSpeed;
    float rotate = 0;
    bool moveFrontFlag = false;
    bool moveBackFlag = false;
    Vector3 move;
    Vector3 angle;

    Vector3 forceDirection;
    float forcePower;
    Vector3 force;
    bool jumpFlag = false;
    public bool flag = false;

    bool runFlag = false;


    Vector3 x, y, z;

    // Start is called before the first frame update
    void Start()
    {
        moveSpeed = 0.3f;
        angle = new Vector3(0, 1.0f, 0);
        myRb = this.GetComponent<Rigidbody>();

        forceDirection = new Vector3(0f, 1.0f, 0f);
        forcePower = 6f;
        force = forcePower * forceDirection;
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
            rotate += 0.8f;

            this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
        }
        if (Input.GetKey(KeyCode.A))
        {
            rotate -= 0.8f;

            this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
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
            moveSpeed = 0.3f;

        }
    }

    void FixedUpdate()
    {
        if (moveFrontFlag)
        {
            myRb.position += move;
        }
        else if (moveBackFlag)
        {
            myRb.position -= move;
        }

        if (jumpFlag)
        {
            flag = true;
            myRb.AddForce(force, ForceMode.Impulse);
        }

        if(runFlag)
        {
            moveSpeed = 0.7f;
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
