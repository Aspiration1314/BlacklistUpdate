#ifndef _SELECTERPTHREAD_H_
#define _SELECTERPTHREAD_H_
#include<event.h>
#include<pthread.h>
#include"Server.h"
#include"Client.h"
#include"enum.h"
class selecterPthread
{
public:
    selecterPthread()
    {
        cout<<"this is cli.selecterPthread"<<endl;
        pthread_t id;
        _base = event_base_new();
        pthread_create(&id,NULL,run,_base);
    }
    static void* run(void* arg)
    {
        cout<<"this is cli.selecterPthread.run()"<<endl;
        struct event_base* base = (struct event_base*)arg;
        struct event* listen_event=event_new(base,Server::getServer()->getListenFd(),EV_READ|EV_PERSIST,listen_cb,base);
        event_add(listen_event,NULL);
        event_base_dispatch(base);
        //while(1){ epoll_wait() }
    }
    static void listen_cb(int fd,short event,void* arg)
    {
        cout<<"this is cli.listen_cb()"<<endl;
        struct event_base* base = (struct event_base*)arg;
        int cliFd = Server::getServer()->Accept();
        if(-1 == cliFd)
        {
            cerr<<"accept client fail;errno:"<<errno<<endl;
            return;
        }
        struct event* cli_event = event_new(base,cliFd,EV_READ|EV_PERSIST,cli_cb,NULL);
        event_add(cli_event,NULL);
    }
    static void cli_cb(int fd,short event,void* arg)
    {
        cout<<"this is cli.cli_cb()"<<endl;
        string id;
        if( 0 >= Server::getServer()->Recv(fd, id) )
        {
            cerr<<"recv fail;errno:"<<errno<<endl;
            return;
        }
        //Server::getServer()->Recv(fd,id);
        //json{TYPE:SELECT,ID:id,FD:fd};
        Json::Value root;
        Json::Reader read;
        if(-1 == read.parse(id,root))
        {
            cerr<<"json prase fail;errno:"<<errno<<endl;
            return;
        }
        Json::Value json;
        json["TYPE"] = SELECT;
        json["ID"] = root["reason"].asString();
        json["FD"] = fd;
        Client::getClient()->Send(json.toStyledString());
    }
private:
    event_base* _base;
};



#endif






