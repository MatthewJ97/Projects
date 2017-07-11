/*
    Changes the scaling of the platforms
    Created by Joshua Corney (joshuacorney2@gmail.com)
    Made 22/11
    Last Edited 23/11
*/

using UnityEngine;
using System.Collections;

public class adjustForCollision : MonoBehaviour
{
    public float timeToChange = 0.5f;
    [HideInInspector]
    public float currentTime = 0f;

    private GameObject parent;
    public GameObject platformCollider;
    public float collisionSize = 0f;
    private float distance;
    public int currentRotation = 1;
    bool initialFix = false;
    float initFixTime = 0.2f;
    float initFixCurTime = 0;

    float ypos;

    private Vector3 midPoint;
    private Vector3 point1;
    private Vector3 point2;

    // Use this for initialization
    void Start()
    {
        ypos = platformCollider.transform.localPosition.y;
        parent = transform.parent.gameObject;
        // Set the distance to check against to that of the maximum collision size for the platforms
        distance = collisionSize;
    }

    // Update is called once per frame
    void Update()
    {
        if (currentTime < timeToChange)
        {
            currentTime += Time.deltaTime;
        }

        if (initFixCurTime < initFixTime && initialFix == false)
        { 
            initFixCurTime += Time.deltaTime;

            if (initFixCurTime >= initFixTime)
            {
                resizeBoxes();
                initialFix = true;
            }
        }

        if (Input.GetKeyUp(KeyCode.G))
        {
            resizeBoxes();
        }

        if (currentRotation == 5)
        {
            currentRotation = 1;
        }
        if (currentRotation == 0)
        {
            currentRotation = 4;
        }
    }

    public void resetBoxes()
    {
        transform.localPosition = new Vector3(0, ypos, 0);
        transform.localScale = new Vector3(1, 1, 1);
    }

