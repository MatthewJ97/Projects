using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using System.Collections;
using System.Collections.Generic;

public class Interactable : MonoBehaviour {
    public Text textDisplay;
    public GameObject player;

    [SerializeField]
    bool triggered = false;
    float position = 0;

    //Vcheckpoint variables V

    //^^                   ^^
    [Header("Type Of Object")]
    public InteractiveType objectType;

    [Header("Checkpoint Variables")]
    public SpawnLocation spLoc;
    [HideInInspector]
    public bool saved = false;

    [Header("Button Variables")]
    public float initFixTime = 0.5f;
    bool initialFix = false;
    float initFixCurTime = 0;
    [SerializeField]
    bool lever;
    [SerializeField]
    public bool toggle;
    public bool wasTriggered;
    public PlayerCapsule ActivObject;

    [Header("Door Variables")]
    public float doorLowerSpeed = 0f;
    public float doorRiseSpeed = 0f;
    public float doorBaseHeight = 0;
    public float doorRiseHeight = 0f;
    bool finished = false;
    bool active = false;
    // ^^             ^^
    [Header("Fan Variables")]
    public float fanUpwardsForce;
    public float fanDownwardsForce;
    public GameObject CollisionBox1;
    public GameObject CollisionBox2;
    private bool one;
    private bool two;

    [Header("MovingPlats Variables")]
    [SerializeField]
    Transform platform;
    [SerializeField]
    Transform startTransform;
    [SerializeField]
    Transform endTransform;
    [SerializeField]
    float platformSpeed;
    [SerializeField]
    bool finishedMovement = false;
    public bool nothingBlocking = true;
    public bool isTogglePlatform = false;
    Vector3 direction;
    Transform destination;

    [Serializable]
    public struct SpawnLocation {
        public Vector3 position;
        public Vector3 rotation;
        public Vector3 scale;
        public Vector3 camPos;
        public Quaternion camRot;
    }
    GameObject mCamera;
    [Header("Skeleton Variables")]
    public bool isTriggerSkel;
    [SerializeField]
    String skeletonText;
    [Header("??? Variables")]
    public Vector3 velocity;
    public bool isURLGrab = false;
    bool URLGrabDone = false;

    public enum InteractiveType {
        DOOR = 1,
        SPIKETRAP,
        BALL,
        BUTTON,
        CHECKPOINT,
        DEATHBOX,
        FAN,
        MOVINGPLATFORM,
        SKELETON,
        Temp
    }


    // ^                        ^
    public bool isFinish = false;
    public int nextLevel;
    void Awake( ) {
        mCamera = GameObject.FindGameObjectWithTag("MainCamera");
        player = GameObject.FindGameObjectWithTag("Player");
        position = this.transform.position.y;
        if ( objectType == InteractiveType.DOOR ) {
            doorBaseHeight = this.transform.position.y;
        }
        if ( objectType == InteractiveType.DEATHBOX ) {
            triggered = true;
        }
        if ( objectType == InteractiveType.BUTTON ) {
            if ( lever ) {
                toggle = true;
            }
            ActivObject = player.transform.FindChild("Capsule").gameObject.GetComponent<PlayerCapsule>();
        }
        if ( objectType == InteractiveType.CHECKPOINT ) {
            spLoc.position = GetComponentInChildren<Transform>().position;
            spLoc.rotation = GetComponentInChildren<Transform>().rotation.eulerAngles;
            spLoc.scale = GetComponentInChildren<Transform>().localScale;
        }
        if ( objectType == InteractiveType.MOVINGPLATFORM ) {
            SetDestination(startTransform);
        }
        if ( objectType == InteractiveType.SKELETON ) {
            textDisplay = GameObject.FindGameObjectWithTag("TextDisplay").transform.FindChild("Text").GetComponent<Text>();
        }
    }

    void OnDrawGizmos( ) {
        if ( objectType == InteractiveType.BALL ) {
            Gizmos.color = Color.magenta;
            Gizmos.DrawWireCube(spLoc.position, spLoc.scale);
        }
        if ( objectType == InteractiveType.MOVINGPLATFORM ) {
            Gizmos.color = Color.green;
            Gizmos.DrawWireCube(startTransform.position, platform.localScale);

            Gizmos.color = Color.red;
            Gizmos.DrawWireCube(endTransform.position, platform.localScale);
        }
        if ( objectType == InteractiveType.CHECKPOINT ) {
            Gizmos.color = Color.red;
            Gizmos.DrawWireCube(spLoc.camPos, new Vector3(1, 1, 1));
        }
    }

