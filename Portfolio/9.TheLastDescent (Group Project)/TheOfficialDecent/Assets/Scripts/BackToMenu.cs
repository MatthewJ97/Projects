/*
    Takes control of the UI for the player
    Created by Joshua Corney (joshuacorney2@gmail.com)
    Made 22/11
    Last Edited 23/11
*/

using UnityEngine;
using UnityEngine.UI;
using UnityEngine.SceneManagement;
using System;
using System.Collections;
using System.Collections.Generic;

public class BackToMenu : MonoBehaviour
{
    public OptionsScript options;
    public GameObject PauseMenu;
    public GameObject OptionsMenu;
    public string sceneName;

    public Resolutions[] resolutionSizes;
    public Dropdown Resolution;
    public Toggle fullscreenToggle;
    public bool fullscreen;

    [NonSerialized]
    public bool isPaused;

    [Serializable]
    public struct Resolutions
    {
        public int Width;
        public int Height;
    }


    void Awake()
    {
        if (options == null)
        {
            options = GameObject.Find("Options").GetComponent<OptionsScript>();
        }
        sceneName = SceneManager.GetActiveScene().name;
        isPaused = false;
        PauseMenu.SetActive(false);
        OptionsMenu.SetActive(false);
    }

    void togglePause()
    {
        isPaused = !isPaused;
        GameObject.FindGameObjectWithTag("Player").GetComponent<PlayerKeyDetection>().paused = isPaused;
        if (isPaused) { PauseMenu.SetActive(true); }
        else { PauseMenu.SetActive(false); OptionsMenu.SetActive(false); }
    }

	// Update is called once per frame
	void Update ()
    {
        Resolution.onValueChanged.AddListener(delegate {ResolutionChange(); });
        fullscreenToggle.onValueChanged.AddListener(delegate { Fullscreen(); });

        if (Input.GetKeyUp(KeyCode.Escape))
        {
            togglePause();
        }
	}

    public void ResolutionChange()
    {
        options.SetResolution(resolutionSizes[Resolution.value].Width, resolutionSizes[Resolution.value].Height, fullscreen);
    }

    public void Fullscreen()
    {
        fullscreen = fullscreenToggle.isOn;
        ResolutionChange();
    }

    public void clickResume()
    {
        togglePause();
    }
    public void clickRestartRoom()
    {
        SceneManager.LoadScene(sceneName); // TODO: Make reset the level and place the player at save zone
    }

    public void clickOptions()
    {
        OptionsMenu.SetActive(true);
        PauseMenu.SetActive(false);
        Debug.Log("Pause " + PauseMenu.activeSelf);
        Debug.Log("Options " + OptionsMenu.activeSelf);
    }
    
    public void clickQuit()
    {
        SceneManager.LoadScene("MainMenu"); // TODO: replace with mainmenu eventually
    }

    public void clickBackOptions()
    {
        OptionsMenu.SetActive(false);
        PauseMenu.SetActive(true);
    }
}
