using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Sword : MonoBehaviour
{
    Rigidbody rb;
    Vector3 now;

    float speed;

    int time = 0;
    int timeMax1 = 40;
    int timeMax2 = 80;

    public string targetName;
    public string hideName;
    // Start is called before the first frame update
    void Start()
    {
        rb = GetComponent<Rigidbody>();
        now = rb.position;
        speed = 0.005f;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        

        if(time <= timeMax1)
        {
            now += new Vector3(0.0f, speed, 0.0f);
            //speed -= 0.02f;
            time++;
            rb.position = now;
            if(time == timeMax1)
            {
                speed = 0.005f;
            }
        }
        else if(time <= timeMax2) 
        {
            now -= new Vector3(0.0f, speed, 0.0f);
            //speed -= 0.02f;
            time++;
            rb.position = now;
            if (time == timeMax2)
            {
                speed = 0.005f;
            }
        }
        else
        {
            time = 0;
        }
    }

    void OnCollisionEnter(Collision collision)                 // “–‚½‚è”»’è‚ðŽ@’m
    {
        if (collision.gameObject.name == targetName)
        {
            GameObject hideObject = GameObject.Find(hideName);
            hideObject.SetActive(false);
        }
    }
}
