using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class ExplosionTrigger : MonoBehaviour {

	// Use this for initialization
    void OnTriggerEnter(Collider col)
    {
        Destroy(col.gameObject);
    }
	
	// Update is called once per frame
	void Update () {
		
	}
}
