#ifndef _TCPSERVER_H_
#define _TCPSERVER_H_
#include<iostream>
#include<string.h>
#include<string>
#include<arpa/inet.h>
#include<errno.h>
#include<json/json.h>
#include<sys/socket.h>
#include<stdlib.h>
using namespace std;

class TcpServer
{
private:
    string _ip;
    unsigned short _port;
    int _listenFd;
public:
    //void TcpServer(string ip,unsigned short port)
    TcpServer(const string& ip,unsigned short port)//{bind()  listen();_listenFd;}
    {

        _ip = ip;
        _port = port;
        //创建服务器
        cout<<"enter ser.TcpServer()"<<endl;
        cout<<"ip:"<<ip.c_str()<<endl;
        _listenFd = socket(AF_INET,SOCK_STREAM,0);
        if(-1 == _listenFd)
        {
            cerr<<"_listenFd creat fail;errno:"<<endl;
            //return 0;
            exit(0);
        }

        struct sockaddr_in saddr;
        saddr.sin_family = AF_INET;
        saddr.sin_port = htons(port);
        saddr.sin_addr.s_addr = inet_addr(ip.c_str());

        cout<<"ser start to bind"<<endl;

        //绑定
        if(-1 == bind(_listenFd,(struct sockaddr*)&saddr,sizeof(saddr)))
        {
            cerr<<"_listenFd bind fail;errno:"<<errno<<endl;
            //return 0;
            exit(0);
        }

        cout<<"ser start to listen"<<endl;

        //监听
        if(- 1 == listen(_listenFd,20))
        {
            cerr<<"_listenFd listen fail;errno:"<<endl;
            //return 0;
            exit(0);
        }
    }
    int acceptClient()
    {
        cout<<"ser start to accept"<<endl;

        //连接客户端
        
        struct sockaddr_in caddr;
        socklen_t len = sizeof(caddr);
        int clifd = accept(_listenFd,(struct sockaddr*)&caddr,&len);
        if(-1 == clifd)
        {
            cerr<<"accept client fail;errno:"<<errno<<endl;
            return 0;
        }
        return clifd;
    }
    int sendToClient(int cliFd,const string& str)
    {
        cout<<"ser start to send"<<endl;
        return send(cliFd,str.c_str(),str.length(),0);
    }
    int recvFromClient(int cliFd,string& str)
    {
        cout<<"ser start to recv"<<endl;
        char buff[100]= {0};
        int n=recv(cliFd,buff,99,0);
        str = buff;
        //cout<<"str:"<<str<<endl;
        return n;
    }
    //int recvFromClient(int cliFd,string& str)
    //{
        //cout<<"ser start to recv"<<endl;
        //return recv(cliFd,const_cast<char*>(str.c_str()),str.length(),0);
    //}
    void closeClient(int cliFd)
    {
        close(cliFd);
    }
    int getListenFd()
    {
        return _listenFd;
    }
    string& getIp()
    {
        return _ip;
    }
    unsigned short getPort()
    {
        return _port;
    }
};


#endif