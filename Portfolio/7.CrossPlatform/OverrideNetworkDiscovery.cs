using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;


public class OverrideNetworkDiscovery : NetworkDiscovery {
    public List<string> BroadcastAddress;
    public override void OnReceivedBroadcast(string fromAddress, string data) {
        if (!BroadcastAddress.Contains(fromAddress))
        {
            BroadcastAddress.Add(fromAddress);
        }

    }

}
