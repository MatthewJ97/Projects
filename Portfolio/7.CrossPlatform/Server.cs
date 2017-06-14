using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.Networking;

public class Server : MonoBehaviour {
    [SerializeField]
    List<Player>players;
    [SerializeField]
    float playerTime = 0;
    [SerializeField]
    private float winnerDisTimer;
    float winnerDisTime = 250;
    string winText = "no winner for the chicken dinner";
    [SerializeField]
    float winTimer = 0;
    float winTime = 200;
    public GUISkin thisSkin;
    bool playersChoosen = false;
    bool scoreUpdated = false;
    public List<Texture>selectionTextures;

    public void AddPlayer(Player aPlayer) {
        players.Add(aPlayer);
    }

    void Update( ) {
        if ( players.Count == 2 ) {


            for ( int i = 0; i < players.Count; ) {
                if ( players[i] == null ) {
                    players.RemoveAt(i);
                }
                else {
                    i++;
                }
            }
        }
    }

    private void OnGUI( ) {

        if (playersChoosen)
        {

            GUI.Box(new Rect(0 + playerTime - Screen.width * 0.3f, Screen.height * 0.4f, Screen.width * 0.3f, Screen.height * 0.4f), selectionTextures[(int)players[0].playerSelection]);
            GUI.Box(new Rect(Screen.width - playerTime, Screen.height * 0.4f, Screen.width * 0.3f, Screen.height * 0.4f), selectionTextures[(int)players[1].playerSelection]);

            if (playerTime <= (Screen.width - Screen.width * 0.3f) / 2.0f)
            {
                playerTime += Time.deltaTime * 60;
            }
            else if (winTimer <= winTime)
            {
                winTimer += Time.deltaTime * 60;
            }
            else if (winTimer > winTime  - 50)
            {
                winnerDisTimer += Time.deltaTime * 60;
            }
            if (!scoreUpdated && players.Count == 2)
            {

                if (players[0].playerSelection == players[1].playerSelection)
                {
                    winText = "Its a tie";
                }
                if (players[0].playerSelection == Player.selection.PAPER && players[1].playerSelection == Player.selection.SCISSORS)
                {
                    winText = players[1].Username + "  wins";
                    players[1].score++;
                }
                else if (players[0].playerSelection == Player.selection.SCISSORS && players[1].playerSelection == Player.selection.ROCK)
                {
                    winText = players[1].Username + "  wins";
                    players[1].score++;

                }
                else if (players[0].playerSelection == Player.selection.ROCK && players[1].playerSelection == Player.selection.PAPER)
                {
                    winText = players[1].Username + "  wins";
                    players[1].score++;

                }
                else if (players[1].playerSelection == Player.selection.PAPER && players[0].playerSelection == Player.selection.SCISSORS)
                {
                    winText = players[0].Username + "  wins";
                    players[0].score++;

                }
                else if (players[1].playerSelection == Player.selection.SCISSORS && players[0].playerSelection == Player.selection.ROCK)
                {
                    winText = players[0].Username + "  wins";
                    players[0].score++;

                }
                else if (players[1].playerSelection == Player.selection.ROCK && players[0].playerSelection == Player.selection.PAPER)
                {
                    winText = players[0].Username + "  wins";
                    players[0].score++;

                }
                scoreUpdated = true;
            }
            else if (winnerDisTimer >= winTime && winnerDisTimer <= winTime *1.5f)
            {
                GUI.Label(new Rect(0 + Screen.width * 0.05f, Screen.height * 0.2f, Screen.width * 0.9f, 200), winText, thisSkin.label);

            }
            else if( winnerDisTimer > winTime *3)
            {
                playersChoosen = false;
                scoreUpdated = false;
                playerTime = 0;
                winTimer = 0;
                winnerDisTimer = 0;
                for (int j = 0; j < players.Count; j++)
                {
                    players[j].confirmedSelection = false;
                }
            }


        }
        for (int i = 0; i < players.Count; i++)
        {
            if ( players[i].confirmedSelection != true ) {
                GUI.Label(new Rect(0 + Screen.width * 0.05f, Screen.height * 0.2f, Screen.width * 0.9f, 200), ( "Waiting..." ), thisSkin.label);
                playersChoosen = false;
                return;
            }
            else {
                playersChoosen = true;
            }

        }
        

    }
}
