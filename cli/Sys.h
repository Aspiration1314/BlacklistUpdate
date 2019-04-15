#ifndef _SYS_H_
#define _SYS_H_
#include<iostream>
#include<json/json.h>
#include"rootSys.h"
#include"TcpClient.h"
#include"Client.h"
#include"enum.h"
using namespace std;

class Sys
{
public:
    Sys()
    {
        _rootSys = new rootSys();
    }
    void put()
    {
        cout<<"1.login"<<endl<<"2.enroll"<<endl<<"3.exit"<<endl;
    }
    void run()
    {
        while(1)
        {
            put();
            int n;
            cin >> n;
            switch(n)
            {
                case 1: 
                    login();
                    break;
                case 2: 
                    enroll();
                    break;
                case 3: 
                    exit(1);
                    break;
                default:
                    break;
            }
        }
    }
    void login()
    {
        string name,pw;
        cout<<"please input your name "<<endl;
        cin >> name;
        cout<<"please input your pw"<<endl;
        cin >> pw;
        Json::Value json;
        json["TYPE"] = LOGIN;
        json["NAME"] = name;
        json["PW"] = pw;
        if( -1 == Client::getClient()->Send(json.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
        //Client::getClient()->Send(json.toStyledString());
        string str;
        if( 0 >= Client::getClient()->Recv(str) )
        {
            cerr<<"recv fail;errno:"<<errno<<endl;
            return;
        }
        //Client::getClient()->Recv(str);
        //解析json
        Json::Value root;
        Json::Reader read;

        if(-1 == read.parse(str,root))
        {
            cerr<<"json prase fail;errno:"<<errno<<endl;
            return;
        }

        if(root["reason"].asString() == "success")
        {
            cout<<"login succeed"<<endl;
            _rootSys->run();
        }   
        else
        {
            cout<<"login fail"<<endl;
        } 
    }
    void enroll()
    {
        string name, pw;
        cout<<"please input username:"<<endl;
        cin>>name;
        cout<<"please input pw:"<<endl;
        cin>>pw;
        
        Json::Value json;
        json["TYPE"] = ENROLL;
        json["NAME"] = name;
        json["PW"] = pw;

        //delete 
        cout<<"TYPE:"<<json["TYPE"].asInt()<<endl;
        
        if(-1 == Client::getClient()->Send(json.toStyledString() ) )
        {         
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }

        string str;
        Client::getClient()->Recv(str);

        Json::Value root;
        Json::Reader read;

        if(-1 == read.parse(str,root))
        {
            cerr<<"json prase fail;errno:"<<errno<<endl;
            return;
        }

        if(root["reason"].asString() == "success")
        {
            cout<<"reason:"<<root["reason"].asString()<<endl;
            cout<<"enroll succeed!"<<endl;
        }
        else
        {
            cout<<"enroll fail"<<endl;
        } 
    }
private:
    rootSys* _rootSys;
};


#endif

