using UnityEngine;

public class enpty : MonoBehaviour
{
    [SerializeField] GameObject player;

    private Vector3 velocity = Vector3.zero;
    Vector3 gole;
    public float smoothTime = 0.3f;
    float mx = 0;
    float my = 0;
    private void Start()
    {

    }
    void Update()
    {
        // マウスの移動量を取得
        mx = Input.GetAxis("Mouse X");
        my = Input.GetAxis("Mouse Y");

        // X方向に一定量移動していれば横回転
        if (Mathf.Abs(mx) > 0.001f)
        {
            // 回転軸はワールド座標のY軸
            transform.RotateAround(player.transform.position, Vector3.up, mx * 5f);
        }

        // Y方向に一定量移動していれば縦回転
        if (Mathf.Abs(my) > 0.001f)
        {
            // 回転軸はカメラ自身のX軸
            transform.RotateAround(transform.position, transform.right, my * 0.5f);
        }
    }

    private void LateUpdate()
    {
        transform.position = player.transform.position;
    }
}