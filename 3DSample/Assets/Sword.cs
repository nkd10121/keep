using System.Collections;
using System.Collections.Generic;
using System.Collections.Specialized;
using System.Net.Mime;
using System.Security.Cryptography;
using UnityEngine;

public class Sword : MonoBehaviour
{
    GameObject player;
    GameObject handPos;

    //�v���C���[�̍��W
    Vector3 playerLocalPos;
    //�v���C���[��transform���擾�p
    Transform playerTransform;

    //�v���C���[�ɓ����������ǂ���
    bool isHitFlag = false;

    //�����O�̌��̍��W
    Vector3 swordPos;
    //������̌��̍��W
    Vector3 eqipPos;
    //���̈ړ����x
    float speed;

    int time = 0;
    //���̏㏸����
    int timeMax1 = 30;
    //���̉��~����
    int timeMax2 = 60;

    //�e�I�u�W�F�N�g�ɂ���I�u�W�F�N�g��
    public GameObject RootObject;

    // Start is called before the first frame update
    void Start()
    {
        //"player"��T��
        player = GameObject.Find("Player");
        handPos = GameObject.Find("mixamorig_RightHandMiddle1");

        //��������O�̌��̍��W���w��
        swordPos = new Vector3(0.0f,1.0f,3.0f);

        //����������̌��̍��W���w��
        eqipPos = new Vector3(0.3f, 1.0f, 0.0f);

        //���̈ړ����x
        speed = 0.0025f;

        //�v���C���[��transform���擾
        playerTransform = player.transform;
    }

    // Update is called once per frame
    void FixedUpdate()
    {
        //�v���C���[�ɓ�����O�̏���
        if (!isHitFlag)
        {
            if (time <= timeMax1)
            {
                //speed�̍Đݒ�
                if (time == 0)
                {
                    speed = 0.005f;
                }
                //������Ɉړ�
                swordPos.y += speed;
                //�ړ����x�����炷
                speed -= 0.0002f;
                time++;
                //���̍��W�ݒ�
                transform.position = swordPos;
            }
            else if (time <= timeMax2)
            {
                //speed�̍Đݒ�

                if (time == timeMax1 + 1)
                {
                    speed = 0.005f;
                }
                //�������Ɉړ�
                swordPos.y -= speed;
                //�ړ����x�����炷
                speed -= 0.0002f;
                time++;
                //���̍��W�ݒ�
                transform.position = swordPos;
            }
            else
            {
                time = 0;
            }
        }
    }

    void OnTriggerEnter(Collider other) // �����蔻����@�m
    {
        if (other.gameObject.tag == "Player")
        {
            //�v���C���[�ɓ�������(���̓���������)
            isHitFlag = true;
            //�����v���C���[�̎q�I�u�W�F�N�g�ɂ���
            this.gameObject.transform.parent = RootObject.gameObject.transform;

            //���[���h���W����ɁA��]���擾
            Vector3 localAngle = playerTransform.localEulerAngles;
            //Rotation��0��(���Ƃ���90�ɐݒ肵�Ĕz�u���Ă���)
            localAngle.y = 0.0f;
            //Rotation��ݒ�
            transform.localEulerAngles = localAngle;

            playerLocalPos.x = 0.0f;
            playerLocalPos.y = 0.0f;
            playerLocalPos.z = 0.0f;
            //���𑕔��������̌��̈ʒu�Ɉړ������邽�߂̍��W�𑫂�
            playerLocalPos += eqipPos;
            //���̑�����̍��W��ݒ�
            transform.localPosition = playerLocalPos;
        }
    }
}