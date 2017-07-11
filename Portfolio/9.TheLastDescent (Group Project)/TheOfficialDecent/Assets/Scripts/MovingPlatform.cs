using UnityEngine;
using System.Collections;

public class MovingPlatform : MonoBehaviour
{
    [SerializeField]
    Transform platform;

    [SerializeField]
    Transform startTransform;

    [SerializeField]
    Transform endTransform;

    [SerializeField]
    float platformSpeed;

    [SerializeField]
    float collisionCheckDist = 0.1f;

    public bool nothingBlocking = true;
    Vector3 direction;
    Transform destination;

    void Start()
    {
        SetDestination(startTransform);
    }

    void FixedUpdate()
    {
        if (nothingBlocking == true)
        {
            platform.GetComponent<Rigidbody>().MovePosition(platform.transform.position + direction * platformSpeed * Time.fixedDeltaTime);
        }

        if (Vector3.Distance(platform.position, destination.position) < platformSpeed * Time.fixedDeltaTime)
        {
            SetDestination(destination == startTransform ? endTransform : startTransform);
        }

        if (direction.y <= 0)
        {
            RaycastHit hit;

            if (this.GetComponentInChildren<Rigidbody>().SweepTest(direction * platformSpeed * Time.fixedDeltaTime, out hit, collisionCheckDist))
            {
                ///Debug.Log("Platform - Checked blockage");

                if (hit.collider.gameObject.tag == "Player")
                {
                    ///Debug.Log("Platform - Blocked");
                    nothingBlocking = false;
                }
                else
                {
                    ///Debug.Log("Platform - Not Blocked");
                    nothingBlocking = true;
                }
            }
            else
            {
                ///Debug.Log("Platform - Not Blocked");
                nothingBlocking = true;
            }
        }
    }

    void OnDrawGizmos()
    {
        Gizmos.color = Color.green;
        Gizmos.DrawWireCube(startTransform.position, platform.localScale);

        Gizmos.color = Color.red;
        Gizmos.DrawWireCube(endTransform.position, platform.localScale);
    }

    void SetDestination(Transform dest)
    {
        destination = dest;
        Vector3 dir;
        dir = (destination.position - platform.position);
        dir = dir.normalized;
        direction = dir;
    }
}
