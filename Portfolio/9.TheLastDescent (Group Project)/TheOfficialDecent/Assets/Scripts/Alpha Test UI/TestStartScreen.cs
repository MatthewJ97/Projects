using UnityEngine;
using System.Collections;

using UnityEngine.UI;
public class TestStartScreen : MonoBehaviour {
    public int x = 0;
    public int maxText;
    public void Continue( ) {

        Text thisText = this.transform.FindChild("Text").GetComponent<Text>();
        switch ( x ) {

            case 0:
                thisText.text = "To Move the Player use the A and D keys.";
                break;
            case 1:
                thisText.text = " And Use Space to Jump ";
                break;
            case 2:
                thisText.text = "use the F key when the green Orb appears to Interact with objects.";
                break;
            case 3:
                thisText.text = "To Rotate the world use the Q and E keys.";
                break;
            default:
                 GameObject.Find("Player").GetComponent<PlayerKeyDetection>().paused = false;
                this.gameObject.SetActive(false);
                break;

        }
        if ( x < maxText ) {
            x++;
        }
        else {
            x = 10000;
        }

    }
}