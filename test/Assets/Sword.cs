using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sword : MonoBehaviour
{
    GameObject player;
    Vector3 playerPos;
    Rigidbody rb;
  
    Vector3 now;

    BoxCollider collider;

    bool moveFlag = true;
    bool equipmentFlag = false;

    float speed;

    int time = 0;
    int timeMax1 = 30;
    int timeMax2 = 60;

    public GameObject RootObject;

    // Start is called before the first frame update
    void Start()
    {
        collider = GetComponent<BoxCollider>();
         
        rb = GetComponent<Rigidbody>();
        now = rb.position;
        speed = 0.0025f;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        if(moveFlag)
        {
            if (time <= timeMax1)
            {
                if (time == 0)
                {
                    speed = 0.005f;
                }
                now += new Vector3(0.0f, speed, 0.0f);
                speed -= 0.0002f;
                time++;
                rb.position = now;
            }
            else if (time <= timeMax2)
            {
                if (time == timeMax1 + 1)
                {
                    speed = 0.005f;
                }
                now -= new Vector3(0.0f, speed, 0.0f);
                speed -= 0.0002f;
                time++;
                rb.position = now;
            }
            else
            {
                time = 0;
            }
        }

        if (equipmentFlag)
        {
            player = GameObject.Find("Player");
            playerPos = player.transform.position;
            rb.position = playerPos;
        }
    }

    void Update()
    {
  
    }

    void OnCollisionEnter(Collision collision)                 // “–‚½‚è”»’è‚ðŽ@’m
    {
        moveFlag = false;
        equipmentFlag = true;
     //   collider.enabled = false;
        this.gameObject.transform.parent = RootObject.gameObject.transform;
    }
}
