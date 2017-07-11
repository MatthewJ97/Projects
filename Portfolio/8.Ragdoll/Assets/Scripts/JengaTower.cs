using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class JengaTower : MonoBehaviour {
    public GameObject towerPiece;

    public Material mat1;
    public Material mat2;
    int height;
    int maxHeight = 20;
	// Use this for initialization
	void Start () {
        height = 0;
	}

    // Update is called once per frame
    private void Update( ) {
        if(height < maxHeight) CreateLayer();
    }

    void CreateLayer( ) {
        Quaternion q = new Quaternion();
        for ( int y = 0; y < 3; y++ ) {


            if ( height % 2 == 0 ) {
                q = Quaternion.identity;
                Instantiate(towerPiece, new Vector3(( y * 0.75f ) - ( 0.75f ), height * 0.45f + 1.01f, 0), q).GetComponent<Renderer>().material = mat1;
            }
            else {
                q = Quaternion.AngleAxis(90, Vector3.up);
                Instantiate(towerPiece, new Vector3(0, height * 0.45f + 1.01f, ( y * 0.75f ) - ( 0.75f )), q).GetComponent<Renderer>().material = mat2;

            }
        }
        height += 1;
    }
}
