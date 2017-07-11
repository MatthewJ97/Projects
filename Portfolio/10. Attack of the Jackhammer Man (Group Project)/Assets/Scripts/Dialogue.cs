using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class Dialogue : MonoBehaviour {
    [SerializeField]
    float waitTime;
    [SerializeField] 
    float waitTimer = 0;
    [SerializeField]
    float displayTime;
    [SerializeField]
    float displayTimer = 0;
    [SerializeField]
    string[] dialogueOptions;
    Rect textRect = new Rect(0, Screen.height - 50, Screen.width, 50);
    string currentDialogue = "";
    [SerializeField]
    GUIStyle dialougueGUI;
    [SerializeField]
    PlayerBehaviours player;
	// Use this for initialization
	void Start () {
        waitTimer = waitTime;
        currentDialogue = dialogueOptions[0];
	}
	
	// Update is called once per frame
	void Update () {
        waitTime = player.distanceFromEndZone * 5;
        displayTime =  waitTime - player.distanceFromEndZone;
        if (waitTimer >= 0)
        {
            waitTimer -= Time.deltaTime;
        }
        else if(waitTimer <= 0)
        {
            currentDialogue = dialogueOptions[Random.Range(0, dialogueOptions.Length - 1)];
            displayTimer = displayTime;
            waitTimer = waitTime;
        }
        
	}

    void OnGUI()
    {

        if (displayTimer >= 0)
        {
            displayTimer -= Time.deltaTime;
            GUI.Box(textRect, "");
            GUI.Label(textRect, currentDialogue, dialougueGUI);
        }
    }

}
