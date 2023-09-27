using UnityEngine;
 
public class CameraScript : MonoBehaviour
{
    [SerializeField] GameObject player;

    void Update()
    {
        // �}�E�X�̈ړ��ʂ��擾
        float mx = Input.GetAxis("Mouse X");
        float my = Input.GetAxis("Mouse Y");

        // X�����Ɉ��ʈړ����Ă���Ή���]
        if (Mathf.Abs(mx) > 0.001f)
        {
            // ��]���̓��[���h���W��Y��
            transform.RotateAround(player.transform.position, Vector3.up, mx * 0.001f);
        }

        // Y�����Ɉ��ʈړ����Ă���Ώc��]
        if (Mathf.Abs(my) > 0.001f)
        {
            // ��]���̓J�������g��X��
            transform.RotateAround(player.transform.position, transform.right, my * 0.2f);
        }
    }
}