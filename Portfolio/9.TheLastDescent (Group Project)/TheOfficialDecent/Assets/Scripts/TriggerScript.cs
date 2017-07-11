using UnityEngine;
using System.Collections;

public class TriggerScript : MonoBehaviour {
    public Animator targetObject;

    public Vector2[] AnimationCalls;
    public string[] AnimationNames;
    int currentAnim = 0;
    float waitTime;
    float currentTime;
    bool active = false;
	void Start ()
    {
	
	}
	
    void OnTriggerEnter(Collider col)
    {
        if (col.gameObject.tag == "Player" && active == false)
        {
            active = true;
        }
    }

    void Update()
    {
        if (active == true)
        {
            if (currentTime >= waitTime)
            {
                if (currentAnim < AnimationCalls.Length)
                {
                    targetObject.SetTrigger(AnimationNames[(int)AnimationCalls[currentAnim].x]);
                    waitTime = AnimationCalls[currentAnim].y;
                    currentTime = 0;
                    currentAnim++;
                }
            }
            else
            {
                currentTime += Time.deltaTime;
            }
        }
    }
}
