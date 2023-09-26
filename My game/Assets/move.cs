using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class move : MonoBehaviour
{
    Rigidbody2D myRb;
    Vector2 playerPos;
    float speed;

    numControl numControl;
    GameObject obj;

    // Start is called before the first frame update
    void Start()
    {
        myRb = GetComponent<Rigidbody2D>();
        speed = 0.05f;

        obj = GameObject.Find("test");
        numControl = obj.GetComponent<numControl>();
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        playerPos = transform.position;

        speed = 0.05f;
        playerPos.x += speed;
        transform.position = playerPos;
    }

    void OnCollisionEnter2D(Collision2D other)
    {

        if (other.gameObject.tag == "ground")
        {
            this.myRb.AddForce(transform.up * 200f);
        }

    }
}
