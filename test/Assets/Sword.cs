using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using static UnityEditor.PlayerSettings;

public class Sword : MonoBehaviour
{
    GameObject player;
    Vector3 playerPos;
    Vector3 playerPos1;
    Vector3 eqipPos;
    bool equipmentFlag = false;

    Rigidbody rb;
    Vector3 now;
    bool moveFlag = true;

    float speed;

    int time = 0;
    int timeMax1 = 30;
    int timeMax2 = 60;

    public GameObject RootObject;

    // Start is called before the first frame update
    void Start()
    {
        player = GameObject.Find("Player");
        eqipPos = new Vector3(0.3f, 1.0f, 0.0f);
        

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

 
    }

    void Update()
    {
        if (equipmentFlag)
        {
            playerPos = (player.transform.position + eqipPos);
            playerPos1 = playerPos * player.transform.forward;
            transform.position = playerPos1;
        }
    }

    void OnTriggerEnter(Collider other) // “–‚½‚è”»’è‚ðŽ@’m
    {
        if(other.gameObject.tag == "Player")
        {
            moveFlag = false;
            equipmentFlag = true;
            this.gameObject.transform.parent = RootObject.gameObject.transform;
        }
    }

    class Vector2
    {
        public float x;
        public float y;
        public float z;

        public static Vector2 operator*(Vector3 v1, Vector3 v2)
        {

            return new Vector2(v1.x * v2.x, v1.y * v2.y);
        }
            

        

    }

}
