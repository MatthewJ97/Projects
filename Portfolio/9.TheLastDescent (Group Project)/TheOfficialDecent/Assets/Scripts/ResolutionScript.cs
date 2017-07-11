using UnityEngine;
using UnityEngine.Events;
using UnityEngine.UI;
using System.Collections;

public class ResolutionScript : MonoBehaviour
{
    public BackToMenu pauseMenu;

    void OnValueChange()
    {
        Debug.Log("Meme");
        
        {
            pauseMenu.ResolutionChange();
        }
    }
}
