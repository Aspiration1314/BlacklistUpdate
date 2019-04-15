#ifndef _SHAREQUEUE_H_
#define _SHAREQUEUE_H_
#include<iostream>
#include<queue>
#include<map>
using namespace std;
pthread_mutex_t pmut;
class shareQueue
{
public:
	//static shareQueue* getShareQueue()
	shareQueue* getShareQueue()
    {
        if(_queue.empty())
        {
            //pthread_mutex_t mut;

            //mut.lock();
            pthread_mutex_lock(&pmut);
            if(_queue.empty())
                new shareQueue();
            //mut.unlock();
            pthread_mutex_unlock(&pmut);
        }
        //return _queue;
    }
	void push(pair<int,string> data)
	{
		_queue.push(data);
	}
	pair<int,string> pop()
	{
		pair<int,string> data;
		//lock();
		pthread_mutex_lock(&mut);
		while(_queue.empty())
		{
			sleep(1);
		}
		//data = _queue.top();
		_queue.pop();
		pthread_mutex_unlock(&mut);
		//unlock();
		return data;
	}
private:
	//static queue< pair<int,string> > _queue;
	queue< pair<int,string> > _queue;

};

//queue<pair<int,string>> shareQueue::_queue = NULL;

#endif