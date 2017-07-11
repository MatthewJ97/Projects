using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Movement : MonoBehaviour {
    // Use this for initialization
    public float MoveSpeed;
    CharacterController cc;
    [SerializeField]
    FlyCam fc;

    public float speed = 50.0f;     
    public float sensitivity = 0.25f;
    public bool inverted = false;
    private Vector3 lastMouse = new Vector3(255, 255, 255);
    private Vector3 lastDir = new Vector3();

    void Start( ) {
        cc = GetComponent<CharacterController>();
    }


    void Update( ) {

        //moves the vector forward 1 point so original point is //vector 0,0,0 then changes to vector 0,0,1
        if ( !fc.cameraFC ) {
            Vector3 forward = (Input.GetAxis("Vertical")*transform.TransformDirection(Vector3.forward)*MoveSpeed) + Input.GetAxis("Horizontal")*transform.TransformDirection(Vector3.right)*MoveSpeed;
            cc.Move(forward * Time.deltaTime);
            cc.SimpleMove(Physics.gravity);
        }


        lastMouse = Input.mousePosition - lastMouse;
        if ( Input.GetMouseButton(1) ) {
            if ( !inverted ) lastMouse.y = -lastMouse.y;
            lastMouse *= sensitivity;
            lastMouse = new Vector3(transform.eulerAngles.x + lastMouse.y, transform.eulerAngles.y + lastMouse.x, 0);
            transform.eulerAngles = lastMouse;


        }
        lastMouse = Input.mousePosition;

    }
}
