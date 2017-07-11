/*
    Takes care of the players controls and rotation
    Created by Joshua Corney (joshuacorney2@gmail.com)
    Made 22/11
    Last Edited 23/11
*/

using UnityEngine;
using System;
using UnityEngine.SceneManagement;
using System.Collections;
using System.Collections.Generic;

public class PlayerMovement : MonoBehaviour
{
    public string thisSceneName;
    public float maxSpeed = 10f; // maximum speed can be edited in unity
    public float deathVelocity = 20f; // Speed tha player needs to be moving downwards to die 
    public float jumpHeight = 1f; // Jumping height
    public float distanceForJump = 0.15f; // Distance the player needs to be from the ground to be able to jump again

    [HideInInspector]
    public bool activateButton;
    [HideInInspector]
    public bool inTrigger;
    [HideInInspector]
    public bool canActivateButton;

    private bool _Alive = false;
    [HideInInspector]
    public bool Alive
    {
        get { return _Alive; }
        set { _Alive = value; }
    }

    [HideInInspector]
    public bool notGrounded = false;

    [HideInInspector]
    public float sidewaysMovement;

    [HideInInspector]
    public SavedStats savedStats;
    [HideInInspector]
    public GameObject Player;
    [HideInInspector]
    public GameObject PlayerCamera;
    [HideInInspector]
    public AutofixColliders autofix;
    [HideInInspector]
    public GameObject[] Objects;
    [HideInInspector]
    public CameraSwap camSwap;

    public int rotationValue = 0;
    public int savedRotationValue = 0;

    [HideInInspector]
    public bool rotating = false;
    [HideInInspector]
    public bool onNinety = false;
    [HideInInspector]
    public bool leftRight = false; // left is false, right is true

    public float rotationSpeed = 1;
    public float rotationSnappingPoint = 3f;
    [HideInInspector]
    public Quaternion rotationAngle;
    [HideInInspector]
    public Quaternion rotationObjective;
    [HideInInspector]
    public Vector3 rotationPosition;

    private Rigidbody player;
    private PlayerKeyDetection plyKey;
    public Vector3 velo;

    [Serializable]
    public struct SavedStats
    {
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale;
        public Vector3 camPosition;
        public Quaternion camRotation;
        public Vector3 camScale;

    }

    // Use this for initialization
    void Awake()
    {
        Alive = true;
        Player = this.gameObject;
        camSwap = GameObject.FindGameObjectWithTag("SceneController").GetComponent<CameraSwap>();
        autofix = GameObject.FindGameObjectWithTag("SceneController").GetComponent<AutofixColliders>();
        player = Player.GetComponent<Rigidbody>();
        plyKey = Player.GetComponent<PlayerKeyDetection>();
        PlayerCamera = GameObject.FindGameObjectWithTag("MainCamera");
        player.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
        Objects = GameObject.FindGameObjectsWithTag("CanTransparent");

        activateButton = false;
        canActivateButton = false;

        thisSceneName = SceneManager.GetActiveScene().name;

        //autofix.rotateColliders(true);
    }

    // Update is called once per frame
    void Update()
    {
        if (rotationValue <= 0)
        {
            rotationValue = 4;
        }
        if (rotationValue >= 5)
        {
            rotationValue = 1;
        }

        if ( inTrigger ) {
            gameObject.transform.FindChild("Capsule").gameObject.SetActive(true);
        }
        else if(!inTrigger){
            gameObject.transform.FindChild("Capsule").gameObject.SetActive(false);

        }
        velo = player.velocity;

        if (Alive == false)
        {
            Alive = true;
            
            // Reset the colliders to what they were on save/checkpoint
            rotationValue = savedRotationValue;
            autofix.changeOnDeath();

            // Set the optional camera as the new camera
            camSwap.setTranslateCam(true);

            // Update the optional camera's positon
            camSwap.updateTranslateCamPos(PlayerCamera.transform);

            // Save the cameras start position
            Vector3 Begin = PlayerCamera.transform.position;

            // Set the players position to its spawnpoint
            player.position = savedStats.position;
            camSwap.transformBegin = savedStats.camPosition;
            camSwap.OptionalCamera1.transform.rotation = savedStats.camRotation;
            player.transform.rotation = savedStats.camRotation;
            //Debug.Log("Camera Rotation = " + savedStats.camRotation + " " + "camera postion = " + savedStats.camPosition);

            // Save the cameras end position
            Vector3 EndPoint = savedStats.camPosition;
            //Debug.Log(Begin + " and " + EndPoint + " with a side of " + PlayerCamera.transform.localPosition);

            // Tell the camera where it needs to move to and where to start
            camSwap.SetTranslate(Begin, EndPoint);

            // Tell the camera it can start moving
            camSwap.moving = true;

            this.GetComponent<PlayerKeyDetection>().paused = true;

            player.constraints = RigidbodyConstraints.None;
            player.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            // Player.transform.rotation = rotationObjective;
            player.useGravity = true;
            player.velocity = Vector3.zero;
            Player.GetComponent<CapsuleCollider>().enabled = true;
            rotating = false;
        }

        if (Input.GetKeyUp(KeyCode.L))
        {
            Alive = true;
        }

        if (!rotating && !plyKey.paused && !plyKey.movingCam  && !plyKey.activeSkel)
        {
            if (Input.GetKey(KeyCode.D))
            {
                sidewaysMovement = 1;
            }
            if (Input.GetKey(KeyCode.A))
            {
                sidewaysMovement = -1;
            }
            if (Input.GetKey(KeyCode.D) && Input.GetKey(KeyCode.A))
            {
                sidewaysMovement = 0;
            }
            if (!Input.GetKey(KeyCode.D) && !Input.GetKey(KeyCode.A))
            {
                sidewaysMovement = 0;
            }

            //sidewaysMovement = Input.GetAxis("Horizontal");

            //Debug.Log(Input.GetAxis("Horizontal"));
            Vector3 sidewaysMotion = this.transform.right.normalized * sidewaysMovement;
            Vector3 movement = sidewaysMotion.normalized;
            Vector3 temp = player.velocity;
            temp.x = movement.x * maxSpeed;
            temp.z = movement.z * maxSpeed;
            player.velocity = temp;
        }
    }

