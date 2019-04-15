#ifndef _SYS_H_
#define _SYS_H_
#include<event.h>
#include<pthread.h>
#include<queue>
#include"Server.h"
#include"shareQueue.h"
#include"workPthread.h"
#include"Control.h"
class Sys
{
public:
    Sys()
    {
        //pthread_t id;
        cout<<"this is ser.sys()"<<endl;
        _base = event_base_new();
        //pthread_create(&id,NULL,run,_base);
    }
    void run()
    {
        cout<<"this is ser.sys.run()"<<endl;
        for(int i=0;i<3;i++)
            new workPthread();

        //struct event_base* base = (struct event_base*)_base;
        struct event* listen_event=event_new(_base,Server::getServer()->getListenFd(),EV_READ|EV_PERSIST,listen_cb,_base);
        event_add(listen_event,NULL);
        event_base_dispatch(_base);
    }
    //void run()
    //{
        //cout<<"this is ser.sys.run()"<<endl;
        //struct event* listen_event=event_new(_base,Server::getServer()->getListenFd(),EV_READ|EV_PERSIST,listen_cb,_base);
        //event_add(listen_event,NULL);
        //event_base_dispatch(_base);
    //}
   // static void* run(void* arg)
    //{
        //for(int i=0;i<3;i++)
            //new workPthread();

        //struct event_base* base = (struct event_base*)arg;
        //struct event* listen_event=event_new(base,Server::getServer()->getListenFd(),EV_READ|EV_PERSIST,listen_cb,base);
        //event_add(listen_event,NULL);
        //event_base_dispatch(base);
    //}
    static void listen_cb(int fd,short event,void* arg)
    {
        cout<<"this is ser.listen_cb,reday for turning to Accept()"<<endl;
        struct event_base* base = (struct event_base*)arg;
        int cliFd = Server::getServer()->Accept();
        if(-1 == cliFd)
        {
            cerr<<"accept client fail;errno:"<<errno<<endl;
            return;
        }
        cout<<"one client have been connected!("<<cliFd<<")"<<endl;
        //struct event* cli_event = event_new(base,cliFd,EV_READ|EV_PERSIST,cli_cb,NULL);
        struct event* cli_event = event_new(NULL,-1,0,NULL,NULL);
        if(NULL == cli_event)
        {
            cerr<<"cli_event creat fail;errno:"<<errno<<endl;
        }
        event_assign(cli_event,base,cliFd,EV_READ|EV_PERSIST,cli_cb,(void*)cli_event);
        event_add(cli_event,NULL);
    }
    static void cli_cb(int fd,short event,void* arg)
    {
        struct event* cli_base = (struct event*)arg;
        cout<<"this is ser.cli_cb,reday for turning to Recv()"<<endl;
        string str;
        //Server::getServer()->Recv(fd,id);
        if( 0 >= Server::getServer()->Recv(fd, str) )
        {
            //cerr<<"recv fail;errno:"<<errno<<endl;
            cout<<"一个客户端连接已关闭"<<endl;
            event_free(cli_base);
            Server::getServer()->Close(fd);
            return;
        }

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
        
        //shareQueue::getShareQueue()->push(make_pair(fd,id));
        Control::getControl()->process(fd,str);
    }
    
    
private:
    struct event_base* _base;
};


#endif