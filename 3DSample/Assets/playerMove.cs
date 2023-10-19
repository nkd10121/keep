using System.Collections;
using System.Collections.Generic;
using Unity.VisualScripting;
using UnityEngine;

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
    Vector3 enptyTra;

    // Start is called before the first frame update
    void Start()
    {
        moveSpeed = 0.3f;
        angle = new Vector3(0, 1.0f, 0);
        myRb = this.GetComponent<Rigidbody>();

        rolling = new Vector3(0.1f, 0.0f, 0.0f);

        enpty = GameObject.Find("cameraPosBase");
        enptyTra = enpty.transform.localEulerAngles;
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
            moveLeftFlag= false;
        }

        if (Input.GetKeyDown(KeyCode.Space))
        {
            rollFlag = true;
        }

        if(Input.GetKeyDown(KeyCode.F))
        {
            resetCamera = true;
        }
    }

    void FixedUpdate()
    {
        if(moveFrontFlag)
        {
            myRb.position += move;
        }
        else if(moveBackFlag)
        {
            if(this.transform.localEulerAngles.y >= -1)
            {

                rotate -= 10f;

                this.transform.rotation = Quaternion.AngleAxis(rotate, angle);


            }

            myRb.position -= move;
        }

        if(moveRightFlag)
        {
            if (this.transform.localEulerAngles.y >= 90 && this.transform.localEulerAngles.y <= 95)
            {
                myRb.position += move;
            }
            else
            {
                rotate += 2f;

                this.transform.rotation = Quaternion.AngleAxis(rotate, angle);
            }
        }

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

        if(resetCamera)
        {
            Debug.Log("reset");
            enpty.transform.forward = this.transform.forward;
            //UpdateÇÃï˚Ç≈falseÇ…Ç∑ÇÈÇÊÇ§Ç…Ç∑ÇÈÇ∆åƒÇŒÇÍÇÈä‘äuÇÃç∑Ç≈åƒÇŒÇÍÇ»Ç¢Ç±Ç∆Ç™Ç†ÇÈ
            resetCamera = false;
        }
    }
}
