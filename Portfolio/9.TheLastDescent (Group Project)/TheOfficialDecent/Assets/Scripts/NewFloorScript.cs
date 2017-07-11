/*
    Used To make the player transfer between multiple points within the same scene
    Created by Joshua Corney (joshuacorney2@gmail.com)
    Made 22/11
    Last Edited 23/11
*/

using UnityEngine;
using System.Collections;

public class NewFloorScript : MonoBehaviour
{
    public GameObject player;
    public Transform OffScreen;
    public Transform OnScreenStart;
    public Transform OnScreenEnd;
    public GameObject SceneController;
    public int rotationValue;
    bool movingOffscreen = false;
    bool movingOnScreen = false;

    public float movementSpeed = 2f;
    Vector3 direction;
    Transform destination;
	
	// Update is called once per frame
	void Update ()
    {
        if (movingOffscreen)
        {
            // Debug.Log(Vector3.Distance(player.transform.position, destination.transform.position));
            player.GetComponent<Rigidbody>().MovePosition(player.transform.position + direction * movementSpeed * Time.fixedDeltaTime);

            if (Vector3.Distance(player.transform.position, destination.position) < movementSpeed)
            {                
                movingOffscreen = false;
                player.transform.rotation = OnScreenStart.rotation;
                player.transform.position = OnScreenStart.position;
                movingOnScreen = true;
                SetDestination(OnScreenEnd);
                player.GetComponent<Rigidbody>().velocity = Vector3.zero;

                // Rotate the players model to face the direction of travel
                Quaternion tempQ = new Quaternion();
                tempQ.eulerAngles = new Vector3(0, 90, 0);
                player.GetComponent<PlayerKeyDetection>().Model.transform.localRotation = tempQ;
            }
        }
        if (movingOnScreen)
        {
            player.GetComponent<Rigidbody>().MovePosition(player.transform.position + direction * movementSpeed * Time.fixedDeltaTime);

            if (Vector3.Distance(player.transform.position, destination.position) < movementSpeed / 2)
            {
                movingOnScreen = false;
                player.GetComponent<PlayerKeyDetection>().FinishingMovemenet = false;
                player.GetComponent<CapsuleCollider>().enabled = true;
                player.GetComponent<Rigidbody>().useGravity = true;
                player.GetComponent<PlayerKeyDetection>().paused = false;
                player.GetComponent<PlayerMovement>().rotationValue = rotationValue;
                SceneController.GetComponent<AutofixColliders>().changeOnDeath();
                player.GetComponent<Rigidbody>().velocity = Vector3.zero;
            }
        }
	}

    void OnTriggerEnter(Collider col)
    {
        if (col.tag == "Player")
        {
            player.GetComponent<PlayerKeyDetection>().FinishingMovemenet = true;
            player.GetComponent<Rigidbody>().velocity = Vector3.zero;
            player.GetComponent<CapsuleCollider>().enabled = false;
            player.GetComponent<Rigidbody>().useGravity = false;
            SetDestination(OffScreen);
            player.GetComponent<PlayerKeyDetection>().paused = true;
            movingOffscreen = true;
        }
    }

    void SetDestination(Transform dest)
    {
        destination = dest;
        Vector3 dir;
        dir = (destination.position - player.transform.position);
        dir = dir.normalized;
        direction = dir;
    }
}
