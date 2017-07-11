using UnityEngine;
using System.Collections;
using System.Collections.Generic;
public class ButtonController : MonoBehaviour
{

    [SerializeField]
    List<ButtonConnection> buttonConnections;
    bool logicBool;
    int numberButtons;
    int numberButtonsTrue;
    void Update()
    {
        foreach (ButtonConnection con in buttonConnections)
        {
            logicBool = false;
            if (con.connectedObject != null)
            {
                #region And Logic 
                if (con.buttonLogic == Logic.AND)
                {
                    logicBool = true;
                    for (int i = 0; i < con.buttonArray.Count; i++)
                    {
                        if (!con.buttonArray[i].getTriggered())
                        {
                            logicBool = false;
                            break;
                        }
                    }
                    foreach (Interactable inter in con.connectedObject)
                    {

                        if (logicBool == true)
                        {
                            inter.Triggered(true);
                        }
                        else
                        {
                            inter.Triggered(false);

                        }
                    }
                }
                #endregion
                #region OR Logic
                if (con.buttonLogic == Logic.OR)
                {
                    logicBool = false;
                    for (int i = 0; i < con.buttonArray.Count; i++)
                    {
                        if (con.buttonArray[i].getTriggered())
                        {
                            logicBool = true;
                            break;
                        }
                    }
                    foreach (Interactable inter in con.connectedObject)
                    {

                        if (logicBool == true)
                        {
                            inter.Triggered(true);
                        }
                        else
                        {
                            inter.Triggered(false);

                        }
                    }
                }
                #endregion
                #region XOR Logic
                if (con.buttonLogic == Logic.OR)
                {
                    logicBool = false;
                    for (int i = 0; i < con.buttonArray.Count; i++)
                    {
                        if (logicBool == true && con.buttonArray[i].getTriggered())
                        {
                            logicBool = false;
                            break;
                        }
                        if (logicBool == false && con.buttonArray[i].getTriggered())
                        {
                            logicBool = true;
                        }
                    }
                    foreach (Interactable inter in con.connectedObject)
                    {
                        if (logicBool == true)
                        {
                            inter.Triggered(true);
                        }
                        else
                        {
                            inter.Triggered(false);

                        }
                    }
                }
                #endregion
                //#region TOGGLE Logic
                //if (con.buttonLogic == Logic.TOGGLE)
                //{
                //    logicBool = false;
                //    for (int i = 0; i < con.buttonArray.Count; i++)
                //    {
                //        if (con.buttonArray[i].getTriggered())
                //        {
                //            logicBool = true;
                //        }
                //    }
                //    foreach (Interactable inter in con.connectedObject)
                //    {
                //        if (logicBool == true)
                //        {
                //            Debug.Log("this has toggled");
                //            inter.Triggered(!inter.getTriggered());
                //        }
                //    }
                
                //}
                //#endregion
            }
        }
    }
}
[System.Serializable]
struct ButtonConnection
{
    public Logic buttonLogic;
    public List<Interactable> connectedObject;
    public List<Interactable> buttonArray;
}

public enum Logic
{
    AND, OR, XOR, TOGGLE
}


