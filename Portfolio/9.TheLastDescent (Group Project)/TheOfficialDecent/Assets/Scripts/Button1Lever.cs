using UnityEngine;
using System.Collections;

public class Button1Lever : MonoBehaviour {

    bool initialFix = false;
    public float initFixTime = 0.5f;
    float initFixCurTime = 0;
    [SerializeField]
    bool lever;
    [SerializeField]
    bool toggle;
    [SerializeField]
    bool triggered;
    [SerializeField]
    bool active;
    public GameObject Player;
    public PlayerCapsule ActivObject;


    //public bool one = false;
    //public bool two = false;
    void Awake( ) {
        if ( lever ) {
            toggle = true;
        }
        Player = GameObject.Find("Player");
        ActivObject = Player.transform.FindChild("Capsule").gameObject.GetComponent<PlayerCapsule>();
    }
    void Update( ) {    // If the button is being collided by the player

        if ( active ) {
            Debug.Log("Button is active");
            // if the player can activate the button from its script ( required to be able to press F and have a response)
            if ( Player.GetComponent<PlayerMovement>().activateButton == true ) {
                initialFix = false;
                initFixCurTime = 0;
                ActivObject.SetOn();
                Debug.Log("button has been activated");

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
                Debug.Log("button feedback");
                initFixCurTime += Time.deltaTime;

                if ( initFixCurTime >= initFixTime ) {
                    ActivObject.SetOff();
                    initialFix = true;
                }
            }
        }
    }


    void OnTriggerEnter(Collider col)
    {
        // Lets the button activate
        if ( col.gameObject.tag == "Player" )
        {
            active = true;
            Player.transform.FindChild("Capsule").gameObject.SetActive(true);

            // The player can now press F to activate the buttons
            Player.GetComponent<PlayerMovement>().canActivateButton = true;
            Player.GetComponent<PlayerMovement>().inTrigger = true;
        }
    }
    void OnTriggerExit( Collider col) {
        // Stops the button from activating
        if ( col.gameObject.tag == "Player" ) {

            active = false;
            // removes the model from the player
            Player.transform.FindChild("Capsule").gameObject.SetActive(false);
            //if()
            Player.GetComponent<PlayerMovement>().inTrigger = false;
        }
        // the player now cant press F to activate the buttons
        // Player.GetComponent<PlayerMovement>().canActivateButton = false;
        ///Debug.Log("Neither collision is active");
    }



    public bool getTriggered() { return triggered; }
    public void setTriggered(bool aTriggered)
    {
        triggered = aTriggered;
    }
}
