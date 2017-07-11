using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Grounded : MonoBehaviour {
    
    // Use this for initialization
    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Player")  col.GetComponent<PlayerBehaviours>().ChangePlayerState(PlayerBehaviours.PLAYERSTATE.GROUNDED);
    }

    void OnTriggerExit(Collider col)
    {
        if (col.gameObject.tag == "Player") col.GetComponent<PlayerBehaviours>().ChangePlayerState(PlayerBehaviours.PLAYERSTATE.JUMPING);

    }

}
