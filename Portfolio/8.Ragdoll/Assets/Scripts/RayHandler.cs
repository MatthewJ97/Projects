using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class RayHandler : MonoBehaviour {

    // Update is called once per frame
    void Update( ) {
        Ray ray = Camera.main.ScreenPointToRay(new Vector3(Input.mousePosition.x, Input.mousePosition.y, 1));

        RaycastHit hit;

        if ( Physics.Raycast(ray, out hit, Mathf.Infinity) ) {

            Debug.Log("Hit = " + hit.collider.name);

            if ( Input.GetMouseButtonDown(0) ) {

                if ( hit.collider.tag == "Player" ) {
                    hit.collider.transform.root.GetComponent<ActivateRigidBody>().SetRagdoll(true);
                    hit.collider.transform.root.GetComponent<PArticleCollision>().Enable();
                }
            }
            if ( Input.GetMouseButtonDown(2) ) {

                if ( hit.collider.tag == "JengaPiece" ) {
                    Destroy(hit.collider.gameObject);
                }


            }
        }
    }
}
