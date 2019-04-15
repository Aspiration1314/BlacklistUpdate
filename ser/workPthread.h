#ifndef _WORKPTHREAD_H_
#define _WORKPTHREAD_H_

#include<iostream>
#include<pthread.h>
#include"Control.h"
using namespace std;

class workPthread
{
public:
    workPthread()
    {
        pthread_t id;
        pthread_create(&id,NULL,run,NULL);
    }
    static void* run(void* arg)
    {
    	while(1)
    	{
        	//pair<int,string> data=shareQueue::getShareQueue()->pop();
        	//Control::getControl()->process(data.first(),data.second());
            //Control::getControl()->process(data);
        }
    }
};

#endif