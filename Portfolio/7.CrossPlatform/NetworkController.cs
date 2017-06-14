using System;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class NetworkController : NetworkManager {
    //THE CLIENT OBJECT ON THE CLIENT
    public client Client;
    
    public OverrideNetworkDiscovery disco;
    //THE DEFAULT IPADDRESS FOR THE NETWORK CONTROLLER
    string ipAddress = "localhost";
    //BOOL TO CHECK IF THIS IS A SERVER APPLICATION OR 
    //CLIENT APPLICATION NEEDS TO BE SET BY THE DEVELOPER
    [SerializeField]
    bool isServer;

    public bool IsServer
    {
        get
        {
            return isServer;
        }
    }
    public string IPAddress
    {
        get
        {
            return ipAddress;
        }
        set
        {
            ipAddress = value;
        }
    }
    public void Start()
    {
        if (isServer)
        {
            //INITIALISE THE BROADCAST FOR THE SERVER
            disco.Initialize();
            disco.StartAsServer();
            StartupHost();
        }
        else {
            //INITIALISE THE LISTEN FOR THE CLIENT
            disco.Initialize();
            //disco.StartAsClient();
        }
        disco.showGUI = false;
    }
    //STARTUP THE HOST AND SET THE IPADDRESS AND PORT BEFORE STARTING THE SERVER 
    public void StartupHost()
    {        
        SetIPAddress();
        SetPort();
        singleton.StartServer();
    }
    //JOIN GAME SETS THE IPADDRESS TO IPADDRESS AND THE PORT BEFORE START THE CLIENT AND TRYING TO CONNECT
    public void JoinGame(client a_client)
    {
        SetIPAddress();
        SetPort();
        singleton.StartClient();        
    }
    //SET THE IPADDRESS
    void SetIPAddress()
    {
        singleton.networkAddress = ipAddress;
    }
    //SETS THE PORT
    void SetPort()
    {
        singleton.networkPort = 7777;
    }

   // WHEN THE CLIENT CONNECTS THE CLIENT CONNECT VARIABLE IS SET TRUE
    public override void OnClientConnect(NetworkConnection conn) {
        base.OnClientConnect(conn);
        Client.clientConnected = true;
    }
    //ON DISCONNECT FROM SERVER THE APPLICATION QUITS.
    public override void OnClientDisconnect(NetworkConnection conn)
    {
        base.OnClientDisconnect(conn);
        Application.Quit();
    }

}

