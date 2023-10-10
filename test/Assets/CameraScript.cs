using UnityEngine;
 
public class CameraScript : MonoBehaviour
{
    [SerializeField] GameObject player;

    Rigidbody cameraRb;

    Transform playerTra;

    bool rotateFlag = false;
    bool reset = false;

    Transform cameraTra;
    Vector3 lAngle;
   void Update()
    {
        // É}ÉEÉXÇÃà⁄ìÆó ÇéÊìæ
        float mx = Input.GetAxis("Mouse X");
        float my = Input.GetAxis("Mouse Y");

        // Xï˚å¸Ç…àÍíËó à⁄ìÆÇµÇƒÇ¢ÇÍÇŒâ°âÒì]
        if (Mathf.Abs(mx) > 0.001f)
        {
            // âÒì]é≤ÇÕÉèÅ[ÉãÉhç¿ïWÇÃYé≤
            transform.RotateAround(player.transform.position, Vector3.up, mx * 1f);
        }

        // Yï˚å¸Ç…àÍíËó à⁄ìÆÇµÇƒÇ¢ÇÍÇŒècâÒì]
        if (Mathf.Abs(my) > 0.001f)
        {
            // âÒì]é≤ÇÕÉJÉÅÉâé©êgÇÃXé≤
            transform.RotateAround(player.transform.position, transform.right, my * 0.2f);
        }

        transform.LookAt(player.transform);

        //if (reset)
        //{
        //    playerTra = player.transform;
        //Vector3 wCameraPos = playerTra.position;

        //    wCameraPos.x = 0f;
        //    wCameraPos.y = 1.5f;
        //    wCameraPos.z = -2f;
        //    transform.position = wCameraPos;
        //}

        if (Input.GetKey(KeyCode.A))
        {
            //Vector3 wCameraAngle = playerTra.eulerAngles;

            //wCameraAngle.x = 0.0f;
            //wCameraAngle.y = 0.0f;
            //wCameraAngle.z = 0.0f;
            //RotationÇê›íË
            //transform.localEulerAngles = wCameraAngle;

            //lAngle.x = 0f;
            //lAngle.y = 1.5f;
            //lAngle.z = -2f;

        }



    }

    private void FixedUpdate()
    {
        if (Input.GetKeyDown(KeyCode.A))
        {
            Transform cameraTra = this.transform;
            Vector3 wAngle = cameraTra.eulerAngles;
            rotateFlag = true;
        }
        else
        {
            rotateFlag = false;
        }


        //if (Input.GetKeyDown(KeyCode.F))
        //{
        //    reset = true;
        //}
        //else
        //{
        //    reset = false;
        //}


    }
}