    // Update is called once per frame
    void Update( ) {
        if ( CollisionBox1 != null && CollisionBox2 != null && objectType != InteractiveType.FAN ) {
            one = CollisionBox1.gameObject.GetComponent<ButtonColliders>().triggerActive;
            two = CollisionBox2.gameObject.GetComponent<ButtonColliders>().triggerActive;
            if ( one || two ) {
                triggered = true;
            }
            else {
                triggered = false;
            }
        }
        else {
            //do nothing
        }
        if ( objectType == InteractiveType.DOOR ) {
            velocity = this.GetComponent<Rigidbody>().velocity;
        }

        // Has the object finished its task?
        if ( finished == true && active == false ) {
            //Debug.Log("Finished");
            finished = false;
        }

        switch ( objectType ) {
            case InteractiveType.DOOR:
                Door(triggered);
                break;
           
        }
        if ( objectType == InteractiveType.BUTTON ) {
            if ( active ) {
                //Debug.Log("Button is active");
                // if the player can activate the button from its script ( required to be able to press F and have a response)
                if ( player.GetComponent<PlayerMovement>().activateButton == true ) {
                    initialFix = false;
                    initFixCurTime = 0;
                    ActivObject.SetOn();
                    //Debug.Log("button has been activated");

                    if ( toggle ) // currently always true
                    {
                        ///Debug.Log("Toggle == True");
                        triggered = !triggered;
                    }
                    else if ( !triggered ) {
                        ///Debug.Log("Toggle == False");
                        triggered = true;

                    }
                    //Debug.Log("button was pressed.");
                    //connect function to activate things
                }
                if ( initFixCurTime < initFixTime && initialFix == false ) {
                    //Debug.Log("button feedback");
                    initFixCurTime += Time.deltaTime;

                    if ( initFixCurTime >= initFixTime ) {
                        ActivObject.SetOff();
                        initialFix = true;
                    }
                }
            }
        }
        if ( objectType == InteractiveType.SKELETON ) {
            if ( active ) {
                if ( player.GetComponent<PlayerMovement>().activateButton == true || isTriggerSkel ) {
                    player.GetComponent<PlayerKeyDetection>().activeSkel = true;
                    textDisplay.text = skeletonText;
                    if ( isTriggerSkel ) {
                        isTriggerSkel = false;
                    }
                }
            }
        }
            if ( objectType == InteractiveType.BALL ) {


        }

        if ( objectType == InteractiveType.FAN && triggered ) {
            if ( CollisionBox1.GetComponent<ButtonColliders>().triggerActive == true ) {
                Debug.Log("Fan - Adding Velocity - 1");

                // Applying Velocity
                player.GetComponent<Rigidbody>().velocity += this.transform.up * fanUpwardsForce;
            }
            if ( CollisionBox2.GetComponent<ButtonColliders>().triggerActive == true ) {
                Debug.Log("Fan - Adding Velocity - 2");

                // Applying Velocity
                player.GetComponent<Rigidbody>().velocity += -this.transform.up * fanDownwardsForce;
            }
        }
    }

    void SwapMovementDestination( ) {
        finishedMovement = false;
        SetDestination(destination == startTransform ? endTransform : startTransform);
    }

    void SwapMovementDestination(bool awap) {
        finishedMovement = false;
        SetDestination(awap == startTransform ? endTransform : startTransform);
    }

    void FixedUpdate( ) {
        if ( objectType == InteractiveType.MOVINGPLATFORM ) {
            if ( isTogglePlatform == true ) {
                //Debug.Log("moving platform is toogle");
                if ( finishedMovement == false ) {
                    //Debug.Log("moving platform is false");

                    if ( nothingBlocking == true ) {
                        //Debug.Log("moving platform is not blocked");

                        platform.GetComponent<Rigidbody>().MovePosition(platform.transform.position + direction * platformSpeed * Time.fixedDeltaTime);
                    }
                    if ( Vector3.Distance(platform.position, destination.position) < platformSpeed * Time.deltaTime ) {
                        //Debug.Log("moving platform is true");

                        finishedMovement = true;
                    }
                }
            }

            else {
                if ( nothingBlocking == true ) {
                    platform.GetComponent<Rigidbody>().MovePosition(platform.transform.position + direction * platformSpeed * Time.fixedDeltaTime);
                }

                if ( Vector3.Distance(platform.position, destination.position) < platformSpeed * Time.fixedDeltaTime ) {
                    SetDestination(destination == startTransform ? endTransform : startTransform);
                }
            }
        }
    }

    void SetDestination(Transform dest) {
        destination = dest;
        Vector3 dir;
        dir = ( destination.position - platform.position );
        dir = dir.normalized;
        direction = dir;
    }

    public void Triggered( ) {
        if ( objectType == InteractiveType.MOVINGPLATFORM ) { SwapMovementDestination(); }
        triggered = !triggered;
    }

