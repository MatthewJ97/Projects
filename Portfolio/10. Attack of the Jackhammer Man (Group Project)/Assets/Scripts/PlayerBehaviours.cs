using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class PlayerBehaviours : MonoBehaviour {
    //ALEX IS A LOSER


    [SerializeField]
    CapsuleCollider cC;
    [SerializeField]
    GameObject running;
    [SerializeField]
    GameObject endZone;
     public float distanceFromEndZone;

    

    public enum PLAYERSTATE
    {
        JUMPING, SLIDING, GROUNDED
    }
    [SerializeField]
    PLAYERSTATE playerState = PLAYERSTATE.GROUNDED;

    public float jumpForce = 10.0f;
    public float score;
    public GameManager gm;
    Rigidbody rb;

    void Start()
    {
        rb = GetComponent<Rigidbody>();
        //Physics.IgnoreCollision(gameObject.GetComponent<CapsuleCollider>(), gameObject.GetComponent<SphereCollider>());
    }

    // Update is called once per frame
    void Update()
    {
        switch (GameManager.state)
        {

            case GameManager.GAMESTATES.START:

                break;

            case GameManager.GAMESTATES.GAME:
                distanceFromEndZone = Vector3.Distance(endZone.transform.position, transform.position);
                if (playerState == PLAYERSTATE.GROUNDED || playerState == PLAYERSTATE.SLIDING)
                {
                    if (Input.GetKeyDown(KeyCode.Space))
                    {
                        rb.AddForce(Vector3.up * jumpForce / 2, ForceMode.Impulse);
                    }
                    //if (Input.GetKey(KeyCode.DownArrow))
                    //{
                    //    ChangePlayerState(PLAYERSTATE.SLIDING);
                    //}
                }
                if( playerState == PLAYERSTATE.SLIDING)
                {
                    if(Input.GetKeyUp(KeyCode.DownArrow))
                        ChangePlayerState(PLAYERSTATE.GROUNDED);
                }

                if(playerState == PLAYERSTATE.JUMPING)
                {

                }

                break;
                

            case GameManager.GAMESTATES.GAMEOVER:
                if (Input.GetKey(KeyCode.Escape))
                {
                    SceneManager.LoadScene(0);
                    GameManager.state = GameManager.GAMESTATES.GAME;
                }
                break;

        }

    }

    void FixedUpdate()
    {
        if (rb.velocity.y < 0.1 && gameObject.transform.position.y < -5.8f) ChangePlayerState(PLAYERSTATE.GROUNDED);
        else ChangePlayerState(PLAYERSTATE.JUMPING);
    }

    // Use this for initialization
    void OnTriggerEnter(Collider col)
    {
        if(col.gameObject.tag == "obstacle") HitObstacle();
        if (col.gameObject.tag == "endzone") gm.ChangeState(GameManager.GAMESTATES.GAMEOVER);
    }

    public void ChangePlayerState(PLAYERSTATE nextState)
    {
        playerState = nextState;
        switch (playerState)
        {
            case PLAYERSTATE.GROUNDED:
                running.SetActive(true);
                cC.enabled = true;
                break;
            case PLAYERSTATE.JUMPING:
                running.SetActive(true);
                cC.enabled = false;
                break;
        }
    }

    public void HitObstacle()
    {
        if(distanceFromEndZone < 4.0f && distanceFromEndZone > 3.0f)
        {
            endZone.transform.position = new Vector3(-8, -5.83f, -4.6f);
        }
        if (distanceFromEndZone < 3.0f && distanceFromEndZone > 2.0f)
        {
            endZone.transform.position = new Vector3(-7, -5.83f, -4.6f);
        }
        if (distanceFromEndZone < 2.0f && distanceFromEndZone > 1.0f)
        {
            endZone.transform.position = new Vector3(-6, -5.83f, -4.6f);
        }
    }
}
