/*
using UnityEngine;
using System.Collections;
using UnityEditor;

[CustomEditor(typeof(ButtonLogic))]
public class ButtonLogic : Editor
{
    private bool AToggle = false;
    private ButtonLogic _evCtrl = null;

    public string ThisVar { get; private set; }
    public string AndThisOne { get; private set; }
    public float AndThisCanBeSlider { get; private set; }

    void OnEnable()
    {
        _evCtrl = (ButtonLogic)target;
    }
    public override void OnInspectorGUI()
    {
        //blablabla
        GUILayout.BeginHorizontal();
        GUILayout.Label("A Features", GUILayout.Width(70));
        AToggle = EditorGUILayout.Toggle(AToggle);
        GUILayout.EndHorizontal();
        if (AToggle)
        {
            GUILayout.Space(5);
            GUILayout.BeginHorizontal();
            GUILayout.Label("This Var", GUILayout.Width(70));
            _evCtrl.ThisVar = EditorGUILayout.TextField(_evCtrl.ThisVar);
            GUILayout.EndHorizontal();
            GUILayout.Space(5);
            GUILayout.BeginHorizontal();
            GUILayout.Label("And This One", GUILayout.Width(70));
            _evCtrl.AndThisOne = EditorGUILayout.TextField(_evCtrl.AndThisOne);
            GUILayout.EndHorizontal();
            GUILayout.Space(5);
            GUILayout.BeginHorizontal();
            GUILayout.Label("And This Can Be Slider", GUILayout.Width(70));
            _evCtrl.AndThisCanBeSlider = EditorGUILayout.Slider(_evCtrl.AndThisCanBeSlider, 0f, 100f);
            GUILayout.EndHorizontal();
        }
        //blablabla
    }
}
*/