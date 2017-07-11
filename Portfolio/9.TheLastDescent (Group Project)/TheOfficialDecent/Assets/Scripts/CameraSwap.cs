using UnityEngine;
using System;
using System.Collections;
using System.Collections.Generic;

public class CameraSwap : MonoBehaviour
{
    public float cameraMovementSpeed = 2f;
    public Vector3 transformBegin;
    public Vector3 transformEnd;
    public Vector3 direction;
    public int timesAccessed = 0;
    // [NonSerialized]
    public bool moving;
    public bool turnedNinety = false;

    public GameObject Player;
    public GameObject PlayerCamera;
    public GameObject OptionalCamera1;
    public GameObject OptionalCamera2;
    public GameObject OptionalCamera3;

    void Awake()
    {
        Player = GameObject.Find("Player");
        PlayerCamera.SetActive(true);
        
        if (OptionalCamera1 != null)
        {   OptionalCamera1.SetActive(false);    }

        if (OptionalCamera2 != null)
        {   OptionalCamera2.SetActive(false);    }

        if (OptionalCamera3 != null)
        {   OptionalCamera3.SetActive(false);    }
    }

    // Use this for initialization
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.U))
        {
            swapToPlayerCam();
        }
        if (Input.GetKeyDown(KeyCode.I))
        {
            swapToOptionalCam(1);
        }
        if (Input.GetKeyDown(KeyCode.O))
        {
            swapToOptionalCam(2);
        }
        if (Input.GetKeyDown(KeyCode.P))
        {
            swapToOptionalCam(3);
        }
    }

    void FixedUpdate()
    {
        if (moving == true)
        {
            TranslateToPosition();
        }
    }
	
	// Update is called once per frame
    public void swapToPlayerCam()
    {
        PlayerCamera.SetActive(true);

        if (OptionalCamera1 != null)
        {   OptionalCamera1.SetActive(false);   }

        if (OptionalCamera2 != null)
        {   OptionalCamera2.SetActive(false);   }

        if (OptionalCamera3 != null)
        {   OptionalCamera3.SetActive(false);   }
    }

    public void swapToOptionalCam(int camNo)
    {
        switch (camNo)
        {
            case 1:
                if (OptionalCamera1 != null)
                {
                    PlayerCamera.SetActive(false);

                    OptionalCamera1.SetActive(true);

                    if(OptionalCamera2 != null)
                        OptionalCamera2.SetActive(false);

                    if (OptionalCamera3 != null)
                        OptionalCamera3.SetActive(false);
                }
                break;
            case 2:
                if (OptionalCamera2 != null)
                {
                    PlayerCamera.SetActive(false);
                    
                    if(OptionalCamera1 != null)
                        OptionalCamera1.SetActive(true);

                        OptionalCamera2.SetActive(false);

                    if (OptionalCamera3 != null)
                        OptionalCamera3.SetActive(false);
                }
                break;
            case 3:
                if(OptionalCamera3 != null)
                {
                    PlayerCamera.SetActive(false);

                    if (OptionalCamera1 != null)
                        OptionalCamera1.SetActive(false);

                    if (OptionalCamera2 != null)
                        OptionalCamera2.SetActive(false);

                    OptionalCamera3.SetActive(true);
                }
                break;
        }
    }

    public void setCamSpeed(float speed)
    {
        cameraMovementSpeed = speed;
    }

    public void SetTranslate(Vector3 beginning, Vector3 end)
    {
        transformEnd = end;
        transformBegin = beginning;

        Vector3 dir;
        dir = (transformEnd - OptionalCamera1.gameObject.transform.position);
        dir = dir.normalized;
        direction = dir;
    }

    public void updateTranslateCamPos(Transform tf)
    {
        timesAccessed++;

        OptionalCamera1.transform.position = tf.position;
        OptionalCamera1.transform.rotation = tf.rotation;
        OptionalCamera1.transform.localScale = tf.lossyScale;
    }
    public void setTranslateCam(bool status)
    {
        if (status == true)
        {
            swapToOptionalCam(1);
        }
        if (status == false)
        {
            swapToPlayerCam();
        }
    }
    public void TranslateToPosition()
    {
        // Move the camera towards the set destination
        OptionalCamera1.GetComponent<Rigidbody>().MovePosition(OptionalCamera1.transform.position + direction * cameraMovementSpeed * Time.fixedDeltaTime);

        if (Vector3.Distance(OptionalCamera1.gameObject.transform.position, transformEnd) < cameraMovementSpeed * Time.fixedDeltaTime)
        {
            setTranslateCam(false);
            OptionalCamera1.transform.position = Vector3.zero;
            direction = Vector3.zero;
            moving = false;
            Player.GetComponent<PlayerKeyDetection>().paused = false;
        }
    }
}
