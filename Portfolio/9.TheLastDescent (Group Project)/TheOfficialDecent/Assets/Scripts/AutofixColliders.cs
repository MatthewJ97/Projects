/*
    Controls the changes made to all of the platforms
    Created by Joshua Corney (joshuacorney2@gmail.com)
    Made 22/11
    Last Edited 23/11
*/

using UnityEngine;
using System.Collections;
using System.Collections.Generic;

public class AutofixColliders : MonoBehaviour
{
    public List<GameObject> platforms;
    public GameObject player;
    public float distance;
    //bool initialFix = false;
    //float initFixTime = 0;

    void Awake()
    {
        player = GameObject.FindGameObjectWithTag("Player");
        platforms = new List<GameObject>(GameObject.FindGameObjectsWithTag("PlatformCollider"));
    }

    public void rotateColliders(bool left)
    {
        if (left)
        {
            foreach (GameObject platform in platforms)
            {
                platform.transform.Rotate(0, 90, 0);
                platform.GetComponent<adjustForCollision>().resetBoxes();
            }
            foreach (GameObject platform in platforms)
            {
                platform.GetComponent<adjustForCollision>().resizeBoxes();
            }
        }
        else
        {
            foreach (GameObject platform in platforms)
            {
                platform.transform.Rotate(0, -90, 0);
                platform.GetComponent<adjustForCollision>().resetBoxes();
            }
            foreach (GameObject platform in platforms)
            {
                platform.GetComponent<adjustForCollision>().resizeBoxes();
            }
        }
    }

    public void checkAll()
    {
        foreach (GameObject platform in platforms)
        {
            platform.GetComponent<adjustForCollision>().resizeBoxes();
        }
    }

    public void toggleColliders(bool toggle)
    {
        foreach ( GameObject platform in platforms ) {
            if ( platform.layer != 10 ) {
                BoxCollider[] children = platform.GetComponentsInChildren<BoxCollider>();

                foreach ( BoxCollider child in children ) {
                    child.enabled = toggle;
                }
            }
        }
    }

    public void increaseRotation()
    {
        foreach (GameObject platform in platforms)
        {
            platform.GetComponent<adjustForCollision>().currentRotation++;
        }
    }

    public void decreaseRotation()
    {
        foreach (GameObject platform in platforms)
        {
            platform.GetComponent<adjustForCollision>().currentRotation--;
        }
    }
    
    public void changeOnDeath()
    {
        foreach (GameObject platform in platforms)
        {
            if (platform.transform.GetChild(0).GetComponent<Interactable>() != null)
            {
                if (platform.transform.GetChild(0).GetComponent<Interactable>().objectType == Interactable.InteractiveType.BUTTON)
                {
                    if ((platform.GetComponent<adjustForCollision>().currentRotation - 2) != player.GetComponent<PlayerMovement>().rotationValue)
                    {
                        continue;
                    }
                    else if ((platform.GetComponent<adjustForCollision>().currentRotation + 2) != player.GetComponent<PlayerMovement>().rotationValue)
                    {
                        continue;
                    }                        
                }
            }

            if (player.GetComponent<PlayerMovement>().rotationValue < platform.GetComponent<adjustForCollision>().currentRotation)
            {
                while (player.GetComponent<PlayerMovement>().rotationValue < platform.GetComponent<adjustForCollision>().currentRotation)
                {
                    platform.GetComponent<adjustForCollision>().currentRotation--;
                    platform.transform.Rotate(0, 90, 0);
                    platform.GetComponent<adjustForCollision>().resizeBoxes();
                }
                platform.transform.Rotate(0, 180, 0);
                platform.GetComponent<adjustForCollision>().resetBoxes();
            }
            else if (player.GetComponent<PlayerMovement>().rotationValue > platform.GetComponent<adjustForCollision>().currentRotation)
            {
                while (player.GetComponent<PlayerMovement>().rotationValue > platform.GetComponent<adjustForCollision>().currentRotation)
                {
                    platform.GetComponent<adjustForCollision>().currentRotation++;
                    platform.transform.Rotate(0, -90, 0);
                    platform.GetComponent<adjustForCollision>().resetBoxes();
                }
                platform.transform.Rotate(0, 180, 0);
                platform.GetComponent<adjustForCollision>().resizeBoxes();
            }
        }
    }

    public void setRotation(Quaternion rotation)
    {
        foreach (GameObject platform in platforms)
        {
            platform.transform.rotation = rotation;
            platform.GetComponent<adjustForCollision>().resizeBoxes();
        }
    }

    public void checkHidden()
    {
        foreach (GameObject platform in platforms)
        {
            BoxCollider[] children = platform.GetComponentsInChildren<BoxCollider>();

            foreach (BoxCollider child in children)
            {
                if (Physics.Linecast(child.transform.position, player.GetComponent<Camera>().transform.position))
                {
                    child.gameObject.SetActive(false);
                }
                else
                {
                    child.gameObject.SetActive(true);
                }
            }
        }
    }
}
