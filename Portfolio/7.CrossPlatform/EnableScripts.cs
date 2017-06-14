using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class EnableScripts : MonoBehaviour {

    public MonoBehaviour enableThis;
    public GameObject enableThis2;
    public GameObject enableThis3;

    void Update()
    {
        if (enableThis != null &&!enableThis.enabled) enableThis.enabled = true;
        if (enableThis2 != null && !enableThis2.activeSelf == true) enableThis2.SetActive(true);
        if (enableThis3 != null && !enableThis3.activeSelf == true) enableThis3.SetActive(true);

    }
}