    void FixedUpdate()
    {
        rotateWorld();
    }

    void OnDrawGizmos()
    {
        Gizmos.color = Color.red;
        Vector3 pos = this.gameObject.transform.position;
        pos.y -= distanceForJump;
        Gizmos.DrawLine(this.gameObject.transform.position, pos);
    }
    
    public void setSavePos(Vector3 pos, Vector3 rot, Vector3 sca, Vector3 camPos, Quaternion camRot)
    {
        //Debug.Log("SavePos - drop 1");
        player.velocity = Vector3.zero;
        Vector3 tempPos = pos;
        tempPos.y += 0.025f;
        savedStats.position = tempPos;
        savedStats.camPosition = camPos;
        savedStats.camRotation = camRot;
        savedRotationValue = rotationValue;
    }

    // Rotates the players view
    private void rotateWorld()
    {
        if (Mathf.Abs(Mathf.Abs(player.rotation.eulerAngles.y) - Mathf.Abs(rotationObjective.eulerAngles.y)) < rotationSnappingPoint && rotating == true)
        {
            player.position = rotationPosition;

            if (leftRight == false)
            {
                autofix.rotateColliders(true);
            }
            else
            {
                autofix.rotateColliders(false);
            }

            player.constraints = RigidbodyConstraints.None;
            player.constraints = RigidbodyConstraints.FreezeRotationX | RigidbodyConstraints.FreezeRotationY | RigidbodyConstraints.FreezeRotationZ;
            Player.transform.rotation = rotationObjective;
            player.useGravity = true;
            player.velocity = Vector3.zero;
            Player.GetComponent<CapsuleCollider>().enabled = true;
            rotating = false;
        }
        if (Mathf.Abs(Mathf.Abs(player.rotation.eulerAngles.y) - Mathf.Abs(rotationObjective.eulerAngles.y)) > rotationSnappingPoint / 2 && rotating == true && leftRight == true)
        {
            player.position = rotationPosition;

            rotating = true;
            Vector3 rotation = new Vector3(0, rotationSpeed, 0);
            Player.transform.Rotate(rotation);
        }
        else if (Mathf.Abs(Mathf.Abs(player.rotation.eulerAngles.y) - Mathf.Abs(rotationObjective.eulerAngles.y)) > rotationSnappingPoint / 2 && rotating == true && leftRight == false)
        {
            player.position = rotationPosition;

            rotating = true;
            Vector3 rotation = new Vector3(0, -rotationSpeed, 0);
            Player.transform.Rotate(rotation);
        }
    }

    void OnTriggerEnter(Collider col)
    {
        if ( col.gameObject.layer == 11 )
        {
            notGrounded = false;
        }
    }
    void OnTriggerStay(Collider col)
    {
        if (col.gameObject.layer == 11)
        {
            notGrounded = false;
        }
        if(col.gameObject.tag == "MovingPlatform" ) {
            transform.parent = col.transform;
        }
    }
    void OnTriggerExit(Collider col)
    {
        if(col.gameObject.layer == 11)
        {
            notGrounded = true;
        }
        if ( col.gameObject.tag == "MovingPlatform" ) {
            transform.parent = null;
        }
    }
}

