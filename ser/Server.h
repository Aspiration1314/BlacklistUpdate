#ifndef _SERVER_H_
#define _SERVER_H_
#include<iostream>
#include<string.h>
#include<string>
#include<json/json.h>
#include<errno.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include"TcpServer.h"
//#include<mutex>
//using namespace std;

//mutex mut;
pthread_mutex_t mut;

class Server
{
public:
    static Server* getServer()
    {
        if(NULL == _server)
        {
            //pthread_mutex_t mut;

            //mut.lock();
            pthread_mutex_lock(&mut);
            if(NULL == _server)
                _server = new Server();
            //mut.unlock();
            pthread_mutex_unlock(&mut);
        }
        return _server;
    }
    int Accept()
    {
        cout<<"this is ser.Accept(),ser ready for accept()"<<endl;
        return _tcpServer->acceptClient();
    }
    int Send(int cliFd,const string& str)
    {
        cout<<"this is ser.send(),ser ready for send()"<<endl;
        return _tcpServer->sendToClient(cliFd,str);
    }
    int Recv(int cliFd,string& str)
    {
        cout<<"this is ser.Recv(),ser ready for recv()"<<endl;
        return _tcpServer->recvFromClient(cliFd,str);
    }
    int getListenFd()
    {
        return _tcpServer->getListenFd();
    }
    void Close(int cliFd)
    {
        _tcpServer->closeClient(cliFd);
    }
    int getFd()
    {
        _tcpServer->getListenFd();
    }
    string& getIp()
    {
        _tcpServer->getIp();
    }
    unsigned short getPort()
    {
        _tcpServer->getPort();
    }

private:
    //Server()
    //{
        //string ip;
        //unsigned short port;
        //cin>>ip;
        //cin>>port;
        //_tcpServer = new TcpServer(ip,port);
        //_tcpServer = new TcpServer("127.0.0.1",6000);
    //}
   //Server(string& ip,const unsigned short port)
    Server()
    {
        //string ip;
        //unsigned short port;
        //cout<<"input ip:";
        //cin>>ip;
        //cout<<"input port:";
        //cin>>port;
        //_tcpServer = new TcpServer(ip,port);
        _tcpServer = new TcpServer("127.0.0.1",6000);
        //_tcpClient* = new TcpClient(ip,port);
    }
    static Server* _server;
    TcpServer* _tcpServer;
};

Server* Server::_server = NULL;

#endif
