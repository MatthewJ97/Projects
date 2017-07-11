using UnityEngine;
using System.Collections;

public class LightingScript : MonoBehaviour
{
    public float waitingTime = 0.05f; //20 times a second
    public float normalRange = 3f; //normal range of light
    public float lowerRange = 0.5f; //flickering range
    public float decrement;
    public float dlT = 0;
    public bool goingDown = true;
    public Light LightComponent;

    void Awake()
    {
        if (LightComponent == null)
        {
            LightComponent = GetComponent<Light>();
        }
    }

    void FixedUpdate()
    {
        if (dlT >= waitingTime)
        {
            if (goingDown == true)
            {
                if (LightComponent.range > lowerRange) LightComponent.range -= decrement;
                else goingDown = !goingDown;
            }
            if (goingDown == false)
            {
                if (LightComponent.range < normalRange) LightComponent.range += decrement;
                else goingDown = !goingDown;
            }

            dlT = 0;
        }
        else
        {
            dlT += Time.deltaTime;
        }
    }
}
