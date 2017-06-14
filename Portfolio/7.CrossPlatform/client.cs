using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class client : NetworkBehaviour {
    //ERROR MESSAGE THAT DISPLAYS ISSUES TO THE USER 
    string errorMessage;
    //ACCOUNT CREATED CHECK
    public bool accountCreated = false;
    //CLIENT CONNECTED CHECK THIS IS SET WHEN CONNECTED TO THE SERVER
    public bool clientConnected = false;
    //THE PLAYER OBJECT FOR THE CLIENT
    Player localPlayer;
    public Player LocalPlayer {
        get
        {
            return localPlayer;
        }
        set
        {
            localPlayer = value;
        }
    }
    //THE NETWROK CONTROLLER FOR THIS CLIENT
    public NetworkController thisNetworkCon;
    /////////////////////////////////////////
    //STRINGS USED BY THE LOGIN MENU
    string accountUser = "newUser";
    string accountPass = "gkgbkb";
    string accountIp = "10.0.0.94";
    /////////////////////////////////////////
    //ACCOUNT CREATED FOR THE USER
    public Account tempAccount;
    public GUISkin thisSkin;
    void OnGUI( )
    ///////////////////////////////////////////////////////////////
    //LOGIN GUI
    {
        //CHECKS IF THIS OBJECT IS ACTIVE ON THE SERVER
        if ( !isServer ) {
            //CHECKS IF THE ACCOUNT IS CREATED
            if ( !accountCreated ) {
                GUILayout.BeginArea(new Rect(( Screen.width / 2.0f ) - ( Screen.width * 0.33f ), 0, ( Screen.width * 0.66f ), Screen.height * 0.8f));
                GUILayout.Label("Username", thisSkin.label);
                accountUser = GUILayout.TextField(accountUser, thisSkin.textField);
                GUILayout.Label("Password", thisSkin.label);

                accountPass = GUILayout.PasswordField(accountPass, '*', thisSkin.textField);
                GUILayout.Label("IpAddress", thisSkin.label);

                accountIp = GUILayout.TextField(accountIp, thisSkin.textField);
                GUILayout.Label(errorMessage, thisSkin.label);
                if ( GUILayout.Button("Login", thisSkin.button) ) {
                    if ( accountPass.Length >= 5 ) {

                        tempAccount = new Account(accountUser, accountPass);
                        accountCreated = true;
                        errorMessage = "";
                        thisNetworkCon.IPAddress = accountIp;
                        //CONNECTS THE CLIENT TO THE ACCOUNTIP (IF POSSIBLE)
                        thisNetworkCon.JoinGame(this);

                    }
                    else if ( accountPass.Length < 5 ) {
                        errorMessage = "password must be 5 or more characters";
                    };
                }
                GUILayout.EndArea();
            }
            //ALLOWS FOR THE CLIENT NO TO CONNECT YET KEEP IT DATA 
            GUILayout.BeginArea(new Rect(( Screen.width / 2.0f ) - ( Screen.width * 0.33f ), Screen.height / 12.0f * 7, ( Screen.width * 0.33f ), Screen.height / 2.0f));
            if ( accountCreated && !clientConnected ) {
                GUILayout.Label(tempAccount.Username, thisSkin.label);
                GUILayout.Label(tempAccount.ID.ToString(), thisSkin.label);
                accountIp = GUILayout.TextField(accountIp, thisSkin.textField);
                //CONNECTS THE CLIENT IF POSSIBLE
                if ( GUILayout.Button("Login", thisSkin.button) ) {
                    thisNetworkCon.StopClient();
                    thisNetworkCon.IPAddress = accountIp;
                    thisNetworkCon.JoinGame(this);

                }
                if ( GUILayout.Button("Change User\n Logout", thisSkin.button) ) {
                    accountCreated = false;
                    accountPass = "";

                }
            }
            //PRINTS OUT TO THE SCREEN A LISTEN OF ALL BROADCAST GAME IP ADDRESSES
            if ( !clientConnected ) {
                GUILayout.Label("Available IPAddress", thisSkin.label);
                if ( thisNetworkCon.disco.BroadcastAddress.Count > 0 ) {
                    for ( int i = 0; i < thisNetworkCon.disco.BroadcastAddress.Count; i++ ) {
                        GUILayout.Label(thisNetworkCon.disco.BroadcastAddress[i], thisSkin.label);
                    }
                }

            }
                GUILayout.EndArea();
        }
    }
    //////////////////////////////////////////////////////////////////

}
