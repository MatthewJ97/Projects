using UnityEngine;
using System.Collections;

public class MusicScript : MonoBehaviour
{
    void Awake()
    {
        DontDestroyOnLoad(transform.gameObject);
    }
}
