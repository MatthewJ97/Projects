using UnityEngine;
using System.Collections;
using System.Collections.Generic;


public class CameraControlScript : MonoBehaviour
{
    public List<Info> Command;
    private CameraSwap SceneController;
    int CurrentCommand = 0;
    public Interactable button;
    bool buttonHasTriggered;
    bool doubleSpeed = false;

    [System.Serializable]
    public struct Info
    { 
        public Transform StartAt;
        public Transform MoveTo;
        public float MovementSpeed;
    }


    // Use this for initialization
    void Start ()
    {
        buttonHasTriggered = false;
        if (button == null  || button.objectType != Interactable.InteractiveType.BUTTON)
        {
            Debug.Log("Cameracontrolscript - button is null or not a button");
        }
        SceneController = GameObject.FindGameObjectWithTag("SceneController").GetComponent<CameraSwap>();
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetKeyDown(KeyCode.Space) && doubleSpeed == false)
        {
            doubleSpeed = true;
            SceneController.setCamSpeed(Command[CurrentCommand].MovementSpeed * 2);
        }

        if (button.getTriggered() && buttonHasTriggered == false)
        {
            if (CurrentCommand < Command.Count)
            {
                Rigidbody referance = GameObject.FindGameObjectWithTag("Player").GetComponent<Rigidbody>();
                Vector3 vel = referance.velocity;
                vel.z = 0;
                vel.x = 0;
                referance.velocity = vel;
                



                if (GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerKeyDetection>().movingCam != true)
                {
                    GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerKeyDetection>().movingCam = true;
                }

                if (SceneController.moving == false)
                {
                    GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerKeyDetection>().movingCam = true;
                    SceneController.swapToOptionalCam(1);
                    SceneController.updateTranslateCamPos(Command[CurrentCommand].StartAt);
                    SceneController.SetTranslate(Command[CurrentCommand].StartAt.position, Command[CurrentCommand].MoveTo.position);
                    SceneController.setCamSpeed(Command[CurrentCommand].MovementSpeed);
                    SceneController.moving = true;
                    CurrentCommand++;
                }
            }
            if (CurrentCommand >= Command.Count && SceneController.moving == false)
            {
                GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerKeyDetection>().movingCam = false;
                buttonHasTriggered = true;
                CurrentCommand = 0;
            }
        }

    }
}
