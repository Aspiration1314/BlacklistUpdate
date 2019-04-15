#ifndef _RECEVERPTHREAD_H_
#define _RECEVERPTHREAD_H_
#include<iostream>
#include<pthread.h>
#include"Client.h"
#include"Server.h"
#include"enum.h"
using namespace std;

class receverPthread
{
public:
    receverPthread()
    {
        cout<<"this is cli.receverPthread"<<endl;
        pthread_t id;
        pthread_create(&id,NULL,run,NULL);
    }
    static void* run(void* arg)
    {
        cout<<"this is cli.receverPthread.run()"<<endl;
        while(1)
        {
            string str;
            if( 0 >= Client::getClient()->Recv(str) )
            {
                cerr<<"recv fail;errno:"<<errno<<endl;
                return NULL;
            }
            //Client::getClient()->Recv(str);
            //解析json  TYPE
            Json::Value root;
            Json::Reader read;
            if(-1 == read.parse(str,root))
            {
                cerr<<"json prase fail;errno:"<<errno<<endl;
                return NULL;
            }
            if(root["TYPE"] == SELECT && root["FD"] != -1)
            {
                //Server::getServer()->Send(fd,reason);
                if( -1 == Server::getServer()->Send( root["FD"].asInt(), str))
                {
                    cerr<<"send fail;errno:"<<errno<<endl;
                    return NULL;
                }
            }
            else
            {
                cout<<"reason:"<<root["reason"].asString()<<endl;
                cout<<"reason:"<<root["hahaha"].asString()<<endl;
            }
        }
    }
};

#endif


