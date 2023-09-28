using UnityEngine;

public class OverHeadMsgCreater : MonoBehaviour
{
    [SerializeField]
    RectTransform canvasRect;

    [SerializeField]
    OverHeadMsg overHeadMsgPrefab;

    OverHeadMsg overHeadMsg;

    void OnEnable()
    {
        overHeadMsg = Instantiate(overHeadMsgPrefab, canvasRect);
        overHeadMsg.targetTran = transform;
    }

    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space))
        {
            overHeadMsg.ShowMsg("Hello");
        }
    }

    void OnDisable()
    {
        if (overHeadMsg == null) return;

        Destroy(overHeadMsg.gameObject);
    }
}