using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ActivateRigidBody : MonoBehaviour {

    public bool isOn; 
    BoxCollider[] colliders = new BoxCollider[] { };

    Animator _anim;
	// Use this for initialization
	void Awake () {
        _anim = GetComponent<Animator>();
        colliders = GetComponentsInChildren<BoxCollider>();
        foreach (BoxCollider box in colliders)
        {
            Rigidbody phys = box.gameObject.GetComponent<Rigidbody>();
            phys.useGravity = false;
            phys.isKinematic = false;
            phys.detectCollisions = false;
        }
    }


    // Update is called once per frame
    public void SetRagdoll(bool aBool)
    {
        _anim.enabled = !aBool;
        foreach (BoxCollider box in colliders)
        {
            Rigidbody phys = box.gameObject.GetComponent<Rigidbody>();
            phys.useGravity = aBool;
            //phys.isKinematic = aBool;
            phys.detectCollisions = aBool;
        }
        isOn = aBool;
    }
}
