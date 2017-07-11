using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PArticleCollision : MonoBehaviour {
    ParticleSystem ps;
    // Use this for initialization

    void Start( ) {
        ps = GetComponent<ParticleSystem>();
        ParticleSystem.CollisionModule coll = ps.collision;
        coll.enabled = true;
        coll.bounce = 0.01f;
    }

    private void OnParticleCollision(GameObject col) {
        Debug.Log("Bouncing");
        }
    

    public void Enable( ) {
        ps.Play();
    } 
}
