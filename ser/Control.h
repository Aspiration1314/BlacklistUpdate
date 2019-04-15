#ifndef _CONTROL_H_
#define _CONTROL_H_
#include<iostream>
#include<json/json.h>
#include<map>
#include<string>
#include"enum.h"
#include"View.h"

using namespace std;

pthread_mutex_t zlmut;

class Control
{
private:
    Control()
    {
        cout<<"Control()"<<endl;
        _model.insert(make_pair(SELECT,new selectView()));
        _model.insert(make_pair(INSERT,new insertView()));
        _model.insert(make_pair(LOGIN,new loginView()));
        _model.insert(make_pair(ENROLL,new enrollView()));
    }
public:
    static Control* getControl()
    {
        cout<<"getControl()"<<endl;
        if(NULL == _control)
        {
            pthread_mutex_lock(&zlmut);
            if(NULL == _control)
            {
                _control = new Control();
            }
            pthread_mutex_unlock(&zlmut);
        }
        return _control;
    }
    void process(int fd,string& str)
    //void process(pair<int,string> data)
    {
        //解析  ----->TYPE
        Json::Value root;
        Json::Reader read;
        
        cout<<"Control::process()"<<endl;
        if(-1 == read.parse(str,root))
        {
            cerr<<"json prase fail;errno:"<<errno<<endl;
            return;
        }

        //cout<<"type:"<<root["TYPE"].asInt()<<endl;
        //cout<<"name:"<<root["NAME"].asString()<<endl;
        //cout<<"pw:"<<root["PW"].asString()<<endl;


        _model[root["TYPE"].asInt()]-> process(fd, root);
           
        }
private:
    static Control* _control;
    map<int,View*> _model;

};
Control* Control::_control = NULL;

#endif