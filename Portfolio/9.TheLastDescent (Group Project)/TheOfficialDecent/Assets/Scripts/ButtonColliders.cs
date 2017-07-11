using UnityEngine;
using System.Collections;

public class ButtonColliders : MonoBehaviour {
    public bool triggerActive;
    [HideInInspector]
    public GameObject player;
    public GameObject collision;
	// Use this for initialization
	void Awake () {
        player = GameObject.Find("Player");
        triggerActive = false;
	}
	
	void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Player")
        {
            player.GetComponent<PlayerMovement>().inTrigger = true;
            triggerActive = true;
            collision = col.gameObject;
        }
    }

    void OnTriggerExit(Collider col)
    {
        if (col.gameObject.tag == "Player")
        {
            player.GetComponent<PlayerMovement>().inTrigger = false; 
            triggerActive = false;
            collision = null;

        }
    }
}
