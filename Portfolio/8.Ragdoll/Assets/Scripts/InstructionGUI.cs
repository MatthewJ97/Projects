using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class InstructionGUI : MonoBehaviour {
    Rect rect = new Rect(50,50, 500,100);
    private void OnGUI( ) {
        GUI.Box(rect,"");
        GUI.Label(rect, "Press Space to swap cameras, \nLeft Click to destroy Jenga Pieces, \nMiddle Click on Model to Ragdoll, \nWASD to move character and Fly camera, \nRight Click to rotate Camera");
    }
}
