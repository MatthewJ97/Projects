using UnityEngine;
using UnityEngine.SceneManagement;
using System.Collections;
using System;
using UnityEngine.UI;
using System.Collections.Generic;

public class MainMenu_Script : MonoBehaviour
{
    public OptionsScript options;
    public AudioSource music;
    public GameObject CameraRig;
    public Camera MainCamera;
    public float RotationSpeed = 0f;
    public float ClimbingSpeed = 0.3f;

    public Slider MasterVolume;
    public Slider SFXVolume;
    public Slider MusicVolume;

    public GameObject Screen1;
    public GameObject Screen2;
    public GameObject Screen3;
    public GameObject Screen4;


    public Resolutions[] resolutionSizes;
    public Dropdown Resolution;
    public Toggle fullscreenToggle;
    public bool fullscreen;

    [Serializable]
    public struct Resolutions
    {
        public int Width;
        public int Height;
    }


    void Awake()
    {
        if (options == null) options = GameObject.Find("Options").GetComponent<OptionsScript>();
        Screen1.SetActive(true);
        Screen2.SetActive(false);
        Screen3.SetActive(false);
        Screen4.SetActive(false);
    }

    // Update is called once per frame
    void Update()
    {
        Resolution.onValueChanged.AddListener(delegate { ResolutionChange(); });
        fullscreenToggle.onValueChanged.AddListener(delegate { Fullscreen(); });

        if (Input.GetKeyDown(KeyCode.X))
        {
            perforce();
        }

        if (options != null)
        {
            options.MusicVolume = MusicVolume.value / 100;
            options.MasterVolume = MasterVolume.value / 100;
            options.SFXVolume = SFXVolume.value / 100;
            music.volume = options.MusicVolume;
        }
        else Debug.LogError("WARNING: Options Gameobject Referance Is Null");

        Vector3 position = CameraRig.transform.position;
        position.y += ClimbingSpeed;

        Vector3 rotation = new Vector3(0, RotationSpeed, 0);

        CameraRig.transform.position = position;
        CameraRig.transform.Rotate(rotation);

        if (Input.GetKeyUp(KeyCode.Escape))
        {
            ExitGame();
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

    public void Scene1() { SceneManager.LoadScene("Floor 1-1"); }
    public void Scene2() { SceneManager.LoadScene("Floor 1-2"); }
    public void Scene3() { SceneManager.LoadScene("Floor 1-3"); }
    public void Scene4() { SceneManager.LoadScene("Floor 1.5"); }
    public void Scene5() { SceneManager.LoadScene("Floor 1.5 T"); }
    public void Scene6() { SceneManager.LoadScene("Floor 2-1"); }
    public void Scene7() { SceneManager.LoadScene("Floor 2-2"); }

    void perforce()
    {
        Screen1.SetActive(false);
        Screen2.SetActive(false);
        Screen3.SetActive(false);
        Screen4.SetActive(true);
    }

    public void SceneSelection()
    {
        Screen1.SetActive(false);
        Screen2.SetActive(true);
        Screen3.SetActive(false);
        Screen4.SetActive(false);
    }

    public void BackToMenu()
    {
        Screen1.SetActive(true);
        Screen2.SetActive(false);
        Screen3.SetActive(false);
        Screen4.SetActive(false);
    }

    public void OptionsMenu()
    {
        Screen1.SetActive(false);
        Screen2.SetActive(false);
        Screen3.SetActive(true);
        Screen4.SetActive(false);
    }

    public void GoogleForm()
    {
        Application.OpenURL("https://goo.gl/forms/X7Yi0CsRnEICUmfn1");
    }

    public void ExitGame()
    {
        Application.Quit();
    }
}
