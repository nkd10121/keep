using System.Collections;
using System.Diagnostics;
using UnityEngine;

public class CoroutineSample : MonoBehaviour
{
    bool wait = false;
    void Start()
    {
        StartCoroutine("TestCoroutine");
    }

    IEnumerator TestCoroutine()
    {
        if(Input.GetKey(KeyCode.Q))
        {
            wait = true;
        }
        yield return new WaitUntil(() => wait);

        UnityEngine.Debug.Log("wait end");
    }

}