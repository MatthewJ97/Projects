using UnityEngine;
using System.Collections;

public class PlayerCapsule : MonoBehaviour {
    [SerializeField]
    public Material capColour;
    [SerializeField]
    public Material flashColour;

    void Awake( ) {
        this.GetComponent<Renderer>().material = capColour;
    }
    public void SetOn( ) {
        this.GetComponent<Renderer>().material = flashColour;

    }
    public void SetOff( ) {
        this.GetComponent<Renderer>().material = capColour;

    }
}   
