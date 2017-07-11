using UnityEngine;
using System.Collections;

public class OptionsScript : MonoBehaviour
{
    public AudioSource[] AudioNodes;
    public GameObject[] MusicNodes;
    public GameObject[] SFXNodes;

    public bool Music = true;
    public float MasterVolume = 0f;
    public float MusicVolume = 0f;
    public float SFXVolume = 0f;

	// Use this for initialization
	void Start ()
    {
        MusicNodes = GameObject.FindGameObjectsWithTag("MusicEmitter");
        SFXNodes = GameObject.FindGameObjectsWithTag("SFXEmitter");
    }

    void OnLevelWasLoaded()
    {
        MusicNodes = GameObject.FindGameObjectsWithTag("MusicEmitter");
        SFXNodes = GameObject.FindGameObjectsWithTag("SFXEmitter");
    }

    // Update is called once per frame
    void Update()
    {
        AudioListener.volume = MasterVolume;
    }

    public void ChangeAudio()
    {
        foreach (GameObject node in MusicNodes)
        {
            node.GetComponent<AudioSource>().volume = MusicVolume;
        }
        foreach (GameObject node in SFXNodes)
        {
            node.GetComponent<AudioSource>().volume = SFXVolume;
        }
    }

    public void SetResolution(int width, int height, bool fullscreen)
    {
        Screen.SetResolution(width, height, fullscreen);
    }
}
