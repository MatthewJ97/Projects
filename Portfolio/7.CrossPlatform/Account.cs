using System.Collections;
using System.Collections.Generic;
using UnityEngine;
[System.Serializable]
public struct Account
{
    [SerializeField]
    string userName;
    public string Username
    {
        get
        {
            return userName;
        }
        set
        {
            userName = value;
        }
    }
    [SerializeField]
    string password;
    public string Password
    {
        get
        {
            return password;
        }
        set
        {
            password = value;
        }
    }
    [SerializeField]
    int id;
    public int ID
    {
        get
        {
            return id;
        }
        set
        {
            id = value;
        }
    }
    public Account(string a_u = "defaultUser", string a_pass = "this is default password for those to lazy")
    {
        userName = a_u;
        password = a_pass;
        string temp = a_u + a_pass;
        id = 0;
        for (int i = 0; i < temp.Length; i++)
        {
            id += temp[i];
        }
        id += 10000;
    }
}