    public void resizeBoxes()
    {
        if (platformCollider != null)
        {
            if (platformCollider.GetComponent<Rigidbody>() != null)
            {
                // Reset the scale and local position of the collider
                platformCollider.transform.localScale = new Vector3(1, 1, 1);
                platformCollider.transform.localPosition = new Vector3(0, ypos, 0);

                RaycastHit Hitpoint1;
                RaycastHit Hitpoint2;

                // If at maximum size, the collision collides with another object
                if (platformCollider.GetComponent<Rigidbody>().SweepTest(platformCollider.transform.forward, out Hitpoint1, distance, QueryTriggerInteraction.Ignore))
                {
                    // Set the first value to the hitpoint of the colliders
                    point1 = Hitpoint1.point;
                }
                else // If there is no collisions at all
                {
                    // Set the size of the colliders to their maximum size
                    point1 = platformCollider.transform.forward * distance;
                }
                // If at maximum size, the collision collides with another object
                if (platformCollider.GetComponent<Rigidbody>().SweepTest(-platformCollider.transform.forward, out Hitpoint2, distance, QueryTriggerInteraction.Ignore))
                {
                    // Set the first value to the hitpoint of the colliders
                    point2 = Hitpoint2.point;
                }
                else // If there are no collisions at all
                {
                    // Set the size of the colliders to their maximum size
                    point2 = -platformCollider.transform.forward * distance;
                }

                // Find the midpoint of the two points using the following formula
                // m = (1x + 2x) / 2, (1y + 2y) / 2, (1z + 2z) / 2
                midPoint.Set(((point1.x + point2.x) / 2), ((point1.y + point2.y) / 2), ((point1.z + point2.z) / 2));
                float scale = Vector3.Distance(point1, point2);

                if (currentRotation == 1)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (midPoint.x / parent.transform.localScale.x) - (parent.transform.position.x / parent.transform.localScale.x);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.z;
                    platformCollider.transform.localScale = tempScale;
                }
                else if (currentRotation == 2)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (-midPoint.z / parent.transform.localScale.z) + (parent.transform.position.z / parent.transform.localScale.z);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.z;
                    platformCollider.transform.localScale = tempScale;
                }
                else if (currentRotation == 3)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (-midPoint.x / parent.transform.localScale.x) + (parent.transform.position.x / parent.transform.localScale.x);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.x;
                    platformCollider.transform.localScale = tempScale;
                }
                else if (currentRotation == 4)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (midPoint.z / parent.transform.localScale.z) - (parent.transform.position.z / parent.transform.localScale.z);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.x;
                    platformCollider.transform.localScale = tempScale;
                }
            }
            else
            {
                Debug.LogError("Platform " + platformCollider.name + " requires a platformCollider asset to be attached");
            }
        }
        else
        {
            Debug.LogError("Platform " + this.name + " requires a Rigidbody to work as intended");
        }
    }

    public void resizeBoxesTrigger()
    {
        if (platformCollider != null)
        {
            if (platformCollider.GetComponent<Rigidbody>() != null)
            {
                // Reset the scale and local position of the collider
                platformCollider.transform.localScale = new Vector3(1, 1, 1);
                platformCollider.transform.localPosition = new Vector3(0, ypos, 0);

                RaycastHit Hitpoint1;
                RaycastHit Hitpoint2;

                // If at maximum size, the collision collides with another object
                if (platformCollider.GetComponent<Rigidbody>().SweepTest(platformCollider.transform.forward, out Hitpoint1, distance))
                {
                    // Set the first value to the hitpoint of the colliders
                    point1 = Hitpoint1.point;
                }
                else // If there is no collisions at all
                {
                    // Set the size of the colliders to their maximum size
                    point1 = platformCollider.transform.forward * distance;
                }
                // If at maximum size, the collision collides with another object
                if (platformCollider.GetComponent<Rigidbody>().SweepTest(-platformCollider.transform.forward, out Hitpoint2, distance))
                {
                    // Set the first value to the hitpoint of the colliders
                    point2 = Hitpoint2.point;
                }
                else // If there are no collisions at all
                {
                    // Set the size of the colliders to their maximum size
                    point2 = -platformCollider.transform.forward * distance;
                }

                // Find the midpoint of the two points using the following formula
                // m = (1x + 2x) / 2, (1y + 2y) / 2, (1z + 2z) / 2
                midPoint.Set(((point1.x + point2.x) / 2), ((point1.y + point2.y) / 2), ((point1.z + point2.z) / 2));
                float scale = Vector3.Distance(point1, point2);

                if (currentRotation == 1)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (midPoint.x / parent.transform.localScale.x) - (parent.transform.position.x / parent.transform.localScale.x);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.z;
                    platformCollider.transform.localScale = tempScale;
                }
                else if (currentRotation == 2)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (-midPoint.z / parent.transform.localScale.z) + (parent.transform.position.z / parent.transform.localScale.z);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.z;
                    platformCollider.transform.localScale = tempScale;
                }
                else if (currentRotation == 3)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (-midPoint.x / parent.transform.localScale.x) + (parent.transform.position.x / parent.transform.localScale.x);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.x;
                    platformCollider.transform.localScale = tempScale;
                }
                else if (currentRotation == 4)
                {
                    // Setting the platform collider's position
                    Vector3 tempPos = platformCollider.transform.localPosition;
                    tempPos.z = (midPoint.z / parent.transform.localScale.z) - (parent.transform.position.z / parent.transform.localScale.z);
                    platformCollider.transform.localPosition = tempPos;

                    // Setting the platforms collider's scale
                    Vector3 tempScale = platformCollider.transform.localScale;
                    tempScale.z = scale / parent.transform.localScale.x;
                    platformCollider.transform.localScale = tempScale;
                }
            }
            else
            {
                Debug.LogError("Platform " + platformCollider.name + " requires a platformCollider asset to be attached");
            }
        }
        else
        {
            Debug.LogError("Platform " + this.name + " requires a Rigidbody to work as intended");
        }
    }
}