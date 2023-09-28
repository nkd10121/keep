using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Net.Mime;
using System.Security.Cryptography;
using UnityEngine;

public class Sword : MonoBehaviour
{
    GameObject player;

    //プレイヤーの座標
    Vector3 playerLocalPos;
    //プレイヤーのtransformを取得用
    Transform playerTransform;

    //プレイヤーに当たったかどうか
    bool isHitFlag = false;

    //装備前の剣の座標
    Vector3 swordPos;
    //装備後の剣の座標
    Vector3 eqipPos;
    //剣の移動速度
    float speed;
    float updownSpeed;

    int time = 0;
    //剣の上昇時間
    int timeMax1 = 40;
    //剣の下降時間
    int timeMax2 = 80;

    //敵
    GameObject ene;

    //親オブジェクトにするオブジェクト名
    public GameObject RootObject;
    public BoxCollider col;
    int hitCount;

    // Start is called before the first frame update
    void Start()
    {
        //"player"を探す
        //player = GameObject.Find("Player");
        player = GameObject.Find("unitychan");
        //装備する前の剣の座標を指定
        swordPos = new Vector3(0.0f,1.0f,3.0f);

        //装備した後の剣の座標を指定
        //eqipPos = new Vector3(0.3f, 1.0f, 0.0f);
        eqipPos = new Vector3(-0.019f, -0.808f, 0.017f);

        updownSpeed = 0.0005f;

        //剣の移動速度
        speed = 0.0025f;

        //プレイヤーのtransformを取得
        playerTransform = player.transform;

        ene = GameObject.Find("enemy");
        col = GetComponent<BoxCollider>();
        hitCount = 0;

    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //プレイヤーに当たる前の処理
        if (!isHitFlag)
        {
            if (time <= timeMax1)
            {
                //speedの再設定
                if (time == 0)
                {
                    speed = 0.004f;
                }
                //剣を上に移動
                swordPos.y += speed;
                //移動速度を減らす
                speed -= updownSpeed;
                time++;
                //剣の座標設定
                transform.position = swordPos;
            }
            else if (time <= timeMax2)
            {
                //speedの再設定

                if (time == timeMax1 + 1)
                {
                    speed = 0.004f;
                }
                //剣を下に移動
                swordPos.y -= speed;
                //移動速度を減らす
                speed -= updownSpeed;
                time++;
                //剣の座標設定
                transform.position = swordPos;
            }
            else
            {
                time = 0;
            }
        }

        if (Input.GetMouseButtonDown(0))
        {
            ////左手コライダーをオンにする
            col.enabled = true;

            //一定時間後にコライダーの機能をオフにする
            Invoke("ColliderReset", 2f);
        }
    }

    void OnTriggerEnter(Collider other) // 当たり判定を察知
    {
        if (other.gameObject.tag == "Player")
        {
            //Debug.Log("hit");

            //プレイヤーに当たった(剣の動きを消す)
            isHitFlag = true;
            //剣をプレイヤーの子オブジェクトにする
            this.gameObject.transform.parent = RootObject.gameObject.transform;

            //ワールド座標を基準に、回転を取得
            Vector3 localAngle = playerTransform.localEulerAngles;
            //Rotationを0に(もともと90に設定して配置している)
            localAngle.y = 0.0f;
            //Rotationを設定
            transform.localEulerAngles = localAngle;

            playerLocalPos.x = 0.0f;
            playerLocalPos.y = 0.0f;
            playerLocalPos.z = 0.0f;
            //剣を装備した時の剣の位置に移動させるための座標を足す
            playerLocalPos += eqipPos;
            //剣の装備後の座標を設定
            transform.localPosition = playerLocalPos;

            col.enabled = false;
        }


        if(other.gameObject.tag == "enemy")
        {
            hitCount += 1;

            Debug.Log("attack");

            if(hitCount == 3)
            {
                Destroy(ene);
            }
        }

    }
}