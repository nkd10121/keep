using UnityEngine;
using UnityEngine.UI;

public class OverHeadMsg : MonoBehaviour
{
    public Transform targetTran;

    void Update()
    {
        transform.position = RectTransformUtility.WorldToScreenPoint(
             Camera.main,
             targetTran.position + Vector3.up);
    }

    public void ShowMsg(string msg)
    {
        GetComponent<Text>().text = msg;
    }
}