    public void Triggered(bool aTrigger) {
        if ( objectType == InteractiveType.MOVINGPLATFORM && aTrigger != triggered ) { SwapMovementDestination(aTrigger); }
        triggered = aTrigger;

    }

    public bool getTriggered( ) { return triggered; }


    public void setTriggered(bool aTriggered) {

        if ( triggered != aTriggered ) {
            wasTriggered = true;
            triggered = aTriggered;
        }

    }

    void OnTriggerEnter(Collider col) {
        if ( col.gameObject.tag == "Player" ) {
            PlayerMovement playerM = col.gameObject.GetComponent<PlayerMovement>();
            #region SpikeTrap

            // If spike trap
            if ( objectType == InteractiveType.SPIKETRAP ) {
                // Killing the player
                playerM.Alive = false;
            }
            #endregion
            #region BALL
            if ( objectType == InteractiveType.BALL ) {
                active = true;

            }
            #endregion
            #region CheckPoint

            // If checkpoint
            if ( objectType == InteractiveType.CHECKPOINT && saved == false && !isFinish ) {
                saved = true;
                spLoc.camPos = mCamera.transform.position;
                spLoc.camRot = mCamera.transform.rotation;
                // Setting the save position to that of a saved transform
                playerM.setSavePos(spLoc.position, spLoc.rotation, spLoc.scale, spLoc.camPos, spLoc.camRot);
            }
            #endregion

            #region Finish
            else if ( objectType == InteractiveType.CHECKPOINT && isFinish && triggered ) {
                SceneManager.LoadScene(nextLevel);

                if ( isURLGrab && URLGrabDone == false ) {
                    URLGrabDone = true;
                    Application.OpenURL("https://goo.gl/forms/X7Yi0CsRnEICUmfn1");
                }
            }
            #endregion
            #region DeathBox 
            // If death box
            if ( objectType == InteractiveType.DEATHBOX || objectType == InteractiveType.SPIKETRAP ) {
                Debug.Log("Deathbox");
                if ( triggered ) {
                    // Killing the player
                    playerM.Alive = false;
                }
            }
            #endregion

        }
    }

    void OnTriggerStay(Collider col) {
        #region Button
        if ( objectType == InteractiveType.BUTTON || objectType == InteractiveType.SKELETON ) {
            if (col.gameObject.tag == "Player")
            {
                active = true;
                // The player can now press F to activate the buttons
                player.GetComponent<PlayerMovement>().canActivateButton = true;
                player.GetComponent<PlayerMovement>().inTrigger = true;
            }
        }
        #endregion
    }
    void OnTriggerExit(Collider col) {
        if ( objectType == InteractiveType.BALL ) {
            if ( col.gameObject.tag != "Player" ) {
                Vector3 vel = this.GetComponent<Rigidbody>().velocity;
                vel.x = 0;
                vel.z = 0;
                this.GetComponent<Rigidbody>().velocity = vel;
            }
        }
        if (objectType == InteractiveType.BUTTON || objectType == InteractiveType.SKELETON)
        {
            if (col.gameObject.tag == "Player")
            {
                active = false;
                player.GetComponent<PlayerMovement>().inTrigger = false;
            }
        }
    }

    void Door(bool aTrigger) {
        if ( aTrigger == true ) {
            finished = false;
            active = true;

            if ( position < doorRiseHeight ) {
                position = this.transform.position.y;
                position += doorRiseSpeed;
                Vector3 pos = this.transform.position;
                pos.y = position;
                this.transform.position = pos;
            }
            // When the door is finished opening
            if ( position > doorRiseHeight ) {
                position = this.transform.position.y;
                position = doorRiseHeight;
                Vector3 pos = this.transform.position;
                pos.y = position;
                this.transform.position = pos;
            }

            if ( ( position > doorRiseHeight || position == doorRiseHeight ) && finished == false && active == true ) {
                active = false;
                finished = true;
            }
        }
        else {
            finished = false;
            active = true;
            if ( position > doorBaseHeight ) {
                position = this.transform.position.y;
                position -= doorLowerSpeed;
                Vector3 pos = this.transform.position;
                pos.y = position;
                this.transform.position = pos;
            }


            if ( position < doorBaseHeight ) {
                position = doorBaseHeight;
                Vector3 pos = this.transform.position;
                pos.y = position;
                this.transform.position = pos;
            }

            if ( ( position > doorBaseHeight || position == doorBaseHeight ) && finished == false && active == true ) {
                active = false;
                finished = true;
            }
        }
    }

    //void SkeletonAct(bool aTrigger) {
    //    if ( active ) {
    //        if ( player.GetComponent<PlayerMovement>().activateButton == true ) {
    //            player.GetComponent<PlayerKeyDetection>().activeSkel = true;
    //            textDisplay.text = skeletonText;
    //        }
    //    }
    //}
}


