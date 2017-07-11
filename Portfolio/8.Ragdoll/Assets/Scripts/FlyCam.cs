using UnityEngine;
using System.Collections;

public class FlyCam : MonoBehaviour {
	
	
	public float speed = 50.0f;		// max speed of camera
	public float sensitivity = 0.25f; 		// keep it from 0..1
	public bool inverted = false;
    [SerializeField]
    GameObject main;
    [SerializeField]
    GameObject sec;
    public bool cameraFC = true;
	private Vector3 lastMouse = new Vector3(255, 255, 255);
	
	public bool smooth = true;
	public float acceleration = 0.1f;
    private float actSpeed = 0.0f;
	private Vector3 lastDir = new Vector3();
	
	
	void Start () {
        sec.GetComponent<Camera>().enabled = false;
        sec.GetComponent<RayHandler>().enabled = false;
    }

    void Update( ) {
        if ( Input.GetKeyUp(KeyCode.Space) ) ChangeCamera(cameraFC);
        if ( cameraFC ) {
            lastMouse = Input.mousePosition - lastMouse;
            if ( Input.GetMouseButton(1) ) {
                if ( !inverted ) lastMouse.y = -lastMouse.y;
                lastMouse *= sensitivity;
                lastMouse = new Vector3(transform.eulerAngles.x + lastMouse.y, transform.eulerAngles.y + lastMouse.x, 0);
                transform.eulerAngles = lastMouse;


            }
            lastMouse = Input.mousePosition;

            Vector3 dir = new Vector3();

            if ( Input.GetKey(KeyCode.W) ) dir.z += 1.0f;
            if ( Input.GetKey(KeyCode.S) ) dir.z -= 1.0f;
            if ( Input.GetKey(KeyCode.A) ) dir.x -= 1.0f;
            if ( Input.GetKey(KeyCode.D) ) dir.x += 1.0f;
            dir.Normalize();


            if ( dir != Vector3.zero ) {
                if ( actSpeed < 1 )
                    actSpeed += acceleration * Time.deltaTime * 40;
                else
                    actSpeed = 1.0f;

                lastDir = dir;
            }
            else {
                if ( actSpeed > 0 )
                    actSpeed -= acceleration * Time.deltaTime * 20;
                else
                    actSpeed = 0.0f;
            }

            if ( smooth )
                transform.Translate(lastDir * actSpeed * speed * Time.deltaTime);

            else
                transform.Translate(dir * speed * Time.deltaTime);
        }
    }
	
    void ChangeCamera( bool aBool) {
        sec.GetComponent<Camera>().enabled = aBool;
        sec.GetComponent<RayHandler>().enabled = aBool;
        main.GetComponent<Camera>().enabled = !aBool;
        main.GetComponent<RayHandler>().enabled = !aBool;
        cameraFC = !cameraFC;
    }
}
