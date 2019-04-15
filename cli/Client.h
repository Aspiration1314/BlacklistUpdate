#ifndef _CLIENT_H_
#define _CLIENT_H_
#include<iostream>
#include<string.h>
#include<string>
#include<json/json.h>
#include<errno.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include"TcpClient.h"
//#include<mutex>
//using namespace std;

//mutex mut;
pthread_mutex_t smut;

class Client
{
public:
    static Client* getClient()
    {
        cout<<"this is cli.getClient()"<<endl;
        if(NULL == _client)
        {
            //mut.lock();
            pthread_mutex_lock(&smut);
            if(NULL == _client)
                _client = new Client();
            //mut.unlock();
            pthread_mutex_unlock(&smut);
        }
        return _client;
    }
    int Send(const string& str)
    {
        cout<<"cli ready for sending"<<endl;
        return _tcpClient->sendToServer(str);
    }
    int Recv(string& str)
    {
        cout<<"cli ready for recv"<<endl;
        return _tcpClient->recvFromServer(str);
    }
    void Close()
    {
        _tcpClient->closeClient();
    }
    int getFd()
    {
        _tcpClient->getFd();
    }
    string& getIp()
    {
        _tcpClient->getIp();
    }
    unsigned short getPort()
    {
        _tcpClient->getPort();
    }


private:
    //Client(string& ip,const unsigned short port)
    Client()
    {
        cout<<"this is cli.Client()"<<endl;
        //string ip;
        //unsigned short port;
        //cout<<"input ip:";
        //cin>>ip;
        //cout<<"input port:";
        //cin>>port;
        //_tcpClient = new TcpClient(ip,port);
        _tcpClient = new TcpClient("127.0.0.1",6000);
        //_tcpClient* = new TcpClient(ip,port);
    }
    //Client()
    //{
        //string ip;
        //unsigned short port;
        //cin>>ip;
        //cin>>port;
        //_tcpClient = new TcpClient("127.0.0.1",6000);
    //}
    static Client* _client;
    TcpClient* _tcpClient;
};

Client* Client::_client = NULL;

#endif
