using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class PlatformController : MonoBehaviour
{
    public GameManager cData;
    public List<GameObject> aliveChunks = new List<GameObject>();
    public List<GameObject> chunkData = new List<GameObject>();
    public List<GameObject> bgPieces = new List<GameObject>();
    Vector3 spawn = new Vector3();
    public GameObject platforms;

    void OnTriggerEnter(Collider col)
    {
        if (col.tag == "chunk")
        {
            aliveChunks.Remove(col.gameObject);
            aliveChunks.Add(
                Instantiate(chunkData[Random.Range(0, chunkData.Count)], spawn, Quaternion.identity, platforms.transform)
            );
            Destroy(col.gameObject);
        }
        if (col.tag == "bg")
        {
            col.gameObject.transform.position = new Vector3(82.74f, -2.38f, -0.01f);
        }
    }

    // Use this for initialization
    void Start()
    {
        spawn = gameObject.transform.parent.GetChild(0).transform.position;
        GameObject[] gos = GameObject.FindGameObjectsWithTag("chunk");
        for (int i = 0; i < gos.Length; i++)
        {
            aliveChunks.Add(gos[i]);
        }
    }

    // Update is called once per frame
    void Update()
    {
        switch (GameManager.state)
        {
            case GameManager.GAMESTATES.GAME:
                Vector3 movement = new Vector3(1 * cData.mapSpeed, 0, 0);
                for (int i = 0; i < aliveChunks.Count; i++)
                {
                    aliveChunks[i].transform.position -= movement * Time.deltaTime;
                }
                for (int i = 0; i < bgPieces.Count; i++)
                {
                    bgPieces[i].transform.position -= movement * Time.deltaTime;
                }
                break;
        }

    }
}