#ifndef _ROOTSYS_H_
#define _ROOTSYS_H_
#include<iostream>
#include<json/json.h>
//#include"Client.h"
#include"receverPthread.h"
#include"selecterPthread.h"
#include"enum.h"
using namespace std;
class rootSys
{  
public:  
    void put()
    {
        cout<<"1.insert"<<endl<<"2.delete"<<endl<<"3.select"<<endl;
    }
    void run()
    {
        new receverPthread();
        new selecterPthread();
        while(1)
        {
            put();
            int n;
            cout<<"please input your choice:"<<endl;
            cin >> n;
            switch(n)
            {
                case 1: 
                    insert();
                    break;
                case 2: 
                    del();
                    break;
                case 3: 
                    select();
                    break;
                default:
                    break;
            }
        }
    }
    void insert()
    {
        cout<<"this is rootSys.insert()"<<endl;
        string name,id;
        cout<<"please input insert username:";
        cin>>name;
        cout<<"please input insert id:";
        cin>>id;
        
        Json::Value json;
        json["TYPE"] = INSERT;
        json["NAME"] = name;
        json["ID"] = id;
        //Client::getClient()->Send(json.toStyledString());
        if( -1 == Client::getClient()->Send(json.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }

    }
    void del()
    {
        cout<<"this is rootSys.del()"<<endl;
        string id;
        cout<<"please input id you want to delete:"<<endl;
        cin>>id;

        Json::Value val;
        val["TYPE"] = DELETE;
        val["ID"] = id;

        if( -1 == Client::getClient()->Send( val.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
    }
    void select()
    {
        cout<<"this is rootSys.select()"<<endl;
        string id;
        cout<<"please input id you want to select:"<<endl;
        cin >> id;
        Json::Value json;
        json["TYPE"] = SELECT;
        json["ID"] = id;
        json["FD"] = -1;
        if( -1 == Client::getClient()->Send(json.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
        //Client::getClient()->send(json.toStyledString());
    }
};
#endif







