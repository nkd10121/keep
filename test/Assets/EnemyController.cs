using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnemyController : MonoBehaviour
{
    int hp;

    // Start is called before the first frame update
    void Start()
    {
        hp = 3;
    }

    // Update is called once per frame
    void Update()
    {
        if(hp == 0) 
        {
            Destroy(this);
        }
    }

    void OnTirrgerEnter(Collision other)
    {
        if(other.gameObject.tag == "Sword")
        {
            Debug.Log("attack");
            hp--;
        }
    }
}
