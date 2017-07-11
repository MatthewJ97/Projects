using UnityEngine;
using System.Collections;

public class FollowScript : MonoBehaviour
{
    public GameObject player;
	// Use this for initialization
	void Start ()
    {
        player = GameObject.Find("Player");
	}
	
	// Update is called once per frame
	void Update ()
    {
        transform.position = player.transform.position;
        transform.rotation = player.transform.rotation;
	}
}
