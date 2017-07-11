using UnityEngine;
using System.Collections;

public class MainCameraScript : MonoBehaviour
{
    private GameObject player;
    // Use this for initialization
    void Start()
    {
        player = GameObject.FindGameObjectWithTag("Player");
    }

    // Update is called once per frame
    void Update()
    {
    }

    void OnTriggerStay(Collider col)
    {
        if (col.name == "platformCollider")
        {
            col.transform.parent.GetComponent<adjustForCollision>().resizeBoxesTrigger();
        }
    }
}
