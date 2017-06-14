using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class Player : NetworkBehaviour
{

    //To sync a Varaible they must have the syncvar attribute (there are some limitations)
    //when assigning variables that are syncvar if it is done client side it will be overwritten by the server, use a 
    //function with the command attribute to overcome this. Command functions pass arguments from the client to the server 
    //then performs the function on the server which will update any syncvar variables you have changed inside this function 
    #region Account Variables
    [SyncVar]
    [SerializeField]
    public string Username = "newUser";
    [SyncVar]
    [SerializeField]
    string PassWord = "assdas";
    [SyncVar]
    public int score = 0;
    string IP = "10.0.0.94";
    [SerializeField]
    bool accountNotCreated = true;
    #endregion 
    [SerializeField]
    client clientManager;
    public List<Texture> selectionButtons;
    [SerializeField]
    GUISkin thisSkin;
    [SyncVar]
    public bool confirmedSelection;
    public enum selection
    {
        ROCK, PAPER, SCISSORS, NOT_SELECTED
    }
    [SyncVar]
    public selection playerSelection = selection.NOT_SELECTED;

    void Awake () {
        //IF THIS IS NOT THE LOCAL PLAYER THAN WE WANT IT TO add itself to the servers list than RETURN 
        //since the gamemanager only exists on the server than it wont be found on the other clients 
        clientManager = GameObject.Find("ClientManager").GetComponent<client>();
        if ( !isLocalPlayer ) {
            if ( GameObject.Find("ServerManager") != null )
                GameObject.Find("ServerManager").GetComponent<Server>().AddPlayer(this);
            return;

        }
        
        //USE THIS CHECK TO LOCALISE ACTIONS IN THE SCRIPT
        if ( isLocalPlayer ) {
            clientManager.LocalPlayer = this;

            //EXAMPLE OF A CHECK FOR CREATING AN ACCOUNT
            if ( clientManager.accountCreated ) {
                //THIS COMMAND SENDS THE ACCOUNT INFORMATION ACROSS THE NETWORK TO THE SERVER OBJECT.
                CmdAddAccount(clientManager.tempAccount.Username, clientManager.tempAccount.Password);
            }
            else {
                accountNotCreated = true;
            }
        }
        //
        playerSelection = selection.NOT_SELECTED;
	}

    // Update is called once per frame
    void Update( ) {
        //IF THIS IS NOT THE LOCAL PLAYER THAN WE WANT IT TO RETURN 
        if ( !isLocalPlayer ) { return; }

        if ( accountNotCreated && 
            clientManager.accountCreated 
            && isLocalPlayer ) {
            accountNotCreated = false;
            CmdAddAccount(clientManager.tempAccount.Username, clientManager.tempAccount.Password);

        }
        if ( isLocalPlayer ) {
            //CODE FOR THE SCISSORS PAPER ROCK GAME
            // THIS CAN BE REPLACED WITH YOUR OWN CODE FOR THE LOCAL PLAYER
            if ( playerSelection != selection.NOT_SELECTED ) {
                if ( Input.GetKey(KeyCode.A) ) CmdMakeSelection(0);
                if ( Input.GetKey(KeyCode.D) ) CmdMakeSelection(1);
                if ( Input.GetKey(KeyCode.S) ) CmdMakeSelection(2);
            }
        }
    }

    void OnGUI()
    {//the gui for the game
        if (!isLocalPlayer) return;
        GUILayout.Label(Username + "'s Score: " + score);
        GUI.Label(new Rect(0 + Screen.width * 0.05f, Screen.height * 0.2f, Screen.width * 0.9f, 200), ("Your Selection  is " + playerSelection.ToString()), thisSkin.label);
        if ( !confirmedSelection ) {
            if ( GUI.Button(new Rect(Screen.width * 0.3f * 0 + Screen.width * 0.05f, Screen.height * 0.4f, Screen.width * 0.3f, Screen.height * 0.4f), selectionButtons[0]) ) {
                CmdMakeSelection(0);
                CmdConfirmSelection(true);
            }
            if ( GUI.Button(new Rect(Screen.width * 0.3f * 1 + Screen.width * 0.05f, Screen.height * 0.4f, Screen.width * 0.3f, Screen.height * 0.4f), selectionButtons[1]) ) {
                CmdMakeSelection(1);
                CmdConfirmSelection(true);

            }
            if ( GUI.Button(new Rect(Screen.width * 0.3f * 2 + Screen.width * 0.05f, Screen.height * 0.4f, Screen.width * 0.3f, Screen.height * 0.4f), selectionButtons[2]) ) {
                CmdMakeSelection(2);
                CmdConfirmSelection(true);

            }
        }
    }
    //example Command functions that send data from the client to the server
    [Command]
    public void CmdAddAccount(string userName, string aPassword) {
        Username = userName;
        PassWord = aPassword;

    }
    [Command]
    public void CmdMakeSelection(int aSelection) {
        playerSelection = (selection)aSelection;
    }

    [Command]
    public void CmdConfirmSelection(bool aBool ) {
        confirmedSelection = aBool;
    }
}
