using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class playerMove : MonoBehaviour
{
    Rigidbody rb;
    Vector3 move;

    float speed;
    bool moveFrotFlag = false;
    bool moveBackFlag = false;

    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        speed = 0.3f;
    }

    // Update is called once per frame
    void Update()
    {
        move = transform.forward * speed;

        if (Input.GetKey(KeyCode.W))
        {
            moveFrotFlag = true;
        }
        else
        {
            moveFrotFlag = false;
        }

        if (Input.GetKey(KeyCode.S))
        {
            moveBackFlag = true;
        }
        else
        {
            moveBackFlag = false;
        }
    }

    private void FixedUpdate()
    {
        if (moveFrotFlag)
        {
            rb.position += move;
        }

        if(moveBackFlag)
        {
            rb.position -= move;

        }
    }
}
