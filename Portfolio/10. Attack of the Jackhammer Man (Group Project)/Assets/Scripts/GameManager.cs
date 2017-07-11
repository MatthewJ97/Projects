using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class GameManager : MonoBehaviour
{
    [SerializeField]
    public float score = 0;
    public GUIStyle scoreGUI;
    public static float gameSpeed = 1.0f;
    public float mapSpeed = 1.0f;
    public float maxMapSpeed = 20.0f;
    public List<GameObject> levelPieces = new List<GameObject>();
    public Rect ScoreGUIRect = new Rect(10, 10, 50, 50);
    public Rect InstructionsGUIRect = new Rect(10, 60, 100, 100);

    public string extra;

    public enum GAMESTATES
    {
        START, GAME, PAUSED, GAMEOVER
    }
    public static GAMESTATES state = GAMESTATES.GAME;
    // Use this for initialization
    void Start()
    {

    }

    // Update is called once per frame
    void Update()
    {
        switch (state)
        {
            case GAMESTATES.GAME:
                score += (mapSpeed * Time.deltaTime)/3.0f;
                if(Input.GetKeyUp(KeyCode.Escape)) Application.Quit();
                
                if (mapSpeed < maxMapSpeed && gameSpeed > 0)
                    mapSpeed += 0.1f * Time.deltaTime * gameSpeed;
                break;

            case GAMESTATES.GAMEOVER:
                //ENTER PAUSED FUNCTIONALITY HERE

               

                break;
        }
    }

    void OnGUI()
    {
        GUI.Label(ScoreGUIRect,"score: " + (int)score + extra, scoreGUI);
        if (state != GAMESTATES.GAMEOVER) GUI.Label(InstructionsGUIRect, "Press Space to jump", scoreGUI);
    }

    public void ChangeState(GAMESTATES nextState)
    {
        state = nextState;
        switch (state)
        {
            case GAMESTATES.GAME:
                score = 0;
                ScoreGUIRect = new Rect(10, 10, 50, 50);
                scoreGUI.fontSize = 50;
                    extra = "";
                break;
            case GAMESTATES.GAMEOVER:
                ScoreGUIRect = new Rect(Screen.width * 0.5f - Screen.width * 0.4f, Screen.height * 0.5f - Screen.height * 0.4f, Screen.width * 0.8f, Screen.height * 0.8f);
                scoreGUI.fontSize = 100;
                extra = "\n Press esc to retry!";
                break;
        }
    }
}
