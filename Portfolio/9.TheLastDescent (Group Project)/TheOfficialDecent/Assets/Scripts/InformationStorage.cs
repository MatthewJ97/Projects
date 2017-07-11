using UnityEngine;
using System.Collections;

public class InformationStorage : MonoBehaviour
{
    public bool Local;
    public Vector3 Position;
    public Quaternion Rotation;
    public Vector3 Scale;
    public bool Transparent;
    public bool isWall = false;
    public Vector3 NeededScale;

	// Use this for initialization
	void Awake ()
    {
        if (Local)
        {
            Transparent = false;
            Position = transform.localPosition;
            Rotation = transform.localRotation;
            Scale = transform.localScale;
        }
        else
        {
            Transparent = false;
            Position = this.transform.position;
            Rotation = this.transform.rotation;
            Scale = this.transform.localScale;
        }
	}
}
