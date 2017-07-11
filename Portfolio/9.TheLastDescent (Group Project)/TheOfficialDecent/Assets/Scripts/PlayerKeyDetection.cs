/*
    Takes care of all button presses for the player
    Created by Joshua Corney (joshuacorney2@gmail.com)
    Made 22/11
    Last Edited 23/11
*/

using UnityEngine;
using UnityEngine.UI;
using System.Collections;

public class PlayerKeyDetection : MonoBehaviour
{
    Text textDisplay;
    PlayerMovement playerCon;
    AutofixColliders autofix;
    CameraSwap camSwap;
    Rigidbody player;
    Animator anim;

    public bool rotationLocked = false;
    public GameObject Model;
    public bool jumping;
    bool Alive;
    public bool movingCam = false;
    bool rotating;
    public bool notGrounded;
    public bool activeSkel;
    public bool paused;
    public bool FinishingMovemenet;
    float lastVelY;
    // Use this for initialization
    void Start ()
    {
        textDisplay = GameObject.FindGameObjectWithTag("TextDisplay").transform.FindChild("Text").GetComponent<Text>();
        if(textDisplay == null)
        {
            Debug.Log("td == null - pkd");
        }
        //paused = true;
        camSwap = GameObject.FindGameObjectWithTag("SceneController").GetComponent<CameraSwap>();
        if (camSwap == null)
        {
            Debug.Log("cS == null - pkd");
        }
        autofix = GameObject.FindGameObjectWithTag("SceneController").GetComponent<AutofixColliders>();
        if (autofix == null)
        {
            Debug.Log("autofix == null - pkd");
        }
        anim = GameObject.Find("Character_model").GetComponent<Animator>();
        if (anim == null)
        {
            Debug.Log("anim == null - pkd");
        }
        player = this.GetComponent<Rigidbody>();
        if (player == null)
        {
            Debug.Log("pRidgid == null - pkd");
        }
        playerCon = this.GetComponent<PlayerMovement>();
        if (playerCon == null)
        {
            Debug.Log("plaMove == null - pkd");
        }
    }

    // Update is called once per frame
    void Update()
    {
        Alive = playerCon.Alive;
        notGrounded = playerCon.notGrounded;
        rotating = playerCon.rotating;
        #region Controls
        if (paused == false)
        {
            if (!activeSkel)
            {
                anim.SetBool("SkeletonChat", false);
                textDisplay.text = "";
                textDisplay.transform.parent.gameObject.SetActive(false);
            }
            else if (activeSkel)
            {
                anim.SetBool("SkeletonChat", true);
                textDisplay.transform.parent.gameObject.SetActive(true);
                Vector3 Vel = player.velocity;
                Vel.x = 0;
                Vel.z = 0;
                player.velocity = Vel;
                if (Input.GetKeyDown(KeyCode.LeftAlt))
                {
                    activeSkel = false;
                }
            }
            if (rotating == false && Alive == true && movingCam == false && activeSkel == false)
            {

                if ((Input.GetKey(KeyCode.A) == false) && (Input.GetKey(KeyCode.D) == false))
                {
                    Vector3 Vel = player.velocity;
                    Vel.x = 0;
                    Vel.z = 0;
                    player.velocity = Vel;
                }

                if (Input.GetKey(KeyCode.A))
                {
                    Quaternion tempQ = new Quaternion();
                    tempQ.eulerAngles = new Vector3(0, 270, 0);

                    Model.transform.localRotation = tempQ;
                }
                if (Input.GetKey(KeyCode.D))
                {
                    Quaternion tempQ = new Quaternion();
                    tempQ.eulerAngles = new Vector3(0, 90, 0);

                    Model.transform.localRotation = tempQ;
                }
                if (rotationLocked == false)
                {
                    // If the player tries to rotate to the left
                    if (Input.GetKey(KeyCode.Q) && rotating == false)
                    {
                        playerCon.rotationValue--;
                        autofix.decreaseRotation();
                        playerCon.rotationPosition = player.position;
                        camSwap.turnedNinety = !camSwap.turnedNinety;
                        Vector3 nullVelocity = Vector3.zero;

                        playerCon.rotationAngle = player.rotation;
                        Vector3 tempQ1 = player.rotation.eulerAngles;
                        Vector3 tempQ2 = new Vector3(0, 90, 0);
                        Vector3 tempQ3;

                        tempQ3.x = tempQ1.x + tempQ2.x;
                        tempQ3.y = tempQ1.y + tempQ2.y;
                        tempQ3.z = tempQ1.z + tempQ2.z;

                        playerCon.rotationObjective.eulerAngles = tempQ3;

                        player.velocity = nullVelocity;
                        player.useGravity = false;
                        player.GetComponent<CapsuleCollider>().enabled = false;
                        playerCon.rotating = true;
                        playerCon.leftRight = true;
                        playerCon.onNinety = !playerCon.onNinety;

                    }

                    // If the player tries to rotate to the right
                    if (Input.GetKey(KeyCode.E) && rotating == false)
                    {
                        playerCon.rotationValue++;
                        autofix.increaseRotation();
                        playerCon.rotationPosition = player.position;
                        camSwap.turnedNinety = !camSwap.turnedNinety;
                        Vector3 nullVelocity = Vector3.zero;

                        playerCon.rotationAngle = player.rotation;
                        Vector3 tempQ1 = player.rotation.eulerAngles;
                        Vector3 tempQ2 = new Vector3(0, -90, 0);
                        Vector3 tempQ3;

                        tempQ3.x = tempQ1.x + tempQ2.x;
                        tempQ3.y = tempQ1.y + tempQ2.y;
                        tempQ3.z = tempQ1.z + tempQ2.z;

                        playerCon.rotationObjective.eulerAngles = tempQ3;

                        player.velocity = nullVelocity;
                        player.useGravity = false;
                        player.GetComponent<CapsuleCollider>().enabled = false;
                        playerCon.rotating = true;
                        playerCon.leftRight = false;
                        playerCon.onNinety = !playerCon.onNinety;
                    }
                }
                // If the player is on the ground then jump when space is pressed
                if (Input.GetKeyDown(KeyCode.Space) && rotating == false && jumping == false && notGrounded == false)
                {
                    jumping = true;
                    player.velocity = Vector3.up * playerCon.jumpHeight;
                    playerCon.notGrounded = true;
                }

                if (player.velocity.y == lastVelY && notGrounded == false)
                {
                    jumping = false;
                }

                // If the player tries to activate a button when they have the ability to use one
                if (Input.GetKeyUp(KeyCode.F) && playerCon.canActivateButton && movingCam == false)
                {
                    playerCon.activateButton = true;
                }
                else
                {
                    playerCon.activateButton = false;
                }
            }


            lastVelY = player.velocity.y;
        }
        #endregion

        if (Input.GetKey(KeyCode.Escape))
        {
            paused = !paused;
        }

        anim.SetBool("Jumping", jumping);
        anim.SetBool("NotGrounded", notGrounded);
        anim.SetBool("FinishingMovement", FinishingMovemenet);
        anim.SetFloat("Velocity", playerCon.sidewaysMovement);
        
    }
}
