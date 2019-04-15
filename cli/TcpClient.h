#ifndef _TCPCLIENT_H_
#define _TCPCLIENT_H_
#include<iostream>
#include<string.h>
#include<string>
#include<json/json.h>
#include<errno.h>
#include<arpa/inet.h>
#include<stdlib.h>
using namespace std;

class TcpClient
{
private:
    string _ip;
    unsigned short _port;
    int _fd;
public:
    //TcpClient(string ip,unsigned short port)//{ connect()->_fd; }
    TcpClient(const string& ip,const unsigned short port)
    {
        cout<<"this is cli.TcpClient()"<<endl;
        _ip = ip;
        _port = port;

        _fd = socket(AF_INET,SOCK_STREAM,0);
        if(-1 == _fd)
        {
            cerr<<"clifd creat fail;errno:"<<errno<<endl;
            //return 0;
            exit(0);
        }

        struct sockaddr_in saddr;
        saddr.sin_family = AF_INET;
        //saddr.sin_port = htons(5000);
        //saddr.sin_addr.s_addr = inet_addr("127.0.0.1");
        saddr.sin_port = htons(port);
        saddr.sin_addr.s_addr = inet_addr(ip.c_str());

         cout<<"cli start to connect"<<endl;

        if(-1 == connect(_fd,(struct sockaddr*)&saddr,sizeof(saddr)))
        {
            cerr<<"clifd connect fail;errno:"<<errno<<endl;
            exit(0);
            //return 0;
        }
    }
    int sendToServer(const string& str)
    {
        cout<<"cli start to send"<<endl;
        return send(_fd,str.c_str(),str.length(),0);
    }
    int recvFromServer(string& str)
    {
        cout<<"cli start to recv"<<endl;
        char buff[100]= {0};
        int n=recv(_fd,buff,99,0);
        str = buff;
        return n;
    }
    //int recvFromServer(const string& str)
    //{
        //cout<<"cli start to recv"<<endl;
        //const char* buff = str.c_str();
        //const_cast<char*>
        //return recv(_fd,str,99,0);
        //return recv(_fd,const_cast<char*>(str.c_str()),str.length(),0);
        //return recv(_fd,str.c_str(),str.length(),0);
    //}
    void closeClient()
    {
        close (_fd);
    }
    int getFd()
    {
        return _fd;
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