#ifndef _VIEW_H_
#define _VIEW_H_

#include<iostream>
#include<json/json.h>
#include"Server.h"
#include"dataBase.h"
using namespace std;
class View
{
public:
    virtual void process(int fd,Json::Value& val) = 0;
};

class enrollView:public View
{
public:
    void process(int fd,Json::Value& val)
    {
        cout<<"this is enrollView::process()"<<endl;
        Json::Value result;
        //result["TYPE"]=ENROLL;
        if(dataBase::getDataBase()->enrollIntoRootList(val))
        {
            result["reason"]="success";
        }
        else
        {
            result["result"]="fail";
        }
        //Server::getServer()->Send(fd,result.toStyledString());
        if( -1 == Server::getServer()->Send( fd, result.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
    }
};

class loginView:public View
{
public:
    void process(int fd,Json::Value& val)
    {
        cout<<"this is loginView::process()"<<endl;
        //string name = val["NAME"].asString().c_str();
        //string pw = val["PW"].asString().c_str();
        //cout<<val["NAME"].asString()<<endl;
        //cout<<val["PW"].asString()<<endl;
        Json::Value json;
        //json["TYPE"] = LOGIN;
        //if(dataBase::getDataBase()->selectFromRootList(val["NAME"].toStyledString(),val["PW"]).toStyledString())
        //if(dataBase::getDataBase()->selectFromRootList(val))
        if(dataBase::getDataBase()->loginIntorootList(val))
        {
            json["reason"] = "success";
        }
        else
        {
            json["reason"] = "fail";
        }
        if( -1 == Server::getServer()->Send( fd, json.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
    }
};

class insertView:public View
{
public:
    void process(int fd,Json::Value& val)
    {
        cout<<"this is insertView::process()"<<endl;
        Json::Value result;
        //result["TYPE"]=INSERT;
        if(dataBase::getDataBase()->insertIntoUserList(val))
        {
            result["reason"]="success";
        }
        else
        {
            result["result"]="fail";
        }
        //Server::getServer()->Send(fd,result.toStyledString());
        if( -1 == Server::getServer()->Send( fd, result.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
    }
};

class selectView:public View
{
public:
    void process(int fd,Json::Value& val)
    {
        cout<<"this is selectView::process()"<<endl;
        //cout<<val["ID"].asString()<<endl;
        //string id = val["ID"].asString().c_str();
        char hahaha[100] = {0};

        Json:: Value json;
        json["TYPE"] = SELECT;
        json["FD"] = -1;
        //if(dataBase::getDataBase()->selectFromUserList(val["ID"].toStyledString()))
        if(dataBase::getDataBase()->selectFromUserList(val, hahaha))
        {
            json["reason"] = "success";
            json["hahaha"] = hahaha;
        }
        else
        {
            json["reason"] = "fail";
        }
        if( -1 == Server::getServer()->Send( fd, json.toStyledString() ))
        {
            cerr<<"send fail;errno:"<<errno<<endl;
            return;
        }
    }
};







#endif

