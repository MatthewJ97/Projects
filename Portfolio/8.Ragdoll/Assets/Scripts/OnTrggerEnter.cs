using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class OnTrggerEnter : MonoBehaviour {

    // Use this for initialization
    void OnTriggerEnter(Collider col) {
        Destroy(col.gameObject);
    }
}
