using UnityEngine;
using System.Collections;
using UnityEngine.UI;

public class AudioLevelsMixer : MonoBehaviour
{ 
    public OptionsScript options;
    public Slider MasterVolume;
    public Slider MusicVolume;
    public Slider SFXVolume;
    float time = 0;
    float DT = 0;

    void Start()
    {
        if (options == null) options = GameObject.Find("Options").GetComponent<OptionsScript>();
        MasterVolume.value = options.MasterVolume * 100;
        MusicVolume.value = options.MusicVolume * 100;
        SFXVolume.value = options.SFXVolume * 100;
    }

    // Update is called once per frame
    void Update()
    {
        if (options != null)
        {
            options.MasterVolume = MasterVolume.value / 100;
            options.MusicVolume = MusicVolume.value / 100;
            options.SFXVolume = SFXVolume.value / 100;
        }
    }
    void FixedUpdate()
    {
        if (options != null)
        {
            if (DT > time)
            {
                options.ChangeAudio();
                DT = 0;
            }
            else
            {
                DT += Time.deltaTime;
            }
        }
    }
}
